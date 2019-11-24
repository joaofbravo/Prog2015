/*****************************************************
 *                                                   *
 *      Sair sem Perguntar                           *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2014                        *
 *                                                   *
 *****************************************************/

#include <gtk/gtk.h>

GtkWindowType       winType  = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos   = GTK_WIN_POS_CENTER  ;

gchar              *winTitle = "Sair sem Perguntar" ;

int                 win_xlen = 400 ;
int                 win_ylen = 200 ;


int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox1, *hbox2, *qmessage, *label ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), win_xlen, win_ylen);
  gtk_window_set_title (GTK_WINDOW (window), winTitle);
  gtk_window_set_position (GTK_WINDOW (window), winPos);

  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  // label, button

  label = gtk_label_new ("Teste de Saida");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, TRUE, 20);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER (vbox), hbox1);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX (vbox), hbox2, FALSE, TRUE, 20);

  qmessage = gtk_button_new_with_label ("Sair");
  gtk_widget_set_size_request (qmessage, 100, 20);
  g_signal_connect (qmessage, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  gtk_box_pack_end (GTK_BOX (hbox2), qmessage, FALSE, TRUE, 30);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
