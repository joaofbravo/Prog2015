/********************************************************
 *                                                      *
 *      gtk3 - Cairo: Scale e Translate                 *
 *             ajustadas com o teclado                  *
 *                                                      *
 *      GTK+ 3                                          *
 *      Versao: 1.0                                     *
 *      Samuel Eleuterio 2015                           *
 *                                                      *
 ********************************************************/

#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

gchar   *winTitle    = "Gtk3-Cairo: 'scale' e 'translate' ajustadas com o teclado" ;
glong    win_xlen    = 800 ;
glong    win_ylen    = 600 ;

gdouble  trans1x = 0., trans1y = 0. ;

gboolean cb_draw_event (GtkWidget *widget , 
                        cairo_t   *cr     , 
                        GtkWidget *darea  )
{      
  gchar          texto[128] ;
  double         pos1x = 130., pos1y = 250.;
  double         pos2x = 500., pos2y = 400;
  GtkAllocation  alloc1 ;

  gtk_widget_get_allocation (darea, &alloc1);
  
  cairo_translate (cr, trans1x, trans1y);

  cairo_move_to (cr, 140, 50);
  cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (cr, 30);
  cairo_set_source_rgb (cr, 0., 0., 1.);
  strcpy (texto, "Exemplo de GTK+ Cairo - Scale");
  cairo_show_text (cr, texto);
  cairo_move_to (cr, 20, 50);
  cairo_stroke (cr);

  cairo_set_source_rgb (cr, 0., 0., 0.);
  cairo_set_font_size (cr, 14);

  sprintf (texto, "Keys [Trans: (%3.0lf,%3.0lf)]:", trans1x, trans1y);
  cairo_move_to (cr, 10, 100);
  cairo_show_text (cr, texto);

  strcpy (texto, "Translation H: (z .. x) -+ 20.");
  cairo_move_to (cr, 30, 120);
  cairo_show_text (cr, texto);

  strcpy (texto, "Translation V: (t .. y) += 20.");
  cairo_move_to (cr, 30, 140);
  cairo_show_text (cr, texto);

  strcpy (texto, "Reset: (r) [ 1.0 ; 0.0 ]");
  cairo_move_to (cr, 30, 160);
  cairo_show_text (cr, texto);

  cairo_stroke (cr);

  // Axis

  cairo_move_to (cr, 0., -trans1y);
  cairo_line_to (cr, 0., alloc1.height - trans1y);

  cairo_move_to (cr, -trans1x, 0.);
  cairo_line_to (cr, alloc1.width - trans1x, 0.);
  cairo_stroke (cr);

  // Rectangulo fill

  cairo_set_font_size (cr, 18);
  cairo_set_source_rgb (cr, 0., 0.84, 0.9);
  cairo_set_line_width (cr, 1.0);
  cairo_rectangle (cr, (gint) pos1x, (gint) pos1y+100, 80, 50);
  cairo_fill (cr);

  strcpy (texto, "Rectangle");
  cairo_move_to (cr, (gint) pos1x-8, (gint) pos1y+170);
  cairo_show_text (cr, texto);
  cairo_stroke (cr);

  // Rectangulo

  cairo_set_source_rgb (cr, 1., 0., 0.);
  cairo_set_line_width (cr, 2.0);
  cairo_rectangle (cr, (gint) pos1x+300, (gint) pos1y-120, 80, 50);

  strcpy (texto, "Rectangle");
  cairo_move_to (cr, (gint) pos1x+292, (gint) pos1y-50);
  cairo_show_text (cr, texto);
  cairo_stroke (cr);

  // Circulo

  cairo_set_source_rgb (cr, 0., 1., 0.);
  cairo_set_line_width (cr, 4.0);
  cairo_arc (cr, pos2x+100, pos2y, 20, 0, 2. * M_PI);
  cairo_stroke (cr);

  cairo_set_source_rgb (cr, 0., 0.3, 0.);
  strcpy (texto, "Arc 2\xCF\x80");                 // pi (utf8): \xCF\x80
  cairo_move_to (cr, (gint) pos2x+67, (gint) pos2y+40);
  cairo_show_text (cr, texto);
  cairo_stroke (cr);

  // Circulo fill

  cairo_set_source_rgb (cr, 1., 0., 0.);
  cairo_set_line_width (cr, 4.0);
  cairo_arc (cr, pos2x-200, pos2y+100, 20, M_PI/3, 1.3 * M_PI);
  cairo_fill (cr);

  strcpy (texto, "Arc \xCF\x80");
  cairo_move_to (cr, (gint) pos2x-231, (gint) pos2y+140);
  cairo_show_text (cr, texto);
  cairo_stroke(cr);

  return FALSE;
}

gboolean
cb_press_key (GtkWidget    *widget   ,
              GdkEventKey  *eventkey ,
	      GtkWidget    *darea    )
{
  switch (eventkey->keyval)
    {
    case 'r' : case 'R' : trans1x = trans1y = 0; break;
    case 'z' : case 'Z' : trans1x = trans1x - 20.0; break;
    case 'x' : case 'X' : trans1x = trans1x + 20.0; break;
    case 't' : case 'T' : trans1y = trans1y - 20.0; break;
    case 'y' : case 'Y' : trans1y = trans1y + 20.0; break;
    default  : break;
    }

  if (trans1x < -800)
    trans1x = 800;
  else if (trans1x > 800)
    trans1x = -800;

  if (trans1y < -600)
    trans1y = 600;
  else if (trans1y > 600)
    trans1y = -600;

  gtk_widget_queue_draw (darea);

  return TRUE;
}


int main(int argc, char *argv[])
{
  GtkWidget *window, *darea;  

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), win_xlen, win_ylen);
  gtk_window_set_title(GTK_WINDOW(window), winTitle);

  darea = gtk_drawing_area_new();
  gtk_container_add (GTK_CONTAINER (window), darea);

  g_signal_connect (G_OBJECT(darea), "draw", G_CALLBACK(cb_draw_event), darea);  
  g_signal_connect (G_OBJECT(window), "key-press-event", 
                    G_CALLBACK(cb_press_key), darea); 
  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
