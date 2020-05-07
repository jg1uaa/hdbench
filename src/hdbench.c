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

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "intl.h"
#include "proto.h"
#include "variable.h"


extern GtkTargetEntry targetlist[];
extern gint ntargets;


GtkWidget*
create_main_window ()
{
  GtkWidget *vbox1;
  GtkWidget *fixed1;
  GtkWidget *bench_text;
  GtkWidget *bench_memory;
  GtkWidget *bench_scroll;
  GtkWidget *bench_image;
  GtkWidget *capacity_option_menu_menu;
  GtkWidget *glade_menuitem;
  GtkWidget *plugins;
  GtkWidget *fixed2;
  GtkWidget *plugin_option_menu_menu;
  GtkWidget *label_capacity;
  GtkWidget *bench_plugin;
  GtkWidget *cpu_xpm;
  GtkWidget *video_xpm;
  GtkWidget *disk_xpm;
  GtkWidget *bench_read;
  GtkWidget *bench_rectangle;
  GtkWidget *bench_float;
  GtkWidget *bench_integer;
  GtkWidget *bench_circle;
  GtkWidget *bench_total;
  GtkWidget *options;
  GtkWidget *hbox1;
  GtkWidget *vbox3;
  GtkWidget *bench_write;
  GtkWidget *label_drive;
  GList *drive_combo_items = NULL;
  gchar *title;


  title = g_strconcat(_("HDBENCH clone Ver "), VERSION, NULL);
  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_object_set_data (GTK_OBJECT (main_window), "main_window", main_window);
  gtk_window_set_title (GTK_WINDOW (main_window), title);
  gtk_window_set_policy (GTK_WINDOW (main_window), TRUE, TRUE, FALSE);
  g_free(title);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (main_window), "vbox1", vbox1);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (main_window), vbox1);

  fixed1 = gtk_fixed_new ();
  gtk_object_set_data (GTK_OBJECT (main_window), "fixed1", fixed1);
  gtk_widget_show (fixed1);
  gtk_box_pack_start (GTK_BOX (vbox1), fixed1, TRUE, TRUE, 0);

  main_func_exit = gtk_button_new_with_label (_("EXIT"));
  gtk_object_set_data (GTK_OBJECT (main_window), "main_func_exit", main_func_exit);
  gtk_widget_show (main_func_exit);
  gtk_fixed_put (GTK_FIXED (fixed1), main_func_exit, 0, 0);
  gtk_widget_set_uposition (main_func_exit, 0, 0);
  gtk_widget_set_usize (main_func_exit, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (main_func_exit), 2);

  main_func_copy = gtk_button_new_with_label (_("COPY"));
  gtk_object_set_data (GTK_OBJECT (main_window), "main_func_copy", main_func_copy);
  gtk_widget_show (main_func_copy);
  gtk_fixed_put (GTK_FIXED (fixed1), main_func_copy, 72, 0);
  gtk_widget_set_uposition (main_func_copy, 72, 0);
  gtk_widget_set_usize (main_func_copy, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (main_func_copy), 2);

  main_func_print = gtk_button_new_with_label (_("PRINT"));
  gtk_object_set_data (GTK_OBJECT (main_window), "main_func_print", main_func_print);
  gtk_widget_show (main_func_print);
  gtk_fixed_put (GTK_FIXED (fixed1), main_func_print, 144, 0);
  gtk_widget_set_uposition (main_func_print, 144, 0);
  gtk_widget_set_usize (main_func_print, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (main_func_print), 2);

  main_func_system = gtk_button_new_with_label (_("SYSTEM"));
  gtk_object_set_data (GTK_OBJECT (main_window), "main_func_system", main_func_system);
  gtk_widget_show (main_func_system);
  gtk_fixed_put (GTK_FIXED (fixed1), main_func_system, 216, 0);
  gtk_widget_set_uposition (main_func_system, 216, 0);
  gtk_widget_set_usize (main_func_system, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (main_func_system), 2);

  main_func_graph = gtk_button_new_with_label (_("GRAPH"));
  gtk_object_set_data (GTK_OBJECT (main_window), "main_func_graph", main_func_graph);
  gtk_widget_show (main_func_graph);
  gtk_fixed_put (GTK_FIXED (fixed1), main_func_graph, 288, 0);
  gtk_widget_set_uposition (main_func_graph, 288, 0);
  gtk_widget_set_usize (main_func_graph, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (main_func_graph), 2);

  bench_func_all = gtk_button_new_with_label (_("ALL"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_func_all", bench_func_all);
  gtk_widget_show (bench_func_all);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_func_all, 48, 64);
  gtk_widget_set_uposition (bench_func_all, 48, 64);
  gtk_widget_set_usize (bench_func_all, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (bench_func_all), 2);

  bench_func_cpu = gtk_button_new_with_label (_("CPU"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_func_cpu", bench_func_cpu);
  gtk_widget_show (bench_func_cpu);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_func_cpu, 48, 128);
  gtk_widget_set_uposition (bench_func_cpu, 48, 128);
  gtk_widget_set_usize (bench_func_cpu, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (bench_func_cpu), 2);

  bench_func_video = gtk_button_new_with_label (_("VIDEO"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_func_video", bench_func_video);
  gtk_widget_show (bench_func_video);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_func_video, 48, 192);
  gtk_widget_set_uposition (bench_func_video, 48, 192);
  gtk_widget_set_usize (bench_func_video, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (bench_func_video), 2);

  bench_func_disk = gtk_button_new_with_label (_("DISK"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_func_disk", bench_func_disk);
  gtk_widget_show (bench_func_disk);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_func_disk, 48, 264);
  gtk_widget_set_uposition (bench_func_disk, 48, 264);
  gtk_widget_set_usize (bench_func_disk, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (bench_func_disk), 2);

  main_func_help = gtk_button_new_with_label (_("HELP"));
  gtk_object_set_data (GTK_OBJECT (main_window), "main_func_help", main_func_help);
  gtk_widget_show (main_func_help);
  gtk_fixed_put (GTK_FIXED (fixed1), main_func_help, 360, 0);
  gtk_widget_set_uposition (main_func_help, 360, 0);
  gtk_widget_set_usize (main_func_help, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (main_func_help), 2);

  video_xpm = create_pixmap (main_window, "video.xpm");
  gtk_object_set_data (GTK_OBJECT (main_window), "video_xpm", video_xpm);
  gtk_widget_show (video_xpm);
  gtk_fixed_put (GTK_FIXED (fixed1), video_xpm, 8, 192);
  gtk_widget_set_uposition (video_xpm, 8, 192);
  gtk_widget_set_usize (video_xpm, 32, 32);

  bench_text = gtk_frame_new (_("TEXT"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_text", bench_text);
  gtk_widget_show (bench_text);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_text, 344, 176);
  gtk_widget_set_uposition (bench_text, 344, 176);
  gtk_widget_set_usize (bench_text, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_text), 0.5, 0.5);

  bench_text_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_text_score", bench_text_score);
  gtk_widget_show (bench_text_score);
  gtk_container_add (GTK_CONTAINER (bench_text), bench_text_score);
  gtk_misc_set_alignment (GTK_MISC (bench_text_score), 0.9, 0.5);

  bench_memory = gtk_frame_new (_("MEMORY"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_memory", bench_memory);
  gtk_widget_show (bench_memory);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_memory, 448, 112);
  gtk_widget_set_uposition (bench_memory, 448, 112);
  gtk_widget_set_usize (bench_memory, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_memory), 0.5, 0.5);

  bench_memory_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_memory_score", bench_memory_score);
  gtk_widget_show (bench_memory_score);
  gtk_container_add (GTK_CONTAINER (bench_memory), bench_memory_score);
  gtk_misc_set_alignment (GTK_MISC (bench_memory_score), 0.9, 0.5);

  bench_scroll = gtk_frame_new (_("SCROLL"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_scroll", bench_scroll);
  gtk_widget_show (bench_scroll);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_scroll, 448, 176);
  gtk_widget_set_uposition (bench_scroll, 448, 176);
  gtk_widget_set_usize (bench_scroll, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_scroll), 0.5, 0.5);

  bench_scroll_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_scroll_score", bench_scroll_score);
  gtk_widget_show (bench_scroll_score);
  gtk_container_add (GTK_CONTAINER (bench_scroll), bench_scroll_score);
  gtk_misc_set_alignment (GTK_MISC (bench_scroll_score), 0.9, 0.5);

  bench_image = gtk_frame_new (_("IMAGE"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_image", bench_image);
  gtk_widget_show (bench_image);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_image, 552, 176);
  gtk_widget_set_uposition (bench_image, 552, 176);
  gtk_widget_set_usize (bench_image, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_image), 0.5, 0.5);

  bench_image_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_image_score", bench_image_score);
  gtk_widget_show (bench_image_score);
  gtk_container_add (GTK_CONTAINER (bench_image), bench_image_score);
  gtk_misc_set_alignment (GTK_MISC (bench_image_score), 0.9, 0.5);

  capacity_option_menu = gtk_option_menu_new ();
  gtk_object_set_data (GTK_OBJECT (main_window), "capacity_option_menu", capacity_option_menu);
  gtk_widget_show (capacity_option_menu);
  gtk_fixed_put (GTK_FIXED (fixed1), capacity_option_menu, 552, 264);
  gtk_widget_set_uposition (capacity_option_menu, 552, 264);
  gtk_widget_set_usize (capacity_option_menu, 96, 32);
  capacity_option_menu_menu = gtk_menu_new ();
  glade_menuitem = gtk_menu_item_new_with_label ("2000MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)2000);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("1024MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)1024);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("512MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)512);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("100MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)100);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("20MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)20);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("10MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)10);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("5MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)5);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("3MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)3);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("2MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)2);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  glade_menuitem = gtk_menu_item_new_with_label ("1MB");
  gtk_signal_connect (GTK_OBJECT (glade_menuitem), "activate",
                      GTK_SIGNAL_FUNC (capacity_option_menu_set),
                      (gpointer)1);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (capacity_option_menu_menu), glade_menuitem);
  gtk_option_menu_set_menu (GTK_OPTION_MENU (capacity_option_menu), capacity_option_menu_menu);
  gtk_option_menu_set_history (GTK_OPTION_MENU (capacity_option_menu), 5);

  plugins = gtk_frame_new (_("PLUGIN"));
  gtk_object_set_data (GTK_OBJECT (main_window), "plugins", plugins);
  gtk_widget_show (plugins);
  gtk_fixed_put (GTK_FIXED (fixed1), plugins, 16, 312);
  gtk_widget_set_uposition (plugins, 16, 312);
  gtk_widget_set_usize (plugins, 296, 136);

  fixed2 = gtk_fixed_new ();
  gtk_object_set_data (GTK_OBJECT (main_window), "fixed2", fixed2);
  gtk_widget_show (fixed2);
  gtk_container_add (GTK_CONTAINER (plugins), fixed2);

  plugin_start = gtk_button_new_with_label (_("Start"));
  gtk_object_set_data (GTK_OBJECT (main_window), "plugin_start", plugin_start);
  gtk_widget_show (plugin_start);
  gtk_fixed_put (GTK_FIXED (fixed2), plugin_start, 8, 16);
  gtk_widget_set_uposition (plugin_start, 8, 16);
  gtk_widget_set_usize (plugin_start, 72, 32);

  plugin_option = gtk_button_new_with_label (_("OPTIONS"));
  gtk_object_set_data (GTK_OBJECT (main_window), "plugin_option", plugin_option);
  gtk_widget_show (plugin_option);
  gtk_fixed_put (GTK_FIXED (fixed2), plugin_option, 184, 8);
  gtk_widget_set_uposition (plugin_option, 184, 8);
  gtk_widget_set_usize (plugin_option, 96, 25);
  gtk_container_set_border_width (GTK_CONTAINER (plugin_option), 1);
  gtk_widget_set_sensitive (plugin_option, FALSE);

  plugin_copy = gtk_button_new_with_label (_("Copy results"));
  gtk_object_set_data (GTK_OBJECT (main_window), "plugin_copy", plugin_copy);
  gtk_widget_show (plugin_copy);
  gtk_fixed_put (GTK_FIXED (fixed2), plugin_copy, 184, 32);
  gtk_widget_set_uposition (plugin_copy, 184, 32);
  gtk_widget_set_usize (plugin_copy, 96, 24);
  gtk_container_set_border_width (GTK_CONTAINER (plugin_copy), 1);

  plugin_option_menu = gtk_option_menu_new ();
  gtk_object_set_data (GTK_OBJECT (main_window), "plugin_option_menu", plugin_option_menu);
  gtk_widget_show (plugin_option_menu);
  gtk_fixed_put (GTK_FIXED (fixed2), plugin_option_menu, 8, 72);
  gtk_widget_set_uposition (plugin_option_menu, 8, 72);
  gtk_widget_set_usize (plugin_option_menu, 272, 32);
  plugin_option_menu_menu = gtk_menu_new ();
  gtk_option_menu_set_menu (GTK_OPTION_MENU (plugin_option_menu), plugin_option_menu_menu);

  bench_plugin = gtk_frame_new (NULL);
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_plugin", bench_plugin);
  gtk_widget_show (bench_plugin);
  gtk_fixed_put (GTK_FIXED (fixed2), bench_plugin, 96, 16);
  gtk_widget_set_uposition (bench_plugin, 96, 16);
  gtk_widget_set_usize (bench_plugin, 72, 32);

  bench_plugin_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_plugin_score", bench_plugin_score);
  gtk_widget_show (bench_plugin_score);
  gtk_container_add (GTK_CONTAINER (bench_plugin), bench_plugin_score);
  gtk_misc_set_alignment (GTK_MISC (bench_plugin_score), 0.9, 0.5);

  disk_xpm = create_pixmap (main_window, "disk.xpm");
  gtk_object_set_data (GTK_OBJECT (main_window), "disk_xpm", disk_xpm);
  gtk_widget_show (disk_xpm);
  gtk_fixed_put (GTK_FIXED (fixed1), disk_xpm, 8, 264);
  gtk_widget_set_uposition (disk_xpm, 8, 264);
  gtk_widget_set_usize (disk_xpm, 32, 32);

  label_capacity = gtk_label_new (_("CAPACITY"));
  gtk_object_set_data (GTK_OBJECT (main_window), "label_capacity", label_capacity);
  gtk_widget_show (label_capacity);
  gtk_fixed_put (GTK_FIXED (fixed1), label_capacity, 552, 240);
  gtk_widget_set_uposition (label_capacity, 552, 240);
  gtk_widget_set_usize (label_capacity, 80, 24);

  cpu_xpm = create_pixmap (main_window, "cpu.xpm");
  gtk_object_set_data (GTK_OBJECT (main_window), "cpu_xpm", cpu_xpm);
  gtk_widget_show (cpu_xpm);
  gtk_fixed_put (GTK_FIXED (fixed1), cpu_xpm, 8, 128);
  gtk_widget_set_uposition (cpu_xpm, 8, 128);
  gtk_widget_set_usize (cpu_xpm, 32, 32);

  bench_read = gtk_frame_new (_("READ(KB/s)"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_read", bench_read);
  gtk_widget_show (bench_read);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_read, 136, 248);
  gtk_widget_set_uposition (bench_read, 136, 248);
  gtk_widget_set_usize (bench_read, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_read), 0.5, 0.5);

  bench_read_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_read_score", bench_read_score);
  gtk_widget_show (bench_read_score);
  gtk_container_add (GTK_CONTAINER (bench_read), bench_read_score);
  gtk_misc_set_alignment (GTK_MISC (bench_read_score), 0.9, 0.5);

  bench_rectangle = gtk_frame_new (_("RECTANGLE"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_rectangle", bench_rectangle);
  gtk_widget_show (bench_rectangle);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_rectangle, 136, 176);
  gtk_widget_set_uposition (bench_rectangle, 136, 176);
  gtk_widget_set_usize (bench_rectangle, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_rectangle), 0.5, 0.5);

  bench_rectangle_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_rectangle_score", bench_rectangle_score);
  gtk_widget_show (bench_rectangle_score);
  gtk_container_add (GTK_CONTAINER (bench_rectangle), bench_rectangle_score);
  gtk_misc_set_alignment (GTK_MISC (bench_rectangle_score), 0.9, 0.5);

  bench_float = gtk_frame_new (_("FLOAT"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_float", bench_float);
  gtk_widget_show (bench_float);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_float, 136, 112);
  gtk_widget_set_uposition (bench_float, 136, 112);
  gtk_widget_set_usize (bench_float, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_float), 0.5, 0.5);

  bench_float_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_float_score", bench_float_score);
  gtk_widget_show (bench_float_score);
  gtk_container_add (GTK_CONTAINER (bench_float), bench_float_score);
  gtk_misc_set_alignment (GTK_MISC (bench_float_score), 0.9, 0.5);

  bench_integer = gtk_frame_new (_("INTEGER"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_integer", bench_integer);
  gtk_widget_show (bench_integer);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_integer, 240, 112);
  gtk_widget_set_uposition (bench_integer, 240, 112);
  gtk_widget_set_usize (bench_integer, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_integer), 0.5, 0.5);

  bench_integer_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_integer_score", bench_integer_score);
  gtk_widget_show (bench_integer_score);
  gtk_container_add (GTK_CONTAINER (bench_integer), bench_integer_score);
  gtk_misc_set_alignment (GTK_MISC (bench_integer_score), 0.9, 0.5);

  bench_circle = gtk_frame_new (_("CIRCLE"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_circle", bench_circle);
  gtk_widget_show (bench_circle);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_circle, 240, 176);
  gtk_widget_set_uposition (bench_circle, 240, 176);
  gtk_widget_set_usize (bench_circle, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_circle), 0.5, 0.5);

  bench_circle_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_circle_score", bench_circle_score);
  gtk_widget_show (bench_circle_score);
  gtk_container_add (GTK_CONTAINER (bench_circle), bench_circle_score);
  gtk_misc_set_alignment (GTK_MISC (bench_circle_score), 0.9, 0.5);

  bench_total = gtk_frame_new (_("TOTAL"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_total", bench_total);
  gtk_widget_show (bench_total);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_total, 136, 48);
  gtk_widget_set_uposition (bench_total, 136, 48);
  gtk_widget_set_usize (bench_total, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_total), 0.5, 0.5);

  bench_total_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_total_score", bench_total_score);
  gtk_widget_show (bench_total_score);
  gtk_container_add (GTK_CONTAINER (bench_total), bench_total_score);
  gtk_misc_set_alignment (GTK_MISC (bench_total_score), 0.9, 0.5);

  options = gtk_frame_new (_("OPTIONS"));
  gtk_object_set_data (GTK_OBJECT (main_window), "options", options);
  gtk_widget_show (options);
  gtk_fixed_put (GTK_FIXED (fixed1), options, 328, 312);
  gtk_widget_set_uposition (options, 328, 312);
  gtk_widget_set_usize (options, 320, 136);

  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (main_window), "hbox1", hbox1);
  gtk_widget_show (hbox1);
  gtk_container_add (GTK_CONTAINER (options), hbox1);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (main_window), "vbox3", vbox3);
  gtk_widget_show (vbox3);
  gtk_box_pack_start (GTK_BOX (hbox1), vbox3, TRUE, TRUE, 0);

  opt_read = gtk_check_button_new_with_label (_("measure READ first(e.g. IDE busmaster)"));
  gtk_object_set_data (GTK_OBJECT (main_window), "opt_read", opt_read);
  gtk_widget_show (opt_read);
  gtk_box_pack_start (GTK_BOX (vbox3), opt_read, TRUE, TRUE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (opt_read), TRUE);

  opt_drivecopy = gtk_check_button_new_with_label (_("copy the drive infomation,too"));
  gtk_object_set_data (GTK_OBJECT (main_window), "opt_drivecopy", opt_drivecopy);
  gtk_widget_show (opt_drivecopy);
  gtk_box_pack_start (GTK_BOX (vbox3), opt_drivecopy, TRUE, TRUE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (opt_drivecopy), TRUE);

  opt_resultonly = gtk_check_button_new_with_label (_("copy the only results"));
  gtk_object_set_data (GTK_OBJECT (main_window), "opt_resultonly", opt_resultonly);
  gtk_widget_show (opt_resultonly);
  gtk_box_pack_start (GTK_BOX (vbox3), opt_resultonly, TRUE, TRUE, 0);

  opt_cdrom = gtk_check_button_new_with_label (_("CD-ROM method(reading existent files)"));
  gtk_object_set_data (GTK_OBJECT (main_window), "opt_cdrom", opt_cdrom);
  gtk_widget_show (opt_cdrom);
  gtk_box_pack_start (GTK_BOX (vbox3), opt_cdrom, TRUE, TRUE, 0);

  opt_image = gtk_check_button_new_with_label (_("measure IMAGE,too"));
  gtk_object_set_data (GTK_OBJECT (main_window), "opt_image", opt_image);
  gtk_widget_show (opt_image);
  gtk_box_pack_start (GTK_BOX (vbox3), opt_image, TRUE, TRUE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (opt_image), TRUE);

  bench_write = gtk_frame_new (_("WRITE(KB/s)"));
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_write", bench_write);
  gtk_widget_show (bench_write);
  gtk_fixed_put (GTK_FIXED (fixed1), bench_write, 240, 248);
  gtk_widget_set_uposition (bench_write, 240, 248);
  gtk_widget_set_usize (bench_write, 96, 48);
  gtk_frame_set_label_align (GTK_FRAME (bench_write), 0.5, 0.5);

  bench_write_score = gtk_label_new ("0");
  gtk_object_set_data (GTK_OBJECT (main_window), "bench_write_score", bench_write_score);
  gtk_widget_show (bench_write_score);
  gtk_container_add (GTK_CONTAINER (bench_write), bench_write_score);
  gtk_label_set_justify (GTK_LABEL (bench_write_score), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (bench_write_score), 0.9, 0.5);

  label_drive = gtk_label_new (_("DRIVE"));
  gtk_object_set_data (GTK_OBJECT (main_window), "label_drive", label_drive);
  gtk_widget_show (label_drive);
  gtk_fixed_put (GTK_FIXED (fixed1), label_drive, 384, 240);
  gtk_widget_set_uposition (label_drive, 384, 240);
  gtk_widget_set_usize (label_drive, 56, 24);

  drive_combo = gtk_combo_new ();
  gtk_object_set_data (GTK_OBJECT (main_window), "drive_combo", drive_combo);
  gtk_widget_show (drive_combo);
  gtk_fixed_put (GTK_FIXED (fixed1), drive_combo, 384, 264);
  gtk_widget_set_uposition (drive_combo, 384, 264);
  gtk_widget_set_usize (GTK_COMBO (drive_combo)->entry, 135, 32);
  gtk_widget_set_usize (drive_combo, 151, 32);

  if(getenv("TMPDIR")==NULL){
    drive_combo_items = g_list_append (drive_combo_items, "/tmp");
  }else{
    drive_combo_items = g_list_append (drive_combo_items, getenv("TMPDIR"));
  }
  drive_combo_items = g_list_append (drive_combo_items, getenv("HOME"));
  gtk_combo_set_popdown_strings (GTK_COMBO (drive_combo), drive_combo_items);
  g_list_free (drive_combo_items);
  disk_drive=gtk_entry_get_text( GTK_ENTRY( GTK_COMBO( drive_combo)->entry ) );

  measuring_all = gtk_button_new_with_label (_("Mesuring"));
  gtk_object_set_data (GTK_OBJECT (main_window), "measuring_all", measuring_all);
  gtk_fixed_put (GTK_FIXED (fixed1), measuring_all, 48, 64);
  gtk_widget_set_uposition (measuring_all, 48, 64);
  gtk_widget_set_usize (measuring_all, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (measuring_all), 2);

  measuring_cpu = gtk_button_new_with_label (_("Mesuring"));
  gtk_object_set_data (GTK_OBJECT (main_window), "measuring_cpu", measuring_cpu);
  gtk_fixed_put (GTK_FIXED (fixed1), measuring_cpu, 48, 128);
  gtk_widget_set_uposition (measuring_cpu, 48, 128);
  gtk_widget_set_usize (measuring_cpu, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (measuring_cpu), 2);

  measuring_video = gtk_button_new_with_label (_("Mesuring"));
  gtk_object_set_data (GTK_OBJECT (main_window), "measuring_video", measuring_video);
  gtk_fixed_put (GTK_FIXED (fixed1), measuring_video, 48, 192);
  gtk_widget_set_uposition (measuring_video, 48, 192);
  gtk_widget_set_usize (measuring_video, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (measuring_video), 2);

  measuring_disk = gtk_button_new_with_label (_("Mesuring"));
  gtk_object_set_data (GTK_OBJECT (main_window), "measuring_disk", measuring_disk);
  gtk_fixed_put (GTK_FIXED (fixed1), measuring_disk, 48, 264);
  gtk_widget_set_uposition (measuring_disk, 48, 264);
  gtk_widget_set_usize (measuring_disk, 72, 32);
  gtk_container_set_border_width (GTK_CONTAINER (measuring_disk), 2);

  gtk_signal_connect (GTK_OBJECT (main_window), "delete_event",
                      GTK_SIGNAL_FUNC (on_main_window_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (main_func_exit), "clicked",
                      GTK_SIGNAL_FUNC (on_exit_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (main_func_copy), "clicked",
                      GTK_SIGNAL_FUNC (on_copy_clicked),
                      GTK_OBJECT (main_func_copy));
  gtk_signal_connect (GTK_OBJECT (main_func_print), "clicked",
                      GTK_SIGNAL_FUNC (on_print_clicked),
                      GTK_OBJECT (main_func_print));
  gtk_signal_connect (GTK_OBJECT (main_func_system), "clicked",
                      GTK_SIGNAL_FUNC (on_system_clicked),
                      GTK_OBJECT (main_func_system));
  gtk_signal_connect (GTK_OBJECT (main_func_graph), "clicked",
                      GTK_SIGNAL_FUNC (on_graph_clicked),
                      GTK_OBJECT (main_func_graph));
  gtk_signal_connect (GTK_OBJECT (bench_func_all), "clicked",
                      GTK_SIGNAL_FUNC (on_all_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (bench_func_cpu), "clicked",
                      GTK_SIGNAL_FUNC (on_cpu_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (bench_func_video), "clicked",
                      GTK_SIGNAL_FUNC (on_video_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (bench_func_disk), "clicked",
                      GTK_SIGNAL_FUNC (on_disk_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (main_func_help), "clicked",
                      GTK_SIGNAL_FUNC (on_help_clicked),
                      GTK_OBJECT (main_func_help));
  gtk_signal_connect (GTK_OBJECT (plugin_start), "clicked",
                      GTK_SIGNAL_FUNC (on_plugin_start_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (plugin_copy), "clicked",
                      GTK_SIGNAL_FUNC (on_plugin_copy_clicked),
                      NULL);
  gtk_signal_connect( GTK_OBJECT( GTK_COMBO( drive_combo )->entry ), "changed",
                      GTK_SIGNAL_FUNC( drive_combo_set_changed ), (gpointer) drive_combo );

  gtk_selection_add_targets (main_window, GDK_SELECTION_PRIMARY,
                             targetlist, ntargets);

  gtk_signal_connect (GTK_OBJECT(main_window), "selection_get",
                      GTK_SIGNAL_FUNC (selection_get), NULL);

  return main_window;
}

GtkWidget*
create_damn_dialog ()
{
  GtkWidget *damn_dialog;
  GtkWidget *dialog_vbox2;
  GtkWidget *label_not_impl;
  GtkWidget *dialog_action_area2;
  GtkWidget *damn_button;

  damn_dialog = gtk_dialog_new ();
  gtk_object_set_data (GTK_OBJECT (damn_dialog), "damn_dialog", damn_dialog);
  GTK_WINDOW (damn_dialog)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_title (GTK_WINDOW (damn_dialog), _("Not implemented"));
  gtk_window_set_position (GTK_WINDOW (damn_dialog), GTK_WIN_POS_MOUSE);
  gtk_window_set_policy (GTK_WINDOW (damn_dialog), TRUE, TRUE, FALSE);

  dialog_vbox2 = GTK_DIALOG (damn_dialog)->vbox;
  gtk_object_set_data (GTK_OBJECT (damn_dialog), "dialog_vbox2", dialog_vbox2);
  gtk_widget_show (dialog_vbox2);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_vbox2), 2);

  label_not_impl = gtk_label_new (_("\n\n  This function is not implemented.  \n\n"));
  gtk_object_set_data (GTK_OBJECT (damn_dialog), "label_not_impl", label_not_impl);
  gtk_widget_show (label_not_impl);
  gtk_box_pack_start (GTK_BOX (dialog_vbox2), label_not_impl, TRUE, TRUE, 0);

  dialog_action_area2 = GTK_DIALOG (damn_dialog)->action_area;
  gtk_object_set_data (GTK_OBJECT (damn_dialog), "dialog_action_area2", dialog_action_area2);
  gtk_widget_show (dialog_action_area2);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_action_area2), 10);

  damn_button = gtk_button_new_with_label (_(" Damn "));
  gtk_object_set_data (GTK_OBJECT (damn_dialog), "damn_button", damn_button);
  gtk_widget_show (damn_button);
  gtk_box_pack_start (GTK_BOX (dialog_action_area2), damn_button, FALSE, FALSE, 0);

  gtk_window_set_modal(GTK_WINDOW(damn_dialog), TRUE);

  gtk_signal_connect (GTK_OBJECT (damn_button), "clicked",
                      GTK_SIGNAL_FUNC (on_close_clicked),
                      GTK_OBJECT (damn_dialog));

  return damn_dialog;
}

GtkWidget*
create_plugin_start_dialog ()
{
  GtkWidget *plugin_start_dialog;
  GtkWidget *dialog_vbox3;
  GtkWidget *label2;
  GtkWidget *dialog_action_area3;
  GtkWidget *button2;

  plugin_start_dialog = gtk_dialog_new ();
  gtk_object_set_data (GTK_OBJECT (plugin_start_dialog), "plugin_start_dialog", plugin_start_dialog);
  GTK_WINDOW (plugin_start_dialog)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_title (GTK_WINDOW (plugin_start_dialog), _("No plugin"));
  gtk_window_set_position (GTK_WINDOW (plugin_start_dialog), GTK_WIN_POS_MOUSE);
  gtk_window_set_policy (GTK_WINDOW (plugin_start_dialog), TRUE, TRUE, FALSE);

  dialog_vbox3 = GTK_DIALOG (plugin_start_dialog)->vbox;
  gtk_object_set_data (GTK_OBJECT (plugin_start_dialog), "dialog_vbox3", dialog_vbox3);
  gtk_widget_show (dialog_vbox3);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_vbox3), 2);

  label2 = gtk_label_new (_("\n\n  Click to execute plugin DLL.  \n  But,there is no installed plugin.  \n\n"));
  gtk_object_set_data (GTK_OBJECT (plugin_start_dialog), "label2", label2);
  gtk_widget_show (label2);
  gtk_box_pack_start (GTK_BOX (dialog_vbox3), label2, TRUE, TRUE, 0);

  dialog_action_area3 = GTK_DIALOG (plugin_start_dialog)->action_area;
  gtk_object_set_data (GTK_OBJECT (plugin_start_dialog), "dialog_action_area3", dialog_action_area3);
  gtk_widget_show (dialog_action_area3);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_action_area3), 10);

  button2 = gtk_button_new_with_label (_("   OK   "));
  gtk_object_set_data (GTK_OBJECT (plugin_start_dialog), "button2", button2);
  gtk_widget_show (button2);
  gtk_box_pack_start (GTK_BOX (dialog_action_area3), button2, FALSE, FALSE, 0);

  gtk_window_set_modal(GTK_WINDOW(plugin_start_dialog), TRUE);

  gtk_signal_connect (GTK_OBJECT (button2), "clicked",
                      GTK_SIGNAL_FUNC (on_close_clicked),
                      GTK_OBJECT (plugin_start_dialog));


  return plugin_start_dialog;
}

GtkWidget*
create_plugin_copy_dialog ()
{
  GtkWidget *plugin_copy_dialog;
  GtkWidget *dialog_vbox4;
  GtkWidget *label3;
  GtkWidget *dialog_action_area4;
  GtkWidget *button3;

  plugin_copy_dialog = gtk_dialog_new ();
  gtk_object_set_data (GTK_OBJECT (plugin_copy_dialog), "plugin_copy_dialog", plugin_copy_dialog);
  GTK_WINDOW (plugin_copy_dialog)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_title (GTK_WINDOW (plugin_copy_dialog), _("No plugin"));
  gtk_window_set_position (GTK_WINDOW (plugin_copy_dialog), GTK_WIN_POS_MOUSE);
  gtk_window_set_policy (GTK_WINDOW (plugin_copy_dialog), TRUE, TRUE, FALSE);

  dialog_vbox4 = GTK_DIALOG (plugin_copy_dialog)->vbox;
  gtk_object_set_data (GTK_OBJECT (plugin_copy_dialog), "dialog_vbox4", dialog_vbox4);
  gtk_widget_show (dialog_vbox4);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_vbox4), 2);

  label3 = gtk_label_new (_("\n\n  There is no installed plugin.  \n\n"));
  gtk_object_set_data (GTK_OBJECT (plugin_copy_dialog), "label3", label3);
  gtk_widget_show (label3);
  gtk_box_pack_start (GTK_BOX (dialog_vbox4), label3, TRUE, TRUE, 0);

  dialog_action_area4 = GTK_DIALOG (plugin_copy_dialog)->action_area;
  gtk_object_set_data (GTK_OBJECT (plugin_copy_dialog), "dialog_action_area4", dialog_action_area4);
  gtk_widget_show (dialog_action_area4);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_action_area4), 10);

  button3 = gtk_button_new_with_label (_("   OK   "));
  gtk_object_set_data (GTK_OBJECT (plugin_copy_dialog), "button3", button3);
  gtk_widget_show (button3);
  gtk_box_pack_start (GTK_BOX (dialog_action_area4), button3, FALSE, FALSE, 0);

  gtk_window_set_modal(GTK_WINDOW(plugin_copy_dialog), TRUE);

  gtk_signal_connect (GTK_OBJECT (button3), "clicked",
                      GTK_SIGNAL_FUNC (on_close_clicked),
                      GTK_OBJECT (plugin_copy_dialog));

  return plugin_copy_dialog;
}

GtkWidget*
create_help_dialog ()
{
  GtkWidget *help_dialog;
  GtkWidget *dialog_vbox5;
  GtkWidget *label_about;
  GtkWidget *dialog_action_area5;
  GtkWidget *button4;
  gchar *temp;

  help_dialog = gtk_dialog_new ();
  gtk_object_set_data (GTK_OBJECT (help_dialog), "help_dialog", help_dialog);
  GTK_WINDOW (help_dialog)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_title (GTK_WINDOW (help_dialog), _("HELP"));
  gtk_window_set_position (GTK_WINDOW (help_dialog), GTK_WIN_POS_MOUSE);
  gtk_window_set_policy (GTK_WINDOW (help_dialog), TRUE, TRUE, FALSE);

  dialog_vbox5 = GTK_DIALOG (help_dialog)->vbox;
  gtk_object_set_data (GTK_OBJECT (help_dialog), "dialog_vbox5", dialog_vbox5);
  gtk_widget_show (dialog_vbox5);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_vbox5), 2);

  temp=g_strconcat(_("\nHDBENCH clone\n\na Graphical Benchmark Software\n\nVer "),VERSION,_("\n\n   Copyright (C) 1999 Yuuki NINOMIYA   \n\nRead the documents to use.\n"),NULL);
  label_about = gtk_label_new (temp);
  gtk_object_set_data (GTK_OBJECT (help_dialog), "label_about", label_about);
  gtk_widget_show (label_about);
  gtk_box_pack_start (GTK_BOX (dialog_vbox5), label_about, TRUE, TRUE, 0);
  g_free(temp);

  dialog_action_area5 = GTK_DIALOG (help_dialog)->action_area;
  gtk_object_set_data (GTK_OBJECT (help_dialog), "dialog_action_area5", dialog_action_area5);
  gtk_widget_show (dialog_action_area5);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_action_area5), 10);

  button4 = gtk_button_new_with_label (_("   OK   "));
  gtk_object_set_data (GTK_OBJECT (help_dialog), "button4", button4);
  gtk_widget_show (button4);
  gtk_box_pack_start (GTK_BOX (dialog_action_area5), button4, FALSE, FALSE, 0);

  gtk_window_set_modal(GTK_WINDOW(help_dialog), TRUE);

  gtk_signal_connect (GTK_OBJECT (button4), "clicked",
                      GTK_SIGNAL_FUNC (on_close_clicked),
                      GTK_OBJECT (help_dialog));

  return help_dialog;
}


GtkWidget*
create_system_dialog ()
{
  GtkWidget *system_dialog;
  GtkWidget *dialog_vbox6;
  GtkWidget *vbox5;
  GtkWidget *hbox6;
  GtkWidget *pixmap1;
  GtkWidget *label6;
  GtkWidget *label24;
  GtkWidget *hbox7;
  GtkWidget *label7;
  GtkWidget *label17;
  GtkWidget *entry_os;
  GtkWidget *label25;
  GtkWidget *hbox8;
  GtkWidget *label8;
  GtkWidget *label16;
  GtkWidget *entry_cpu;
  GtkWidget *hbox9;
  GtkWidget *label9;
  GtkWidget *label18;
  GtkWidget *entry_vendor;
  GtkWidget *hbox10;
  GtkWidget *label10;
  GtkWidget *label19;
  GtkWidget *entry_family;
  GtkWidget *hbox11;
  GtkWidget *label11;
  GtkWidget *label20;
  GtkWidget *entry_model;
  GtkWidget *hbox12;
  GtkWidget *label12;
  GtkWidget *label21;
  GtkWidget *entry_stepping;
  GtkWidget *label26;
  GtkWidget *label13;
  GtkWidget *hbox13;
  GtkWidget *label14;
  GtkWidget *label22;
  GtkWidget *entry_totalmem;
  GtkWidget *hbox14;
  GtkWidget *label15;
  GtkWidget *label23;
  GtkWidget *entry_freemem;
  GtkWidget *label27;
  GtkWidget *dialog_action_area7;
  GtkWidget *vbox4;
  GtkWidget *hbox5;
  GtkWidget *system_ok_button;
  GtkWidget *system_copy_button;
  GtkWidget *label5;

  gint32 total_mem,free_mem;
  gchar *name;
  gchar *total_mem_str,*free_mem_str;
  gchar *vendor;
  gchar *family;
  gchar *model;
  gchar *stepping;
  gchar *buf;
  gchar *os_name;

  get_meminfo(&total_mem,&free_mem);
  get_cpuinfo(&name,&vendor,&family,&model,&stepping);
  get_osinfo(&os_name);

  total_mem_str=g_strdup_printf("%d Bytes",total_mem);
  free_mem_str=g_strdup_printf("%d Bytes",free_mem);

  system_dialog = gtk_dialog_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "system_dialog", system_dialog);
  gtk_widget_set_usize (system_dialog, 450, -2);
  GTK_WINDOW (system_dialog)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_title (GTK_WINDOW (system_dialog), _("SYSTEM"));
  gtk_window_set_position (GTK_WINDOW (system_dialog), GTK_WIN_POS_MOUSE);
  gtk_window_set_policy (GTK_WINDOW (system_dialog), TRUE, TRUE, FALSE);

  dialog_vbox6 = GTK_DIALOG (system_dialog)->vbox;
  gtk_object_set_data (GTK_OBJECT (system_dialog), "dialog_vbox6", dialog_vbox6);
  gtk_widget_show (dialog_vbox6);
  gtk_widget_set_usize (dialog_vbox6, 276, -2);

  vbox5 = gtk_vbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "vbox5", vbox5);
  gtk_widget_show (vbox5);
  gtk_box_pack_start (GTK_BOX (dialog_vbox6), vbox5, TRUE, TRUE, 0);

  hbox6 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox6", hbox6);
  gtk_widget_show (hbox6);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox6, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox6), 10);

  pixmap1 = create_pixmap (system_dialog, "disk.xpm");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "pixmap1", pixmap1);
  gtk_widget_show (pixmap1);
  gtk_box_pack_start (GTK_BOX (hbox6), pixmap1, FALSE, TRUE, 0);

  buf=g_strdup_printf(_("HDBENCH clone Ver %s"),VERSION);
  label6 = gtk_label_new (buf);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label6", label6);
  gtk_widget_show (label6);
  gtk_box_pack_start (GTK_BOX (hbox6), label6, FALSE, FALSE, 0);
  gtk_misc_set_padding (GTK_MISC (label6), 10, 0);
  g_free(buf);

  label24 = gtk_label_new ("");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label24", label24);
  gtk_widget_show (label24);
  gtk_box_pack_start (GTK_BOX (vbox5), label24, FALSE, FALSE, 0);

  hbox7 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox7", hbox7);
  gtk_widget_show (hbox7);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox7, TRUE, TRUE, 0);

  label7 = gtk_label_new (_(" OS"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label7", label7);
  gtk_widget_show (label7);
  gtk_box_pack_start (GTK_BOX (hbox7), label7, FALSE, FALSE, 0);
  gtk_widget_set_usize (label7, 100, -2);
  gtk_misc_set_alignment (GTK_MISC (label7), 0, 0.5);

  label17 = gtk_label_new (":");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label17", label17);
  gtk_widget_show (label17);
  gtk_box_pack_start (GTK_BOX (hbox7), label17, FALSE, FALSE, 0);

  entry_os = gtk_entry_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "entry_os", entry_os);
  gtk_widget_show (entry_os);
  gtk_box_pack_start (GTK_BOX (hbox7), entry_os, TRUE, TRUE, 5);
  gtk_entry_set_editable (GTK_ENTRY (entry_os), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry_os), os_name);

  label25 = gtk_label_new ("");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label25", label25);
  gtk_widget_show (label25);
  gtk_box_pack_start (GTK_BOX (vbox5), label25, FALSE, FALSE, 0);

  hbox8 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox8", hbox8);
  gtk_widget_show (hbox8);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox8, FALSE, TRUE, 0);

  label8 = gtk_label_new (_(" CPU"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label8", label8);
  gtk_widget_show (label8);
  gtk_box_pack_start (GTK_BOX (hbox8), label8, FALSE, FALSE, 0);
  gtk_widget_set_usize (label8, 100, -2);
  gtk_misc_set_alignment (GTK_MISC (label8), 0, 0.5);

  label16 = gtk_label_new (":");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label16", label16);
  gtk_widget_show (label16);
  gtk_box_pack_start (GTK_BOX (hbox8), label16, FALSE, FALSE, 0);

  entry_cpu = gtk_entry_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "entry_cpu", entry_cpu);
  gtk_widget_show (entry_cpu);
  gtk_box_pack_start (GTK_BOX (hbox8), entry_cpu, TRUE, TRUE, 5);
  gtk_entry_set_editable (GTK_ENTRY (entry_cpu), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry_cpu), name);

  hbox9 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox9", hbox9);
  gtk_widget_show (hbox9);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox9, TRUE, TRUE, 0);

  label9 = gtk_label_new (_(" Vendor"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label9", label9);
  gtk_widget_show (label9);
  gtk_box_pack_start (GTK_BOX (hbox9), label9, FALSE, FALSE, 0);
  gtk_widget_set_usize (label9, 100, -2);
  gtk_misc_set_alignment (GTK_MISC (label9), 0, 0.5);

  label18 = gtk_label_new (":");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label18", label18);
  gtk_widget_show (label18);
  gtk_box_pack_start (GTK_BOX (hbox9), label18, FALSE, FALSE, 0);

  entry_vendor = gtk_entry_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "entry_vendor", entry_vendor);
  gtk_widget_show (entry_vendor);
  gtk_box_pack_start (GTK_BOX (hbox9), entry_vendor, TRUE, TRUE, 5);
  gtk_entry_set_editable (GTK_ENTRY (entry_vendor), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry_vendor), vendor);

  hbox10 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox10", hbox10);
  gtk_widget_show (hbox10);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox10, TRUE, TRUE, 0);

  label10 = gtk_label_new (_(" Family"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label10", label10);
  gtk_widget_show (label10);
  gtk_box_pack_start (GTK_BOX (hbox10), label10, FALSE, FALSE, 0);
  gtk_widget_set_usize (label10, 100, -2);
  gtk_misc_set_alignment (GTK_MISC (label10), 0, 0.5);

  label19 = gtk_label_new (":");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label19", label19);
  gtk_widget_show (label19);
  gtk_box_pack_start (GTK_BOX (hbox10), label19, FALSE, FALSE, 0);

  entry_family = gtk_entry_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "entry_family", entry_family);
  gtk_widget_show (entry_family);
  gtk_box_pack_start (GTK_BOX (hbox10), entry_family, TRUE, TRUE, 5);
  gtk_entry_set_editable (GTK_ENTRY (entry_family), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry_family), family);

  hbox11 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox11", hbox11);
  gtk_widget_show (hbox11);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox11, TRUE, TRUE, 0);

  label11 = gtk_label_new (_(" Model"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label11", label11);
  gtk_widget_show (label11);
  gtk_box_pack_start (GTK_BOX (hbox11), label11, FALSE, FALSE, 0);
  gtk_widget_set_usize (label11, 100, -2);
  gtk_misc_set_alignment (GTK_MISC (label11), 0, 0.5);

  label20 = gtk_label_new (":");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label20", label20);
  gtk_widget_show (label20);
  gtk_box_pack_start (GTK_BOX (hbox11), label20, FALSE, FALSE, 0);

  entry_model = gtk_entry_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "entry_model", entry_model);
  gtk_widget_show (entry_model);
  gtk_box_pack_start (GTK_BOX (hbox11), entry_model, TRUE, TRUE, 5);
  gtk_entry_set_editable (GTK_ENTRY (entry_model), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry_model), model);

  hbox12 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox12", hbox12);
  gtk_widget_show (hbox12);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox12, TRUE, TRUE, 0);

  label12 = gtk_label_new (_(" Stepping"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label12", label12);
  gtk_widget_show (label12);
  gtk_box_pack_start (GTK_BOX (hbox12), label12, FALSE, FALSE, 0);
  gtk_widget_set_usize (label12, 100, -2);
  gtk_misc_set_alignment (GTK_MISC (label12), 0, 0.5);

  label21 = gtk_label_new (":");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label21", label21);
  gtk_widget_show (label21);
  gtk_box_pack_start (GTK_BOX (hbox12), label21, FALSE, FALSE, 0);

  entry_stepping = gtk_entry_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "entry_stepping", entry_stepping);
  gtk_widget_show (entry_stepping);
  gtk_box_pack_start (GTK_BOX (hbox12), entry_stepping, TRUE, TRUE, 5);
  gtk_entry_set_editable (GTK_ENTRY (entry_stepping), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry_stepping), stepping);

  label26 = gtk_label_new ("");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label26", label26);
  gtk_widget_show (label26);
  gtk_box_pack_start (GTK_BOX (vbox5), label26, FALSE, FALSE, 0);

  label13 = gtk_label_new (_(" Memory"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label13", label13);
  gtk_widget_show (label13);
  gtk_box_pack_start (GTK_BOX (vbox5), label13, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label13), 0, 0.5);

  hbox13 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox13", hbox13);
  gtk_widget_show (hbox13);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox13, TRUE, TRUE, 0);

  label14 = gtk_label_new (_("  Total"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label14", label14);
  gtk_widget_show (label14);
  gtk_box_pack_start (GTK_BOX (hbox13), label14, FALSE, FALSE, 0);
  gtk_widget_set_usize (label14, 100, -2);
  gtk_misc_set_alignment (GTK_MISC (label14), 0, 0.5);

  label22 = gtk_label_new (":");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label22", label22);
  gtk_widget_show (label22);
  gtk_box_pack_start (GTK_BOX (hbox13), label22, FALSE, FALSE, 0);

  entry_totalmem = gtk_entry_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "entry_totalmem", entry_totalmem);
  gtk_widget_show (entry_totalmem);
  gtk_box_pack_start (GTK_BOX (hbox13), entry_totalmem, TRUE, TRUE, 5);
  gtk_entry_set_editable (GTK_ENTRY (entry_totalmem), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry_totalmem), total_mem_str);

  hbox14 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox14", hbox14);
  gtk_widget_show (hbox14);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox14, TRUE, TRUE, 0);

  label15 = gtk_label_new (_("  Free"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label15", label15);
  gtk_widget_show (label15);
  gtk_box_pack_start (GTK_BOX (hbox14), label15, FALSE, FALSE, 0);
  gtk_widget_set_usize (label15, 100, -2);
  gtk_misc_set_alignment (GTK_MISC (label15), 0, 0.5);

  label23 = gtk_label_new (":");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label23", label23);
  gtk_widget_show (label23);
  gtk_box_pack_start (GTK_BOX (hbox14), label23, FALSE, FALSE, 0);

  entry_freemem = gtk_entry_new ();
  gtk_object_set_data (GTK_OBJECT (system_dialog), "entry_freemem", entry_freemem);
  gtk_widget_show (entry_freemem);
  gtk_box_pack_start (GTK_BOX (hbox14), entry_freemem, TRUE, TRUE, 5);
  gtk_entry_set_editable (GTK_ENTRY (entry_freemem), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry_freemem), free_mem_str);

  label27 = gtk_label_new ("");
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label27", label27);
  gtk_widget_show (label27);
  gtk_box_pack_start (GTK_BOX (vbox5), label27, FALSE, FALSE, 0);

  dialog_action_area7 = GTK_DIALOG (system_dialog)->action_area;
  gtk_object_set_data (GTK_OBJECT (system_dialog), "dialog_action_area7", dialog_action_area7);
  gtk_widget_show (dialog_action_area7);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_action_area7), 5);

  vbox4 = gtk_vbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "vbox4", vbox4);
  gtk_widget_show (vbox4);
  gtk_box_pack_start (GTK_BOX (dialog_action_area7), vbox4, TRUE, TRUE, 0);

  hbox5 = gtk_hbox_new (FALSE, 0);
  gtk_object_set_data (GTK_OBJECT (system_dialog), "hbox5", hbox5);
  gtk_widget_show (hbox5);
  gtk_box_pack_start (GTK_BOX (vbox4), hbox5, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox5), 5);

  system_ok_button = gtk_button_new_with_label (_("   OK   "));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "system_ok_button", system_ok_button);
  gtk_widget_show (system_ok_button);
  gtk_box_pack_start (GTK_BOX (hbox5), system_ok_button, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (system_ok_button), 2);

  system_copy_button = gtk_button_new_with_label (_("  Copy  "));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "system_copy_button", system_copy_button);
  gtk_widget_show (system_copy_button);
  gtk_box_pack_start (GTK_BOX (hbox5), system_copy_button, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (system_copy_button), 2);

  label5 = gtk_label_new (_("Copyright (C) 1999 Yuuki NINOMIYA"));
  gtk_object_set_data (GTK_OBJECT (system_dialog), "label5", label5);
  gtk_widget_show (label5);
  gtk_box_pack_start (GTK_BOX (vbox4), label5, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label5), 0.3, 0.5);
  gtk_misc_set_padding (GTK_MISC (label5), 0, 5);

  gtk_signal_connect (GTK_OBJECT (system_ok_button), "clicked",
                      GTK_SIGNAL_FUNC (on_close_clicked),
                      GTK_OBJECT (system_dialog));
  gtk_signal_connect (GTK_OBJECT (system_copy_button), "clicked",
                      GTK_SIGNAL_FUNC (on_system_copy_button_clicked),
                      NULL);

  gtk_window_set_modal(GTK_WINDOW(system_dialog), TRUE);

  g_free(name);
  g_free(total_mem_str);
  g_free(free_mem_str);
  g_free(vendor);
  g_free(family);
  g_free(model);
  g_free(stepping);
  g_free(os_name);

  return system_dialog;
}

