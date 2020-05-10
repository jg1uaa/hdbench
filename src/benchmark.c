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
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#else
#include <wait.h>
#endif
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include "intl.h"
#include "proto.h"
#include "variable.h"


#define calc_all() ((result_integer+result_float+result_memory+result_rectangle+result_circle+result_text+result_scroll+result_read+result_write)/10)

gint default_rgb_palette_color[8][3]={
	{0x0000,0x0000,0x0000},
	{0x0000,0x0000,0xffff},
	{0xffff,0x0000,0x0000},
	{0xffff,0x0000,0xffff},
	{0x0000,0xffff,0x0000},
	{0x0000,0xffff,0xffff},
	{0xffff,0xffff,0x0000},
	{0xffff,0xffff,0xffff}
};


void benchmark_cpu(void)
{
	gint pipe_fd[2];


	if(pipe(pipe_fd)==-1){
		g_error(_("Cannot create a pipe.\n"));
	}
	io_check_tag=gdk_input_add(pipe_fd[0],GDK_INPUT_READ,bench_cpu_update,NULL);

	switch(fork()){
		case -1:
			g_error(_("Cannot fork.\n"));

		case 0:
			close(pipe_fd[0]);

			bench_cpu_and_write(pipe_fd[1]);
			close(pipe_fd[1]);

			_exit(0);

		default:
			close(pipe_fd[1]);
			gtk_widget_hide(bench_func_cpu);
			gtk_widget_show(measuring_cpu);

			set_sensitive(FALSE);
	}

}


void bench_cpu_and_write(gint write_fd)
{
	gchar *src,*dest;
	struct CPU_Result result;


	sleep(1);

/* integer */
	set_sigalarm(3);
	result.integer=bench_integer();

/* float */
	set_sigalarm(3);
	result.floatp=bench_float();

/* memory */
	src=g_malloc(1024L*1024L*2L);   /* each 2MB */
	dest=g_malloc(1024L*1024L*2L);
	set_sigalarm(3);
	result.memory=bench_memory(src,dest);
	g_free(dest);
	g_free(src);

/* writing results to pipe */
	write(write_fd,&result,sizeof(result));
}


void bench_cpu_update(gpointer userdata,gint read_fd,GdkInputCondition condition)
{
	gchar *temp;
	struct CPU_Result result;


	gdk_input_remove(io_check_tag);
	read(read_fd,&result,sizeof(result));
	close(read_fd);
	wait(NULL);

	set_sensitive(TRUE);
	gtk_widget_hide(measuring_cpu);
	gtk_widget_show(bench_func_cpu);

	result_integer=result.integer;
	result_float=result.floatp;
	result_memory=result.memory;
	result_all=calc_all();

	temp=g_strdup_printf("%d",result_integer);
	gtk_label_set(GTK_LABEL(bench_integer_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_float);
	gtk_label_set(GTK_LABEL(bench_float_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_memory);
	gtk_label_set(GTK_LABEL(bench_memory_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_all);
	gtk_label_set(GTK_LABEL(bench_total_score),temp);
	g_free(temp);
}


void benchmark_video(void)
{
	gint pipe_fd[2];


	if(pipe(pipe_fd)==-1){
		g_error(_("Cannot create a pipe.\n"));
	}
	io_check_tag=gdk_input_add(pipe_fd[0],GDK_INPUT_READ,bench_video_update,NULL);

	switch(fork()){
		case -1:
			g_error(_("Cannot fork.\n"));

		case 0:
			close(pipe_fd[0]);

			bench_video_and_write(pipe_fd[1]);
			close(pipe_fd[1]);

			_exit(0);

		default:
			close(pipe_fd[1]);
			gtk_widget_hide(bench_func_video);
			gtk_widget_show(measuring_video);

			set_sensitive(FALSE);
	}
}


void bench_video_and_write(gint write_fd)
{
	struct Video_Result result;
	Display *d;
	Window w;
	GC gc;
	guint32 palette[8];
	gint width,height;
	gint bpp;
	XImage *image;
	gpointer buffer;


	initx(&d,&w,&gc,palette,&width,&height);
	sleep(1);

/* rectangle */
	set_sigalarm(3);
	result.rectangle=bench_rectangle(d,w,gc,palette);

/* circle */
	XClearWindow(d,w);
	set_sigalarm(3);
	result.circle=bench_circle(d,w,gc,palette);

/* text */
	XClearWindow(d,w);
	XSetBackground(d,gc,palette[7]);

	set_sigalarm(3);
	result.text=bench_text(d,w,gc,palette,width,height);

/* scroll */
	XClearWindow(d,w);
	set_sigalarm(3);
	result.scroll=bench_scroll(d,w,gc,palette);

/* image */
	XClearWindow(d,w);

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(opt_image))){
		bpp=DefaultDepth(d,DefaultScreen(d));
		switch(bpp){
			default:
				g_warning(_("Unsupported color depth."));
				result.image=0;
				break;
			case 24:
				bpp=32;
				/*FALLTHROUGH*/
			case 8:
			case 16:
			case 32:
				buffer=calloc(VIDEO_WIN_X*VIDEO_WIN_Y,bpp/8);
				image=XCreateImage(d,DefaultVisual(d,DefaultScreen(d)),DefaultDepth(d,DefaultScreen(d)),ZPixmap,0,buffer,VIDEO_WIN_X,VIDEO_WIN_Y,bpp,0);

				set_sigalarm(5);
				result.image=bench_image(d,w,gc,image,bpp,buffer)/5;

				free(buffer);
				break;
		}
	}

	XDestroyWindow(d,w);
	XCloseDisplay(d);


/* writing results to pipe */
	write(write_fd,&result,sizeof(result));
}


gint32 bench_rectangle(Display *d,Window w,GC gc,guint32 *palette)
{
	gint32 i;
	gint j,x,y;

	for(i=0;;i++){
		for(j=0;j<3;j++){
			x=(rand() % 590);
			y=(rand() % 430);
			XSetForeground(d,gc,palette[(i%7)+1]);
			XFillRectangle(d,w,gc,x,y,50,50);
			XSetForeground(d,gc,palette[0]);
			XDrawRectangle(d,w,gc,x,y,50,50);
			XFlush(d);
		}
		if(done_flag==1){
			return(i);
		}
	}
}


gint32 bench_circle(Display *d,Window w,GC gc,guint32 *palette)
{
	gint32 i;
	gint j,x,y;

	for(i=0;;i++){
		for(j=0;j<3;j++){
			x=(rand() % 590);
			y=(rand() % 430);
			XSetForeground(d,gc,palette[(i%7)+1]);
			XFillArc(d,w,gc,x,y,50,50,0,23040);
			XSetForeground(d,gc,palette[0]);
			XDrawArc(d,w,gc,x,y,50,50,0,23040);
			XFlush(d);
		}
		if(done_flag==1){
			return(i);
		}
	}
}


gint32 bench_text(Display *d,Window w,GC gc,guint32 *palette,gint width,gint height)
{
	gint32 i;
	gint j,x,y;

	for(i=0;;i++){
		for(j=0;j<3;j++){
			x=(rand() % (VIDEO_WIN_X-width));
			y=(rand() % (VIDEO_WIN_Y+height));
			XSetForeground(d,gc,palette[(i%7)+1]);
			XDrawImageString(d,w,gc,x,y,video_text,strlen(video_text));
			XFlush(d);
		}
		if(done_flag==1){
			return(i);
		}
	}
}


gint32 bench_scroll(Display *d,Window w,GC gc,guint32 *palette)
{
	gint32 i;
	gint j;

	for(i=0;;i++){
		for(j=0;j<50;j++){
			XCopyArea(d,w,w,gc,0,0,VIDEO_WIN_X,VIDEO_WIN_Y,0,1);
			XSetForeground(d,gc,palette[(i%7)+1]);
			XDrawRectangle(d,w,gc,0,0,VIDEO_WIN_X,1);
			XFlush(d);
		}
		if(done_flag==1){
			XSync(d,False);
			return(i);
		}
	}
}


static void sprite_renderer_8(gpointer buffer,gint x,gint y,gint color)
{
	gint j,k;
	guint8 *p=(guint8*)buffer;

	for(j=0;j<SPRITE_SIZE;j++){
		for(k=0;k<SPRITE_SIZE;k++){
			*(p+(x+k)+(y+j)*VIDEO_WIN_X)=color;
		}
	}
}


static void sprite_renderer_16(gpointer buffer,gint x,gint y,gint color)
{
	gint j,k;
	guint16 *p=(guint16*)buffer;

	for(j=0;j<SPRITE_SIZE;j++){
		for(k=0;k<SPRITE_SIZE;k++){
			*(p+(x+k)+(y+j)*VIDEO_WIN_X)=color;
		}
	}
}


static void sprite_renderer_32(gpointer buffer,gint x,gint y,gint color)
{
	gint j,k;
	guint32 c=((color&0xf800)<<8)|((color&0x07e0)<<5)|((color&0x001f)<<3);
	guint32 *p=(guint32*)buffer;

	for(j=0;j<SPRITE_SIZE;j++){
		for(k=0;k<SPRITE_SIZE;k++){
			*(p+(x+k)+(y+j)*VIDEO_WIN_X)=c;
		}
	}
}


gint32 bench_image(Display *d,Window w,GC gc,XImage *image,gint bpp,gpointer buffer)
{
	gint i,l;
	gint x[SPRITES],y[SPRITES];
	gint color[SPRITES];
	gint x_vel[SPRITES],y_vel[SPRITES];
	void (*renderer)(gpointer,gint,gint,gint);


	switch(bpp){
		case 8:
			renderer=sprite_renderer_8;
			break;
		case 16:
			renderer=sprite_renderer_16;
			break;
		default:
			bpp=32;
			renderer=sprite_renderer_32;
			break;
	}

	for(i=0;i<SPRITES;i++){
		x[i]=rand() % (VIDEO_WIN_X-(SPRITE_SIZE+SPRITE_BORDER));
		y[i]=rand() % (VIDEO_WIN_Y-(SPRITE_SIZE+SPRITE_BORDER));
		color[i]=(rand() % 65536);
		x_vel[i]=((rand() % 4)+1)*((rand() % 2)*2-1);
		y_vel[i]=((rand() % 4)+1)*((rand() % 2)*2-1);
	}

	for(i=0;;i++){
		memset(buffer,0,VIDEO_WIN_X*VIDEO_WIN_Y*(bpp/8));
		for(l=0;l<SPRITES;l++){
			x[l]+=x_vel[l];
			y[l]+=y_vel[l];
			if(x[l]>VIDEO_WIN_X-(SPRITE_SIZE+SPRITE_BORDER) || x[l]<0){
				x_vel[l]=-x_vel[l];
				x[l]+=x_vel[l];
			}
			if(y[l]>VIDEO_WIN_Y-(SPRITE_SIZE+SPRITE_BORDER) || y[l]<0){
				y_vel[l]=-y_vel[l];
				y[l]+=y_vel[l];
			}

			(*renderer)(buffer,x[l],y[l],color[l]);
		}
		XPutImage(d,w,gc,image,0,0,0,0,VIDEO_WIN_X,VIDEO_WIN_Y);

		if(done_flag==1){
			return(i);
		}
	}
}


void bench_video_update(gpointer userdata,gint read_fd,GdkInputCondition condition)
{
	gchar *temp;
	struct Video_Result result;


	gdk_input_remove(io_check_tag);
	read(read_fd,&result,sizeof(result));
	close(read_fd);
	wait(NULL);

	set_sensitive(TRUE);
	gtk_widget_hide(measuring_video);
	gtk_widget_show(bench_func_video);

	result_rectangle=result.rectangle;
	result_circle=result.circle;
	result_text=result.text;
	result_scroll=result.scroll;
	result_image=result.image;
	result_all=calc_all();

	temp=g_strdup_printf("%d",result_rectangle);
	gtk_label_set(GTK_LABEL(bench_rectangle_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_circle);
	gtk_label_set(GTK_LABEL(bench_circle_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_text);
	gtk_label_set(GTK_LABEL(bench_text_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_scroll);
	gtk_label_set(GTK_LABEL(bench_scroll_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_image);
	gtk_label_set(GTK_LABEL(bench_image_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_all);
	gtk_label_set(GTK_LABEL(bench_total_score),temp);
	g_free(temp);
}


void benchmark_disk(void)
{
	gint pipe_fd[2];


	if(pipe(pipe_fd)==-1){
		g_error(_("Cannot create a pipe.\n"));
	}
	io_check_tag=gdk_input_add(pipe_fd[0],GDK_INPUT_READ,bench_disk_update,NULL);

	switch(fork()){
		case -1:
			g_error(_("Cannot fork.\n"));

		case 0:
			close(pipe_fd[0]);

			bench_disk_and_write(pipe_fd[1]);
			close(pipe_fd[1]);

			_exit(0);

		default:
			close(pipe_fd[1]);
			gtk_widget_hide(bench_func_disk);
			gtk_widget_show(measuring_disk);

			set_sensitive(FALSE);
	}
}


void bench_disk_and_write(gint write_fd)
{
	gchar *buf;
	gchar *temp1,*temp2;
	struct Disk_Result result;


	buf=g_malloc(1024L*1024L);
	temp1=g_strdup_printf("%s/hdbench1.%d",disk_drive,getppid());
	temp2=g_strdup_printf("%s/hdbench2.%d",disk_drive,getppid());
	sleep(1);

/* write */
	result.write=bench_write(buf,temp1);
	sleep(3);

/* cache flush */
	bench_cache_flash(buf,temp2);
	sleep(3);

/* read */
	result.read=bench_read(buf,temp1);
	remove(temp1);
	remove(temp2);
	g_free(buf);
	g_free(temp1);
	g_free(temp2);

/* writing results to pipe */
	write(write_fd,&result,sizeof(result));
}


gint32 bench_write(gchar *buf,gchar *temp)
{
	struct timeval start,now;
	gint32 sec,usec;
	gint fd;
	gchar *err_mes_temp;
	gint i;


	if((fd=open(temp,O_CREAT | O_TRUNC | O_RDWR,S_IRWXU))==-1){
		kill(getppid(),SIGTERM);
		err_mes_temp=g_strdup_printf(_("Cannot create temporary file `%s'.\n"),temp);
		g_error(err_mes_temp);
	}

	gettimeofday(&start,NULL);

	for(i=0;i<disk_capacity*2;i++){
		if(write(fd,buf,512L*1024L)<512L*1024L){
			kill(getppid(),SIGTERM);
			remove(temp);
			err_mes_temp=g_strdup_printf(_("Writing temporary file `%s' failed.\n"),temp);
			g_error(err_mes_temp);
		}
	}
	fsync(fd);

	gettimeofday(&now,NULL);

	if(start.tv_usec<now.tv_usec){
		sec=now.tv_sec-start.tv_sec;
		usec=now.tv_usec-start.tv_usec;
	}else{
		sec=now.tv_sec-start.tv_sec-1;
		usec=1000000+now.tv_usec-start.tv_usec;
	}
	close(fd);

	return(512L*1024L*disk_capacity*2L)/((sec*1000000L+usec)/1000L);
}


void bench_cache_flash(gchar *buf,gchar *temp)
{
	gint fd;
	gchar *err_mes_temp;
	gint i;
	gint64 totalmem,freemem;

	if((fd=open(temp,O_CREAT | O_TRUNC | O_RDWR,S_IRWXU))==-1){
		kill(getppid(),SIGTERM);
		err_mes_temp=g_strdup_printf(_("Cannot create temporary file `%s'.\n"),temp);
		g_error(err_mes_temp);
	}
	if(!get_meminfo(&totalmem,&freemem)){
		g_error(_("Cannot get memory infomation.\n"));
	}

	for(i=0;i<totalmem/1024L/1024L;i++){
		if(write(fd,buf,1024L*1024L)<1024L*1024L){
			kill(getppid(),SIGTERM);
			remove(temp);
			err_mes_temp=g_strdup_printf(_("Writing temporary file `%s' failed.\n"),temp);
			g_error(err_mes_temp);
		}
	}
	fsync(fd);
	close(fd);
}


gint32 bench_read(gchar *buf,gchar *temp)
{
	struct timeval start,now;
	gint32 sec,usec;
	gint fd;
	gchar *err_mes_temp;
	gint i;


	if((fd=open(temp,O_RDONLY))==-1){
		kill(getppid(),SIGTERM);
		err_mes_temp=g_strdup_printf(_("Cannot create temporary file `%s'.\n"),temp);
		g_error(err_mes_temp);
	}

	gettimeofday(&start,NULL);

	for(i=0;i<disk_capacity*2;i++){
		if(read(fd,buf,512L*1024L)<512L*1024L){
			kill(getppid(),SIGTERM);
			remove(temp);
			err_mes_temp=g_strdup_printf(_("Reading temporary file `%s' failed.\n"),temp);
			g_error(err_mes_temp);
		}
	}
	fsync(fd);

	gettimeofday(&now,NULL);

	if(start.tv_usec<now.tv_usec){
		sec=now.tv_sec-start.tv_sec;
		usec=now.tv_usec-start.tv_usec;
	}else{
		sec=now.tv_sec-start.tv_sec-1;
		usec=1000000+now.tv_usec-start.tv_usec;
	}
	close(fd);

	return(512L*1024L*disk_capacity*2L)/((sec*1000000L+usec)/1000L);
}


void bench_disk_update(gpointer userdata,gint read_fd,GdkInputCondition condition)
{
	gchar *temp;
	struct Disk_Result result;


	gdk_input_remove(io_check_tag);
	read(read_fd,&result,sizeof(result));
	close(read_fd);
	wait(NULL);

	set_sensitive(TRUE);
	gtk_widget_hide(measuring_disk);
	gtk_widget_show(bench_func_disk);

	result_read=result.read;
	result_write=result.write;
	result_all=calc_all();

	temp=g_strdup_printf("%d",result_read);
	gtk_label_set(GTK_LABEL(bench_read_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_write);
	gtk_label_set(GTK_LABEL(bench_write_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_all);
	gtk_label_set(GTK_LABEL(bench_total_score),temp);
	g_free(temp);
}


void benchmark_all(void)
{
	gint pipe_fd[2];


	if(pipe(pipe_fd)==-1){
		g_error(_("Cannot create a pipe.\n"));
	}
	io_check_tag=gdk_input_add(pipe_fd[0],GDK_INPUT_READ,bench_all_update,NULL);

	switch(fork()){
		case -1:
			g_error(_("Cannot fork.\n"));

		case 0:
			close(pipe_fd[0]);

			bench_cpu_and_write(pipe_fd[1]);
			bench_video_and_write(pipe_fd[1]);
			bench_disk_and_write(pipe_fd[1]);
			close(pipe_fd[1]);

			_exit(0);

		default:
			close(pipe_fd[1]);
			gtk_widget_hide(bench_func_all);
			gtk_widget_show(measuring_all);

			set_sensitive(FALSE);
	}
}


void bench_all_update(gpointer userdata,gint read_fd,GdkInputCondition condition)
{
	gchar *temp;
	struct CPU_Result cpu_result;
	struct Video_Result video_result;
	struct Disk_Result disk_result;


	read(read_fd,&cpu_result,sizeof(cpu_result));

	result_integer=cpu_result.integer;
	result_float=cpu_result.floatp;
	result_memory=cpu_result.memory;

	temp=g_strdup_printf("%d",result_integer);
	gtk_label_set(GTK_LABEL(bench_integer_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_float);
	gtk_label_set(GTK_LABEL(bench_float_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_memory);
	gtk_label_set(GTK_LABEL(bench_memory_score),temp);
	g_free(temp);

	while (gtk_events_pending()){
		gtk_main_iteration();
	}

	read(read_fd,&video_result,sizeof(video_result));

	result_rectangle=video_result.rectangle;
	result_circle=video_result.circle;
	result_text=video_result.text;
	result_scroll=video_result.scroll;
	result_image=video_result.image;

	temp=g_strdup_printf("%d",result_rectangle);
	gtk_label_set(GTK_LABEL(bench_rectangle_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_circle);
	gtk_label_set(GTK_LABEL(bench_circle_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_text);
	gtk_label_set(GTK_LABEL(bench_text_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_scroll);
	gtk_label_set(GTK_LABEL(bench_scroll_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_image);
	gtk_label_set(GTK_LABEL(bench_image_score),temp);
	g_free(temp);

	while (gtk_events_pending()){
		gtk_main_iteration();
	}

	read(read_fd,&disk_result,sizeof(disk_result));

	result_read=disk_result.read;
	result_write=disk_result.write;

	temp=g_strdup_printf("%d",result_read);
	gtk_label_set(GTK_LABEL(bench_read_score),temp);
	g_free(temp);

	temp=g_strdup_printf("%d",result_write);
	gtk_label_set(GTK_LABEL(bench_write_score),temp);
	g_free(temp);


	result_all=calc_all();

	temp=g_strdup_printf("%d",result_all);
	gtk_label_set(GTK_LABEL(bench_total_score),temp);
	g_free(temp);


	gdk_input_remove(io_check_tag);
	close(read_fd);
	wait(NULL);

	set_sensitive(TRUE);
	gtk_widget_hide(measuring_all);
	gtk_widget_show(bench_func_all);
}


void initx(Display **d,Window *w,GC *gc,guint32 *palette,gint *width,gint *height)
{
	XColor xcolor;
	Colormap color_map;
	XFontStruct *xfs;
	gint i;
	gchar *err_mes_temp;


	*d=XOpenDisplay(NULL);
	*w=XCreateSimpleWindow(*d,RootWindow(*d,0),0,0,VIDEO_WIN_X,VIDEO_WIN_Y,1,0,0);
	XStoreName(*d,*w,_("HDBENCH clone"));
	*gc=XCreateGC(*d,*w,0,0);

	color_map=DefaultColormap(*d,DefaultScreen(*d));
	for(i=0;i<8;i++){
		xcolor.red=default_rgb_palette_color[i][0];     /* store default palette */
		xcolor.green=default_rgb_palette_color[i][1];
		xcolor.blue=default_rgb_palette_color[i][2];
		xcolor.flags=DoRed|DoGreen|DoBlue;
		if(XAllocColor(*d,color_map,&xcolor)==0){     /* allocate color map cell */
			kill(getppid(),SIGTERM);
			g_error(_("Cannot allocate color.\n"));
		}
		palette[i]=xcolor.pixel;	/* sort color map cell number as palette number */
		}

	xfs = XLoadQueryFont ( *d, font_name );
	if(xfs==NULL){
		kill(getppid(),SIGTERM);
		err_mes_temp=g_strdup_printf(_("Cannot load font `%s'.\n"),font_name);
		g_error(err_mes_temp);
	}
	XSetFont ( *d, *gc, xfs->fid );
	*width=XTextWidth(xfs,video_text,strlen(video_text));
	*height=xfs->max_bounds.ascent+xfs->max_bounds.descent;

	XMapWindow(*d,*w);
	XFlush(*d);
}


void set_sensitive(gint val)
{
	gtk_widget_set_sensitive (bench_func_all, val);
	gtk_widget_set_sensitive (bench_func_cpu, val);
	gtk_widget_set_sensitive (bench_func_video, val);
	gtk_widget_set_sensitive (bench_func_disk, val);
	gtk_widget_set_sensitive (main_func_exit, val);
	gtk_widget_set_sensitive (main_func_copy, val);
	gtk_widget_set_sensitive (main_func_print, val);
	gtk_widget_set_sensitive (main_func_system, val);
	gtk_widget_set_sensitive (main_func_graph, val);
	gtk_widget_set_sensitive (main_func_help, val);
	gtk_widget_set_sensitive (plugin_option_menu, val);
	gtk_widget_set_sensitive (plugin_start, val);
/*	gtk_widget_set_sensitive (plugin_option, val); */
	gtk_widget_set_sensitive (plugin_copy, val);
	gtk_widget_set_sensitive (opt_read, val);
	gtk_widget_set_sensitive (opt_drivecopy, val);
	gtk_widget_set_sensitive (opt_resultonly, val);
	gtk_widget_set_sensitive (opt_cdrom, val);
	gtk_widget_set_sensitive (opt_image, val);
	gtk_widget_set_sensitive (drive_combo, val);
	gtk_widget_set_sensitive (capacity_option_menu, val);
}


void set_sigalarm(gint sec)
{
	done_flag=0;
	if(signal(SIGALRM,(void *)alarm_handler)==SIG_ERR){
		kill(getppid(),SIGTERM);
		g_error(_("Cannot install a signal handler of SIGALRM.\n"));
	}
	alarm(sec);
}



void alarm_handler(void)
{
	done_flag=1;
}

