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

#ifndef SELECTION_H_INCLUDED
#define SELECTION_H_INCLUDED

#include <gtk/gtk.h>


typedef enum {
  SEL_TYPE_NONE,
  APPLE_PICT,
  ATOM,
  ATOM_PAIR,
  BITMAP,
  C_STRING,
  COLORMAP,
  COMPOUND_TEXT,
  DRAWABLE,
  INTEGER,
  PIXEL,
  PIXMAP,
  SPAN,
  STRING,
  TEXT,
  WINDOW,
  LAST_SEL_TYPE
} SelType;

GdkAtom seltypes[LAST_SEL_TYPE];

typedef struct _Target {
  gchar *target_name;
  SelType type;
  GdkAtom target;
  gint format;
} Target;

/* The following is a list of all the selection targets defined
   in the ICCCM */

Target targets[]={
  { "ADOBE_PORTABLE_DOCUMENT_FORMAT",       STRING,        0, 8 },
  { "APPLE_PICT",                           APPLE_PICT,    0, 8 },
  { "BACKGROUND",                           PIXEL,         0, 32 },
  { "BITMAP",                               BITMAP,        0, 32 },
  { "CHARACTER_POSITION",                   SPAN,          0, 32 },
  { "CLASS",                                TEXT,          0, 8 },
  { "CLIENT_WINDOW",                        WINDOW,        0, 32 },
  { "COLORMAP",                             COLORMAP,      0, 32 },
  { "COLUMN_NUMBER",                        SPAN,          0, 32 },
  { "COMPOUND_TEXT",                        COMPOUND_TEXT, 0, 8 },
  /*  { "DELETE", "NULL", 0, ? }, */
  { "DRAWABLE",                             DRAWABLE,      0, 32 },
  { "ENCAPSULATED_POSTSCRIPT",              STRING,        0, 8 },
  { "ENCAPSULATED_POSTSCRIPT_INTERCHANGE",  STRING,        0, 8 },
  { "FILE_NAME",                            TEXT,          0, 8 },
  { "FOREGROUND",                           PIXEL,         0, 32 },
  { "HOST_NAME",                            TEXT,          0, 8 },
  /*  { "INSERT_PROPERTY", "NULL", 0, ? NULL }, */
  /*  { "INSERT_SELECTION", "NULL", 0, ? NULL }, */
  { "LENGTH",                               INTEGER,       0, 32 },
  { "LINE_NUMBER",                          SPAN,          0, 32 },
  { "LIST_LENGTH",                          INTEGER,       0, 32 },
  { "MODULE",                               TEXT,          0, 8 },
  /*  { "MULTIPLE", "ATOM_PAIR", 0, 32 }, */
  { "NAME",                                 TEXT,          0, 8 },
  { "ODIF",                                 TEXT,          0, 8 },
  { "OWNER_OS",                             TEXT,          0, 8 },
  { "PIXMAP",                               PIXMAP,        0, 32 },
  { "POSTSCRIPT",                           STRING,        0, 8 },
  { "PROCEDURE",                            TEXT,          0, 8 },
  { "PROCESS",                              INTEGER,       0, 32 },
  { "STRING",                               STRING,        0, 8 },
  { "TARGETS",                              ATOM,          0, 32 },
  { "TASK",                                 INTEGER,       0, 32 },
  { "TEXT",                                 TEXT,          0, 8  },
  { "TIMESTAMP",                            INTEGER,       0, 32 },
  { "USER",                                 TEXT,          0, 8 },
};

int num_targets=sizeof(targets)/sizeof(Target);

#endif /* SELECTION_H_INCLUDED */

