/*****************************************************
 *                                                   *
 *      Scale                                        *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2015                        *
 *                                                   *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <gtk/gtk.h>

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;

gchar              *winTitle    = "Gtk3: Horizontal scale" ;
long int            win_xlen    = 600 ;
long int            win_ylen    = 250 ;

char               *ch_LabelValue   = "%4d  -  Valor:  %6.2lf" ;
gdouble             ScaleInitValue  = 1.0;
gint                n_digits        = 2 ;
char               *ch_digits       = "Digits: " ;
gint                n_show_value    = 1 ;
char               *ch_show_value[] = {"Põe Valor", "Tira Valor"} ;
char               *cb_text[]       = {"Left", "Right", "Top", "Bottom"};

//GtkWidget          *scale ;

gboolean
cb_change_scale (GtkWidget  *w     ,
		 GtkWidget  *label )
{
  static gint c = 0    ;
  double      x        ;
  char        str1[24] ;

  x = gtk_range_get_value (GTK_RANGE(w));
  sprintf (str1, ch_LabelValue, ++c, x);
  gtk_label_set_text (GTK_LABEL(label), str1);

  return FALSE;
}

gboolean
cb_show_value (GtkWidget  *w      ,
	       GtkWidget  *scale1 )
{
  ++n_show_value;
  n_show_value = (n_show_value) % 2;

  gtk_scale_set_draw_value (GTK_SCALE (scale1), (n_show_value ? TRUE : FALSE));
  gtk_button_set_label (GTK_BUTTON(w), ch_show_value[n_show_value]);

  return FALSE;
}


gboolean
cb_change_digits (GtkWidget  *w      ,
		  GtkWidget  *scale1 )
{
  char str1[16] ;

  ++n_digits;
  if (n_digits > 6)
    n_digits = 0;

  sprintf (str1, "%s%d", ch_digits, n_digits);

  gtk_scale_set_digits (GTK_SCALE(scale1), n_digits);
  gtk_button_set_label (GTK_BUTTON(w), str1);

  return FALSE;
}

gboolean
cb_change_value_pos (GtkWidget  *w      ,
		     GtkWidget  *scale1 )
{
  gint  opt1     ;

  opt1 = gtk_combo_box_get_active (GTK_COMBO_BOX (w));
  gtk_scale_set_value_pos (GTK_SCALE(scale1), (GtkPositionType) opt1);

  return FALSE;
}

GtkWidget *
cria_scale (void)
{
  GtkWidget *w ;

  w = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, -10, 10, 1);
  gtk_scale_set_digits (GTK_SCALE(w), n_digits);
  gtk_scale_set_value_pos (GTK_SCALE(w), GTK_POS_TOP); // GTK_POS_LEFT, GTK_POS_RIGHT, GTK_POS_TOP, GTK_POS_BOTTOM
  gtk_scale_set_draw_value (GTK_SCALE(w), (n_show_value ? TRUE : FALSE));
  gtk_range_set_value (GTK_RANGE(w), ScaleInitValue);

  return w;
}

GtkWidget *
create_ComboBox_Text (void)
{
  gint       i1    ;
  GtkWidget *cbBox ;

  cbBox = gtk_combo_box_text_new ();
  gtk_widget_set_size_request (cbBox, 52, 29);

  for (i1 = 0 ; i1 < 4 ; ++i1)
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cbBox), cb_text[i1]);
  gtk_combo_box_set_active (GTK_COMBO_BOX (cbBox), 2);

  return cbBox;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *scale, *vbox, *sep, *cbBox ;
  GtkWidget *hbox2, *bt1, *label ;
  char       str1[32] ;

  gtk_init (&argc, &argv);
  setlocale (LC_ALL, "pt_PT.UTF-8");
  setlocale (LC_NUMERIC, "en_US.UTF-8");

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), win_xlen, win_ylen);
  gtk_widget_set_size_request (window, win_xlen - 50, win_ylen - 50);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  // Cria toolbar

  scale = cria_scale ();
  gtk_box_pack_start (GTK_BOX(vbox), scale, FALSE, FALSE, 3);

  // Botoes Finais

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox2), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 10);
  gtk_box_pack_end (GTK_BOX(vbox), hbox2, FALSE, TRUE, 10);

  sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_end (GTK_BOX(vbox), sep, FALSE, TRUE, 0);

  sprintf (str1, ch_LabelValue, 0, ScaleInitValue);
  label = gtk_label_new (str1);
  gtk_box_pack_start (GTK_BOX(vbox), label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(scale), "value-changed", G_CALLBACK(cb_change_scale), label);

  cbBox = create_ComboBox_Text ();
  gtk_box_pack_start (GTK_BOX (hbox2), cbBox, FALSE, TRUE, 20);
  g_signal_connect (G_OBJECT (cbBox), "changed", G_CALLBACK (cb_change_value_pos), scale);
  
  sprintf (str1, "%s%d", ch_digits, n_digits);
  bt1 = gtk_button_new_with_label (str1);
  gtk_widget_set_size_request (bt1, 100, 15);
  gtk_box_pack_start (GTK_BOX (hbox2), bt1, FALSE, TRUE, 20);
  g_signal_connect (bt1, "clicked", G_CALLBACK(cb_change_digits), scale);

  bt1 = gtk_button_new_with_label (ch_show_value[n_show_value]);
  gtk_widget_set_size_request (bt1, 100, 15);
  gtk_box_pack_start (GTK_BOX (hbox2), bt1, FALSE, TRUE, 20);
  g_signal_connect (bt1, "clicked", G_CALLBACK(cb_show_value), scale);

  bt1 = gtk_button_new_with_label (" Exit ");
  gtk_widget_set_size_request (bt1, 100, 15);
  gtk_box_pack_end (GTK_BOX (hbox2), bt1, FALSE, TRUE, 20);
  g_signal_connect (bt1, "clicked", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
