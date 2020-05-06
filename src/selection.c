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

/*
 * Original version is made by Peter Mattis, Spencer Kimball and Josh MacDonald,
 * the GTK+ Team and others 1997-1999.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif  

#include <string.h>
#include "selection.h"
#include "variable.h"
#include "proto.h"


GtkTargetEntry targetlist[] = {
    { "STRING",        0, STRING },
    { "TEXT",          0, TEXT },
    { "COMPOUND_TEXT", 0, COMPOUND_TEXT }
};
gint ntargets = sizeof(targetlist) / sizeof(targetlist[0]);


void
init_atoms (void)
{
  int i;

  seltypes[SEL_TYPE_NONE] = GDK_NONE;
  seltypes[APPLE_PICT] = gdk_atom_intern ("APPLE_PICT",FALSE);
  seltypes[ATOM]       = gdk_atom_intern ("ATOM",FALSE);
  seltypes[ATOM_PAIR]  = gdk_atom_intern ("ATOM_PAIR",FALSE);
  seltypes[BITMAP]     = gdk_atom_intern ("BITMAP",FALSE);
  seltypes[C_STRING]   = gdk_atom_intern ("C_STRING",FALSE);
  seltypes[COLORMAP]   = gdk_atom_intern ("COLORMAP",FALSE);
  seltypes[COMPOUND_TEXT] = gdk_atom_intern ("COMPOUND_TEXT",FALSE);
  seltypes[DRAWABLE]   = gdk_atom_intern ("DRAWABLE",FALSE);
  seltypes[INTEGER]    = gdk_atom_intern ("INTEGER",FALSE);
  seltypes[PIXEL]      = gdk_atom_intern ("PIXEL",FALSE);
  seltypes[PIXMAP]     = gdk_atom_intern ("PIXMAP",FALSE);
  seltypes[SPAN]       = gdk_atom_intern ("SPAN",FALSE);
  seltypes[STRING]     = gdk_atom_intern ("STRING",FALSE);
  seltypes[TEXT]       = gdk_atom_intern ("TEXT",FALSE);
  seltypes[WINDOW]     = gdk_atom_intern ("WINDOW",FALSE);

  for (i=0; i<num_targets; i++)
    targets[i].target = gdk_atom_intern (targets[i].target_name, FALSE);
}


void
selection_get (GtkWidget *widget, 
               GtkSelectionData *selection_data,
               guint      info,
               guint      time,
               gpointer   data)
{
  gint len;
  GdkAtom type = GDK_NONE;

  if (selection_buffer==NULL)
    {
      len = 0;
    }      
  else
    {
      len = strlen(selection_buffer);
    }

  switch (info)
    {
    case COMPOUND_TEXT:
    case TEXT:
      type = gdk_atom_intern ("COMPOUND_TEXT",FALSE);
    case STRING:
      type = gdk_atom_intern ("STRING",FALSE);
    }
  
  gtk_selection_data_set (selection_data, type, 8, selection_buffer, len);
}

