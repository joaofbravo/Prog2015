/*****************************************************
 *                                                   *
 *      statusbar                                    *
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

gchar              *winTitle    = "Criação de statusbar" ;
long int            xlen        = 350 ;
long int            ylen        = 200 ;


gboolean 
cb_func_statusbar (GtkWidget  *widget    , 
	           GtkWidget  *statusbar )
{
  static int conta = 1 ;
  char       str1[64]  ;

  printf ("Actuou no botão para alterar a 'Statusbar': %d\n", conta);

  if (conta % 2 == 0)
    {
      gtk_widget_show (statusbar);
      sprintf (str1, "  Isto é uma statusbar. Contador: %d", conta);
      gtk_statusbar_push (GTK_STATUSBAR(statusbar), 1, str1);
    }
  else
    gtk_widget_hide (statusbar);
  ++conta;

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox1,*bt1, *statusbar, *sep ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  // Cria statusbar

  statusbar = gtk_statusbar_new ();
  gtk_box_pack_end (GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);
  gtk_statusbar_push (GTK_STATUSBAR(statusbar), 1, "  Isto e' uma statusbar.");

  sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_end (GTK_BOX(vbox), sep, FALSE, TRUE, 0);

  // button

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(vbox), hbox1, FALSE, TRUE, 20);

  bt1 = gtk_button_new_with_label ("Altera 'statusbar'");
  gtk_widget_set_size_request (bt1, 200, 35);
  gtk_box_pack_start (GTK_BOX(hbox1), bt1, FALSE, TRUE, 20);
  g_signal_connect (bt1, "clicked", G_CALLBACK(cb_func_statusbar), statusbar);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
