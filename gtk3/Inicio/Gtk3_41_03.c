/********************************************************
 *                                                      *
 *      gtk3 - Cairo: Move Circulo com Rato             *
 *             Mudar cor do circulo com 'SPACE'         *
 *             Mostra um 'png'                          *
 *                                                      *
 *      GTK+ 3                                          *
 *      Versao: 1.0                                     *
 *      Samuel Eleuterio 2015                           *
 *                                                      *
 ********************************************************/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cairo.h>
#include <gtk/gtk.h>

#define RAIO_MINIMO            5
#define RAIO_DELTA            10
#define CIRCULO_CENTRO_X     200
#define CIRCULO_CENTRO_Y     200

#if defined(_WIN32)
char *image_png_file = "images\\ist.png";
#else
char *image_png_file = "images/ist.png";
#endif


typedef struct
{
  gint              flag_move   ;    // "1" (rato carregado); "0" (quando larga)
  gint              width       ;    // Comprimento da janela 
  gint              height      ;    // Altura da janela

  gdouble           raio        ;    // Raio do circulo
  gdouble           raio2       ;    // Quadrado do raio do circulo
  gdouble           centro[2]   ;    // Coordenadas do centro do circulo

  gdouble           ratoPos[2]  ;    // Posicao do rato
  gdouble           press[2]    ;    // Posicao em que foi carregado o botao do rato
  gdouble           delta[2]    ;    // Desvio do rato do centro do circulo
  gdouble           rgb[3]      ;    // Cor do circulo
  
  GtkWidget        *window      ;    // Widget da Window
  GtkWidget        *darea       ;    // Drawing area
  GtkAllocation     darea_alloc ;    // Drawing area allocation
  cairo_surface_t  *image       ;    // Imagem a mostrar
} ProgData ;

gchar  *winTitle    = "Move Circulo com Rato" ;
glong   win_xlen    = 400 ;
glong   win_ylen    = 400 ;


gboolean 
cb_draw_event(GtkWidget  *widget ,
	      cairo_t    *cr     ,
	      gpointer    data   )
{
  char       str1[32] ;
  ProgData  *pinfo    ;

  pinfo = (ProgData *) data;

  gtk_widget_get_allocation (pinfo->darea, &pinfo->darea_alloc);
  
  cairo_set_source_surface (cr, pinfo->image, 10, 10);
  cairo_paint(cr);

  cairo_set_line_width (cr, 2);

  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_move_to (cr, 60, 25);
  cairo_set_font_size (cr, 14.);
  cairo_show_text  (cr, "* Para mudar a cor do circulo prima uma tecla");

  cairo_move_to (cr, 20, pinfo->darea_alloc.height - 60);
  sprintf (str1, "Rato: %4d , %4d", (int) pinfo->ratoPos[0], (int) pinfo->ratoPos[1]);
  cairo_show_text (cr, str1);

  cairo_move_to (cr, 20, pinfo->darea_alloc.height - 40);
  sprintf (str1, "Centro: %4d , %4d", (int) pinfo->centro[0], (int) pinfo->centro[1]);
  cairo_show_text  (cr, str1);

  cairo_move_to (cr, 20, pinfo->darea_alloc.height - 20);
  sprintf (str1, "Cores: %.3lf , %.3lf , %.3lf", pinfo->rgb[0], pinfo->rgb[1], pinfo->rgb[2]);
  cairo_show_text  (cr, str1);

  cairo_stroke(cr); 

  // Circulo

  cairo_set_source_rgb (cr, pinfo->rgb[0], pinfo->rgb[1], pinfo->rgb[2]);
  cairo_move_to (cr,pinfo->centro[0], pinfo->centro[1]);
  cairo_arc (cr, pinfo->centro[0], pinfo->centro[1], pinfo->raio, 15, 7. * M_PI);
  cairo_fill (cr);
  cairo_stroke(cr); 

  return FALSE;
}


gboolean
cb_motion_notify (GtkWidget  *widget ,
                  GdkEvent   *event  ,
                  ProgData   *pinfo  )
{
  double  dist  ;

  gtk_widget_get_allocation (pinfo->darea, &pinfo->darea_alloc);
  
  if (event->type == GDK_MOTION_NOTIFY)
    {
      //printf ("Event: Motion Notify\n");
      pinfo->ratoPos[0] = ((GdkEventMotion *)event)->x;
      pinfo->ratoPos[1] = ((GdkEventMotion *)event)->y;
      if (pinfo->flag_move == 1)
        {
          if (pinfo->ratoPos[0] + pinfo->delta[0] + pinfo->raio > pinfo->darea_alloc.width)
            pinfo->centro[0] = pinfo->darea_alloc.width - pinfo->raio;
          else if (pinfo->ratoPos[0] + pinfo->delta[0] - pinfo->raio < 0)
            pinfo->centro[0] = pinfo->raio;
	  else
            pinfo->centro[0] = pinfo->ratoPos[0] + pinfo->delta[0];

          if (pinfo->ratoPos[1] + pinfo->delta[1] + pinfo->raio > pinfo->darea_alloc.height)
            pinfo->centro[1] = pinfo->darea_alloc.height - pinfo->raio;
          else if (pinfo->ratoPos[1] + pinfo->delta[1] - pinfo->raio < 0)
            pinfo->centro[1] = pinfo->raio;
          else
            pinfo->centro[1] = pinfo->ratoPos[1] + pinfo->delta[1];
	}
    }
  else if (event->type == GDK_BUTTON_PRESS)
    {
      //printf ("Event: Button Press - x: %.2lf ; y: %2lf\n", pinfo->ratoPos[0], pinfo->ratoPos[1]);
      pinfo->press[0] = ((GdkEventButton *)event)->x;
      pinfo->press[1] = ((GdkEventButton *)event)->y;
      pinfo->delta[0] = pinfo->centro[0] - pinfo->press[0];
      pinfo->delta[1] = pinfo->centro[1] - pinfo->press[1];
      dist = pow(pinfo->delta[0], 2) + pow(pinfo->delta[1], 2);
      if (dist < pinfo->raio2)
	{
          pinfo->flag_move = 1;
          pinfo->centro[0] = pinfo->press[0] + pinfo->delta[0];
          pinfo->centro[1] = pinfo->press[1] + pinfo->delta[1];
	}
    }
  else if (event->type == GDK_BUTTON_RELEASE)
    {
      //printf ("Event: Button Release\n");
      pinfo->flag_move = 0;
    }
  else if (event->type == GDK_KEY_PRESS)
    {
      //printf ("Event: Key Press\n");
      pinfo->rgb[0] = modf (pinfo->rgb[0] + 0.05, &dist);
      pinfo->rgb[1] = modf (pinfo->rgb[1] + 0.07, &dist);
      pinfo->rgb[2] = modf (pinfo->rgb[2] + 0.09, &dist);
    }

  gtk_widget_queue_draw(pinfo->darea);


  return FALSE;
}


ProgData *
ProgData_new (void)
{
  ProgData *pinfo ;

  pinfo = (ProgData *) calloc (1, sizeof (ProgData));

  pinfo->flag_move = 0;
  pinfo->raio = RAIO_MINIMO + RAIO_DELTA * ((double) rand()) / ((double) RAND_MAX) ;
  pinfo->raio2 = pinfo->raio * pinfo->raio;
  pinfo->centro[0] = CIRCULO_CENTRO_X;
  pinfo->centro[1] = CIRCULO_CENTRO_Y; 

  return pinfo;
}

int main(int argc, char *argv[])
{
  ProgData *pinfo    ;

  pinfo = (ProgData *) ProgData_new ();

  gtk_init(&argc, &argv);

  pinfo->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (pinfo->window), winTitle);
  gtk_window_set_default_size (GTK_WINDOW (pinfo->window), win_xlen, win_ylen);
  gtk_widget_set_size_request (pinfo->window, win_xlen, win_ylen);
  gtk_window_set_position (GTK_WINDOW (pinfo->window), GTK_WIN_POS_CENTER);

  pinfo->darea = gtk_drawing_area_new();
  gtk_container_add (GTK_CONTAINER (pinfo->window), pinfo->darea);

  pinfo->image = cairo_image_surface_create_from_png (image_png_file);
  
  gtk_widget_set_events (pinfo->window, GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK | 
			 GDK_BUTTON_RELEASE_MASK | GDK_KEY_PRESS_MASK);

  g_signal_connect (G_OBJECT(pinfo->window), "motion-notify-event", 
		    G_CALLBACK (cb_motion_notify), pinfo);
  g_signal_connect (G_OBJECT(pinfo->window), "button_press_event", 
		    G_CALLBACK (cb_motion_notify), pinfo);
  g_signal_connect (G_OBJECT(pinfo->window), "button_release_event", 
		    G_CALLBACK (cb_motion_notify), pinfo);
  g_signal_connect (G_OBJECT(pinfo->window), "key_press_event", 
		    G_CALLBACK (cb_motion_notify), pinfo);

  g_signal_connect (G_OBJECT(pinfo->darea), "draw", G_CALLBACK(cb_draw_event), pinfo);  
  g_signal_connect (G_OBJECT(pinfo->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all (pinfo->window);

  gtk_main();

  return 0;
}
