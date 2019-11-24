/*
   gtk01_03.c

   Exemplo inspirado no 'The GTK+ tutorial' (First Programs)

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;

gchar              *winTitle    = "GTK-Ex: 'button' com imagem 'gif'" ;
long int            xlen        = 350 ;
long int            ylen        = 200 ;


gboolean
cb_button_clicked (GtkWidget *w    ,
		   gpointer   data )
{
  static int contador = 0;

  contador++;
  printf ("Contador de 'clicked': %d\n", contador);

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox1, *bt1, *image ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_box_pack_start (GTK_BOX(vbox), hbox1, FALSE, TRUE, 10);

  image = gtk_image_new_from_file ("icons/Plus.gif");
  bt1 = gtk_button_new ();
  gtk_button_set_image (GTK_BUTTON(bt1), image);
  gtk_widget_set_size_request (bt1, 80, 80);
  gtk_box_pack_start (GTK_BOX (hbox1), bt1, FALSE, TRUE, 20);
  g_signal_connect (bt1, "clicked", G_CALLBACK(cb_button_clicked), NULL);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
