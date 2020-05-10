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

#define GLOBAL_VALUE_DEFINE

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "intl.h"
#include "shhopt.h"
#include "proto.h"
#include "variable.h"


int main(int argc, char *argv[])
{
	GtkWidget *main_window;
	gchar *temp;

	optStruct opt[] =
	{
		/* short long        type      var/func     special */
		{  'h', "help",    OPT_FLAG,   put_usage,   OPT_CALLFUNC},
		{  'V', "version", OPT_FLAG,   put_version, OPT_CALLFUNC},
		{  'f', "font",    OPT_STRING, &font_name,  0},
		{  't', "text",    OPT_STRING, &video_text, 0},
		{0, 0, OPT_END, 0, 0}	/* no more options */
	};


#ifdef ENABLE_NLS
	bindtextdomain(PACKAGE, PACKAGE_LOCALE_DIR);
	textdomain(PACKAGE);
#endif

	optParseOptions(&argc, argv, opt, 0);

	gtk_set_locale();
	gtk_init(&argc, &argv);

	init_atoms();

	add_pixmap_directory(PACKAGE_DATA_DIR "/pixmaps");
	add_pixmap_directory(PACKAGE_SOURCE_DIR "/pixmaps");

	temp = g_strconcat(getenv("HOME"), "/.gtkrc", NULL);
	gtk_rc_parse(temp);
	g_free(temp);

	main_window = create_main_window();
	gtk_widget_show(main_window);

	gtk_main();
	return 0;
}


void put_usage(void)
{
	printf(_("\
HDBENCH clone Ver %s Copyright (C) 1999 Yuuki NINOMIYA\n\n\
This is free software with ABSOLUTELY NO WARRANTY.\n\
For details please see the file COPYING.\n\n\
usage: hdbench [OPTIONS]\n\
\n\
options:\n\
  -h | --help          display this help and exit\n\
  -f | --font=FONT     font name used in TEXT of VIDEO\n\
  -t | --text=TEXT     string written in TEXT of VIDEO\n\
  -V | --version       display version infomation and exit\n\
\n"), VERSION);

	exit(0);
}


void put_version(void)
{
	printf(_("HDBENCH clone Ver %s Copyright (C) 1999 Yuuki NINOMIYA\n"), VERSION);
	exit(0);
}

