/* 
 * Proview   $Id: xtt_fileview_gtk.cpp,v 1.1 2008-04-25 11:08:06 claes Exp $
 * Copyright (C) 2005 SSAB Oxel�sund AB.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 2 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with the program, if not, write to the Free Software 
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "pwr.h"
#include "rt_gdh.h"
#include "co_wow_gtk.h"
#include "co_lng.h"
#include "xtt_fileview_gtk.h"
#include "xtt_xnav.h"

void XttFileviewGtk::execute( char *file)
{
  pwr_tStatus sts;
  pwr_tFileName fname;

  strcpy( fname, dir);
  strcat( fname, "/");
  strcat( fname, file);

  sts = gdh_SetObjectInfo( target_attr, fname, 80);
  if ( EVEN(sts)) {
    printf( "** Fileview: unable to set target %s\n", target_attr);
    return;
  }

  pwr_tBoolean b = 1;
  sts = gdh_SetObjectInfo( trigger_attr, &b, sizeof(b));
  if ( EVEN(sts)) {
    printf( "** Fileview: unable to set trigger %s\n", trigger_attr);
    return;
  }
}

void XttFileviewGtk::list_cursor_changed_cb( GtkTreeView *tree_view, 
					     gpointer data)
{
  XttFileviewGtk *fileview = (XttFileviewGtk *) data;

  if ( fileview->type == fileview_eType_Save) {
    char		*text;
    static char   selected_text[80];
    GtkTreeIter   iter;
    GtkTreeModel  *store;
  
    g_object_get( fileview->list, "model", &store, NULL);

    GtkTreeSelection *selection = gtk_tree_view_get_selection( 
				  GTK_TREE_VIEW(fileview->list));
    if ( gtk_tree_selection_get_selected( selection, NULL, &iter)) {
      gtk_tree_model_get( GTK_TREE_MODEL( store), &iter, 0, 
			  &text, -1);
      strcpy( selected_text, text);
    }
    gint pos = 0;
    gtk_editable_delete_text( GTK_EDITABLE(fileview->input_text), 0, -1);
    gtk_editable_insert_text( GTK_EDITABLE(fileview->input_text), selected_text, 
			      strlen(selected_text), &pos);
    // Select the text
    gtk_editable_set_position( GTK_EDITABLE(fileview->input_text), -1);
    gtk_editable_select_region( GTK_EDITABLE(fileview->input_text), 0, -1);    
  }
}

void XttFileviewGtk::list_row_activated_cb( GtkTreeView *tree_view, 
					    GtkTreePath *path,
					    GtkTreeViewColumn *column,
					    gpointer data)
{
  list_ok_cb( 0, data);
}

void XttFileviewGtk::list_input_cb ( GtkWidget *w, 
				     gpointer data)
{
  list_ok_cb( 0, data);
}

void XttFileviewGtk::list_ok_cb ( GtkWidget *w, 
				  gpointer data)
{
  XttFileviewGtk *fileview = (XttFileviewGtk *) data;

  if ( fileview->type == fileview_eType_Open) {
    char		*text;
    static char   selected_text[80];
    GtkTreeIter   iter;
    GtkTreeModel  *store;
  
    // Get selected tree entry
    g_object_get( fileview->list, "model", &store, NULL);

    GtkTreeSelection *selection = gtk_tree_view_get_selection( 
			  GTK_TREE_VIEW(fileview->list));
    if ( gtk_tree_selection_get_selected( selection, NULL, &iter)) {
      gtk_tree_model_get( GTK_TREE_MODEL( store), &iter, 0, 
			  &text, -1);
      strcpy( selected_text, text);
    }

    char *textiso = g_convert( selected_text, -1, "ISO8859-1", "UTF-8", NULL, NULL, NULL);
    strcpy( selected_text, textiso);
    g_free( textiso);

    fileview->execute( selected_text);
  }
  else {
    // Get value from text entry
    char 	*text, *textutf8;
    bool	file_exist = false;

    textutf8 = gtk_editable_get_chars( GTK_EDITABLE(fileview->input_text), 0, -1);
    text = g_convert( textutf8, -1, "ISO8859-1", "UTF-8", NULL, NULL, NULL);
    g_free( textutf8);

    for ( int i = 0; i < fileview->filecnt; i++) {
      if ( strcmp( fileview->filelist[i], text) == 0) {
	file_exist = true;
	break;
      }
    }
    if ( file_exist) {
      char msg[200];

      strcpy( fileview->selected_file, text);
      sprintf( msg, "%s %s\n", 
	       text, Lng::translate("already exists"));
      sprintf( &msg[strlen(msg)], "%s",
	       Lng::translate("Do you want to replace it"));
      ((XNav *)fileview->parent_ctx)->wow->DisplayQuestion( fileview, 
							    Lng::translate("File already exists"),
							    msg, list_save_cb, 0, 0);
      return;
    }
    fileview->execute( text);

  }
  gtk_widget_destroy( fileview->toplevel);
  free( fileview->filelist);
  delete fileview;
}

void XttFileviewGtk::list_save_cb( void *ctx, void *data)
{
  XttFileviewGtk *fileview = (XttFileviewGtk *) ctx;

  fileview->execute( fileview->selected_file);

  gtk_widget_destroy( fileview->toplevel);
  free( fileview->filelist);
  delete fileview;
}
				  
void XttFileviewGtk::list_cancel_cb (
  GtkWidget *w, 
  gpointer data
)
{
  XttFileviewGtk *fileview = (XttFileviewGtk *) data;
  
  gtk_widget_destroy( fileview->toplevel);
  free( fileview->filelist);
  delete fileview;
}

static gboolean list_action_inputfocus( GtkWidget *w, GdkEvent *event, gpointer data)
{
  gtk_window_present( GTK_WINDOW(w));
  return FALSE;
}

XttFileviewGtk::XttFileviewGtk( void *xn_parent_ctx, GtkWidget *xn_parent_wid, pwr_tOid xn_oid,
				char *xn_title, char *xn_dir, char *xn_pattern, int xn_type,
				char *xn_target_attr, char *xn_trigger_attr) :
  filelist(0), parent_ctx( xn_parent_ctx), oid(xn_oid), type(xn_type)
{
  pwr_tStatus sts;
  GtkListStore *store;
  GtkTreeIter iter;
  GtkCellRenderer *text_renderer;
  GtkTreeViewColumn *name_column;
  char ok_text[20];
 
  strncpy( dir, xn_dir, sizeof(dir));
  strncpy( pattern, xn_pattern, sizeof(pattern));
  strncpy( target_attr, xn_target_attr, sizeof(target_attr));
  strncpy( trigger_attr, xn_trigger_attr, sizeof(trigger_attr));
  strcpy( selected_file, "");

  sts = gdh_SearchFile( oid, dir, pattern, &filelist, &filecnt);
  if ( type == fileview_eType_Open && (EVEN(sts) || filecnt == 0))
    return;

  toplevel = (GtkWidget *) g_object_new( GTK_TYPE_WINDOW, 
					      "default-height", 500,
					      "default-width", 500,
					      "title", CoWowGtk::translate_utf8(xn_title),
					      "window-position", GTK_WIN_POS_CENTER,
					      NULL);

  g_signal_connect( toplevel, "focus-in-event", G_CALLBACK(list_action_inputfocus), this);


  store = gtk_list_store_new( 1, G_TYPE_STRING);

  for ( int i = 0; i < filecnt; i++) {
    char *nameutf8 = g_convert( filelist[i], -1, "UTF-8", "ISO8859-1", NULL, NULL, NULL);

    gtk_list_store_append( store, &iter);
    gtk_list_store_set( store, &iter, 0, nameutf8, -1);
    g_free( nameutf8);
  }

  list = (GtkWidget *) g_object_new(GTK_TYPE_TREE_VIEW,
				 "model", store,
				 "rules-hint", TRUE,
				 "headers-clickable", TRUE,
				 "reorderable", TRUE,
				 "enable-search", TRUE,
				 "search-column", 0,
				 "headers-visible", FALSE,
				 NULL);

  text_renderer = gtk_cell_renderer_text_new();
  name_column = gtk_tree_view_column_new_with_attributes( "",
							  text_renderer,
							  "text", 0,
							  NULL);
  g_object_set( name_column,
		"resizable", TRUE,
		"clickable", TRUE,
		NULL);

  gtk_tree_view_append_column( GTK_TREE_VIEW(list), name_column);
  g_signal_connect( list, "row-activated", 
 		    G_CALLBACK(XttFileviewGtk::list_row_activated_cb), this);
  g_signal_connect( list, "cursor-changed", 
 		    G_CALLBACK(XttFileviewGtk::list_cursor_changed_cb), this);

  if ( type == fileview_eType_Save)
    strcpy( ok_text, "Save");
  else
    strcpy( ok_text, "Open");
    
  GtkWidget *ok_button = gtk_button_new_with_label( CoWowGtk::translate_utf8(ok_text));
  gtk_widget_set_size_request( ok_button, 70, 28);
  g_signal_connect( ok_button, "clicked", 
 		    G_CALLBACK(XttFileviewGtk::list_ok_cb), this);

  GtkWidget *cancel_button = gtk_button_new_with_label( CoWowGtk::translate_utf8("Cancel"));
  gtk_widget_set_size_request( cancel_button, 70, 28);
  g_signal_connect( cancel_button, "clicked", 
 		    G_CALLBACK(XttFileviewGtk::list_cancel_cb), this);

  input_text = gtk_entry_new();
  g_signal_connect( input_text, "activate",
  		    G_CALLBACK(XttFileviewGtk::list_input_cb), this);
  GtkWidget *input_label = gtk_label_new( CoWowGtk::translate_utf8("Save as"));

  GtkWidget *hboxentry = gtk_hbox_new( FALSE, 40);
  gtk_box_pack_start( GTK_BOX(hboxentry), input_label, FALSE, FALSE, 15);
  gtk_box_pack_end( GTK_BOX(hboxentry), input_text, TRUE, TRUE, 15);

  GtkWidget *hboxbuttons = gtk_hbox_new( TRUE, 40);
  gtk_box_pack_start( GTK_BOX(hboxbuttons), ok_button, FALSE, FALSE, 20);
  gtk_box_pack_end( GTK_BOX(hboxbuttons), cancel_button, FALSE, FALSE, 20);

  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL);
  gtk_container_add( GTK_CONTAINER( scrolled_window), list);

  GtkWidget *vbox = gtk_vbox_new( FALSE, 0);
  gtk_box_pack_start( GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 30);
  if ( type == fileview_eType_Save) {
    gtk_box_pack_start( GTK_BOX(vbox), hboxentry, FALSE, FALSE, 10);
    gtk_box_pack_start( GTK_BOX(vbox), gtk_hseparator_new(), FALSE, FALSE, 0);
  }
  gtk_box_pack_end( GTK_BOX(vbox), hboxbuttons, FALSE, FALSE, 10);

  gtk_container_add( GTK_CONTAINER(toplevel), vbox);
  gtk_widget_show_all( toplevel);

  // GtkTreeSelection *selection = gtk_tree_view_get_selection( GTK_TREE_VIEW(list));
  // gtk_tree_selection_set_mode( selection, GTK_SELECTION_SINGLE);

  // Set input focus to the scrolled list widget
  gtk_widget_grab_focus( list);
}
