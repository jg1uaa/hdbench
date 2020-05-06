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
#  include <config.h>
#endif

#include <time.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "intl.h"
#include "proto.h"
#include "variable.h"


gboolean
on_main_window_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_main_quit();
  return FALSE;
}


void
on_exit_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gchar *format_result(void)
{
  gchar *name;
  gchar *vendor;
  gchar *family;
  gchar *model;
  gchar *stepping;
  gchar *os_name;
  gint32 freemem,totalmem;
  struct tm *nowtime;
  time_t t;
  gchar *machine_info1,*machine_info2,*bench_result;
  gchar *display_name;
  gchar *drive_data;
  gchar *formated;


  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(opt_resultonly))){
  	formated=g_strdup_printf("%6d%6d%6d%6d%6d%6d%6d%6d%6d%6d%6d %s:%dMB\n"
,result_all,result_float,result_integer,result_memory,
result_rectangle,result_circle,result_text,result_scroll,result_image,
result_read,result_write,
disk_drive,disk_capacity);
  }else{
	get_cpuinfo(&name,&vendor,&family,&model,&stepping);
	get_osinfo(&os_name);
	get_meminfo(&totalmem,&freemem);
	t=time(NULL);
	nowtime=localtime(&t);

	machine_info1=g_strdup_printf("\
* * *  HDBENCH clone Ver %s  * * *\n\
Machine Infomation\n\
Processor   %s\n\
            Vendor %s Family %s Model %s Stepping %s\n\
Resolution  %dx%d %ucolors(%dbit)\n",
VERSION,name,vendor,family,model,stepping,
DisplayWidth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
DisplayHeight(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
lpow(2,DefaultDepth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY()))),
DefaultDepth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())));

	machine_info2=g_strdup_printf("\
Memory      %dKBytes\n\
OS          %s\n\
Date        %d/%02d/%02d %02d:%02d\n\n",
totalmem/1024,os_name,
nowtime->tm_year+1900,nowtime->tm_mon+1,nowtime->tm_mday,nowtime->tm_hour,nowtime->tm_min);

        g_free(name);
        g_free(vendor);
        g_free(family);
        g_free(model);
        g_free(stepping);
        g_free(os_name);

	bench_result=g_strdup_printf("\
 TOTAL FLOAT INTGR MEMRY  RECT CIRCL  TEXT  SCRL IMAGE  READ WRITE DRIVE\n\
%6d%6d%6d%6d%6d%6d%6d%6d%6d%6d%6d %s:%dMB\n",
result_all,result_float,result_integer,result_memory,
result_rectangle,result_circle,result_text,result_scroll,result_image,
result_read,result_write,
disk_drive,disk_capacity);

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(opt_drivecopy))){
		display_name=get_display_name();
		drive_data=get_drive_data();

		formated=g_strconcat(machine_info1,"Display     ",display_name,"\n",machine_info2,drive_data,"\n",bench_result,NULL);

		g_free(display_name);
		g_free(drive_data);
	}else{
		formated=g_strconcat(machine_info1,machine_info2,bench_result,NULL);
	}

	g_free(machine_info1);
	g_free(machine_info2);
	g_free(bench_result);
  }
  return(formated);
}

void
on_copy_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
  if(selection_buffer!=NULL){
  	g_free(selection_buffer);
  }
  selection_buffer=format_result();
  gtk_selection_owner_set (main_window,GDK_SELECTION_PRIMARY,GDK_CURRENT_TIME);
}


void
on_print_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *temp;
  FILE *fp;

  temp=format_result();
  fp=popen("lpr","w");
  if(fp==NULL){
  	g_error(_("Cannot create a pipe.\n"));
  }
  fputs(temp,fp);
  pclose(fp);
}


void
on_system_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *system_dialog;

  system_dialog = create_system_dialog ();
  gtk_widget_show (system_dialog);
}


void
on_graph_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *damn_dialog;

  damn_dialog = create_damn_dialog ();
  gtk_widget_show (damn_dialog);
}


void
on_all_clicked                         (GtkButton       *button,
                                        gpointer         user_data)
{
	benchmark_all();
}


void
on_cpu_clicked                         (GtkButton       *button,
                                        gpointer         user_data)
{
	benchmark_cpu();
}


void
on_video_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	benchmark_video();
}


void
on_disk_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	benchmark_disk();
}


void
on_help_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *help_dialog;

  help_dialog = create_help_dialog ();
  gtk_widget_show (help_dialog);
}


void
on_plugin_start_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *plugin_start_dialog;

  plugin_start_dialog = create_plugin_start_dialog ();
  gtk_widget_show (plugin_start_dialog);
}


void
on_plugin_copy_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *plugin_copy_dialog;

  plugin_copy_dialog = create_plugin_copy_dialog ();
  gtk_widget_show (plugin_copy_dialog);
}
 

void
on_close_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(user_data);
}


void
capacity_option_menu_set               (GtkWidget       *item,
                                        gpointer         user_data)
{
        disk_capacity=(int)user_data;
}


void
drive_combo_set_changed                (GtkWidget       *item,
                                        gpointer         user_data)
{
	disk_drive=gtk_entry_get_text( GTK_ENTRY( GTK_COMBO( user_data )->entry ) );
}


void
on_system_copy_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *name;
  gchar *vendor;
  gchar *family;
  gchar *model;
  gchar *stepping;
  gchar *os_name;

  get_cpuinfo(&name,&vendor,&family,&model,&stepping);
  get_osinfo(&os_name);

  if(selection_buffer!=NULL){
	g_free(selection_buffer);
  }
  selection_buffer=g_strdup_printf("** HDBENCH clone Ver %s **\n\
OS       %s\n\
CPU      %s\n\
Vendor   %s\n\
Family   %s\n\
Model    %s\n\
Stepping %s\n",VERSION,os_name,name,vendor,family,model,stepping);

  gtk_selection_owner_set (main_window,GDK_SELECTION_PRIMARY,GDK_CURRENT_TIME);

  g_free(name);
  g_free(vendor);
  g_free(family);
  g_free(model);
  g_free(stepping);
  g_free(os_name);
}

