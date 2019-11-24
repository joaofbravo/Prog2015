/*****************************************************
 *                                                   *
 *      botao                                        *
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

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL  ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER   ;
gchar              *winTitle    = "GTK3 - Buttons"     ;
long int            xlen        = 350                  ;
long int            ylen        = 200                  ;

int
main (int argc, char **argv)
{
  GtkWidget *window, *button ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  button = gtk_button_new_with_label ("Sou um botão!");
  gtk_container_add (GTK_CONTAINER(window), button);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
