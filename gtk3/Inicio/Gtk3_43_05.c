/********************************************************
 *                                                      *
 *      gtk3 - Cairo: Scale e Translate                 *
 *             ajustadas com spin buttons               *
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

typedef enum 
{
  Sp_PosX, Sp_PosY, Sp_PosR, Sp_TransX, Sp_TransY, Sp_ScaleX, Sp_ScaleY, 
  Sp_End
} SpinButtonEnum ;

gchar   *winTitle    = "Gtk3-Cairo: 'scale' e 'translate' ajustadas com spin buttons" ;
glong    win_xlen    = 800 ;
glong    win_ylen    = 600 ;

GtkWidget      *sb[Sp_End]  ;
GtkAdjustment  *adj[Sp_End] ;

double adj_val[Sp_End][5] = {
  {100.,     0.  , 1000., 10.  , 100.0},    // Sp_PosX
  {100.,     0.  , 1000., 10.  , 100.0},    // Sp_PosY
  { 20.,     2.  ,   30.,  1.  ,   5.0},    // Sp_PosR
  {  0., -1000.  , 1000., 10.  , 100.0},    // Sp_TransX
  {  0., -1000.  , 1000., 10.  , 100.0},    // Sp_TransY
  {  1.,     0.01,   10.,  0.01,   0.1},    // Sp_ScaleX
  {  1.,     0.01,   10.,  0.01,   0.1}     // Sp_ScaleY
};

SpinButtonEnum  spBt_actual = Sp_End;

gboolean 
on_draw_event (GtkWidget  *widget , 
               cairo_t    *cr     , 
	       gpointer    data   )
{ 
  GtkAllocation  alloc1 ;
  double posX, posY, raio, transX, transY, scaleX, scaleY ;
  double lenX, lenY ;

  gtk_widget_get_allocation (widget, &alloc1);  
  posX = gtk_spin_button_get_value (GTK_SPIN_BUTTON(sb[Sp_PosX]));
  posY = gtk_spin_button_get_value (GTK_SPIN_BUTTON(sb[Sp_PosY]));
  raio = gtk_spin_button_get_value (GTK_SPIN_BUTTON(sb[Sp_PosR]));

  scaleX = gtk_spin_button_get_value (GTK_SPIN_BUTTON(sb[Sp_ScaleX]));
  scaleY = gtk_spin_button_get_value (GTK_SPIN_BUTTON(sb[Sp_ScaleY]));

  transX = gtk_spin_button_get_value (GTK_SPIN_BUTTON(sb[Sp_TransX]));
  transY = gtk_spin_button_get_value (GTK_SPIN_BUTTON(sb[Sp_TransY]));

  lenX = alloc1.width / scaleX;
  lenY = alloc1.height / scaleY;

  switch (spBt_actual)
    {
      case Sp_TransX : case Sp_ScaleX : 
	gtk_adjustment_set_lower (adj[Sp_PosX], -transX);
	gtk_adjustment_set_upper (adj[Sp_PosX], -transX + lenX);
	break;
      case Sp_TransY : case Sp_ScaleY : 
	gtk_adjustment_set_lower (adj[Sp_PosY], -transY);
	gtk_adjustment_set_upper (adj[Sp_PosY], -transY + lenY);
	break;
      default :
	break;
    }

  cairo_scale (cr, scaleX, scaleY);
  cairo_translate (cr, transX, transY);

  cairo_move_to (cr, -transX + 10, 0);
  cairo_line_to (cr, -transX + lenX - 10, 0);
  cairo_move_to (cr, 0, -transY + 10);
  cairo_line_to (cr, 0, -transY + lenY - 10);

  cairo_stroke(cr);

  cairo_move_to (cr, 0, 0);
  cairo_line_to (cr, 0, 200);
  cairo_move_to (cr, 0, 0);
  cairo_line_to (cr, 200, 0);

  cairo_move_to (cr, 0, 0);
  cairo_set_line_width (cr, 4.0);
  cairo_arc (cr, posX, posY, raio, 0, 2. * M_PI);
  cairo_fill (cr);

  cairo_stroke(cr);

  return FALSE;
}

gboolean
cb_reset_values (GtkWidget *widget , 
                 gpointer   data   )
{
  int i1 ;

  for (i1 = 0 ; i1 < Sp_End ; ++i1)
    gtk_spin_button_set_value (GTK_SPIN_BUTTON(sb[i1]), adj_val[i1][0]);

  return FALSE;
}

gboolean 
ajusta_valores (GtkWidget *widget , 
                GtkWidget *darea   )
{
  SpinButtonEnum  n1 ;

  if ((!GTK_IS_WIDGET (darea)) || (!gtk_widget_get_window(darea)))
    return FALSE;

  for (n1 = 0 ; n1 < Sp_End ; ++n1)
    {
      if (sb[n1] == widget)
	{
	  spBt_actual = n1;
	  break;
	}
    }

  gtk_widget_queue_draw (darea);

  return FALSE;
}

void
create_frame (gchar          *frame_name , 
	      SpinButtonEnum  spBt       ,
	      GtkWidget      *parent     ,
	      GtkWidget      *darea      )

{
  GtkWidget *frame ;

  frame = gtk_frame_new (frame_name);
  gtk_frame_set_label_align (GTK_FRAME(frame), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX(parent), frame, FALSE, TRUE, 0);
  adj[spBt] = (GtkAdjustment *) gtk_adjustment_new (adj_val[spBt][0], adj_val[spBt][1], adj_val[spBt][2], 
						   adj_val[spBt][3], adj_val[spBt][4], 0.);
  sb[spBt] = gtk_spin_button_new (adj[spBt], 0, 0);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON(sb[spBt]), 2);
  g_signal_connect (G_OBJECT(sb[spBt]), "value_changed", G_CALLBACK(ajusta_valores), darea);
  gtk_container_add (GTK_CONTAINER (frame), sb[spBt]);
 }

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox1, *vbox2, *vbox3, *hbox1, *frame1, *frame2, *darea, *bt1;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window, win_xlen, win_ylen);
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
  gtk_window_set_title (GTK_WINDOW (window), winTitle);
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), window);

  vbox1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox1);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(vbox1), hbox1, TRUE, TRUE, 3);

  frame1 = gtk_frame_new ("  Desenho  ");
  gtk_frame_set_label_align (GTK_FRAME(frame1), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX(hbox1), frame1, TRUE, TRUE, 3);

  darea = gtk_drawing_area_new();
  g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);  
  gtk_container_add(GTK_CONTAINER (frame1), darea);

  // Comandos

  vbox3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_pack_end (GTK_BOX(hbox1), vbox3, FALSE, FALSE, 3);

  frame2 = gtk_frame_new ("Posição");
  gtk_frame_set_label_align (GTK_FRAME(frame2), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX(vbox3), frame2, FALSE, FALSE, 0);

  vbox2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width (GTK_CONTAINER (vbox2), 5);
  gtk_container_add (GTK_CONTAINER (frame2), vbox2);

  create_frame (" X ", Sp_PosX, vbox2, darea);
  create_frame (" Y ", Sp_PosY, vbox2, darea);
  create_frame (" Raio ", Sp_PosR, vbox2, darea);

  frame2 = gtk_frame_new ("Translation");
  gtk_frame_set_label_align (GTK_FRAME(frame2), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX(vbox3), frame2, FALSE, FALSE, 0);

  vbox2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width (GTK_CONTAINER (vbox2), 5);
  gtk_container_add (GTK_CONTAINER (frame2), vbox2);

  create_frame (" X ", Sp_TransX, vbox2, darea);
  create_frame (" Y ", Sp_TransY, vbox2, darea);
  
  frame2 = gtk_frame_new ("Scale");
  gtk_frame_set_label_align (GTK_FRAME(frame2), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX(vbox3), frame2, FALSE, FALSE, 0);

  vbox2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width (GTK_CONTAINER (vbox2), 5);
  gtk_container_add (GTK_CONTAINER (frame2), vbox2);

  create_frame (" X ", Sp_ScaleX, vbox2, darea);
  create_frame (" Y ", Sp_ScaleY, vbox2, darea);

  bt1 = gtk_button_new_with_label (" Reset ");
  gtk_box_pack_end (GTK_BOX(vbox3), bt1, FALSE, FALSE, 10);
  g_signal_connect (bt1, "clicked", G_CALLBACK(cb_reset_values), NULL);


  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
