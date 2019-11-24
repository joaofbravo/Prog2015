/*****************************************************
 *                                                   *
 *      Criação de um "Font Chooser Dialog"         *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2014                        *
 *                                                   *
 *****************************************************/

#include <string.h>
#include <gtk/gtk.h>

GtkWindowType       winType  = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos   = GTK_WIN_POS_CENTER  ;

gchar              *winTitle = "GTK3: Font Chooser Dialog" ;

int                 xlen     = 400 ;
int                 ylen     = 200 ;

GdkRGBA             color1, color2, color3 ;
GtkWidget          *label ;
gchar              *fontname; // = "Tahoma bold 14";



gboolean 
font_chooser_cancel (GtkWidget *w      ,
		     GtkWidget *dialog )
{
  gtk_widget_destroy (dialog);

  return FALSE;
}

gboolean 
font_chooser_ok (GtkWidget *w      ,
	         GtkWidget *dialog )
{
  gchar *fontname ;

  fontname = gtk_font_chooser_get_font (GTK_FONT_CHOOSER(dialog));
  g_print ("Font: %s\n", fontname);


  g_free (fontname);
  gtk_widget_destroy (dialog);

  return FALSE;
}

gboolean 
font_chooser2 (GtkWidget *w      ,
              GtkWidget *window )
{
  GtkWidget *dialog, *button ;

  dialog = gtk_font_chooser_dialog_new ("GTK3: Font Chooser Dialog", GTK_WINDOW(window));

  gtk_font_chooser_set_font(GTK_FONT_CHOOSER(dialog), fontname); 

  button = gtk_dialog_get_widget_for_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(font_chooser_ok), dialog);

  button = gtk_dialog_get_widget_for_response(GTK_DIALOG(dialog), GTK_RESPONSE_CANCEL);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(font_chooser_cancel), dialog);

    gtk_widget_show(dialog);

  return FALSE;
}

gboolean 
font_chooser (GtkWidget *w      ,
              GtkWidget *window )
{
  gint        res      ;
  GtkWidget  *dialog   ;

  dialog = gtk_font_chooser_dialog_new ("GTK3: Font Chooser Dialog", GTK_WINDOW(window));
  gtk_font_chooser_set_font(GTK_FONT_CHOOSER(dialog), fontname); 

  res = gtk_dialog_run (GTK_DIALOG(dialog));

  if (res == GTK_RESPONSE_OK)
    {
      g_free (fontname);
      fontname = gtk_font_chooser_get_font (GTK_FONT_CHOOSER(dialog));
      gtk_widget_override_font (label, pango_font_description_from_string(fontname));
      g_print ("Font: %s\n", fontname);
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

  fontname = strdup ("Tahoma bold 14");

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

  label = gtk_label_new ("Font Chooser Dialog");
  gtk_widget_override_font (label, pango_font_description_from_string("Tahoma bold 14"));
  gtk_box_pack_start (GTK_BOX(vbox), label, FALSE, TRUE, 20);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER(vbox), hbox1);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox2, FALSE, TRUE, 20);

  button1 = gtk_button_new_with_label ("Aplica");
  gtk_widget_set_size_request (button1, 100, 22);
  gtk_widget_override_color (button1, GTK_STATE_NORMAL, &color3);
  gtk_widget_override_font (button1, pango_font_description_from_string (fontname));
  gtk_box_pack_end (GTK_BOX(hbox2), button1, FALSE, TRUE, 30);
  g_signal_connect (button1, "clicked", G_CALLBACK(font_chooser), window);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
