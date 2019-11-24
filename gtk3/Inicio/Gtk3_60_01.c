/*****************************************************
 *                                                   *
 *      Window - Dimensões e Dimensões Mínimas       *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.1                                  *
 *      Samuel Eleuterio 2014, 2015                  *
 *                                                   *
 *****************************************************/

#include <gtk/gtk.h>

gchar     *winTitle    = "GTK3 - Window: Dimensões e Dimensões Mínimas" ;
glong      win_xlen    = 800 ;
glong      win_ylen    = 600 ;

int
main (int argc, char **argv)
{
  GtkWidget *window ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), win_xlen, win_ylen);
  gtk_window_set_title (GTK_WINDOW (window), winTitle);
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request (window, win_xlen - 200, win_ylen - 200);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show (window);
  gtk_main ();

  return 0;
}
