/*****************************************************
 *                                                   *
 *      Menu                                         *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2015                        *
 *                                                   *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;

gchar              *winTitle    = "Criação de um menus" ;

long int            xlen        = 350 ;
long int            ylen        = 200 ;


gboolean 
cb_func_new (GtkWidget *widget , 
	     gpointer   data   )
{
  printf ("Actuou no menu 'File' 'item' 'New'\n");

  return FALSE;
}


gboolean 
cb_func_open (GtkWidget *widget , 
	      gpointer   data   )
{
  printf ("Actuou no menu 'File' 'item' 'Open'\n");

  return FALSE;
}

gboolean 
cb_func_help (GtkWidget *widget , 
	      gpointer   data   )
{
  printf ("Actuou no menu 'Help' 'item' 'Help'\n");

  return FALSE;
}


gboolean 
cb_func_about (GtkWidget *widget , 
	       gpointer   data   )
{
  printf ("Actuou no menu 'Help' 'item' 'About'\n");

  return FALSE;
}

gboolean 
cb_func_item1 (GtkWidget *widget , 
	       gpointer   data   )
{
  printf ("Actuou no menu 'View' 'item' 'Item 1'\n");

  return FALSE;
}

GtkWidget *
cria_barra_de_menus (GtkWidget *window)
{
  GtkWidget *menubar, *mib_file, *menu_file, *mi_quit, *mi_new, *mi_open, *mi_sep ;
  GtkWidget *mib_view, *menu_view, *mi_item1 ;
  GtkWidget *mib_help, *menu_help, *mi_help, *mi_about ;
  GtkAccelGroup *accel_group = NULL;

  accel_group = gtk_accel_group_new ();
  gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

  // Menu File ( New, Open, Quit )

  menubar = gtk_menu_bar_new ();

  mib_file = gtk_menu_item_new_with_mnemonic ("_File");                   // Alt F 
  gtk_menu_shell_append (GTK_MENU_SHELL(menubar), mib_file);

  menu_file = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM(mib_file), menu_file);

  mi_new = gtk_menu_item_new();
  gtk_menu_item_set_label (GTK_MENU_ITEM(mi_new), "New");
  gtk_menu_shell_append (GTK_MENU_SHELL(menu_file), mi_new);
  g_signal_connect (G_OBJECT(mi_new), "activate", G_CALLBACK(cb_func_new), NULL);

  mi_open = gtk_menu_item_new_with_label ("Open");
  gtk_menu_shell_append (GTK_MENU_SHELL(menu_file), mi_open);
  g_signal_connect (G_OBJECT(mi_open), "activate", G_CALLBACK(cb_func_open), NULL);

  mi_sep = gtk_separator_menu_item_new ();
  gtk_menu_shell_append (GTK_MENU_SHELL(menu_file), mi_sep);

  mi_quit = gtk_menu_item_new_with_label ("Quit");
  gtk_menu_shell_append (GTK_MENU_SHELL(menu_file), mi_quit);

  g_signal_connect (G_OBJECT(mi_quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_add_accelerator (mi_quit, "activate", accel_group, 
                              GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  // Menu View ( Item 1 )

  mib_view = gtk_menu_item_new_with_label ("View");
  gtk_menu_shell_append (GTK_MENU_SHELL(menubar), mib_view);

  menu_view = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM(mib_view), menu_view);

  mi_item1 = gtk_menu_item_new_with_label ("Item 1");
  gtk_menu_shell_append (GTK_MENU_SHELL(menu_view), mi_item1);
  g_signal_connect (G_OBJECT(mi_item1), "activate", G_CALLBACK(cb_func_item1), NULL);

  // Menu Help ( Help, about )

  mib_help = gtk_menu_item_new_with_label ("Help");
  gtk_menu_shell_append (GTK_MENU_SHELL(menubar), mib_help);

  menu_help = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM(mib_help), menu_help);

  mi_help = gtk_menu_item_new_with_label ("Help");
  gtk_menu_shell_append (GTK_MENU_SHELL(menu_help), mi_help);
  g_signal_connect (G_OBJECT(mi_help), "activate", G_CALLBACK(cb_func_help), NULL);

  mi_about = gtk_menu_item_new_with_label ("About");
  gtk_menu_shell_append (GTK_MENU_SHELL(menu_help), mi_about);
  g_signal_connect (G_OBJECT(mi_about), "activate", G_CALLBACK(cb_func_about), NULL);

  return menubar;
}


int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *menubar ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  // Cria MenuBar
  
  menubar = cria_barra_de_menus (window);
  gtk_box_pack_start (GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
