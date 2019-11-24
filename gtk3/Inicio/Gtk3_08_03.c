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

GtkWidget  *entry1, *spin1, *label1, *label2 ;

char        chl2[32] = "Número actual: " ;
int         len_chl2 ;
char        chd2[32] = "Número de décimas: " ;
int         len_chd2 ;

void
cria_string_value (double x1 , 
		   int    d1  )
{
  char    sform[16] ;

  sprintf (sform, "%%.%dlf", d1);
  sprintf (&chl2[len_chl2], sform, x1);
  
}

gboolean
func_reset (GtkWidget  *w    ,
            gpointer    data )
{
  gtk_spin_button_set_value (GTK_SPIN_BUTTON(spin1), 0);

  return FALSE;
}

gboolean
func_decimas (GtkWidget  *w    ,
                   gpointer    data )
{
  int    d1 ;

  d1 = 1 + gtk_spin_button_get_digits (GTK_SPIN_BUTTON(spin1));
  if (d1 > 5)
    d1 = 0;
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON(spin1), d1);

  sprintf (&chd2[len_chd2], "%d", d1);
  gtk_label_set_text (GTK_LABEL(label2), chd2);

  return FALSE;
}

gboolean
func_spin_change (GtkWidget  *w    ,
                  gpointer    data )
{
  int    d1 ;
  double x1 ;

  x1 = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spin1));
  d1 = gtk_spin_button_get_digits (GTK_SPIN_BUTTON(spin1));

  cria_string_value (x1, d1);
  gtk_label_set_text (GTK_LABEL(label1), chl2);

  return FALSE;
}

GtkWidget *
create_spin_button (double val ,
                    int    d1  )
{
  GtkWidget      *spinButton ;
  GtkAdjustment  *adj1       ;

  adj1 = (GtkAdjustment *) gtk_adjustment_new (val, -10.0, 31.0, 0.5, 5.0, 0);
  spinButton = gtk_spin_button_new (adj1, 0, d1);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(spinButton), TRUE);
  //gtk_spin_button_set_digits (GTK_SPIN_BUTTON(spinButton), d1);
  gtk_widget_set_size_request (spinButton, 150, 30);

  return spinButton;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox0, *hbox1 ;
  GtkWidget *button1, *button2, *label0, *sep ;
  int        d1 ;
  double     x1 ;

  d1 = 2;
  x1 = 1.;
  len_chl2 = strlen (chl2);
  len_chd2 = strlen (chd2);
  sprintf (&chd2[len_chd2], "%d", d1);
  cria_string_value (x1, d1);

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 450, 380);
  gtk_widget_set_size_request (window, 400, 350);

  gtk_window_set_title (GTK_WINDOW(window), "GTK-Ex: Entrada de Dados");
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  g_signal_connect_swapped (G_OBJECT(window), "destroy",
                            G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  // label

  label0 = gtk_label_new ("Spin Button");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 10);
  label0 = gtk_label_new ("Teclas do rato a usar:");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 5);
  label0 = gtk_label_new ("Esquerda: Recua/Avança normal");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 5);
  label0 = gtk_label_new ("Central: Recua/Avança uma página");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 5);
  label0 = gtk_label_new ("Direita: Início/Fim ");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 5);

  // spin_button

  hbox0 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox0), TRUE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox0, FALSE, TRUE, 20);

  spin1 = create_spin_button (x1, d1);
  gtk_box_pack_start (GTK_BOX (hbox0), spin1, TRUE, FALSE, 10);
  g_signal_connect (spin1, "changed", G_CALLBACK (func_spin_change), NULL);

  // label1 e label2

  label1 = gtk_label_new (chl2);
  gtk_box_pack_start (GTK_BOX (vbox), label1, FALSE, TRUE, 10);

  label2 = gtk_label_new (chd2);
  gtk_box_pack_start (GTK_BOX (vbox), label2, FALSE, TRUE, 10);

  // button1

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  gtk_box_set_homogeneous (GTK_BOX(hbox1), TRUE);
  gtk_box_pack_end (GTK_BOX (vbox), hbox1, FALSE, TRUE, 10);

  sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_end (GTK_BOX (vbox), sep, FALSE, TRUE, 0);

  button1 = gtk_button_new_with_label ("Spin Nº. Decimas");
  gtk_widget_set_size_request (button1, 150, 30);
  g_signal_connect (button1, "clicked", G_CALLBACK (func_decimas), NULL);
  gtk_box_pack_start (GTK_BOX (hbox1), button1, TRUE, FALSE, 10);

  button2 = gtk_button_new_with_label ("Reset Spin");
  gtk_widget_set_size_request (button2, 150, 30);
  g_signal_connect (button2, "clicked", G_CALLBACK (func_reset), NULL);
  gtk_box_pack_end (GTK_BOX (hbox1), button2, TRUE, FALSE, 10);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
