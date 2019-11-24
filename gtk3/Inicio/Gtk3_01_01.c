/*****************************************************
 *                                                   *
 *      O meu primeiro programa em GTK+ - v3         *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2014                        *
 *                                                   *
 *****************************************************/

#include <stdio.h>
#include <gtk/gtk.h>


int
main (int argc, char **argv)
{
  GtkWidget *window ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 600, 400);
  gtk_window_set_title (GTK_WINDOW(window), "O Meu Primeiro Programa em GTK+");
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show (window);
  gtk_main ();

  return 0;
}
