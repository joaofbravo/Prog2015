/*
   gtk3_02_02.c

   Exemplo de um Botão

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

gchar              *winTitle    = "GTK3 - Ex: button e callback" ;

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;
long int            xlen        = 350 ;
long int            ylen        = 200 ;


gboolean 
bt_carrega (GtkWidget *widget , 
            gpointer   ptr    )
{
  static int contador = 0 ;

  contador++;
  if (contador == 1)
    printf ("Carregou %d vez.\n", contador);
  else
    printf ("Carregou %d vezes.\n", contador);

  return FALSE;
}

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

  button = gtk_button_new_with_label ("Sou um botão!\nCarregue, por favor.");
  g_signal_connect (button, "clicked", G_CALLBACK(bt_carrega), NULL);

  gtk_container_add (GTK_CONTAINER(window), button);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
