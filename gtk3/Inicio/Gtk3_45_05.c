/*********************************************************
 *                                                       *
 *      gtk3 - Cairo: Rectangulo e círculo a             *
 *             moverem-se numa janela                    *
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

gchar  *winTitle    = "Gtk3-Cairo: Rectângulo e círculo a moverem-se numa janela" ;
glong   win_xlen    = 800 ;
glong   win_ylen    = 600 ;

glong   xlen        = 450 ;
glong   ylen        = 200 ;
gdouble dt          = 1.  ;
gdouble dt_max      = 10. ;
gint    flag_wa     = 0   ;


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
cb_draw (GtkWidget  *darea  , 
         cairo_t    *cr     , 
         GtkWidget  *window )
{      
  gchar          texto[128] ;
  static double  pos1x = 30., pos1y = 40.;
  static double  pos2x = 500., pos2y = 30;
  static double  s2x = -1., s2y = 1.;
  GtkAllocation  alloc1 ;

  gtk_widget_get_allocation (darea, &alloc1);

  if (flag_wa)
    gtk_widget_get_allocation (window, &alloc1);

  cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (cr, 18);
  cairo_set_source_rgb (cr, 0., 0., 1.);
  sprintf (texto, "Exemplo de funcionamento de GTK+ Cairo");
  cairo_move_to (cr, 20, 20);
  cairo_show_text (cr, texto);

  sprintf (texto, "Velocidade: %.0lf", dt);
  cairo_move_to (cr, 20, 50);
  cairo_show_text (cr, texto);

  sprintf (texto, "Ajuste de colisão feito com %s", 
	   (flag_wa ? "window" : "drawing area"));
  cairo_move_to (cr, 20, 80);
  cairo_show_text (cr, texto);

  cairo_stroke (cr);

  // Rectangle

  cairo_set_source_rgb (cr, 0.2, 0.84, 0.9);
  cairo_set_line_width (cr, 1.0);
  cairo_rectangle (cr, (gint) pos1x, (gint) pos1y, 80, 50);
  cairo_fill (cr);
  cairo_stroke (cr);
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_fill (cr);
  cairo_stroke (cr);

  pos1x = pos1x + 2. * dt;
  if ((pos1x + 100.) > alloc1.width)
    {
      pos1x = 30.;
      pos1y = pos1y + 75;
      if ((pos1y + 70.) > alloc1.height) 
        pos1y = 30;
    }

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

gboolean
cb_window_darea (GtkWidget  *widget , 
	         gpointer    data   )
{ 
  if (flag_wa)
    gtk_button_set_label (GTK_BUTTON(widget), "Ajuste para Window");
  else
    gtk_button_set_label (GTK_BUTTON(widget), "Ajuste para DArea");

  flag_wa = (flag_wa + 1) % 2;

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
  GtkWidget *window, *darea, *vbox, *hbox1, *frame1, *button1 ;  

  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW(window), win_xlen, win_ylen);
  gtk_widget_set_size_request (window, win_xlen - 50, win_ylen - 50);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);

  vbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  frame1 = gtk_frame_new (" Desenho ");
  gtk_frame_set_label_align (GTK_FRAME(frame1), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX(vbox), frame1, TRUE, TRUE, 3);

  darea = gtk_drawing_area_new ();
  gtk_container_add (GTK_CONTAINER (frame1), darea);

  frame1 = gtk_frame_new (" Comandos ");
  gtk_frame_set_label_align (GTK_FRAME(frame1), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX(vbox), frame1, FALSE, TRUE, 3);

  hbox1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox1), 10);
  gtk_container_add (GTK_CONTAINER (frame1), hbox1);

  button1 = gtk_button_new_with_label ("Exit");
  gtk_widget_set_size_request (button1, 170, 20);
  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(gtk_main_quit), NULL);
  gtk_box_pack_end (GTK_BOX(hbox1), button1, FALSE, TRUE, 3);

  button1 = gtk_button_new_with_label ("Ajuste para Window");
  gtk_widget_set_size_request (button1, 170, 20);
  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(cb_window_darea), NULL);
  gtk_box_pack_end (GTK_BOX(hbox1), button1, FALSE, TRUE, 3);

  g_signal_connect (G_OBJECT(darea), "draw", G_CALLBACK(cb_draw), window);  
  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT(window), "button_press_event", 
		    G_CALLBACK(press_click), NULL); 

  g_timeout_add (10, (GSourceFunc) time_handler, darea);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
