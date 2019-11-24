/*****************************************************
 *                                                   *
 *      Toggle Buttons                               *
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

gchar     *winTitle    = "GTK3 - Toggle Buttons" ;
long int   win_xlen    = 500                     ;
long int   win_ylen    = 300                     ;

GtkWidget  *label1, *label2 ;

gboolean 
cb_buttonA (GtkWidget  *w    ,
            gpointer    data )
{
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(w)))
    gtk_label_set_text (GTK_LABEL (label1), "A: Eu estou activado!");
  else
    gtk_label_set_text (GTK_LABEL (label1), "A: Eu não estou activado...");

  return FALSE;
}

gboolean 
cb_buttonB (GtkWidget  *w     ,
            gpointer    data )
{      
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(w)))
    gtk_label_set_text (GTK_LABEL (label2), "B: Eu estou activado!");
  else
    gtk_label_set_text (GTK_LABEL (label2), "B: Eu não estou activado...");

  return FALSE;
}

gboolean 
cb_button_act_A (GtkWidget  *w  ,
		 GtkWidget  *bt )
{
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(bt)))
    gtk_label_set_text (GTK_LABEL (label1), "A: Já estava activado!");
  else
    {
      gtk_label_set_text (GTK_LABEL (label1), "A: Agora estou activado...");
      gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(bt), TRUE);
    }

  return FALSE;
}

gboolean 
cb_button_Nact_B (GtkWidget  *w  ,
	 	  GtkWidget  *bt )
{
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(bt)))
    {
      gtk_label_set_text (GTK_LABEL (label2), "B: Agora estou activado!");
      gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(bt), FALSE);
    }
  else
    gtk_label_set_text (GTK_LABEL (label2), "B: Já estava desactivado...");

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox, *hbox1 ;
  GtkWidget *button, *button1, *button2 ;

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

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
  gtk_box_pack_start (GTK_BOX(vbox), hbox, TRUE, FALSE, 3);

  button1 = gtk_toggle_button_new_with_label ("Eu sou a 'Escolha' A");
  gtk_widget_set_size_request (button1, 180, 20);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button1), FALSE);
  gtk_box_pack_start (GTK_BOX(hbox), button1, TRUE, FALSE, 3);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
  gtk_box_pack_start (GTK_BOX(vbox), hbox, TRUE, FALSE, 3);

  button2 = gtk_toggle_button_new_with_label ("Eu sou a 'Escolha' B");
  gtk_widget_set_size_request (button2, 180, 20);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button2), TRUE);
  gtk_box_pack_start (GTK_BOX(hbox), button2, TRUE, FALSE, 3);

  label1 = gtk_label_new ("A: Eu não estou activado...");
  gtk_box_pack_start (GTK_BOX(vbox), label1, TRUE, TRUE, 3);
  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(cb_buttonA), label1);

  label2 = gtk_label_new ("B: Eu estou activado!");
  gtk_box_pack_start (GTK_BOX(vbox), label2, TRUE, TRUE, 3);
  g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(cb_buttonB), label2);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox1, FALSE, TRUE, 3);

  button = gtk_button_new_with_label ("Activa A");
  gtk_widget_set_size_request (button, 100, 20);
  gtk_box_pack_start (GTK_BOX(hbox1), button, FALSE, TRUE, 3);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cb_button_act_A), button1);

  button = gtk_button_new_with_label ("Desactiva B");
  gtk_widget_set_size_request (button, 100, 20);
  gtk_box_pack_start (GTK_BOX(hbox1), button, FALSE, TRUE, 3);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cb_button_Nact_B), button2);

  button = gtk_button_new_with_label ("Exit");
  gtk_widget_set_size_request (button, 100, 20);
  gtk_box_pack_end (GTK_BOX(hbox1), button, FALSE, TRUE, 3);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), button2);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
