/*
   gtk3_02_03.c

   
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

gchar              *winTitle    = "GTK-Ex: box e buttons" ;

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;

long int            xlen        = 450 ;
long int            ylen        = 250 ;

gboolean 
bt1_carrega (GtkWidget *widget , 
             gpointer   ptr    )
{
  static int contador = 0 ;

  contador++;
  if (contador == 1)
    printf ("Carregou %d vez no botão esquerdo.\n", contador);
  else
    printf ("Carregou %d vezes no botão esquerdo.\n", contador);

  return FALSE;
}

gboolean 
bt2_carrega (GtkWidget *widget , 
             gpointer   ptr    )
{
  static int contador = 0 ;

  contador++;
  if (contador == 1)
    printf ("Carregou %d vez no botão direito.\n", contador);
  else
    printf ("Carregou %d vezes no botão direito.\n", contador);

  return FALSE;
}


int
main (int argc, char **argv)
{
  GtkWidget *window, *hbox, *bt1, *bt2 ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER(window), hbox);

  bt1 = gtk_button_new_with_label ("Botão Esquerdo");
  gtk_widget_set_size_request (bt1, 150, 35);
  g_signal_connect (bt1, "clicked", G_CALLBACK(bt1_carrega), NULL);
  gtk_box_pack_start (GTK_BOX (hbox), bt1, FALSE, TRUE, 20);

  bt2 = gtk_button_new_with_label ("Botão Direito");
  gtk_widget_set_size_request (bt2, 150, 35);
  g_signal_connect (bt2, "clicked", G_CALLBACK(bt2_carrega), NULL);
  gtk_box_pack_end (GTK_BOX(hbox), bt2, FALSE, TRUE, 20);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
