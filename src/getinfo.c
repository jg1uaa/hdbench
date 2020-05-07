/***************************************************************************/
/*                                                                         */
/* HDBENCH clone - a graphical benchmark software                          */
/* Copyright (C) 1999 Yuuki NINOMIYA, gm@smn.enjoy.ne.jp                   */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by    */
/* the Free Software Foundation; either version 2, or (at your option)     */
/* any later version.                                                      */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/* GNU General Public License for more details.                            */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the                           */
/* Free Software Foundation, Inc., 59 Temple Place - Suite 330,            */
/* Boston, MA 02111-1307, USA.                                             */
/*                                                                         */
/***************************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "intl.h"
#include "proto.h"
#include "variable.h"


gint get_meminfo(gint32 *totalmem,gint32 *freemem)
{
	FILE *fp;
	gchar *buf;

#ifdef INFO_PROC		/* by proc filesystem */
	gint32 buffers,cached;

	if((fp=fopen("/proc/meminfo","r"))==NULL){
		fprintf(stderr,_("Cannot open `/proc/meminfo'.\n"));
		return(FALSE);
	}
	str_skip_fgets(fp);
	buf=str_fgets(fp);
	sscanf(buf,"%*s %d %*d %d %*d %d %d",totalmem,freemem,&buffers,&cached);
	g_free(buf);
	fclose(fp);

	*freemem+=(buffers+cached);

	return(TRUE);
#endif

#ifdef INFO_SYSCTL	/* by sysctl command */
	if((fp=popen("/sbin/sysctl hw.physmem hw.usermem","r"))==NULL){
		fprintf(stderr,_("Cannot create a pipe.\n"));
		return(FALSE);
	}
	buf=str_fgets(fp);
	sscanf(buf,"%*s %d",totalmem);
	g_free(buf);

	buf=str_fgets(fp);
	sscanf(buf,"%*s %d",freemem);
	g_free(buf);
	if(feof(fp)){
		fprintf(stderr,_("Cannot execute `/sbin/sysctl'.\n"));
		return(FALSE);
	}
	pclose(fp);

	return(TRUE);
#endif	

	return(FALSE);
}


void get_cpuinfo(gchar **name,gchar **vendor,gchar **family,gchar **model,gchar **stepping)
{
	FILE *fp;
	gchar *model_name,*clock;
	gchar *buf;

#ifdef INFO_SYSCTL	/* by sysctl command */
	gint processor;
	gchar *clock_temp;
	gint i;
#endif

#ifdef INFO_PROC	/* by proc filesystem */
	gchar *item=NULL,*val=NULL,*processor;
	gchar *ptr;

	*vendor=g_strdup("unknown");
	*family=g_strdup("unknown");
	*model=g_strdup("unknown");
	*stepping=g_strdup("unknown");
	model_name=g_strdup("unknown");
	clock=g_strdup("unknown");
	processor=g_strdup("0");

	if((fp=fopen("/proc/cpuinfo","r"))==NULL){
		g_error(_("Cannot open `/proc/cpuinfo'.\n"));
	}

	for(;;){
		buf=str_fgets(fp);
		if(buf==NULL){
			break;
		}
		if(buf[0]=='\0'){
			g_free(buf);
			continue;
		}

		ptr=strchr(buf,'\t');
		if(ptr==NULL){
			g_free(buf);
			continue;
		}
		*ptr='\0';
		item=g_strdup(buf);

		val=g_strdup(strchr(ptr+1,':')+2);

		if(strcmp(item,"model")==0){
			g_free(*model);
			*model=g_strdup(val);
		}
		if(strcmp(item,"model name")==0){
			g_free(model_name);
			model_name=g_strdup(val);
		}
		if(strcmp(item,"cpu MHz")==0){
			g_free(clock);
			clock=g_strdup(val);
		}
		if(strcmp(item,"vendor_id")==0){
			g_free(*vendor);
			*vendor=g_strdup(val);
		}
		if(strcmp(item,"cpu family")==0){
			g_free(*family);
			*family=g_strdup(val);
		}
		if(strcmp(item,"stepping")==0){
			g_free(*stepping);
			*stepping=g_strdup(val);
		}
		if(strcmp(item,"processor")==0){
			g_free(processor);
			processor=g_strdup(val);
		}
		g_free(buf);
	}
	fclose(fp);

	if(strcmp(model_name,"unknown")==0){
		gchar *swap_temp;

		swap_temp=model_name;
		model_name=*model;
		*model=swap_temp;
	}

	if(processor[0]=='0'){
		*name=g_strdup_printf("%s [%s MHz]",model_name,clock);
	}else{
		*name=g_strdup_printf("%s [%s MHz] %d processors",model_name,clock,atoi(processor)+1);
	}

	g_free(model_name);
	g_free(processor);
	g_free(clock);
	g_free(item);
	g_free(val);

	return;
#endif

#ifdef INFO_SYSCTL	/* by sysctl command */
	if((fp=popen("/sbin/sysctl hw.model machdep.tsc_freq hw.ncpu","r"))==NULL){
		g_error(_("Cannot create a pipe.\n"));
	}
	buf=str_fgets(fp);
	if(buf==NULL){
		g_error(_("Cannot execute `/sbin/sysctl'.\n"));
	}
	model_name=g_strdup(buf+10);
	g_free(buf);

	buf=str_fgets(fp);
	sscanf(buf,"%*s %s",clock_temp);
	g_free(buf);

	buf=str_fgets(fp);
	sscanf(buf,"%*s %d",&processor);
	g_free(buf);
	pclose(fp);

	for(i=strlen(clock_temp);i>strlen(clock_temp)-6;i--){
		clock[i]=clock_temp[i-1];
	}
	clock[i]='.';
	for(i=strlen(clock_temp)-7;i>=0;i--){
		clock[i]=clock_temp[i];
	}
	clock[strlen(clock_temp)+1]='\0';

	if(processor==1){
		*name=g_strdup_printf("%s [%s MHz]",model_name,clock);
	}else{
		*name=g_strdup_printf("%s [%s MHz] %d processors",model_name,clock,processor);
	}

	*vendor=g_strdup("unknown");
	*family=g_strdup("unknown");
	*model=g_strdup("unknown");
	*stepping=g_strdup("unknown");

	return;
#endif	
	g_error(_("Cannot get cpu infomation.\n"));
}


void get_osinfo(gchar **name)
{
	FILE *fp;

	if((fp=popen("uname -s -r","r"))==NULL){
		g_error(_("Cannot create a pipe.\n"));
	}
	*name=str_fgets(fp);
	if(*name==NULL){
		g_error(_("Cannot execute `uname'.\n"));
	}
	pclose(fp);
}


gchar *get_display_name(void)
{
	FILE *fp;
	gchar *temp;

	fp=popen("grep BoardName /etc/X11/XF86Config","r");
	if(fp==NULL){
		g_error(_("Cannot create a pipe.\n"));
	}
	temp=parse_display_name(fp);

	if(strcmp(temp,"unknown")==0){
		fp=popen("grep BoardName /etc/XF86Config","r");
		if(fp==NULL){
			g_error(_("Cannot create a pipe.\n"));
		}
		temp=parse_display_name(fp);

		if(strcmp(temp,"unknown")==0){
			g_warning(_("Cannot execute `grep' or open `XF86Config'.\n"));
		}
	}

	return(temp);
}


gchar *parse_display_name(FILE *fp)
{
	gchar *temp,*ret;
	gint i,j;

	while((temp=str_fgets(fp))!=NULL){
		for(i=0;i<strlen(temp);i++){
			if(temp[i]=='#' || temp[i]=='\0'){
				break;
			}
			if(temp[i]=='\"'){
				for(j=i+1;j<strlen(temp);j++){
					if(temp[j]=='\0'){	//閉じの'\"'がない
						pclose(fp);
						g_free(temp);
						return(g_strdup("unknown"));
					}
					if(temp[j]=='\"'){
						temp[j]='\0';
						pclose(fp);
						ret=g_strdup(temp+i+1);
						g_free(temp);
						return(ret);
					}
				}
			}
		}
		g_free(temp);
	}
	pclose(fp);
	return(g_strdup("unknown"));
}


guint32 lpow(gint x,gint y)
{
	gint i;
	gint32 ret;

	if(x==2 && y==32){
		return(0x00ffffff);
	}
	ret=x;
	for(i=1;i<y;i++){
		ret*=x;
	}
	return(ret);
}


gchar *get_drive_data(void)
{
	gint i;
	gchar *temp;
	gchar *ret;
	FILE *fp;
	gchar *cmd;
	gchar *buf;

	gchar *grep[]={
		"^ide:",
		"^scsi0 :",
		"^scsi1 :",
		"^scsi2 :",
		"^scsi3 :",
		"^hda:",
		"^hdb:",
		"^hdc:",
		"^hdd:",
		"^da0:",
		"^da1:",
		"^da2:",
		"^da3:",
		"^SCSI device sda:",
		"^SCSI device sdb:",
		"^SCSI device sdc:",
		"^SCSI device sdd:",
		"^sr0:",
		"^sr1:",
		"^sr2:",
		"^sr3:",	/* 21 */
	};


	ret=g_strdup("");

	for(i=0;i<21;i++){
		cmd=g_strdup_printf("dmesg | grep '%s' | tac",grep[i]);
		fp=popen(cmd,"r");
		g_free(cmd);
		if(fp==NULL){
			g_error(_("Cannot create a pipe.\n"));
		}
		for(;;){
			if((buf=str_fgets(fp))==NULL){
				break;
			}
			if(strstr(buf,"media changed")==NULL){
				temp=g_strconcat(ret,buf,"\n",NULL);
				g_free(ret);
				g_free(buf);
				ret=temp;
				break;
			}
			g_free(buf);
		}
		pclose(fp);
	}

	fp=popen("df","r");
	if(fp==NULL){
		g_error(_("Cannot create a pipe.\n"));
	}
	buf=str_fgets(fp);
	if(buf==NULL){
		g_warning(_("Cannot execute `df'.\n"));
		return(ret);
	}

	if(strncmp(buf,"Filesystem",10)==0){	/* for Vine */
		temp=g_strconcat(ret,"\n",buf,"\n",NULL);
	}else{
		temp=g_strconcat(ret,"\nFilesystem         1024-blocks  Used Available Capacity Mounted on\n",NULL);
	}
	g_free(ret);
	g_free(buf);
	ret=temp;

	while((buf=str_fgets(fp))!=NULL){
		temp=g_strconcat(ret,buf,"\n",NULL);
		g_free(ret);
		g_free(buf);
		ret=temp;
	}
	return(ret);
}


/* --------------------------------------------------
 NAME       str_fgets
 FUNCTION   fgets with dynamic allocated memory
 INPUT      fp ... file pointer
 OUTPUT     pointer to got strings
-------------------------------------------------- */
char *str_fgets(FILE *fp)
{
	char *ptr;
	char temp[128];
	int i;

	ptr=g_malloc(1);
	*ptr='\0';
	for(i=0;;i++){
		if(fgets(temp,128,fp)==NULL){
			g_free(ptr);
			return(NULL);
		}
		ptr=g_realloc(ptr,127*(i+1)+1);
		strcat(ptr,temp);
		if(strchr(temp,'\n')!=NULL){
			*strchr(ptr,'\n')='\0';
			return(ptr);
		}
	}
}


/* --------------------------------------------------
 NAME       str_skip_fgets
 FUNCTION   skip a single line
 INPUT      fp ... file pointer
 OUTPUT     return 0 if successful, otherwise -1
-------------------------------------------------- */
int str_skip_fgets(FILE *fp)
{
	char temp[128];
	for(;;){
		if(fgets(temp,128,fp)==NULL){
			return(-1);
		}
		if(strchr(temp,'\n')!=NULL){
			return(0);
		}
	}
}





