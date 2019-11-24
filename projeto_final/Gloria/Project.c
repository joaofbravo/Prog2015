#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>
#include <math.h>


double      teta[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double      omega[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double      ox = 441., oy = 0.;//ponto de origem
double      poseqx =441., poseqy = 400.;//ponto de equilibrio
double      posx[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double      posy[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double      L=400;
double      janelaX=1420, janelaY=770;

GdkColor       cor_red, cor_blue, cor ,cor1,cor2,cor3;



typedef struct
{
  //janelas e caixas gerais
  GtkWidget *window;
  GtkWidget *window_erro;

  //frames gerais
  GtkWidget *frame[5];
  
  //butões
    
  GtkWidget  *button[11];
  
  //spin
  GtkWidget  *toggle, *spin[9];
  GtkAdjustment *adj[10];
 
  //caixas
  GtkWidget *hbox[6];
  GtkWidget *vbox[7];
  
  //labels
  GtkWidget *label[18];
  GtkWidget *radio[5];
    
    
  //condições iniciais
  double n_p;
  double n_m_p_direita;
  double n_m_p_esquerda;
  double *pen;
  int play;
  int erro;
  int pausa;
    
  GdkPixbuf  *image;
  GdkPixmap  *background;
  GtkStyle   *style;

}data;



void func_play (GtkWidget *widget,
               
                gpointer pointer)
{
    
  data *info;
  info = (data *)pointer;
  info->play=1;
    
}


void
func_pausa (GtkWidget *widget,
            
            gpointer pointer)
{
    
  data *info;
  info = (data *)pointer;
  info->play = 0;
    
}


//_______________________________________________________________THEMES

void
miley (GtkWidget *widget,
            
       gpointer pointer)
{
    
  data *info;
  info = (data *)pointer;
    
  //cores
  gdk_color_parse ("#000000", &cor_red);
  gdk_color_parse ("#E8F1D4", &cor_blue);
  gdk_color_parse ("#EED5D2", &cor);
  gdk_color_parse ("#CD9B9B", &cor1);
  gdk_color_parse ("#dbd2d2", &cor2);
  gdk_color_parse ("#FFFFFF", &cor3);
    
  gtk_widget_modify_bg (info->frame[0], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_bg (info->frame[1], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_bg (info->frame[2], GTK_STATE_NORMAL, &cor_red);
    
  gtk_widget_modify_bg (info->button[2], GTK_STATE_NORMAL, &cor_blue);
  gtk_widget_modify_bg (info->button[3], GTK_STATE_NORMAL, &cor_blue);
    
  gtk_widget_modify_bg (info->button[5], GTK_STATE_NORMAL, &cor);
  gtk_widget_modify_bg (info->button[4], GTK_STATE_NORMAL, &cor);
  gtk_widget_modify_bg (info->button[6], GTK_STATE_NORMAL, &cor);
 
  gtk_widget_modify_bg (info->button[7], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[8], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[9], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[10], GTK_STATE_NORMAL, &cor1);
    
  gtk_widget_modify_fg (info->label[0], GTK_STATE_NORMAL, &cor3);
  gtk_widget_modify_fg (info->label[1], GTK_STATE_NORMAL, &cor3);
  gtk_widget_modify_fg (info->label[4], GTK_STATE_NORMAL, &cor3);
  gtk_widget_modify_fg (info->label[16], GTK_STATE_NORMAL, &cor2);
  gtk_widget_modify_fg (info->label[6], GTK_STATE_NORMAL, &cor3);
  gtk_widget_modify_fg (info->label[5], GTK_STATE_NORMAL, &cor3);
  gtk_widget_modify_fg (info->label[3], GTK_STATE_NORMAL,&cor_red);
    
  info->image = gdk_pixbuf_new_from_file ("1.jpg", NULL);
  gdk_pixbuf_render_pixmap_and_mask (info->image, &info->background, NULL, 0);
  info->style = gtk_style_new ();
  info->style->bg_pixmap[0] = info->background;
  gtk_widget_set_style (GTK_WIDGET(info->window), GTK_STYLE(info->style));
    
}



void
white (GtkWidget *widget,
        
       gpointer pointer)
{
    
  data *info;
  info = (data *)pointer;
    
  gdk_color_parse ("#000000", &cor_red);
  gdk_color_parse ("#CCEEFF", &cor_blue);
  gdk_color_parse ("#FF8C69", &cor);
  gdk_color_parse ("#FA8072", &cor1);
    
  gtk_widget_modify_bg (info->frame[0], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_bg (info->frame[1], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_bg (info->frame[2], GTK_STATE_NORMAL, &cor_red);
    
  gtk_widget_modify_bg (info->button[2], GTK_STATE_NORMAL, &cor_blue);
  gtk_widget_modify_bg (info->button[3], GTK_STATE_NORMAL, &cor_blue);
  gtk_widget_modify_bg (info->button[5], GTK_STATE_NORMAL, &cor);
  gtk_widget_modify_bg (info->button[4], GTK_STATE_NORMAL, &cor);
  gtk_widget_modify_bg (info->button[6], GTK_STATE_NORMAL, &cor);
   
  gtk_widget_modify_bg (info->button[7], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[8], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[9], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[10], GTK_STATE_NORMAL, &cor1);
 
  gtk_widget_modify_fg (info->label[0], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[1], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[4], GTK_STATE_NORMAL,&cor_red);
  gtk_widget_modify_fg (info->label[6], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[5], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[3], GTK_STATE_NORMAL,&cor_red);
  gtk_widget_modify_fg (info->label[16], GTK_STATE_NORMAL,&cor_red);

  info->image = gdk_pixbuf_new_from_file ("white.jpg", NULL);
  gdk_pixbuf_render_pixmap_and_mask (info->image, &info->background, NULL, 0);
  info->style = gtk_style_new ();
  info->style->bg_pixmap[0] = info->background;
  gtk_widget_set_style (GTK_WIDGET(info->window), GTK_STYLE(info->style));
    
}


void
linux (GtkWidget *widget,
       
       gpointer pointer)
{
    
  data *info;
  info = (data *)pointer;
    
  gdk_color_parse ("#000000", &cor_red);
  gdk_color_parse ("#CCEEFF", &cor_blue);
  gdk_color_parse ("#FF8C69", &cor);
  gdk_color_parse ("#FA8072", &cor1);
    
  gtk_widget_modify_bg (info->frame[0], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_bg (info->frame[1], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_bg (info->frame[2], GTK_STATE_NORMAL, &cor_red);
    
  gtk_widget_modify_bg (info->button[2], GTK_STATE_NORMAL, &cor_blue);
  gtk_widget_modify_bg (info->button[3], GTK_STATE_NORMAL, &cor_blue);
  gtk_widget_modify_bg (info->button[5], GTK_STATE_NORMAL, &cor);
  gtk_widget_modify_bg (info->button[4], GTK_STATE_NORMAL, &cor);
  gtk_widget_modify_bg (info->button[6], GTK_STATE_NORMAL, &cor);
    
  gtk_widget_modify_bg (info->button[7], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[8], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[9], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[10], GTK_STATE_NORMAL, &cor1);
    
  gtk_widget_modify_fg (info->label[0], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[1], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[4], GTK_STATE_NORMAL,&cor_red);
  gtk_widget_modify_fg (info->label[6], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[5], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[3], GTK_STATE_NORMAL,&cor_red);
  gtk_widget_modify_fg (info->label[16], GTK_STATE_NORMAL,&cor_red);
    
  info->image = gdk_pixbuf_new_from_file ("linux.jpg", NULL);
  gdk_pixbuf_render_pixmap_and_mask (info->image, &info->background, NULL, 0);
  info->style = gtk_style_new ();
  info->style->bg_pixmap[0] = info->background;
  gtk_widget_set_style (GTK_WIDGET(info->window), GTK_STYLE(info->style));
    
}


void
bet (GtkWidget *widget,
        
     gpointer pointer)
{
    
  data *info;
  info = (data *)pointer;
    
  gdk_color_parse ("#000000", &cor_red);
  gdk_color_parse ("#EEEE00", &cor_blue);
  gdk_color_parse ("#8BA446", &cor);
  gdk_color_parse ("#EE7942", &cor1);
  gdk_color_parse ("#FFFFFF", &cor2);
    
  gtk_widget_modify_bg (info->frame[0], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_bg (info->frame[1], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_bg (info->frame[2], GTK_STATE_NORMAL, &cor_red);
    
  gtk_widget_modify_bg (info->button[2], GTK_STATE_NORMAL, &cor_blue);
  gtk_widget_modify_bg (info->button[3], GTK_STATE_NORMAL, &cor_blue);
  gtk_widget_modify_bg (info->button[5], GTK_STATE_NORMAL, &cor);
  gtk_widget_modify_bg (info->button[4], GTK_STATE_NORMAL, &cor);
  gtk_widget_modify_bg (info->button[6], GTK_STATE_NORMAL, &cor);

  gtk_widget_modify_bg (info->button[7], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[8], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[9], GTK_STATE_NORMAL, &cor1);
  gtk_widget_modify_bg (info->button[10], GTK_STATE_NORMAL, &cor1);

    
  gtk_widget_modify_fg (info->label[0], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[1], GTK_STATE_NORMAL, &cor_red);
  gtk_widget_modify_fg (info->label[4], GTK_STATE_NORMAL,&cor_red);
    
  gtk_widget_modify_fg (info->label[6], GTK_STATE_NORMAL, &cor2);
  gtk_widget_modify_fg (info->label[5], GTK_STATE_NORMAL, &cor2);
  gtk_widget_modify_fg (info->label[3], GTK_STATE_NORMAL, &cor2);
  gtk_widget_modify_fg (info->label[16], GTK_STATE_NORMAL,&cor_red);
    
  info->image = gdk_pixbuf_new_from_file ("47.jpg", NULL);
  gdk_pixbuf_render_pixmap_and_mask (info->image, &info->background, NULL, 0);
  info->style = gtk_style_new ();
  info->style->bg_pixmap[0] = info->background;
  gtk_widget_set_style (GTK_WIDGET(info->window), GTK_STYLE(info->style));
    
}

//_______________________________________________________________ERR



void
func_erro(data *info)

{
    
  info->window_erro = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
  gtk_window_set_position (GTK_WINDOW(info->window_erro), GTK_WIN_POS_CENTER);
  gtk_window_set_title (GTK_WINDOW(info->window_erro), "ERROR");
  gtk_window_set_default_size (GTK_WINDOW(info->window_erro), 400, 200);
  gtk_widget_set_app_paintable(info->window_erro, TRUE);
    
  info->vbox[3] = gtk_vbox_new(FALSE, 0);
  gtk_container_add (GTK_CONTAINER (info->window_erro),info->vbox[3]);
  gtk_widget_show (info->vbox[3] );
   
  info->label[8] = gtk_label_new ("\nUPS!\n\n");
  gtk_box_pack_start (GTK_BOX (info->vbox[3]), info->label[8], FALSE, FALSE, 0);
  gtk_widget_show (info->label[8]);
    
  info->label[10] = gtk_label_new ("\n\nIt is not possible to\n");
  gtk_box_pack_start (GTK_BOX (info->vbox[3]), info->label[10], FALSE, FALSE, 0);
  gtk_widget_show ( info->label[10]);
   
  info->label[11] = gtk_label_new ("\nrelease more pendulums, than\n");
  gtk_box_pack_start (GTK_BOX (info->vbox[3]),  info->label[11] , FALSE, FALSE, 0);
  gtk_widget_show ( info->label[11] );
    
  info->label[12] = gtk_label_new ("\ntheir total number.\n\n");
  gtk_box_pack_start (GTK_BOX (info->vbox[3]), info->label[12] , FALSE, FALSE, 0);
  gtk_widget_show ( info->label[12] );
    
  g_signal_connect(info->window,"delete_event",G_CALLBACK(gtk_widget_hide),NULL);
  gtk_widget_show(info->window_erro);
    
}
//_______________________________________________________________OBTER VALORES


void obter_valores (GtkWidget       *widget,
                    gpointer pointer)
{
  data *info;
  info = (data *)pointer;
    
  int i1,i;
    
  info->n_p = gtk_spin_button_get_value (GTK_SPIN_BUTTON(info->spin[0]));
  info->n_m_p_direita = gtk_spin_button_get_value (GTK_SPIN_BUTTON(info->spin[1]));
  info-> n_m_p_esquerda= gtk_spin_button_get_value (GTK_SPIN_BUTTON(info->spin[4]));
  
  if( info-> n_m_p_esquerda +info->n_m_p_direita > info->n_p)
    {
      func_erro(info);
      info->erro = 1;
    }
    
    
  if(info->erro==0)
    {
        
    
      for(i=0; i<26; i++)
	{
	  teta[i] = 0;
	  omega[i] = 0;
	}
 
    
      for (i1=0; i1<info->n_m_p_esquerda; ++i1)
    
	{
        
	  teta[i1]=-gtk_spin_button_get_value (GTK_SPIN_BUTTON(info->spin[5]))*0.0174;

	  omega[i1]=gtk_spin_button_get_value (GTK_SPIN_BUTTON(info->spin[6]));
	}
    
      for (i1= info->n_p-1; i1> info->n_p-info->n_m_p_direita-1; --i1)
        
	{
	  teta[i1]=gtk_spin_button_get_value (GTK_SPIN_BUTTON(info->spin[3]))*0.0174;
        
	  omega[i1]=-gtk_spin_button_get_value (GTK_SPIN_BUTTON(info->spin[2]));
	}
  
      info->pen[0]=20;
  
   
      posx[i] = poseqx + L*(teta[i]);
      posy[i] = poseqy- L*(1 - cos(teta[i]));
    }
}

//_______________________________________________________________RESET

void
do_inicio (GtkWidget *widget,
           
           gpointer pointer)
{
  int i;
    
  data *info;
  info = (data *)pointer;
    
  for(i=0; i<26; i++)
    {
      teta[i] = 0;
      omega[i] = 0;
    }
    
  gtk_adjustment_set_value(GTK_ADJUSTMENT(info->adj[1]),0);
  g_signal_connect( info->spin[1],"changed",G_CALLBACK(obter_valores), info);
    
  gtk_adjustment_set_value(GTK_ADJUSTMENT(info->adj[4]),0);
  g_signal_connect( info->spin[4],"changed",G_CALLBACK(obter_valores), info);
    
  gtk_adjustment_set_value(GTK_ADJUSTMENT(info->adj[2]),0);
  g_signal_connect( info->spin[2],"changed",G_CALLBACK(obter_valores), info);
    
  gtk_adjustment_set_value(GTK_ADJUSTMENT(info->adj[0]),3);
  g_signal_connect( info->spin[0],"changed",G_CALLBACK(obter_valores), info);
    
  gtk_adjustment_set_value(GTK_ADJUSTMENT(info->adj[5]),0);
  g_signal_connect( info->spin[5],"changed",G_CALLBACK(obter_valores), info);
    
  gtk_adjustment_set_value(GTK_ADJUSTMENT(info->adj[6]),0);
  g_signal_connect( info->spin[6],"changed",G_CALLBACK(obter_valores), info);
    
  gtk_adjustment_set_value(GTK_ADJUSTMENT(info->adj[3]),0);
  g_signal_connect( info->spin[3],"changed",G_CALLBACK(obter_valores), info);
    
  
    
  
    
  info->play=0;
    
}


gboolean
colisao(gdouble v1, gdouble v2)
{
  if(v1==0 && v2>0)
    return TRUE;
  else if(v1<0 && v1<v2)
    return TRUE;
  else if(v1>0 && v1<v2)
    return TRUE;
  return FALSE;
}

void
troca_valores (double *w1, double *w2)
{
  double w;
  w=(*w1);
  (*w1)=(*w2);
  (*w2)=w;
}

//_______________________________________________________________CAIRO


gboolean
on_expose_event (GtkWidget       *widget ,
                 GdkEventExpose  *event  ,
                 gpointer         pointer   )
{
  cairo_t        *cr ;
  int            width, height;
  int            i1 , i2,i3,troca;
  data *info;
  static double   dt;
  double dist;
  cairo_pattern_t *pat;
    
  info=(data*)pointer;

    
  gtk_window_get_size(GTK_WINDOW(info->window), &width, &height);
  cr = gdk_cairo_create(info->window->window);
 
    
    
  for (i1 = 0 ; i1 < .2e4 ; ++i1)
    {
      for (i2=0; i2<info->n_p; ++i2)
        {
	  if (info->play==0)
                
            {
	      dt=0;
                
            }
            
	  else
            {
	      dt=1e-4;
            }
            
	  omega[i2] = omega[i2] + (9.8/L)*sin(teta[i2])*dt;
	  teta[i2] = teta[i2] - omega[i2]*dt;
            
                
	  posx[i2] = poseqx + L*sin(teta[i2])+i2*40;
	  posy[i2] = poseqy- L*(1 - cos(teta[i2]));
        
    
	  if (posy[i2]<=20||posx[i2]<=20||posx[i2]>=janelaX-20)
            
	    {
	      omega[i2]=-omega[i2];
            
	    }
	}

    
    
      while(1)
        {
	  troca=0;
	  for(i3=0;i3<info->n_p-1;i3++)
            {

                
	      //COLISAO
                
	      dist = fabs(posx[i3]-posx[i3+1]);
	      if(dist<40)
                {
		  if(omega[i3]>0 && (omega[i3])<(omega[i3+1]))
                    {
		      troca_valores(&omega[i3], &omega[i3+1]);
		      troca=1;
                    }
		  if(omega[i3]==0 && omega[i3+1]>0)
                    {
		      troca_valores(&omega[i3], &omega[i3+1]);
		      troca=1;
                    }
		  if(omega[i3]<0 && omega[i3+1] > omega[i3])
                    {
		      troca_valores(&omega[i3], &omega[i3+1]);
		      troca=1;

                    }
                }
            }
	  if(troca==0)
	    break;
        }
      
        
        
    }
    

  /**** pendulo ****/
  for (i2=0; i2<info->n_p; ++i2)
        
    {
      
      cairo_move_to (cr, ox+i2*40, oy);
      cairo_line_to (cr, posx[i2], posy[i2]);
      cairo_move_to (cr,  posx[i2], posy[i2]);
      cairo_set_source_rgb (cr, 0., 0., 0.);
      cairo_set_line_width (cr, 2.0);
      cairo_arc (cr,  posx[i2], posy[i2], 20, 0, 2. * M_PI);
      cairo_stroke_preserve (cr);
      cairo_set_source_rgb (cr, .1+omega[i2]*0.2, .5-omega[i2]*0.2, .8);
      cairo_fill (cr);
        
      pat = cairo_pattern_create_radial (posx[i2]-7, posy[i2]-7, 1.,
					 posx[i2],  posy[i2], 35.0);
      cairo_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
      cairo_pattern_add_color_stop_rgba (pat, 1, .1+omega[i2]*6, .5-omega[i2]*6, .8, 0);
      cairo_set_source (cr, pat);
      cairo_arc (cr, posx[i2], posy[i2], 20., 0, 2 * M_PI);
      cairo_fill (cr);
      cairo_pattern_destroy (pat);
    
    }

    

  cairo_stroke(cr);
  cairo_destroy(cr);
    
   
   
  return FALSE;
}




static gboolean
time_handler (gpointer pointer)
{
  data   *info ;
    
  info = (data *) pointer;
    
  if (info->window->window == NULL)
    return FALSE;
    
  gtk_widget_queue_draw(info->window);
    
  return TRUE;
}





void about (GtkWidget *widget, GtkWidget *win)
{
  GtkWidget *dialog;
    
  dialog = gtk_about_dialog_new();
  gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG(dialog), "(c) Gloria de Sa Pereira, 81826 & João Cunha, 81541");
  gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG(dialog), "Newton's Cradle ");

  gtk_dialog_run (GTK_DIALOG (dialog));
   
    
  gtk_widget_show_all (dialog);
  gtk_widget_destroy (dialog);
}


void
quick_message (GtkWidget *w, GtkWidget *win)

{
    
  GtkWidget *dialog, *label;
  gchar *message = "Are you sure you want to Exit?";
  gint  resultado ;
    
    
  dialog = gtk_dialog_new_with_buttons ("Exit",
					GTK_WINDOW(win),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_YES,
					GTK_RESPONSE_YES,
					GTK_STOCK_NO,
					GTK_RESPONSE_NO,
					NULL);
  gtk_window_set_default_size (GTK_WINDOW(dialog), 200, 200);
  gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
  label = gtk_label_new (message);
    
    
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), label);
  gtk_widget_show_all (dialog);
    
  resultado = gtk_dialog_run (GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
    
  if (resultado == GTK_RESPONSE_YES)
    gtk_main_quit();
    
}


//_______________________________________________________________BOXES

void
box_all(data *info)
{
  //caixas
    
  info->vbox[0]= gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (info->window), info->vbox[0]);
    
    
    
  info->hbox[1]=gtk_hbox_new(0,0);
  gtk_box_pack_end (GTK_BOX (info->vbox[0]),info->hbox[1], FALSE, TRUE, 10);
    
    
  info->hbox[2]=gtk_hbox_new(0,0);
  gtk_box_pack_start (GTK_BOX (info->vbox[0]),info->hbox[2], FALSE, TRUE, 7);
    
  info->hbox[4]=gtk_hbox_new(0,0);
  gtk_box_pack_start (GTK_BOX (info->vbox[0]),info->hbox[4], FALSE, TRUE, 7);
    
    
  //frams
    
  info->frame[0] = gtk_frame_new (" Right ");
  gtk_frame_set_label_align ( GTK_FRAME(info->frame[0]) , 0.5 , 0.5 );
  gtk_box_pack_end ( GTK_BOX(info->hbox[1]) , info->frame[0] , FALSE , TRUE , 7 );
  gtk_box_pack_end(GTK_BOX (info->frame[0]),info->hbox[0], FALSE, TRUE, 7);
    
  info->frame[1] = gtk_frame_new (" Left ");
  gtk_frame_set_label_align ( GTK_FRAME(info->frame[1]) , 0.5 , 0.5 );
  gtk_box_pack_end ( GTK_BOX(info->hbox[1]) , info->frame[1] , FALSE , TRUE , 7 );
    
    
  info->frame[2] = gtk_frame_new ("");
  gtk_frame_set_label_align ( GTK_FRAME(info->frame[2]) , 0.5 , 0.5 );
  gtk_box_pack_end ( GTK_BOX(info->vbox[0]) , info->frame[2] , FALSE , TRUE , 7);
    
    
    
  info->vbox[1]= gtk_hbox_new (FALSE, 0);
  gtk_container_add(GTK_CONTAINER(info->frame[0]),info->vbox[1]);         //  COISAS PARA A DIREITA CAIXA 1
    
  info->vbox[2]=gtk_hbox_new(0,0);                                         // PARA A ESQUERDA CAIXA 2
  gtk_container_add(GTK_CONTAINER(info->frame[1]),info->vbox[2]);
    
    
    
  info->hbox[3]=gtk_hbox_new(0,0);
  gtk_container_add(GTK_CONTAINER(info->frame[2]),info->hbox[3]);
    
    

    
    
}

void
buttons_all(data *info)
{



    
    
  //NÚMERO DE PENDULOS
    
  info->label[0] = gtk_label_new (" Total Number of Pendulums ");
  gtk_box_pack_start (GTK_BOX (info->hbox[3]),info->label[0], FALSE, TRUE, 10);
    
    
  info->adj[0] = (GtkAdjustment *) gtk_adjustment_new (3.0, 2.0, 15.0, 1, 5.0, 0.0);
  info->spin[0] = gtk_spin_button_new (info->adj[0], 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(info->spin[0]), TRUE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spin[0]), 2);
  gtk_box_pack_start (GTK_BOX (info->hbox[3]),info->spin[0], FALSE, TRUE, 10);
    
    
  g_signal_connect(info->spin[0],"changed",G_CALLBACK(obter_valores),info);
   
    
  //Quit
    
  info->button[2]=gtk_button_new_with_mnemonic(" _Quit ");
  gtk_widget_set_size_request ( info->button[2], 80, 35);
  g_signal_connect ( info->button[2], "clicked", G_CALLBACK (quick_message), info->label[5]);
  gtk_box_pack_end (GTK_BOX (info->hbox[3]), info->button[2], FALSE, TRUE, 10);
  
    
  // Play
  info->button[6]= gtk_button_new_with_label ("Play");
  g_signal_connect ( info->button[6], "clicked", G_CALLBACK (func_play), info);
  gtk_widget_set_size_request ( info->button[6],80 , 35);
  gtk_box_pack_end (GTK_BOX (info->hbox[3]), info->button[6], FALSE, TRUE, 10);
    

    
  // Pausa
    
    
  info->button[4]= gtk_button_new_with_label ("Pause");
  g_signal_connect ( info->button[4], "clicked", G_CALLBACK (func_pausa), info);
  gtk_widget_set_size_request ( info->button[4],80 , 35);
  gtk_box_pack_end (GTK_BOX (info->hbox[3]), info->button[4], FALSE, TRUE, 10);
   
    
  //rest
    
    
  info->button[5]= gtk_button_new_with_mnemonic (" _Reset ");
  g_signal_connect ( info->button[5], "clicked", G_CALLBACK (do_inicio), info);
  gtk_widget_set_size_request ( info->button[5],80 , 35);
  gtk_box_pack_end (GTK_BOX (info->hbox[3]), info->button[5], FALSE, TRUE, 10);
    
   
    
  //miley
    
    
  info->button[7]= gtk_button_new_with_mnemonic ("_Miley");
  g_signal_connect ( info->button[7], "clicked", G_CALLBACK (miley), info);
  gtk_widget_set_size_request ( info->button[7],80 , 35);
  gtk_box_pack_end (GTK_BOX (info->hbox[2]), info->button[7], FALSE, TRUE, 10);
    
  //default
    
    
  info->button[8]= gtk_button_new_with_mnemonic ("_Default");
  g_signal_connect ( info->button[8], "clicked", G_CALLBACK (white), info);
  gtk_widget_set_size_request ( info->button[8],80 , 35);
  gtk_box_pack_end (GTK_BOX (info->hbox[2]), info->button[8], FALSE, TRUE, 10);
    

  //bet
    
    
  info->button[9]= gtk_button_new_with_mnemonic ("_Beatles ");
  g_signal_connect ( info->button[9], "clicked", G_CALLBACK (bet), info);
  gtk_widget_set_size_request ( info->button[9],80 , 35);
  gtk_box_pack_end (GTK_BOX (info->hbox[2]), info->button[9], FALSE, TRUE, 10);
    
  //linux
    
  info->button[10]= gtk_button_new_with_mnemonic ("_Linux ");
  g_signal_connect ( info->button[10], "clicked", G_CALLBACK (linux), info);
  gtk_widget_set_size_request ( info->button[10],80 , 35);
  gtk_box_pack_end (GTK_BOX (info->hbox[2]), info->button[10], FALSE, TRUE, 10);
    
 
    
  //Temas
  info->label[16] = gtk_label_new (" Themes: ");
  gtk_box_pack_end (GTK_BOX (info->hbox[2]),info->label[16], FALSE, TRUE, 10);
    



  //ABOUT
    
  info->button[3]=gtk_button_new_with_mnemonic(" _About ");
  gtk_widget_set_size_request ( info->button[3], 80, 35);
  g_signal_connect (info->button[3], "clicked", G_CALLBACK (about), info->label[6]);
  gtk_box_pack_start (GTK_BOX (info->hbox[2]),info->button[3], FALSE, TRUE, 10);
    
    
    
  //  _______________________________________________________________________________DIREITA vBOX1
    
   
    
  //NÚMERO DE MASSAS QUE PARTEM à DIREITA
  info->label[1] = gtk_label_new (" Number of pendulums that are released");
  gtk_box_pack_start (GTK_BOX (info->vbox[1]),info->label[1], FALSE, TRUE, 10);
    
    
  info->adj[1]= (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10.0, 1, 5.0, 0.0);
  info->spin[1]= gtk_spin_button_new ( info->adj[1], 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(info->spin[1]), TRUE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spin[1]), 2);
  gtk_box_pack_start (GTK_BOX (info->vbox[1]), info->spin[1], FALSE, TRUE, 10);
    
  g_signal_connect(info->spin[1],"changed",G_CALLBACK(obter_valores),info);
    
  
    
  //Vel à Direita
  info->label[2]= gtk_label_new (" Velocity (m/s)");
  gtk_box_pack_start (GTK_BOX (info->vbox[1]),info->label[2], FALSE, TRUE, 10);
    
    
  info->adj[2]= (GtkAdjustment *) gtk_adjustment_new (0.0, -50., 50., 0.05, 5.0, 0.0);
  info->spin[2] = gtk_spin_button_new (info->adj[2], 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(info->spin[2]), FALSE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spin[2]), 2);
  gtk_box_pack_start (GTK_BOX (info->vbox[1]), info->spin[2], FALSE, TRUE, 10);
   
    
  g_signal_connect(info->spin[2],"changed",G_CALLBACK(obter_valores),info);

    
  //Psição à Direita
    
  info->label[3]= gtk_label_new (" Angle (º)");
  gtk_box_pack_start (GTK_BOX (info->vbox[1]), info->label[3], FALSE, TRUE, 10);
    
    
  info->adj[3]= (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 86.0, 0.5, 5.0, 0.0);
  info->spin[3] = gtk_spin_button_new (info->adj[3], 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(info->spin[3]), TRUE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spin[3]), 2);
  gtk_box_pack_start (GTK_BOX (info->vbox[1]),info->spin[3], FALSE, TRUE, 10);
    
  
  g_signal_connect( info->spin[3],"changed",G_CALLBACK(obter_valores), info);

    
    
  //  _______________________________________________________________________________ESQUERDA VBOX2
    
  //NÚMERO DE MASSAS QUE PARTEM À ESQUERDA
  info->label[4]= gtk_label_new ( "Number of pendulums that are released");
  gtk_box_pack_start (GTK_BOX (info->vbox[2]), info->label[4], FALSE, TRUE, 10);
    
    
  info->adj[4]= (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10.0, 1, 5.0, 0.0);
  info->spin[4]= gtk_spin_button_new ( info->adj[4], 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(info->spin[4]), TRUE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spin[4]), 2);
  gtk_box_pack_start(GTK_BOX (info->vbox[2]), info->spin[4], FALSE, TRUE, 10);
    
  g_signal_connect(info->spin[4],"changed",G_CALLBACK(obter_valores),info);
    

  //Vel à esquerda!

  info->label[6]= gtk_label_new (" Velocity (m/s)");
  gtk_box_pack_start (GTK_BOX (info->vbox[2]),info->label[6], FALSE, TRUE, 10);
    
    
  info->adj[6]= (GtkAdjustment *) gtk_adjustment_new (0.0, -50., 50., 0.05, 5.0, 0.0);
  info->spin[6] = gtk_spin_button_new (info->adj[6], 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(info->spin[6]), FALSE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spin[6]), 2);
  gtk_box_pack_start (GTK_BOX (info->vbox[2]), info->spin[6], FALSE, TRUE, 10);
 
  
    
  g_signal_connect(info->spin[6],"changed",G_CALLBACK(obter_valores),info);
    
    
    
    
  //Psição à Esquerda
    
  info->label[5]= gtk_label_new (" Angle (º)");
  gtk_box_pack_start (GTK_BOX (info->vbox[2]), info->label[5], FALSE, TRUE, 10);
    
    
  info->adj[5]= (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 86.0, 0.5, 5.0, 0.0);
  info->spin[5] = gtk_spin_button_new (info->adj[5], 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(info->spin[5]), TRUE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spin[5]), 2);
  gtk_box_pack_start (GTK_BOX (info->vbox[2]),info->spin[5], FALSE, TRUE, 10);
    
    
   
  g_signal_connect( info->spin[5],"changed",G_CALLBACK(obter_valores), info);
  
   
   
   
}


//_______________________________________________________________MAIN



int
main(int argc, char **argv)
{
    
  gtk_init(&argc,&argv);
  data *info;
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("Baby-Baby-Bottle-icon.jpg", NULL);

      
  info = (data *) calloc (1, sizeof (data));
    
    
  info->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(info->window,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
  gtk_widget_set_size_request((info->window),janelaX,janelaY);
  gtk_window_set_title(GTK_WINDOW(info->window),"Newton's Cradle");
  gtk_window_set_position(GTK_WINDOW(info->window), GTK_WIN_POS_CENTER);
    
  gtk_window_set_default_icon (GDK_PIXBUF (pixbuf));
  
    
  info->n_p = 3;
    
    

    
  info->image = gdk_pixbuf_new_from_file ("white.jpg", NULL);
  gdk_pixbuf_render_pixmap_and_mask (info->image, &info->background, NULL, 0);
  info->style = gtk_style_new ();
  info->style->bg_pixmap[0] = info->background;
  gtk_widget_set_style (GTK_WIDGET(info->window), GTK_STYLE(info->style));


  info->pen=(gdouble*) malloc (4*sizeof(gdouble));

    
  info->play=0;
    
  gtk_widget_set_app_paintable(info->window, TRUE);
    
  box_all(info);
  buttons_all(info);
    
  g_timeout_add (10, (GSourceFunc) time_handler, info);
  g_signal_connect (info->window, "expose-event", G_CALLBACK(on_expose_event), info);
    
  gtk_widget_show_all(info->window);
  gtk_main();
    
  free(info);
  return 0;
}


