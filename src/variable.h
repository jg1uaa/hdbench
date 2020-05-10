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

#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED

#ifdef	GLOBAL_VALUE_DEFINE
#define	GLOBAL
#define	GLOBAL_VAL(v) =(v)
#else
#define	GLOBAL extern
#define	GLOBAL_VAL(v)  /* */
#endif


#define SPRITES 1000
#define SPRITE_SIZE 30
#define SPRITE_BORDER 5
#define VIDEO_WIN_X 640
#define VIDEO_WIN_Y 480

struct CPU_Result{
	gint32 integer;
	gint32 floatp;
	gint32 memory;
};

struct Video_Result{
	gint32 rectangle;
	gint32 circle;
	gint32 text;
	gint32 scroll;
	gint32 image;
};

struct Disk_Result {
	gint32 read;
	gint32 write;
};

GLOBAL volatile gint done_flag;
GLOBAL gint disk_capacity GLOBAL_VAL(10);
GLOBAL gchar *font_name GLOBAL_VAL("-adobe-helvetica-medium-r-*--14-*");
GLOBAL gchar *video_text GLOBAL_VAL("HDBENCH clone");
GLOBAL const gchar *disk_drive;
GLOBAL gint32 result_all;
GLOBAL gint32 result_integer;
GLOBAL gint32 result_float;
GLOBAL gint32 result_memory;
GLOBAL gint32 result_rectangle;
GLOBAL gint32 result_circle;
GLOBAL gint32 result_text;
GLOBAL gint32 result_scroll;
GLOBAL gint32 result_image;
GLOBAL gint32 result_read;
GLOBAL gint32 result_write;
GLOBAL gchar *selection_buffer;
GLOBAL gint io_check_tag;

GLOBAL GtkWidget *main_window;
GLOBAL GtkWidget *bench_func_all;
GLOBAL GtkWidget *bench_func_cpu;
GLOBAL GtkWidget *bench_func_video;
GLOBAL GtkWidget *bench_func_disk;
GLOBAL GtkWidget *main_func_exit;
GLOBAL GtkWidget *main_func_copy;
GLOBAL GtkWidget *main_func_print;
GLOBAL GtkWidget *main_func_system;
GLOBAL GtkWidget *main_func_graph;
GLOBAL GtkWidget *main_func_help;
GLOBAL GtkWidget *plugin_option_menu;
GLOBAL GtkWidget *plugin_start;
GLOBAL GtkWidget *plugin_option;
GLOBAL GtkWidget *plugin_copy;
GLOBAL GtkWidget *opt_read;
GLOBAL GtkWidget *opt_drivecopy;
GLOBAL GtkWidget *opt_resultonly;
GLOBAL GtkWidget *opt_cdrom;
GLOBAL GtkWidget *opt_image;
GLOBAL GtkWidget *drive_combo;
GLOBAL GtkWidget *capacity_option_menu;

GLOBAL GtkWidget *bench_total_score;
GLOBAL GtkWidget *bench_float_score;
GLOBAL GtkWidget *bench_integer_score;
GLOBAL GtkWidget *bench_memory_score;
GLOBAL GtkWidget *bench_rectangle_score;
GLOBAL GtkWidget *bench_circle_score;
GLOBAL GtkWidget *bench_text_score;
GLOBAL GtkWidget *bench_scroll_score;
GLOBAL GtkWidget *bench_image_score;
GLOBAL GtkWidget *bench_read_score;
GLOBAL GtkWidget *bench_write_score;
GLOBAL GtkWidget *bench_plugin_score;
GLOBAL GtkWidget *measuring_all;
GLOBAL GtkWidget *measuring_cpu;
GLOBAL GtkWidget *measuring_video;
GLOBAL GtkWidget *measuring_disk;


#undef	GLOBAL
#undef	GLOBAL_VAL
#endif /* VARIABLE_H_INCLUDED */

