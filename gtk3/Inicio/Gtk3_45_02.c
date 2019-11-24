/*********************************************************
 *                                                       *
 *      gtk3 - Cairo: Rectangulo a mover-se numa janela  *
 *                                                       *
 *      GTK+ 3                                           *
 *      Versao: 1.0                                      *
 *      Samuel Eleuterio 2015                            *
 *                                                       *
 *********************************************************/

#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

gchar  *winTitle    = "Gtk3-Cairo: Rectângulo a mover-se numa janela" ;
glong   win_xlen    = 800 ;
glong   win_ylen    = 600 ;

glong   xlen        = 450 ;
glong   ylen        = 200 ;
gdouble dt          = 1.  ;
gdouble dt_max      = 10. ;


gboolean
press_click (GtkWidget       *widget ,
	     GdkEventButton  *event  ,
             gpointer         data   )
{
  if (event->button == 1)
    dt = dt + 1.;
  else if (event->button == 3)
    dt = dt - 1.;
  else
    dt = 1.;

  if (dt > dt_max)
    dt = 1.;
  else if (dt <= 0)
    dt = dt_max;

  return FALSE;
}

gboolean 
cb_draw_event (GtkWidget  *darea , 
               cairo_t    *cr    , 
               gpointer    data  )
{      
  gchar          texto[128] ;
  static double  pos2x = 500., pos2y = 30;
  static double  s2x = -1., s2y = 1.;
  GtkAllocation  alloc1 ;

  gtk_widget_get_allocation (darea, &alloc1);

  cairo_move_to (cr, 20, 20);
  cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (cr, 18);
  cairo_set_source_rgb (cr, 0., 0., 1.);
  sprintf (texto, "Exemplo de funcionamento de GTK+ Cairo            Velocidade: %.0lf", dt);
  cairo_show_text (cr, texto);
  cairo_stroke (cr);

  // Circulo

  cairo_set_source_rgb (cr, 1., 0., 0.);
  cairo_set_line_width (cr, 4.0);
  cairo_arc (cr, pos2x, pos2y, 20, 0, 2. * M_PI);
  cairo_stroke_preserve (cr);

  // Nota: ver o que acontece se se comentar a linha anterior e descomentar a seguinte
  //cairo_stroke (cr);

  cairo_set_source_rgb (cr, 0, 0, 1);
  cairo_fill (cr);

  if ((pos2x < 30.) || ((pos2x + 30.) > alloc1.width))
    s2x = - s2x;
  pos2x = pos2x + s2x * dt;

  if ((pos2y < 30.) || ((pos2y + 30.) > alloc1.height))
    s2y = - s2y;
  pos2y = pos2y + s2y * dt;

  cairo_stroke(cr);

  return FALSE;
}

gboolean time_handler (GtkWidget *widget)
{  
  if (!gtk_widget_get_window (widget))
    return FALSE;

  gtk_widget_queue_draw(widget);

  return TRUE;
}


int main(int argc, char *argv[])
{
  GtkWidget *window, *darea;  

  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW(window), win_xlen, win_ylen);
  gtk_widget_set_size_request (window, win_xlen - 50, win_ylen - 50);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);

  darea = gtk_drawing_area_new ();
  gtk_container_add (GTK_CONTAINER (window), darea);

  g_signal_connect (G_OBJECT(darea), "draw", G_CALLBACK(cb_draw_event), NULL);  
  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT(window), "button_press_event", 
		    G_CALLBACK(press_click), NULL); 

  g_timeout_add (10, (GSourceFunc) time_handler, darea);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
