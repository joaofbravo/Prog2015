/*
   gtk3_02_04.c

   Exemplo inspirado no 'The GTK+ tutorial' (First Programs)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;

gchar              *winTitle    = "GTK-Ex: box, buttons, label" ;
gchar               chlabel[32] = "Valor actual: " ;
gchar              *chhex       = "0123456789ABCDEF" ;
GdkRGBA             color1, color2, color3 ;

long int            xlen        = 350 ;
long int            ylen        = 200 ;
gint                contador    = 0   ;
gint                len_chlabel       ;


void
nova_cor_rand (GdkRGBA *color)
{
  int  n1, n2 ;
  char ch[16] ;

  
  ch[0] = '#';
  for (n1 = 1 ; n1 <= 6 ; ++n1)
    {
      n2 = rand () % 16;
      ch[n1] = chhex[n2];
    }
  ch[n1] = 0;
  gdk_rgba_parse (&color1, ch);
}

gboolean 
cb_plus (GtkWidget *widget , 
         gpointer   label  )
{
  ++contador;
  sprintf (&chlabel[len_chlabel], "%d", contador);

  nova_cor_rand (&color1);
  gtk_widget_override_color (label, GTK_STATE_NORMAL, &color1);
  gtk_label_set_text(label, chlabel);

  return FALSE;
}

gboolean 
cb_minus (GtkWidget *widget , 
          gpointer   label  )
{
  --contador;
  sprintf (&chlabel[len_chlabel], "%d", contador);

  nova_cor_rand (&color1);
  gtk_widget_override_color (label, GTK_STATE_NORMAL, &color1);
  gtk_label_set_text(label, chlabel);

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox1, *hbox2, *bplus, *bminus, *label ;

  srand (time(NULL));

  len_chlabel = strlen (chlabel);
  sprintf (&chlabel[len_chlabel], "%d", contador);

  gtk_init (&argc, &argv);

  nova_cor_rand (&color1);
  gdk_rgba_parse (&color2, "#000567");
  gdk_rgba_parse (&color3, "#FF0000");

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(vbox), hbox1, TRUE, TRUE, 0);

  label = gtk_label_new (chlabel);
  gtk_widget_override_color (label, GTK_STATE_NORMAL, &color1);
  gtk_widget_override_font (label, pango_font_description_from_string("Tahoma bold 16"));
  gtk_box_pack_start (GTK_BOX(hbox1), label, TRUE, FALSE, 0);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox2, FALSE, TRUE, 20);

  bminus = gtk_button_new_with_label ("-");
  gtk_widget_set_size_request (bminus, 100, 45);
  gtk_widget_override_color (bminus, GTK_STATE_NORMAL, &color2);
  gtk_widget_override_font (bminus, pango_font_description_from_string("Tahoma bold 22"));
  g_signal_connect (bminus, "clicked", G_CALLBACK(cb_minus), label);
  gtk_box_pack_start (GTK_BOX(hbox2), bminus, FALSE, TRUE, 20);

  bplus = gtk_button_new_with_label ("+");
  gtk_widget_set_size_request (bplus, 100, 45);
  gtk_widget_override_color (bplus, GTK_STATE_NORMAL, &color3);
  gtk_widget_override_font (bplus, pango_font_description_from_string("Tahoma bold 22"));
  g_signal_connect (bplus, "clicked", G_CALLBACK(cb_plus), label);
  gtk_box_pack_end (GTK_BOX(hbox2), bplus, FALSE, TRUE, 20);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
