/*****************************************************
 *                                                   *
 *      spin button                                  *
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

GtkWidget  *entry1, *spin1, *label1;

gboolean
func_button1 (GtkWidget  *w    ,
              gpointer    data )
{
  gdouble x1       ;
  gchar   str1[16] ;

  x1 = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spin1));
  sprintf (str1, "%.2lf", x1);
  gtk_label_set_text (GTK_LABEL(label1), str1);

  return FALSE;
}

GtkWidget *
create_spin_button (void)
{
  GtkWidget      *spinButton ;
  GtkAdjustment  *adj1       ;

  adj1 = (GtkAdjustment *) gtk_adjustment_new (1.0, -10.0, 31.0, 0.5, 5.0, 0);
  spinButton = gtk_spin_button_new (adj1, 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(spinButton), TRUE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON(spinButton), 2);
  gtk_widget_set_size_request (spinButton, 150, 30);

  return spinButton;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox0, *hbox1, *hbox2, *button1, *label0 ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 450, 300);
  gtk_widget_set_size_request (window, 400, 250);

  gtk_window_set_title (GTK_WINDOW(window), "GTK3-Ex: SpinButtun");
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  g_signal_connect_swapped (G_OBJECT(window), "destroy",
                            G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  /* label, button */ 

  //label0 = gtk_label_new ("Spin Button\nSe carregar usando a tecla do meio\nAvança de 'page_increment'");
  label0 = gtk_label_new ("Spin Button");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 10);
  label0 = gtk_label_new ("Teclas do rato a usar:");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 0);
  label0 = gtk_label_new ("Esquerda: Recua/Avança normal");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 0);
  label0 = gtk_label_new ("Central: Recua/Avança uma página");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 0);
  label0 = gtk_label_new ("Direita: Início/Fim ");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 0);


  hbox0 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox0), TRUE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox0, FALSE, TRUE, 50);

  spin1 = create_spin_button ();

  gtk_box_pack_start (GTK_BOX (hbox0), spin1, TRUE, FALSE, 10);
  
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox2), TRUE);
  gtk_box_pack_end (GTK_BOX (vbox), hbox2, FALSE, TRUE, 20);

  label1 = gtk_label_new ("Value");
  gtk_box_pack_start (GTK_BOX (hbox2), label1, FALSE, TRUE, 20);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  gtk_box_set_homogeneous (GTK_BOX(hbox1), TRUE);
  gtk_box_pack_end (GTK_BOX (vbox), hbox1, FALSE, TRUE, 10);

  button1 = gtk_button_new_with_label ("Spin Value");
  gtk_widget_set_size_request (button1, 150, 30);
  g_signal_connect (button1, "clicked", G_CALLBACK (func_button1), NULL);
  gtk_box_pack_start (GTK_BOX (hbox1), button1, TRUE, FALSE, 10);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
