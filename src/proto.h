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

#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED

#include <X11/Xlib.h>
#include <stdio.h>
#include <gtk/gtk.h>


/* main.c */

void put_usage(void);
void put_version(void);


/* benchmark.c */

void benchmark_cpu(void);
void bench_cpu_and_write(gint write_fd);
void bench_cpu_update(gpointer userdata,gint read_fd,GdkInputCondition condition);
void benchmark_video(void);
void bench_video_and_write(gint write_fd);
gint32 bench_rectangle(Display *d,Window w,GC gc,guint32 *palette);
gint32 bench_circle(Display *d,Window w,GC gc,guint32 *palette);
gint32 bench_text(Display *d,Window w,GC gc,guint32 *palette,gint width,gint height);
gint32 bench_scroll(Display *d,Window w,GC gc,guint32 *palette);
gint32 bench_image(Display *d,Window w,GC gc,XImage *image,guint16 *buffer);
void bench_video_update(gpointer userdata,gint read_fd,GdkInputCondition condition);
void benchmark_disk(void);
void bench_disk_and_write(gint write_fd);
gint32 bench_write(char *buf,gchar *temp);
void bench_cache_flash(char *buf,gchar *temp);
gint32 bench_read(char *buf,gchar *temp);
void bench_disk_update(gpointer userdata,gint read_fd,GdkInputCondition condition);
void benchmark_all(void);
void bench_all_update(gpointer userdata,gint read_fd,GdkInputCondition condition);
void initx(Display **d,Window *w,GC *gc,guint32 *palette,gint *width,gint *height);
void set_sensitive(gint val);
void set_sigalarm(gint sec);
void alarm_handler(void);


/* benchcpu.s */

gint32 bench_integer(void);
gint32 bench_float(void);
gint32 bench_memory(char *src,char *dest);


/* getinfo.c */

gint get_meminfo(gint64 *totalmem,gint64 *freemem);
void get_cpuinfo(char **name,char **vendor,char **family,char **model,char **stepping);
void get_osinfo(char **name);
guint32 lpow(gint x,gint y);
char *get_display_name(void);
char *parse_display_name(FILE *fp);
char *get_drive_data(void);
char *str_fgets(FILE *fp);
int str_skip_fgets(FILE *fp);


/* selection.c */
void init_atoms(void);
void selection_get(GtkWidget *widget,GtkSelectionData *selection_data,guint info,guint time,gpointer data);


/* hdbench.h */

GtkWidget* create_main_window (void);
GtkWidget* create_damn_dialog (void);
GtkWidget* create_plugin_start_dialog (void);
GtkWidget* create_plugin_copy_dialog (void);
GtkWidget* create_help_dialog (void);
GtkWidget* create_system_dialog (void);


/* sighandler.h */

gboolean
on_main_window_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_exit_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_copy_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_print_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_system_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_graph_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_all_clicked                         (GtkButton       *button,
                                        gpointer         user_data);

void
on_cpu_clicked                         (GtkButton       *button,
                                        gpointer         user_data);

void
on_video_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_disk_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_help_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_plugin_start_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_plugin_copy_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_close_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
capacity_option_menu_set               (GtkWidget       *item,
                                        gpointer         user_data);

void
drive_combo_set_changed                (GtkWidget       *item,
                                        gpointer         user_data);


void
on_system_copy_button_clicked          (GtkButton       *button,
                                        gpointer         user_data);


/* support.c */

/*
 * This function returns a widget in a component created by Glade.
 * Call it with the toplevel widget in the component (i.e. a window/dialog),
 * or alternatively any widget in the component, and the name of the widget
 * you want returned.
 */
GtkWidget*  lookup_widget              (GtkWidget       *widget,
                                        const gchar     *widget_name);

/* get_widget() is deprecated. Use lookup_widget instead. */
#define get_widget lookup_widget

/* Use this function to set the directory containing installed pixmaps. */
void        add_pixmap_directory       (const gchar     *directory);

/* This is used to create the pixmaps in the interface. */
GtkWidget*  create_pixmap              (GtkWidget       *widget,
                                        const gchar     *filename);


#endif /* PROTO_H_INCLUDED */



