/*
   PrGtk01_40.c

   Exemplo de "entry" e de "spin button"

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

GtkWidget  *entry1, *spin1, *label1, *label2;

gboolean
func_button1 (GtkWidget  *w    ,
              gpointer    data )
{
  const gchar *str1 ;

  str1 = gtk_entry_get_text (GTK_ENTRY(entry1));
  gtk_label_set_text (GTK_LABEL(label1), str1);

  return FALSE;
}

gboolean
func_button2 (GtkWidget  *w    ,
              gpointer    data )
{
  gdouble x1       ;
  gchar   str1[16] ;

  x1 = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spin1));
  sprintf (str1, "%.2lf", x1);
  gtk_label_set_text (GTK_LABEL(label2), str1);

  return FALSE;
}

GtkWidget *
create_entry (void)
{
  GtkWidget  *entry ;
  
  entry = gtk_entry_new ();
  gtk_widget_set_size_request (entry, 80, 30);
  gtk_entry_set_max_length (GTK_ENTRY(entry), 10);
  gtk_entry_set_width_chars (GTK_ENTRY(entry), 10);
  gtk_widget_set_size_request (entry, 130, 30);
  gtk_entry_set_text (GTK_ENTRY(entry), "23");

  return entry;
}

GtkWidget *
create_spin_button (void)
{
  GtkWidget      *spinButton ;
  GtkAdjustment  *adj1       ;

  adj1 = (GtkAdjustment *) gtk_adjustment_new (1.0, -10.0, 31.0, 0.5, 5.0, 0.0);
  spinButton = gtk_spin_button_new (adj1, 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(spinButton), TRUE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (spinButton), 2);
  gtk_widget_set_size_request (spinButton, 130, 30);

  return spinButton;
}

int
main (int argc, char **argv)
{
  GtkWidget  *window, *vbox, *hbox0, *hbox1, *hbox2, *button1, *button2, *label0 ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 450, 300);
  gtk_widget_set_size_request (window, 400, 250);

  gtk_window_set_title (GTK_WINDOW (window), "GTK-Ex: Entrada de Dados");
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

  g_signal_connect_swapped (G_OBJECT (window), "destroy",
                            G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  /* label, button */ 

  label0 = gtk_label_new ("Entry   -   Spin Button");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 10);

  hbox0 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox0), TRUE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox0, FALSE, TRUE, 50);

  entry1 = create_entry ();
  gtk_box_pack_start (GTK_BOX (hbox0), entry1, TRUE, FALSE, 10);

  spin1 = create_spin_button ();
  gtk_box_pack_start (GTK_BOX (hbox0), spin1, TRUE, FALSE, 10);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox2), TRUE);
  gtk_box_pack_end (GTK_BOX (vbox), hbox2, FALSE, TRUE, 20);

  label1 = gtk_label_new ("Valor");
  gtk_box_pack_start (GTK_BOX (hbox2), label1, FALSE, TRUE, 20);

  label2 = gtk_label_new ("Valor");
  gtk_box_pack_end (GTK_BOX (hbox2), label2, FALSE, TRUE, 20);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  gtk_box_set_homogeneous (GTK_BOX(hbox1), TRUE);
  gtk_box_pack_end (GTK_BOX (vbox), hbox1, FALSE, TRUE, 10);

  button1 = gtk_button_new_with_label ("Mostra Entry");
  g_signal_connect (button1, "clicked", G_CALLBACK (func_button1), NULL);
  gtk_box_pack_start (GTK_BOX (hbox1), button1, FALSE, TRUE, 10);
  //gtk_container_add (GTK_CONTAINER (hbox1), button1);

  button2 = gtk_button_new_with_label ("Mostra Spin Button");
  g_signal_connect (button2, "clicked", G_CALLBACK (func_button2), NULL);
  gtk_box_pack_start (GTK_BOX (hbox1), button2, FALSE, TRUE, 10);
  //gtk_container_add (GTK_CONTAINER (hbox1), button2);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
