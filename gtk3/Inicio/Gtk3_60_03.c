/*****************************************************
 *                                                   *
 *      Window - Sub-sub-windows                     *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2014                        *
 *                                                   *
 *****************************************************/

#include <gtk/gtk.h>

gchar     *winTitle    = "GTK3 - Windows: 0 (sub-windows)" ;
glong      win_xlen    = 600 ;
glong      win_ylen    = 400 ;

gboolean
create_other_window (GtkWidget  *w   ,
		     GtkWidget  *win )
{
  static gint   num = 1                       ;
  gchar         str1[32]                      ;
  GtkWidget    *win2, *button1, *vbox, *hbox1 ;

  sprintf (str1, "GTK3 - Windows: %d (sub-windows)", num++);

  win2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (win2, win_xlen, win_ylen);
  gtk_window_set_title (GTK_WINDOW (win2), str1);
  g_signal_connect (G_OBJECT(win2), "destroy", G_CALLBACK(gtk_widget_destroy), win2);
  
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
  gtk_container_add (GTK_CONTAINER (win2), vbox);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox1, FALSE, TRUE, 3);

  button1 = gtk_button_new_with_label ("New window");
  gtk_widget_set_size_request (button1, 100, 20);
  gtk_box_pack_end (GTK_BOX(hbox1), button1, FALSE, TRUE, 3);
  g_signal_connect (G_OBJECT(button1), "clicked", G_CALLBACK(create_other_window), win2);

  gtk_widget_show_all (win2);

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *button1, *vbox, *hbox1 ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window, 600, 400);
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
  gtk_window_set_title (GTK_WINDOW (window), "Gtk3 - Window: 0");
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox1, FALSE, TRUE, 3);

  button1 = gtk_button_new_with_label ("New window");
  gtk_widget_set_size_request (button1, 100, 20);
  gtk_box_pack_end (GTK_BOX(hbox1), button1, FALSE, TRUE, 3);
  g_signal_connect (G_OBJECT(button1), "clicked", G_CALLBACK(create_other_window), window);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
