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
#include <inttypes.h>
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
  gint64 freemem,totalmem;
  struct tm *nowtime;
  time_t t;
  gchar *machine_info,*bench_result;
  gchar *display_name;
  gchar *drive_data=NULL;
  gchar *formatted;
  gint sep;


  get_cpuinfo(&name,&vendor,&family,&model,&stepping);
  get_osinfo(&os_name);
  get_meminfo(&totalmem,&freemem);
  display_name=get_display_name();
  t=time(NULL);
  nowtime=localtime(&t);

  if(output_format==FORMAT_STANDARD){
	  /* standard format */
	  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(opt_drivecopy))&&
	     !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(opt_resultonly))){
		  drive_data=get_drive_data();
	  }
	  machine_info=g_strdup_printf(
		  "* * *  HDBENCH clone Ver %s  * * *\n"
		  "M/B Name    %s\n"
		  "Processor   %s\n"
		  "            Vendor %s Family %s Model %s Stepping %s\n"
		  "Resolution  %dx%d (%dbit color)\n"
		  "Display     %s\n"
		  "Memory      %"PRId64" KBytes\n"
		  "OS          %s\n"
		  "Date        %d/%02d/%02d %02d:%02d\n\n",
		  VERSION,
		  gtk_entry_get_text(GTK_ENTRY(mbname_entry)),
		  name,
		  vendor,family,model,stepping,
		  DisplayWidth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
		  DisplayHeight(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
		  DefaultDepth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
		  display_name,
		  totalmem/1024,
		  os_name,
		  nowtime->tm_year+1900,nowtime->tm_mon+1,nowtime->tm_mday,
		  nowtime->tm_hour,nowtime->tm_min);
	  bench_result=g_strdup_printf(
		  "%s"
		  "    TOTAL     FLOAT   INTEGER    MEMORY\n"
		  "%9d %9d %9d %9d\n"
		  "\n"
		  "   RECT  CIRCLE    TEXT  SCROLL   IMAGE     READ    WRITE DRIVE\n"
		  "%7d %7d %7d %7d %7d %8d %8d %s:%dMB\n\n",
		  (drive_data==NULL)?"":"\n",
		  result_all,result_float,result_integer,result_memory,
		  result_rectangle,result_circle,result_text,
		  result_scroll,result_image,
		  result_read,result_write,disk_drive,disk_capacity);
  }else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(opt_resultonly))){
	  /* FORMAT_CSV_SINGLE/FORMAT_CSV_MULTI, result only */
	  sep=(output_format==FORMAT_CSV_MULTI)?'\n':'\t';
	  machine_info=g_strdup("");
	  bench_result = g_strdup_printf(
		  "%d%c" "%d%c" "%d%c"
		  "%d%c" "%d%c" "%d%c"
		  "%d%c" "%d%c" "%d%c"
		  "%d%c" "%d%c" "%s:%dMB\n",
		  result_all,sep, result_float,sep, result_integer,sep,
		  result_memory,sep, result_rectangle,sep, result_circle,sep,
		  result_text,sep, result_scroll,sep, result_image,sep,
		  result_read,sep, result_write,sep, disk_drive,disk_capacity);
  }else if(output_format==FORMAT_CSV_MULTI){
	  /* FORMAT_CSV_MULTI with machine information */
	  sep='\t';
	  machine_info=g_strdup_printf(
		  "Ver%c%s\n" "M/B Name%c%s\n"
		  "Processor%c%s\n" "Vendor%c%s\n" "Family%c%s\n"
		  "Model%c%s\n" "Stepping%c%s\n"
		  "Resolution%c%dx%d (%dbit color)\n"
		  "Display%c%s\n" "Memory(KBytes)%c%"PRId64"\n" "OS%c%s\n"
		  "Date%c%d/%02d/%02d %02d:%02d\n",
		  sep,VERSION, sep,gtk_entry_get_text(GTK_ENTRY(mbname_entry)),
		  sep,name, sep,vendor, sep,family,
		  sep,model, sep,stepping,
		  sep,DisplayWidth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
		  DisplayHeight(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
		  DefaultDepth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
		  sep,display_name, sep,totalmem/1024, sep,os_name,
		  sep,nowtime->tm_year+1900,nowtime->tm_mon+1,nowtime->tm_mday,
		  nowtime->tm_hour,nowtime->tm_min);
	  bench_result=g_strdup_printf(
		  "TOTAL%c%d\n" "FLOAT%c%d\n" "INTEGER%c%d\n"
		  "MEMORY%c%d\n" "RECT%c%d\n" "CIRCLE%c%d\n"
		  "TEXT%c%d\n" "SCROLL%c%d\n" "IMAGE%c%d\n"
		  "READ%c%d\n" "WRITE%c%d\n"
		  "DRIVE%c%s:%dMB\n",
		  sep,result_all, sep,result_float, sep,result_integer,
		  sep,result_memory, sep,result_rectangle, sep,result_circle,
		  sep,result_text, sep,result_scroll, sep,result_image,
		  sep,result_read, sep,result_write,
		  sep,disk_drive,disk_capacity);
  }else{
	  /* FORMAT_CSV_SINGLE with machine information */
	  sep='\t';
	  machine_info=g_strdup_printf(
		  "Ver%c" "M/B Name%c"
		  "Processor%c" "Vendor%c" "Family%c" "Model%c"
		  "Stepping%c" "Resolution%c" "Display%c" "Memory(KBytes)%c"
		  "OS%c" "Date%c"
		  "TOTAL%c" "FLOAT%c" "INTEGER%c" "MEMORY%c" "RECT%c"
		  "CIRCLE%c" "TEXT%c" "SCROLL%c" "IMAGE%c"
		  "READ%c" "WRITE%c" "DRIVE\n",
		  sep,sep,
		  sep,sep,sep,sep,
		  sep,sep,sep,sep,
		  sep,sep,
		  sep,sep,sep,sep,sep,
		  sep,sep,sep,sep,
		  sep,sep);
	  bench_result=g_strdup_printf(
		  "%s%c" "%s%c"
		  "%s%c" "%s%c" "%s%c"
		  "%s%c" "%s%c"
		  "%dx%d (%dbit color)%c"
		  "%s%c" "%"PRId64"%c" "%s%c"
		  "%d/%02d/%02d %02d:%02d%c"
		  "%d%c" "%d%c" "%d%c"
		  "%d%c" "%d%c" "%d%c"
		  "%d%c" "%d%c" "%d%c"
		  "%d%c" "%d%c" "%s:%dMB\n",
		  VERSION,sep, gtk_entry_get_text(GTK_ENTRY(mbname_entry)),sep,
		  name,sep, vendor,sep, family,sep,
		  model,sep, stepping,sep,
		  DisplayWidth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
		  DisplayHeight(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),
		  DefaultDepth(GDK_DISPLAY(),DefaultScreen(GDK_DISPLAY())),sep,
		  display_name,sep, totalmem/1024,sep, os_name,sep,
		  nowtime->tm_year+1900,nowtime->tm_mon+1,nowtime->tm_mday,
		  nowtime->tm_hour,nowtime->tm_min,sep,
		  result_all,sep, result_float,sep, result_integer,sep,
		  result_memory,sep, result_rectangle,sep, result_circle,sep,
		  result_text,sep, result_scroll,sep, result_image,sep,
		  result_read,sep, result_write,sep, disk_drive,disk_capacity);
  }

  if(drive_data==NULL){
	  drive_data=g_strdup("");
  }

  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(opt_resultonly))){
	  formatted=g_strdup(bench_result);
  }else{
	  formatted=g_strconcat(machine_info,drive_data,bench_result,NULL);
  }

  g_free(name);
  g_free(vendor);
  g_free(family);
  g_free(model);
  g_free(stepping);
  g_free(os_name);
  g_free(display_name);
  g_free(drive_data);
  g_free(machine_info);
  g_free(bench_result);

  return(formatted);
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
on_close_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_destroy(user_data);
}


void
capacity_option_menu_set               (GtkWidget       *item,
                                        gpointer         user_data)
{
        disk_capacity=(gintptr)user_data;
}


void
format_toggled                         (GtkWidget       *item,
                                        gpointer         user_data)
{
        output_format=(gintptr)user_data;
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

