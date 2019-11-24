/*****************************************************
 *                                                   *
 *      Criação de um "Color Chooser Dialog"         *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2014                        *
 *                                                   *
 *****************************************************/

#include <gtk/gtk.h>

GtkWindowType       winType  = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos   = GTK_WIN_POS_CENTER  ;

gchar              *winTitle = "GTK3: Color Chooser Dialog" ;

int                 xlen     = 400 ;
int                 ylen     = 200 ;

GdkRGBA             color1, color2, color3 ;

GtkWidget          *label ;

gboolean 
color_chooser (GtkWidget *w      ,
	       GtkWidget *window )
{
  int        res    ;
  GtkWidget *dialog ;

  dialog = gtk_color_chooser_dialog_new ("GTK3: Color Chooser Dialog", GTK_WINDOW(window));
  res = gtk_dialog_run (GTK_DIALOG(dialog));

  if (res == GTK_RESPONSE_OK)
    {
      printf ("Res: %d (OK)\n", res);
      gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(dialog), &color2);
      gtk_widget_override_color (label, GTK_STATE_NORMAL, &color2);
    }
  else
    printf ("Res: %d (not OK)\n", res);

  gtk_widget_destroy (dialog);

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox1, *hbox2, *button1 ;
  gtk_init (&argc, &argv);

  gdk_rgba_parse (&color1,"red");
  gdk_rgba_parse (&color3,"#ab0567");

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  /* label, button */ 

  label = gtk_label_new ("Teste de Saida");
  gtk_widget_override_font (label, pango_font_description_from_string("Tahoma bold 14"));
  gtk_box_pack_start (GTK_BOX(vbox), label, FALSE, TRUE, 20);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER(vbox), hbox1);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox2, FALSE, TRUE, 20);

  button1 = gtk_button_new_with_label ("Aplica");
  gtk_widget_set_size_request (button1, 100, 22);
  gtk_widget_override_color (button1, GTK_STATE_NORMAL, &color3);
  gtk_widget_override_font (button1, pango_font_description_from_string("Tahoma bold 12"));
  gtk_box_pack_end (GTK_BOX(hbox2), button1, FALSE, TRUE, 30);
  g_signal_connect (button1, "clicked", G_CALLBACK(color_chooser), window);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
