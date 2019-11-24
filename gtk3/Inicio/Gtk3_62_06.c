/*****************************************************
 *                                                   *
 *      Sair com Pergunta                            *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2015                        *
 *                                                   *
 *****************************************************/

#include <gtk/gtk.h>

GtkWindowType       winType  = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos   = GTK_WIN_POS_CENTER  ;

gchar              *winTitle = "Sair a Perguntar (a cores)" ;

int                 win_xlen = 400 ;
int                 win_ylen = 200 ;

gboolean
quick_message (GtkWidget *win) 
{

  GtkWidget *dialog, *label;
  gchar *message = "Quer Sair?";
  gint  resultado ;
   
  dialog = gtk_dialog_new_with_buttons ("Message", GTK_WINDOW(win), 
					GTK_DIALOG_DESTROY_WITH_PARENT,
					"_Yes", GTK_RESPONSE_ACCEPT,
					"_Cancel", GTK_RESPONSE_REJECT,
					NULL);
  gtk_window_set_default_size (GTK_WINDOW(dialog), 300, 300);
  gtk_window_set_modal (GTK_WINDOW(dialog), TRUE);

  label = gtk_label_new (message);
  gtk_box_pack_start (GTK_BOX(gtk_bin_get_child (GTK_BIN(dialog))), label, TRUE, FALSE, 0);
  gtk_widget_show_all (dialog);

  resultado = gtk_dialog_run (GTK_DIALOG(dialog));
  g_print ("Resultado: %d\n", resultado);
  gtk_widget_destroy (dialog);

  if (resultado == GTK_RESPONSE_ACCEPT)
    return TRUE;
  else
    return FALSE;
}

gboolean
Teste_BotaoSair (GtkWidget  *w   , 
		 GtkWidget  *win ) 
{
  gboolean teste ;

  teste = quick_message (win);
  if (!teste)
    return TRUE;

  gtk_main_quit();
  return FALSE;
}

gboolean
Teste_DeleteEvent (GtkWidget *w   ,
		   GtkWidget *w1  ,
		   GtkWidget *win ) 
{
  gboolean teste ;

  teste = quick_message (win);
  if (!teste)
    return TRUE;

  // Nota se se descomentar o callback associado a "destroy" 
  // a linha seguinte deve ser retirada

  gtk_main_quit();

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox1, *hbox2, *qmessage, *label ;
  GdkRGBA color1 ;

  gtk_init (&argc, &argv);

  gdk_rgba_parse (&color1,"#ab0567");

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), win_xlen, win_ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  //g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT(window), "delete_event", G_CALLBACK(Teste_DeleteEvent), window);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  // label, button

  label = gtk_label_new ("Teste de Saida");
  gtk_widget_override_color (label, GTK_STATE_NORMAL, &color1);
  gtk_widget_override_font (label, pango_font_description_from_string("Tahoma bold 18"));
  gtk_box_pack_start (GTK_BOX(vbox), label, FALSE, TRUE, 20);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER (vbox), hbox1);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox2, FALSE, TRUE, 20);

  qmessage = gtk_button_new_from_icon_name ("application-exit", GTK_ICON_SIZE_BUTTON);
  g_signal_connect (qmessage, "clicked", G_CALLBACK (Teste_BotaoSair), window);
  gtk_box_pack_end (GTK_BOX (hbox2), qmessage, FALSE, TRUE, 30);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
