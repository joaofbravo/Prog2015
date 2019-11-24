/*****************************************************
 *                                                   *
 *      radio botao                                  *
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

gchar     *winTitle    = "GTK3 - Radio buttons" ;
long int   win_xlen    = 400                  ;
long int   win_ylen    = 250                  ;


gboolean
cb_raio_button (GtkWidget  *w     ,
		GtkWidget  *label )
{
  gint              n1       ;
  char              str1[16] ;
  GSList           *list     ;
  GtkToggleButton  *bt       ;

  n1 = 0;
  bt = NULL;

  list = gtk_radio_button_get_group (GTK_RADIO_BUTTON(w));

  while (list)
    {
      bt = list->data;
      list = list->next;

      if (gtk_toggle_button_get_active(bt))
	break;

      bt = NULL;
      ++n1;
    }

  sprintf (str1, "Escolha: %d", n1);
  gtk_label_set_text (GTK_LABEL(label), str1);

  return FALSE;
}

int
main (int argc, char **argv)
{
  int        i1 ;
  char       str1[16] ;
  GtkWidget *window, *vbox, *hbox1, *radio[4], *button, *sep, *label ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), win_xlen, win_ylen);
  gtk_widget_set_size_request (window, win_xlen - 50, win_ylen - 50);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  label = gtk_label_new ("Escolha feita: 3");

  
  for (i1 = 0 ; i1 < 4 ; ++i1)
    {
      sprintf (str1, "Escolha: %d", 3 - i1);
      if (i1 == 0)
	radio[i1] = gtk_radio_button_new_with_label (NULL, str1);
      else
	radio[i1] = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio[i1-1]), str1);
      gtk_box_pack_start (GTK_BOX (vbox), radio[i1], TRUE, TRUE, 2);
      g_signal_connect(G_OBJECT(radio[i1]), "clicked", G_CALLBACK(cb_raio_button), label);
    }

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio[1]), TRUE);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox1, FALSE, TRUE, 3);

  gtk_box_pack_start (GTK_BOX(hbox1), label, FALSE, TRUE, 3);

  button = gtk_button_new_with_label ("Exit");
  gtk_widget_set_size_request (button, 100, 20);
  gtk_box_pack_end (GTK_BOX(hbox1), button, FALSE, TRUE, 3);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

  sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (vbox), sep, FALSE, TRUE, 0);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
