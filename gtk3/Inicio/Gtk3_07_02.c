/*****************************************************
 *                                                   *
 *      entry                                        *
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

GtkWidget  *entry1, *label1, *label2 ;
char       *ch_text = "2a" ;
char        chl2[32] = "Comprimento do texto: " ;
int         len_chl2 ;

gboolean
func_reset (GtkWidget  *w    ,
            gpointer    data )
{
  gtk_entry_set_text (GTK_ENTRY(entry1), "");

  return FALSE;
}

gboolean
func_entry (GtkWidget  *w    ,
             gpointer    data )
{
  const gchar *str1 ;

  str1 = gtk_entry_get_text (GTK_ENTRY(entry1));
  gtk_label_set_text (GTK_LABEL(label1), str1);

  sprintf (&chl2[len_chl2], "%ld", strlen (str1));
  gtk_label_set_text (GTK_LABEL(label2), chl2);

  return FALSE;
}

GtkWidget *
create_entry (void)
{
  GtkWidget  *entry ;
  
  entry = gtk_entry_new ();
  gtk_widget_set_size_request (entry, 80, 30);
  gtk_entry_set_max_length (GTK_ENTRY(entry), 30);
  gtk_entry_set_width_chars (GTK_ENTRY(entry), 40);
  gtk_widget_set_size_request (entry, 100, 29);
  gtk_entry_set_text (GTK_ENTRY(entry), ch_text);

  return entry;
}

int
main (int argc, char **argv)
{
  GtkWidget  *window, *vbox, *hbox0, *hbox1, *hbox2, *hbox3 ;
  GtkWidget  *button1, *label0 ;

  len_chl2 = strlen (chl2);
  sprintf (&chl2[len_chl2], "%ld", strlen (ch_text));

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 450, 300);
  gtk_widget_set_size_request (window, 400, 250);

  gtk_window_set_title (GTK_WINDOW (window), "GTK-Ex: 'Entry' com botão de reset ");
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

  g_signal_connect_swapped (G_OBJECT (window), "destroy",
                            G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  // label0

  hbox3 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox3), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER(hbox3), 20);
  gtk_box_pack_start (GTK_BOX (vbox), hbox3, FALSE, TRUE, 10);

  label0 = gtk_label_new ("Entry");
  gtk_box_pack_start (GTK_BOX (hbox3), label0, FALSE, TRUE, 10);

  // entry

  hbox0 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox0), TRUE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox0, FALSE, TRUE, 10);

  entry1 = create_entry ();
  gtk_box_pack_start (GTK_BOX (hbox0), entry1, TRUE, FALSE, 10);
  g_signal_connect (entry1, "changed", G_CALLBACK (func_entry), NULL);
 
  // label1 e label2

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox2), TRUE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox2, FALSE, TRUE, 10);

  label1 = gtk_label_new (ch_text);
  gtk_box_pack_start (GTK_BOX (hbox2), label1, FALSE, TRUE, 10);

  label2 = gtk_label_new (chl2);
  gtk_box_pack_start (GTK_BOX (vbox), label2, FALSE, TRUE, 10);

  // button1

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  gtk_box_set_homogeneous (GTK_BOX(hbox1), TRUE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox1, FALSE, TRUE, 10);

  button1 = gtk_button_new_with_label ("Reset Entry");
  gtk_widget_set_size_request (button1, 150, 30);
  g_signal_connect (button1, "clicked", G_CALLBACK (func_reset), NULL);
  gtk_box_pack_end (GTK_BOX (hbox1), button1, TRUE, FALSE, 10);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
