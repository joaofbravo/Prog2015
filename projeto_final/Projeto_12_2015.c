#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cairo.h>
#include <math.h>


//=============== Widgets e dados ===============

double win_xlen_percent = 0.6;
double win_ylen_percent = 0.8;
gchar *wintitle = "Movimento Browniano em 2D";

int p_gerar = 1;        //Gerar mais circulos quando 1
int mover_rato = 0;     //Mover com rato quando 1
int move = 0;           //Mover circulos quando 1
int p_desenhar = 1;     //Mostrar circulos quando 1
int mostra_vel = 0;     //Mostrar velocidade do circulo grande quando 1
int p_reset = 0;        //Gerar novos circulos pequenos com novas velocidades quando 1
int teste_val = 0;      //Força o teste de sobreposição mesmo em movimento quando 1
int da_fundo = 0;       //Mostrar fundos dos temas quando 1, 2, 3, 4

#define G_POS_X_INI     200
#define G_POS_Y_INI     150
#define G_RAIO_INI       50
#define G_VEL_INI        15
#define G_MASSA_INI      20

#define N_BOLAS_INI     100
#define N_BOLAS_MAX    1000
#define P_RAIO_INI        5
#define P_VEL_INI         5
#define P_MASSA_INI       5

//Para mostrar velocidade do grande
gchar string_gvel[128] = "Velocidade do círculo grande:  ";
gint len_string;

#ifdef _WIN32
gchar *image0 = "images\\pause.png";
gchar *image1 = "images\\play.png";
gchar *image2 = "images\\logoIST.png";
gchar *image3 = "images\\espaco.png";
gchar *image4 = "images\\vangogh.png";
gchar *image5 = "images\\linux.png";
gchar *image6 = "images\\egg.png";
gchar *image7 = "images\\easter.png";
#else
gchar *image0 = "images/pause.png";
gchar *image1 = "images/play.png";
gchar *image2 = "images/logoIST.png";
gchar *image3 = "images/espaco.png";
gchar *image4 = "images/vangogh.png";
gchar *image5 = "images/linux.png";
gchar *image6 = "images/egg.png";
gchar *image7 = "images/easter.png";
#endif


//Fundos e Temas
gchar *combo_text[8] = {
  "Fundos e Temas",
  "Default",
  "Selecionar Cor",
  "Espaço",
  "Van Gogh",
  "Linux, I Am Your Father!",
  "Negativo",
  "Easter Egg"
};

typedef struct{

  //----------_ Widgets base ----------
  GtkWidget *window;
  GtkWidget *hbox[7];
  GtkWidget *vbox[9];
  GtkWidget *sep[3];
  GtkWidget *toolbar;
  GtkToolItem *tb_exit, *tb_sobre;
  GtkWidget *dialog[2];
  GtkWidget *link[1];
  GtkWidget *frame[12];
  GtkWidget *button[8];
  GtkWidget *image[4];
  GtkWidget *label[7];
  GtkWidget *spin[6];
  GtkWidget *scale[3];
  //GtkWidget *entry[3];
  GtkAdjustment *adj[9];
  GtkWidget *color_chooser[3];
  GdkScreen *screen_size;
  GdkRGBA frames_color;
  GdkRGBA window_color;


  //---------- Desenho ----------
  GtkWidget *darea[1];
  GtkAllocation darea_alloc;
  GdkRGBA darea_color;
  GdkRGBA g_cor;
  GdkRGBA p_cor;

  //Fundos
  cairo_surface_t *cr_image[4];


  //---------- Dados Circulos ----------
  //Circulo grande
  gdouble g_pos_x;
  gdouble g_pos_y;
  gdouble g_raio;
  gdouble g_massa;
  gdouble g_vel;
  gdouble g_vel_x;
  gdouble g_vel_y;

  //Circulos pequenos
  gint n_bolas;
  gdouble *p_pos_x;
  gdouble *p_pos_y;
  gdouble p_raio;
  gdouble p_massa;
  gdouble p_vel;
  gdouble *p_vel_x;
  gdouble *p_vel_y;

  //Extras
  gdouble g_pos_max_x, g_pos_max_y;
  gdouble p_pos_max_x, p_pos_max_y;
  gdouble p_range_x, p_range_y;
  gdouble dist_min;
  
  //---------- Dados Rato ----------
  gdouble rato_pos[2];
  gdouble rato_press[2];
  gdouble rato_delta[2];

} data;



//=============== Criar Spin buttons ===============

GtkWidget* criar_spin_button(int i, double val_spin, double min, double max, double step, int cd, data *info){
  GtkWidget *spin_button;

  info->adj[i]= (GtkAdjustment*) gtk_adjustment_new (val_spin, min, max, step, 10, 0);

  spin_button= gtk_spin_button_new (info->adj[i], 0, cd);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(spin_button), TRUE);
  gtk_widget_set_size_request (spin_button, 100, 30);

  return spin_button;
}



//=============== Criar Scale ===============

GtkWidget* criar_scale(int i, double val_scale, double min, double max, double step, int cd, data* info){
  GtkWidget *scale;

  info->adj[i]= (GtkAdjustment*) gtk_adjustment_new (val_scale, min, max, step, 50, 0);

  scale= gtk_scale_new (GTK_ORIENTATION_HORIZONTAL, info->adj[i]);
  gtk_scale_set_digits (GTK_SCALE(scale), cd);
  gtk_scale_set_value_pos (GTK_SCALE(scale), GTK_POS_TOP);

  return scale;
}



/*=============== Criar Entry ===============

//isto nao tem limites, logo acabei por decidir não usar

GtkWidget* criar_entry(gchar *inicio, gint min, gint max){
GtkWidget *entry;
  
entry= gtk_entry_new ();
gtk_entry_set_input_purpose (GTK_ENTRY(entry), GTK_INPUT_PURPOSE_NUMBER);
 
gtk_entry_set_max_length (GTK_ENTRY(entry), 4);
gtk_entry_set_width_chars (GTK_ENTRY(entry), 4);
gtk_entry_set_text (GTK_ENTRY(entry), inicio);

return entry;
} */



//=============== Confirmar saida ===============

gboolean confirmar_sair (data *info){
  gint result; 

  info->dialog[0] = gtk_dialog_new_with_buttons ("Saída", GTK_WINDOW(info->window), 
						 GTK_DIALOG_DESTROY_WITH_PARENT, 
						 "_Sim, estou tonto...", GTK_RESPONSE_ACCEPT, 
						 "_Não! Deixa-me ficar!", GTK_RESPONSE_REJECT, 
						 NULL);
  
  gtk_window_set_default_size (GTK_WINDOW(info->dialog[0]), -1, 150);
  gtk_window_set_modal (GTK_WINDOW(info->dialog[0]), TRUE);

  info->label[2] = gtk_label_new ("O quê?? Queres mesmo sair?");
  gtk_widget_override_font (info->label[2], pango_font_description_from_string("15"));
  gtk_box_pack_start (GTK_BOX(gtk_bin_get_child (GTK_BIN(info->dialog[0]))), info->label[2], TRUE, FALSE, 0);
  gtk_widget_show_all (info->dialog[0]);
   
  result = gtk_dialog_run (GTK_DIALOG(info->dialog[0]));
  gtk_widget_destroy (info->dialog[0]);

  if (result == GTK_RESPONSE_ACCEPT)
    return TRUE;
  else
    return FALSE;
}



//=============== Botao Exit ===============

gboolean testar_sair (GtkWidget *widget, data *info){
 
  if (!(confirmar_sair(info)))
    return TRUE;

  gtk_main_quit();
  return FALSE;
}



//=============== Botao Sobre ===============

gboolean sobre_nos(GtkWidget *widget, data *info){
  
  info->dialog[1] = gtk_dialog_new_with_buttons ("Sobre Nós!", GTK_WINDOW(info->window), 
						 GTK_DIALOG_DESTROY_WITH_PARENT, 
						 "_Fechar", GTK_RESPONSE_ACCEPT, 
						 NULL);
  
  gtk_window_set_default_size (GTK_WINDOW(info->dialog[1]), 340, -1);
  gtk_window_set_modal (GTK_WINDOW(info->dialog[1]), TRUE);


  info->vbox[8] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX(gtk_bin_get_child (GTK_BIN(info->dialog[1]))), info->vbox[8], TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->vbox[8]), 10);
  
  info->label[3] = gtk_label_new ("Movimento Browniano em 2D");
  gtk_widget_override_font (info->label[3], pango_font_description_from_string("bold 16"));
  gtk_box_pack_start (GTK_BOX(info->vbox[8]), info->label[3], TRUE, TRUE, 10);
  
  info->image[2]= gtk_image_new_from_file(image2);
  gtk_box_pack_start (GTK_BOX(info->vbox[8]), info->image[2], TRUE, TRUE, 0);
  
  info->link[0] = gtk_link_button_new("http://arjuna.ist.utl.pt/IC/");
  gtk_box_pack_start (GTK_BOX(info->vbox[8]), info->link[0], TRUE, TRUE, 10);
  
  info->label[4] = gtk_label_new ("João Bravo & Carolina Martins");
  gtk_widget_override_font (info->label[4], pango_font_description_from_string("14"));
  gtk_box_pack_start (GTK_BOX(info->vbox[8]), info->label[4], TRUE, TRUE, 0);

  info->label[5] = gtk_label_new ("MEFT 2015/2016");
  gtk_widget_override_font (info->label[5], pango_font_description_from_string("12"));
  gtk_box_pack_start (GTK_BOX(info->vbox[8]), info->label[5], TRUE, TRUE, 0);

  gtk_widget_show_all (info->dialog[1]);
  gtk_dialog_run (GTK_DIALOG(info->dialog[1]));
  gtk_widget_destroy (info->dialog[1]);

  return FALSE;
}



//============= Seleção de cor ===============

gboolean color(int cc, int bt, gchar *titulo, GdkRGBA *cor, data *info){
  int result;
  
  info->color_chooser[cc] = gtk_color_chooser_dialog_new (titulo, GTK_WINDOW(info->window));
  result = gtk_dialog_run (GTK_DIALOG(info->color_chooser[cc]));

  if(result == GTK_RESPONSE_OK){
    gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(info->color_chooser[cc]), cor);
    gtk_widget_override_color (info->button[bt], GTK_STATE_NORMAL, cor);
  }

  gtk_widget_destroy (info->color_chooser[cc]);

  return FALSE;
}



//=============== Cor do circulo grande e dos pequenos ===============

gboolean gp_color(GtkWidget *widget, data *info){
   
  if(widget == info->button[2])
    color(0, 2, "Cor do Círculo Grande", &info->g_cor, info);
  if(widget == info->button[1])
    color(1, 1, "Cor dos Círculos Pequenos", &info->p_cor, info);
  
  return FALSE;
}



//=============== Fundos e Temas ===============

gboolean fundos_temas (GtkWidget *widget, data *info){
  int result;
 
  result = gtk_combo_box_get_active (GTK_COMBO_BOX (info->button[0]));

  switch (result){
  case 0:
    break;
    

    //Default
  case 1:
    da_fundo = 0;

    gdk_rgba_parse (&info->darea_color, "white");
    gdk_rgba_parse (&info->g_cor, "rgb(0, 0, 150)");
    gdk_rgba_parse (&info->p_cor, "rgb(60, 60, 60)");
    gdk_rgba_parse (&info->frames_color, "gray89");

    gtk_widget_override_background_color (info->frame[4], GTK_STATE_NORMAL, &info->darea_color);

    gtk_widget_override_color (info->button[2], GTK_STATE_NORMAL, &info->g_cor);
    gtk_widget_override_color (info->button[1], GTK_STATE_NORMAL, &info->p_cor);
    gtk_widget_override_color (info->button[0], GTK_STATE_NORMAL, NULL);

    gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[1], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[3], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->window, GTK_STATE_NORMAL, NULL);

    gtk_combo_box_set_active (GTK_COMBO_BOX(info->button[0]), 0);

    gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);

    break;


    //Selecionar Cor
  case 2:
    color(2, 0, "Cor do Fundo", &info->darea_color, info);
    gtk_widget_override_background_color (info->frame[4], GTK_STATE_NORMAL, &info->darea_color);

    da_fundo = 0;
      
    gtk_combo_box_set_active (GTK_COMBO_BOX(info->button[0]), 0);

    gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);

    break;


    //Espaço
  case 3:
    da_fundo = 1;

    gdk_rgba_parse (&info->g_cor, "rgb(230, 230, 230)");
    gdk_rgba_parse (&info->p_cor, "#CC66FF");
    gdk_rgba_parse (&info->frames_color, "#b7abc7");
    gdk_rgba_parse (&info->window_color, "#dbd5e3");

    gtk_widget_override_color (info->button[2], GTK_STATE_NORMAL, &info->g_cor);
    gtk_widget_override_color (info->button[1], GTK_STATE_NORMAL, &info->p_cor);
    gtk_widget_override_color (info->button[0], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[1], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[3], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->window, GTK_STATE_NORMAL, &info->window_color);

    gtk_combo_box_set_active (GTK_COMBO_BOX(info->button[0]), 0);

    gtk_widget_set_size_request (info->window, 1152, 864);
    gtk_window_set_resizable (GTK_WINDOW (info->window), FALSE);

    break;


    //Van Gogh
  case 4:
    da_fundo = 2;
      
    gdk_rgba_parse (&info->g_cor, "#FF9A00");
    gdk_rgba_parse (&info->p_cor, "rgb(230, 230, 230)");
    gdk_rgba_parse (&info->frames_color, "#FFFF99");
    gdk_rgba_parse (&info->window_color, "#000066");

    gtk_widget_override_color (info->button[2], GTK_STATE_NORMAL, &info->g_cor);
    gtk_widget_override_color (info->button[1], GTK_STATE_NORMAL, &info->p_cor);
    gtk_widget_override_color (info->button[0], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[1], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[3], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->window, GTK_STATE_NORMAL, &info->window_color);

    gtk_combo_box_set_active (GTK_COMBO_BOX(info->button[0]), 0);

    gtk_widget_set_size_request (info->window, 1152, 864);
    gtk_window_set_resizable (GTK_WINDOW (info->window), FALSE);

    break;


    //Linux, I Am Your Father!
  case 5:
    da_fundo = 3;

    gdk_rgba_parse (&info->g_cor, "rgb(0, 0, 210)");
    gdk_rgba_parse (&info->p_cor, "white");
    gdk_rgba_parse (&info->frames_color, "gray89");

    gtk_widget_override_color (info->button[2], GTK_STATE_NORMAL, &info->g_cor);
    gtk_widget_override_color (info->button[1], GTK_STATE_NORMAL, &info->p_cor);
    gtk_widget_override_color (info->button[0], GTK_STATE_NORMAL, NULL);

    gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[1], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[3], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->window, GTK_STATE_NORMAL, NULL);

    gtk_combo_box_set_active (GTK_COMBO_BOX(info->button[0]), 0);

    gtk_widget_set_size_request (info->window, 1152, 864);
    gtk_window_set_resizable (GTK_WINDOW (info->window), FALSE);

    break;


    //Negativo
  case 6:
    da_fundo = 0;

    gdk_rgba_parse (&info->darea_color, "black");
    gdk_rgba_parse (&info->g_cor, "rgb(255, 255, 105)");
    gdk_rgba_parse (&info->p_cor, "rgb(195, 195, 195)");
    gdk_rgba_parse (&info->frames_color, "rgb(80, 80, 80)");
    gdk_rgba_parse (&info->window_color, "rgb(40, 40, 40)");

    gtk_widget_override_background_color (info->frame[4], GTK_STATE_NORMAL, &info->darea_color);

    gtk_widget_override_color (info->button[2], GTK_STATE_NORMAL, &info->g_cor);
    gtk_widget_override_color (info->button[1], GTK_STATE_NORMAL, &info->p_cor);
    gtk_widget_override_color (info->button[0], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[1], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[3], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->window, GTK_STATE_NORMAL, &info->window_color);

    gtk_combo_box_set_active (GTK_COMBO_BOX(info->button[0]), 0);

    gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);

    break;


    //Easter Egg
  case 7:
    da_fundo = 4;

    gtk_widget_show (info->image[3]);
 
    gdk_rgba_parse (&info->darea_color, "white");
    gdk_rgba_parse (&info->g_cor, "rgb(0, 0, 150)");
    gdk_rgba_parse (&info->p_cor, "rgb(60, 60, 60)");
    gdk_rgba_parse (&info->frames_color, "gray89");

    gtk_widget_override_background_color (info->frame[4], GTK_STATE_NORMAL, &info->darea_color);

    gtk_widget_override_color (info->button[2], GTK_STATE_NORMAL, &info->g_cor);
    gtk_widget_override_color (info->button[1], GTK_STATE_NORMAL, &info->p_cor);
    gtk_widget_override_color (info->button[0], GTK_STATE_NORMAL, NULL);

    gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[1], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[3], GTK_STATE_NORMAL, &info->frames_color);
    gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &info->frames_color);

    gtk_widget_override_background_color (info->window, GTK_STATE_NORMAL, NULL);

    gtk_combo_box_set_active (GTK_COMBO_BOX(info->button[0]), 0);

    gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);

    break;
  }

  if(result != 0 && result != 7)
    gtk_widget_hide (info->image[3]);

  return FALSE;
}



//=============== Gerar Velocidades ===============

gboolean gerar_vel(gdouble vel, gdouble *vel_x, gdouble *vel_y){
  
  double ang;
 
  //Gerar angulo
  ang = ((double) rand() / (double) RAND_MAX) * 2*M_PI;
 
  *vel_x = vel * cos(ang);
  *vel_y = vel * sin(ang);
 
  return FALSE;
}



//=============== Gerar circulos ===============

gboolean gerar_circulos(data *info){

  int i=0;
  double p_posx;
  static double pvel = 0;

  while(i < info->n_bolas){
    p_posx = info->p_pos_x[i];

    //Gerar posiçoes
    if(p_posx < 0.01 || p_reset == 1){
      info->p_pos_x[i] = ((double) rand()) / ((double) RAND_MAX) * info->p_range_x + info->p_raio;
      info->p_pos_y[i] = ((double) rand()) / ((double) RAND_MAX) * info->p_range_y + info->p_raio;
    }
    

    //Gerar velocidades
    if(info->p_vel != pvel || p_posx < 0.01 || p_reset == 1)
      gerar_vel(info->p_vel, &info->p_vel_x[i], &info->p_vel_y[i]);

    ++i;
  }

  pvel = info->p_vel;


  //Para apagar os circulos restantes
  while(i < N_BOLAS_MAX){
    info->p_pos_x[i] = 0.;
    info->p_pos_y[i] = 0.;
    ++i;
  }

  return FALSE;
}



//=============== Botao Pausa ===============

gboolean pausa (GtkWidget *widget, data *info){
  move = 0;
  return FALSE;
}



//=============== Botao Play ===============

gboolean play (GtkWidget *widget, data *info){
  move = 1;
  return FALSE;
}



//=============== Botao Reset ===============

gboolean reset_val (GtkWidget *widget, data *info){

  gtk_adjustment_set_value(info->adj[0], G_RAIO_INI);
  gtk_adjustment_set_value(info->adj[1], P_RAIO_INI);
  gtk_adjustment_set_value(info->adj[2], G_MASSA_INI);
  gtk_adjustment_set_value(info->adj[3], P_MASSA_INI);

  gtk_adjustment_set_value(info->adj[4], G_VEL_INI);
  gerar_vel(info->g_vel, &info->g_vel_x, &info->g_vel_y);

  gtk_adjustment_set_value(info->adj[5], P_VEL_INI);

  gtk_adjustment_set_value(info->adj[6], N_BOLAS_INI);
  gtk_adjustment_set_value(info->adj[7], G_POS_X_INI);
  gtk_adjustment_set_value(info->adj[8], G_POS_Y_INI);

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (info->button[7]), FALSE); 
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (info->button[6]), FALSE); 

  move = 0;
  p_desenhar = 1;
  mostra_vel = 0;
  p_gerar = 0;
  da_fundo = 0;

  //Gerar novos circulos pequenos com novas velocidades
  p_reset = 1;
  gerar_circulos(info);
  p_reset = 0;

  gtk_widget_hide (info->label[6]);
  gtk_widget_hide (info->image[3]);

  gdk_rgba_parse (&info->darea_color, "white");
  gdk_rgba_parse (&info->g_cor, "rgb(0, 0, 150)");
  gdk_rgba_parse (&info->p_cor, "rgb(60, 60, 60)");
  gdk_rgba_parse (&info->frames_color, "gray89");

  gtk_widget_override_background_color (info->frame[4], GTK_STATE_NORMAL, &info->darea_color);

  gtk_widget_override_color (info->button[2], GTK_STATE_NORMAL, &info->g_cor);
  gtk_widget_override_color (info->button[1], GTK_STATE_NORMAL, &info->p_cor);
  gtk_widget_override_color (info->button[0], GTK_STATE_NORMAL, NULL);

  gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &info->frames_color);
  gtk_widget_override_background_color (info->frame[1], GTK_STATE_NORMAL, &info->frames_color);
  gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &info->frames_color);
  gtk_widget_override_background_color (info->frame[3], GTK_STATE_NORMAL, &info->frames_color);
  gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &info->frames_color);

  gtk_widget_override_background_color (info->window, GTK_STATE_NORMAL, NULL);

  gtk_combo_box_set_active (GTK_COMBO_BOX(info->button[0]), 0);

  gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);

  return FALSE;
}



//=============== Esconder circulos pequenos ===============

gboolean esconder_pequenos (GtkWidget *widget, data *info){

  if(p_desenhar == 1)
    p_desenhar = 0;
   
  else
    p_desenhar = 1;

  return FALSE;
}



//=============== Mostrar velocidades ===============

gboolean mostrar_velocidade (GtkWidget *widget, data *info){
    
  if(mostra_vel == 0){
    gtk_widget_show (info->label[6]);
    mostra_vel = 1;
  }
  
  else{
    gtk_widget_hide (info->label[6]);
    mostra_vel = 0;
  }
 
  return FALSE;
}



//=============== Obter Valores dos Widgets ===============

gboolean obter_valores (GtkWidget *widget, data *info){

  if(widget == info->spin[0]){
    info->g_raio = gtk_adjustment_get_value (info->adj[0]);
    gtk_adjustment_set_lower (info->adj[7], info->g_raio);
    gtk_adjustment_set_lower (info->adj[8], info->g_raio);
    teste_val = 1;
  }

  if(widget == info->spin[1]){
    info->p_raio = gtk_adjustment_get_value (info->adj[1]);
    teste_val = 1;
  }

  if(widget == info->spin[2])
    info->g_massa = gtk_adjustment_get_value (info->adj[2]);
  if(widget == info->spin[3])
    info->p_massa = gtk_adjustment_get_value (info->adj[3]);

  if(widget == info->spin[4]){
    info->g_vel = gtk_adjustment_get_value (info->adj[4]);
    gerar_vel(info->g_vel, &info->g_vel_x, &info->g_vel_y);
    move = 0;
  }
  if(widget == info->spin[5]){
    info->p_vel = gtk_adjustment_get_value (info->adj[5]);
    p_gerar = 1;
    move = 0;
  }

  if(widget == info->scale[2]){
    info->n_bolas = (gint) gtk_adjustment_get_value (info->adj[6]);
    p_gerar = 1;
    teste_val = 1;
  }

  if(widget == info->scale[0]){
    info->g_pos_x = gtk_adjustment_get_value (info->adj[7]);
    teste_val = 1;
  }

  if(widget == info->scale[1]){
    info->g_pos_y = gtk_adjustment_get_value (info->adj[8]);
    teste_val = 1;
  }

  return FALSE;
}



//=============== Mover com rato ===============

gboolean mouse_motion (GtkWidget *widget, GdkEvent *event, data *info){
  double distancia, g_raio2;
  
  if (event->type == GDK_MOTION_NOTIFY){
    info->rato_pos[0] = ((GdkEventMotion*) event)->x;
    info->rato_pos[1] = ((GdkEventMotion*) event)->y;

    if (mover_rato == 1){

      //Para x
      if ((info->rato_pos[0] + info->rato_delta[0]) > info->g_pos_max_x)
      	info->g_pos_x = info->g_pos_max_x;
      else if ((info->rato_pos[0] + info->rato_delta[0]) < info->g_raio)
	info->g_pos_x = info->g_raio;
      else
	info->g_pos_x = info->rato_pos[0] + info->rato_delta[0];

      //Para y
      if ((info->rato_pos[1] + info->rato_delta[1]) > info->g_pos_max_y)
	info->g_pos_y = info->g_pos_max_y;
      else if ((info->rato_pos[1] + info->rato_delta[1]) < info->g_raio)
	info->g_pos_y = info->g_raio;
      else
	info->g_pos_y = info->rato_pos[1] + info->rato_delta[1];
    }
  }
 

  if (event->type == GDK_BUTTON_PRESS){
    //Debugging purpose: printf("Event: Button Press - x: %.2lf ; y: %2lf\n", info->rato_pos[0], info->rato_pos[1]);

    info->rato_press[0] = ((GdkEventButton*) event)->x;
    info->rato_press[1] = ((GdkEventButton*) event)->y;

    info->rato_delta[0] = info->g_pos_x - info->rato_press[0];
    info->rato_delta[1] = info->g_pos_y - info->rato_press[1];
      
    distancia = (info->rato_delta[0] * info->rato_delta[0]) + (info->rato_delta[1] * info->rato_delta[1]);
    g_raio2 = info->g_raio * info->g_raio;

    if (distancia < g_raio2){
      mover_rato = 1;

      info->g_pos_x = info->rato_press[0] + info->rato_delta[0];
      info->g_pos_y = info->rato_press[1] + info->rato_delta[1];
    }
  }


  if (event->type == GDK_BUTTON_RELEASE){
    //Debugging purpose: printf("Event: Button Release\n");
    mover_rato = 0;
  }

  return FALSE;
}



//=============== Teste de Sobreposicao e Colisao ===============

gboolean teste_sobrepor_colidir(data *info, int i, int t){

  double cat_x, cat_y, hipotenusa;
  
  if(t == 1){
    if(info->p_pos_x[i] < info->p_raio)
      return FALSE;
    if(info->p_pos_y[i] < info->p_raio)
      return FALSE;
    if(info->p_pos_x[i] > info->p_pos_max_x)
      return FALSE;
    if(info->p_pos_y[i] > info->p_pos_max_y)
      return FALSE;

    cat_x= info->g_pos_x - info->p_pos_x[i];
    cat_y= info->g_pos_y - info->p_pos_y[i];
    hipotenusa = sqrt(cat_x * cat_x + cat_y * cat_y);
  
    if(hipotenusa < info->dist_min)
      return FALSE;
  }
 
  if(t == 2){
    cat_x = (info->g_pos_x + (info->g_vel_x / 100)) - (info->p_pos_x[i] + (info->p_vel_x[i] / 100));
    cat_y = (info->g_pos_y + (info->g_vel_y / 100)) - (info->p_pos_y[i] + (info->p_vel_y[i] / 100));
    hipotenusa = sqrt(cat_x * cat_x + cat_y * cat_y);

    if(hipotenusa <= info->dist_min)
      return FALSE;
  }

  return TRUE;
}



//=============== Colisoes ===============

gboolean colisoes (data *info, int i){

  double p_vi, p_vi_x, p_vi_y;
  double p_vf, g_vf;
  double ang_pos, ang_pvel, theta, phi;
  //double energia;

  //Debugging purpose:  
  //energia = 0.5 * (info->p_massa * ((info->p_vel_x[i] * info->p_vel_x[i]) + (info->p_vel_y[i] * info->p_vel_y[i])) + info->g_massa * ((info->g_vel_x * info->g_vel_x) + (info->g_vel_y * info->g_vel_y)));
  //printf(" %lf \n", energia);

  //Vi de p
  p_vi_x = info->p_vel_x[i] - info->g_vel_x;
  p_vi_y = info->p_vel_y[i] - info->g_vel_y;
  p_vi = sqrt((p_vi_x * p_vi_x) + (p_vi_y * p_vi_y));

  //Angulos
  ang_pos = atan2(info->p_pos_y[i] - info->g_pos_y, info->p_pos_x[i] - info->g_pos_x);
  ang_pvel = atan2(p_vi_y, p_vi_x);
  theta = ang_pos - ang_pvel;
  phi = atan2 (((info->p_massa + info->g_massa) * tan(theta)), (info->p_massa - info->g_massa)) - theta;

  //Vf de p e g
  p_vf = sin(theta) / sin(theta + phi) * p_vi;
  g_vf = (info->p_massa / (info->p_massa + info->g_massa)) * 2 * cos(theta) * p_vi;

  //Velocidades finais
  info->p_vel_x[i] = (p_vf * cos(ang_pvel - phi)) + info->g_vel_x;
  info->p_vel_y[i] = (p_vf * sin(ang_pvel - phi)) + info->g_vel_y;
  info->g_vel_x = g_vf * cos(ang_pos) + info->g_vel_x;
  info->g_vel_y = g_vf * sin(ang_pos) + info->g_vel_y;

  //Debugging purpose:
  //energia = 0.5 * (info->p_massa * ((info->p_vel_x[i] * info->p_vel_x[i]) + (info->p_vel_y[i] * info->p_vel_y[i])) + info->g_massa * ((info->g_vel_x * info->g_vel_x) + (info->g_vel_y * info->g_vel_y)));
  //printf (" %lf \n\n", energia);
  
  return FALSE;
}



//=============== Desenhar circulos ===============

gboolean desenhar (GtkWidget *darea, cairo_t *cr, data *info){

  int i, i2;
  static int alloc_width = 0, alloc_height = 0, praio = 0, graio = 0;

  //Obter tamanho da janela  
  gtk_widget_get_allocation(darea, &info->darea_alloc);


  //Alterar maximo das scales x e y
  if(alloc_width != info->darea_alloc.width || alloc_height != info->darea_alloc.height || graio != info->g_raio){
    info->g_pos_max_x = info->darea_alloc.width - info->g_raio;
    info->g_pos_max_y = info->darea_alloc.height - info->g_raio;

    if(gtk_adjustment_get_upper(info->adj[7]) != info->g_pos_max_x)
      gtk_adjustment_set_upper (info->adj[7], info->g_pos_max_x);

    if(gtk_adjustment_get_upper(info->adj[8]) != info->g_pos_max_y)
      gtk_adjustment_set_upper (info->adj[8], info->g_pos_max_y);
  }

  gtk_adjustment_set_value(info->adj[7], info->g_pos_x);
  gtk_adjustment_set_value(info->adj[8], info->g_pos_y);
 

  //Alterar tamanho do frame das scales x e y
  if(alloc_width != info->darea_alloc.width)
    gtk_widget_set_size_request (info->frame[5], info->darea_alloc.width /2, -1);


  if(alloc_width != info->darea_alloc.width || alloc_height != info->darea_alloc.height || praio != info->p_raio || graio != info->g_raio){
    info->p_pos_max_x = info->darea_alloc.width - info->p_raio;
    info->p_pos_max_y = info->darea_alloc.height - info->p_raio;
    info->p_range_x = info->p_pos_max_x - info->p_raio;
    info->p_range_y = info->p_pos_max_y - info->p_raio;
    info->dist_min = info->g_raio + info->p_raio;

    alloc_width = info->darea_alloc.width;
    alloc_height = info->darea_alloc.height;
    praio = info->p_raio;
    graio = info->g_raio;
  }


  //Alterar Fundos dos Temas
  switch (da_fundo){
  case 0:
    break;
    
  case 1:
    cairo_set_source_surface (cr, info->cr_image[0], 0, 0);
    cairo_paint (cr);

    break;

  case 2:
    cairo_set_source_surface (cr, info->cr_image[1], 0, 0);
    cairo_paint (cr);

    break;
  
  case 3:
    cairo_set_source_surface (cr, info->cr_image[2], 0, 0);
    cairo_paint (cr);

    break;
   
  case 4:
    cairo_set_source_surface (cr, info->cr_image[3], info->darea_alloc.width * 0.8, info->darea_alloc.height * 0.1);
    cairo_paint (cr);

    break;
  }


  //Desenhar circulo grande
  cairo_arc(cr, info->g_pos_x, info->g_pos_y, info->g_raio, 0, 2*M_PI);
  cairo_set_source_rgb(cr, info->g_cor.red, info->g_cor.green, info->g_cor.blue);
  cairo_fill(cr);
  cairo_stroke(cr);


  //Gera circulos pequenos
  if (p_gerar == 1){
    gerar_circulos(info);
    p_gerar = 0;
  }


  for(i=0; i < info->n_bolas; ++i){

    if(move == 0 || teste_val == 1){
      //Testa se circulos estao nos limites da frame e nao intercetam o grande
      while(teste_sobrepor_colidir(info, i, 1) == FALSE){
        info->p_pos_x[i] = ((double) rand()) / ((double) RAND_MAX) * info->p_range_x + info->p_raio;
        info->p_pos_y[i] = ((double) rand()) / ((double) RAND_MAX) * info->p_range_y + info->p_raio;
      }
    }


    //Desenhar circulos pequenos
    if(p_desenhar == 1){
      cairo_arc(cr, info->p_pos_x[i], info->p_pos_y[i], info->p_raio, 0, 2*M_PI);
      cairo_set_source_rgb(cr, info->p_cor.red, info->p_cor.green, info->p_cor.blue);
      cairo_fill(cr);
      cairo_stroke(cr);
    }
  }

  if(teste_val == 1)
    teste_val = 0;


  //Mover Circulos
  if (move == 1){

    //Mover circulo grande
    for(i2=0; i2 < 100; ++i2){
      info->g_pos_x += (info->g_vel_x / 100);
      info->g_pos_y += (info->g_vel_y / 100);

      if (info->g_pos_x < info->g_raio){
	info->g_vel_x = - info->g_vel_x;
	info->g_pos_x = info->g_raio;
      }

      if (info->g_pos_y < info->g_raio){
	info->g_vel_y = - info->g_vel_y;
	info->g_pos_y = info->g_raio;
      }

      if (info->g_pos_x > info->g_pos_max_x){
	info->g_vel_x = - info->g_vel_x;
	info->g_pos_x = info->g_pos_max_x;
      }


      if (info->g_pos_y > info->g_pos_max_y){
	info->g_vel_y = - info->g_vel_y;
	info->g_pos_y = info->g_pos_max_y;
      }


      //Mover circulos pequenos
      for(i=0; i < info->n_bolas; ++i){
	info->p_pos_x[i] += (info->p_vel_x[i] / 100);
	info->p_pos_y[i] += (info->p_vel_y[i] / 100);

	if (info->p_pos_x[i] < info->p_raio){
	  info->p_vel_x[i] = - info->p_vel_x[i];
	  info->p_pos_x[i] = info->p_raio;
	}

	if (info->p_pos_y[i] < info->p_raio){
	  info->p_vel_y[i] = - info->p_vel_y[i];
	  info->p_pos_y[i] = info->p_raio;
	}

	if (info->p_pos_x[i] > info->p_pos_max_x){
	  info->p_vel_x[i] = - info->p_vel_x[i];
	  info->p_pos_x[i] = info->p_pos_max_x;
	}

	if (info->p_pos_y[i] > info->p_pos_max_y){
	  info->p_vel_y[i] = - info->p_vel_y[i];
	  info->p_pos_y[i] = info->p_pos_max_y;
	}

	//Testa se circulos colidem
	if(teste_sobrepor_colidir(info, i, 2) == FALSE)
	  colisoes(info, i);
      }
    }
  }

  //Mostrar velocidade do circulo grande
  if(mostra_vel == 1){
    sprintf (&string_gvel[len_string], "%lf", sqrt((info->g_vel_x * info->g_vel_x) + (info->g_vel_y * info->g_vel_y)));
    gtk_label_set_text(GTK_LABEL(info->label[6]), string_gvel);
  }

  return FALSE;
}



//=============== Mover ===============

gboolean mover (data *info){

  if ((!GTK_IS_WIDGET (info->darea[0])) || (!gtk_widget_get_window (info->darea[0])))
    return FALSE;

  gtk_widget_queue_draw (info->darea[0]);

  return TRUE;
}



//=============== Criar Estrutura ===============

gboolean criar_estrutura(data *info){

  info->window= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(info->window), win_xlen_percent * gdk_screen_get_width(info->screen_size), win_ylen_percent * gdk_screen_get_height(info->screen_size));
  gtk_window_set_title (GTK_WINDOW(info->window), wintitle);
  gtk_window_set_position (GTK_WINDOW(info->window), GTK_WIN_POS_CENTER);

  g_signal_connect (G_OBJECT(info->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);


  //=============== Boxes ===============

  info->vbox[0]= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(info->window), info->vbox[0]);


  info->hbox[0]= gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(info->vbox[0]), info->hbox[0], FALSE, FALSE, 0);

  info->sep[0] = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX(info->vbox[0]), info->sep[0], FALSE, TRUE, 0);

  info->hbox[1]= gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(info->vbox[0]), info->hbox[1], TRUE, TRUE, 0);


  info->vbox[1]= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX(info->hbox[1]), info->vbox[1], TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->vbox[1]), 10);

  info->sep[1] = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
  gtk_box_pack_start (GTK_BOX(info->hbox[1]), info->sep[1], FALSE, TRUE, 0);

  info->vbox[2]= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX(info->hbox[1]), info->vbox[2], FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->vbox[2]), 10);


  //=============== Toolbar topo ===============

  info->toolbar= gtk_toolbar_new ();
  gtk_toolbar_set_style (GTK_TOOLBAR(info->toolbar), GTK_TOOLBAR_ICONS);
  gtk_container_set_border_width(GTK_CONTAINER(info->toolbar), 2);
  gtk_box_pack_start (GTK_BOX(info->hbox[0]), info->toolbar, FALSE, FALSE, 2);

  info->tb_exit= gtk_tool_button_new (NULL, "Quit");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON(info->tb_exit), "application-exit");
  gtk_toolbar_insert (GTK_TOOLBAR(info->toolbar), info->tb_exit, -1);
  g_signal_connect (G_OBJECT(info->tb_exit), "clicked", G_CALLBACK(testar_sair), info);

  info->tb_sobre= gtk_tool_button_new (NULL, "Sobre");
  gtk_toolbar_insert (GTK_TOOLBAR(info->toolbar), info->tb_sobre, -1);
  g_signal_connect (G_OBJECT(info->tb_sobre), "clicked", G_CALLBACK(sobre_nos), info);



  //=============== Lado direito ===============


  //=============== Raio ===============

  info->frame[0]= gtk_frame_new (" Raio ");
  gtk_box_pack_start (GTK_BOX(info->vbox[2]), info->frame[0], FALSE, FALSE, 10);
  gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &info->frames_color);
  gtk_frame_set_label_align (GTK_FRAME(info->frame[0]), 0.5, 1);

  info->vbox[5]= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(info->frame[0]), info->vbox[5]);
  gtk_container_set_border_width (GTK_CONTAINER (info->vbox[5]), 5);


  //---------- Raio - Spin buttons ----------

  info->frame[6]= gtk_frame_new (" Grande ");
  gtk_box_pack_start (GTK_BOX(info->vbox[5]), info->frame[6], FALSE, FALSE, 5);

  info->spin[0] = criar_spin_button (0, G_RAIO_INI, 0, 275, 1, 2, info);
  gtk_container_add (GTK_CONTAINER(info->frame[6]), info->spin[0]);
  g_signal_connect (G_OBJECT(info->spin[0]), "value_changed", G_CALLBACK(obter_valores), info);

  info->frame[7]= gtk_frame_new (" Pequenos ");
  gtk_box_pack_start (GTK_BOX(info->vbox[5]), info->frame[7], FALSE, FALSE, 5);

  info->spin[1] = criar_spin_button (1, P_RAIO_INI, 0, 100, 1, 2, info);
  gtk_container_add (GTK_CONTAINER(info->frame[7]), info->spin[1]);  
  g_signal_connect (G_OBJECT(info->spin[1]), "value_changed", G_CALLBACK(obter_valores), info);


  //=============== Massa ===============

  info->frame[1]= gtk_frame_new (" Massa ");
  gtk_box_pack_start (GTK_BOX(info->vbox[2]), info->frame[1], FALSE, FALSE, 10);
  gtk_widget_override_background_color (info->frame[1], GTK_STATE_NORMAL, &info->frames_color);
  gtk_frame_set_label_align (GTK_FRAME(info->frame[1]), 0.5, 1);

  info->vbox[6]= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(info->frame[1]), info->vbox[6]);
  gtk_container_set_border_width (GTK_CONTAINER (info->vbox[6]), 5);


  //---------- Massa - Spin buttons ----------

  info->frame[8]= gtk_frame_new (" Grande ");
  gtk_box_pack_start (GTK_BOX(info->vbox[6]), info->frame[8], FALSE, FALSE, 5);

  info->spin[2] = criar_spin_button (2, G_MASSA_INI, 0, 200, 0.5, 3, info);
  gtk_container_add (GTK_CONTAINER(info->frame[8]), info->spin[2]);
  g_signal_connect (G_OBJECT(info->spin[2]), "value_changed", G_CALLBACK(obter_valores), info);

  info->frame[9]= gtk_frame_new (" Pequenos ");
  gtk_box_pack_start (GTK_BOX(info->vbox[6]), info->frame[9], FALSE, FALSE, 5);

  info->spin[3] = criar_spin_button (3, P_MASSA_INI, 0, 100, 0.5, 3, info);
  gtk_container_add (GTK_CONTAINER(info->frame[9]), info->spin[3]);
  g_signal_connect (G_OBJECT(info->spin[3]), "value_changed", G_CALLBACK(obter_valores), info);


  //=============== Velocidade Inicial ===============

  info->frame[2]= gtk_frame_new (" Velocidade Inicial ");
  gtk_box_pack_start (GTK_BOX(info->vbox[2]), info->frame[2], FALSE, FALSE, 10);
  gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &info->frames_color);
  gtk_frame_set_label_align (GTK_FRAME(info->frame[2]), 0.5, 1);

  info->vbox[7]= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(info->frame[2]), info->vbox[7]);
  gtk_container_set_border_width (GTK_CONTAINER (info->vbox[7]), 5);


  //---------- Velocidade Inicial - Spin buttons ----------

  info->frame[10]= gtk_frame_new (" Grande ");
  gtk_box_pack_start (GTK_BOX(info->vbox[7]), info->frame[10], FALSE, FALSE, 5);

  info->spin[4] = criar_spin_button (4, G_VEL_INI, 0, 50, 0.5, 2, info);
  gtk_container_add (GTK_CONTAINER(info->frame[10]), info->spin[4]);
  g_signal_connect (G_OBJECT(info->spin[4]), "value_changed", G_CALLBACK(obter_valores), info);

  info->frame[11]= gtk_frame_new (" Pequenos ");
  gtk_box_pack_start (GTK_BOX(info->vbox[7]), info->frame[11], FALSE, FALSE, 5);

  info->spin[5] = criar_spin_button (5, P_VEL_INI, 0, 50, 0.5, 2, info);
  gtk_container_add (GTK_CONTAINER(info->frame[11]), info->spin[5]);
  g_signal_connect (G_OBJECT(info->spin[5]), "value_changed", G_CALLBACK(obter_valores), info);


  //=============== Nº de circulos pequenos - Scale ===============

  info->frame[3]= gtk_frame_new (" Nº de círculos pequenos ");
  gtk_box_pack_start (GTK_BOX(info->vbox[2]), info->frame[3], FALSE, FALSE, 10);
  gtk_widget_override_background_color (info->frame[3], GTK_STATE_NORMAL, &info->frames_color);
  gtk_frame_set_label_align (GTK_FRAME(info->frame[3]), 0.5, 1);

  info->hbox[6]= gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER(info->frame[3]), info->hbox[6]);
  gtk_container_set_border_width (GTK_CONTAINER (info->hbox[6]), 5);
  gtk_widget_set_size_request (info->hbox[6], 250, -1);

  info->scale[2]= criar_scale(6, N_BOLAS_INI, 0, N_BOLAS_MAX, 1, 0, info);
  gtk_box_pack_start (GTK_BOX(info->hbox[6]), info->scale[2], TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(info->scale[2]), "value_changed", G_CALLBACK(obter_valores), info);

  /* info->entry[2] = criar_entry ("100", 0, 1000);
     gtk_widget_set_size_request (info->entry[2], 20, 20);
     gtk_box_pack_end (GTK_BOX (info->hbox[6]), info->entry[2], FALSE, FALSE, 5); */


  //=============== Botoes de Cor ===============
  
  int i1;
  info->button[0]= gtk_combo_box_text_new ();
  for (i1=0 ; i1 < 8 ; ++i1)
    gtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (info->button[0]), i1, NULL, combo_text[i1]);
  gtk_combo_box_set_active (GTK_COMBO_BOX (info->button[0]), 0);

  gtk_widget_set_size_request (info->button[0], 160, 40);
  gtk_box_pack_end (GTK_BOX(info->vbox[2]), info->button[0], FALSE, FALSE, 6);
  g_signal_connect (info->button[0], "changed", G_CALLBACK(fundos_temas), info);


  info->button[1]= gtk_button_new_with_label ("Cor dos círculos pequenos");
  gtk_widget_set_size_request (info->button[1], 160, 40);
  gtk_widget_override_color (info->button[1], GTK_STATE_NORMAL, &info->p_cor);
  gtk_box_pack_end (GTK_BOX(info->vbox[2]), info->button[1], FALSE, FALSE, 6);
  g_signal_connect (info->button[1], "clicked", G_CALLBACK(gp_color), info);

  info->button[2]= gtk_button_new_with_label ("Cor do círculo grande");
  gtk_widget_set_size_request (info->button[2], 160, 40);
  gtk_widget_override_color (info->button[2], GTK_STATE_NORMAL, &info->g_cor);
  gtk_box_pack_end (GTK_BOX(info->vbox[2]), info->button[2], FALSE, FALSE, 6);
  g_signal_connect (info->button[2], "clicked", G_CALLBACK(gp_color), info);

  info->sep[3]= gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_end (GTK_BOX(info->vbox[2]), info->sep[3], FALSE, TRUE, 6);



  //=============== Lado esquerdo ===============

  info->frame[4]= gtk_frame_new (NULL);
  gtk_widget_override_background_color (info->frame[4], GTK_STATE_NORMAL, &info->darea_color);
  gtk_box_pack_start (GTK_BOX(info->vbox[1]), info->frame[4], TRUE, TRUE, 0);

  info->hbox[2]= gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(info->vbox[1]), info->hbox[2], FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->hbox[2]), 0);

  info->sep[4]= gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX(info->vbox[1]), info->sep[4], FALSE, TRUE, 10);

  info->hbox[3]= gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  gtk_box_pack_start (GTK_BOX(info->vbox[1]), info->hbox[3], FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->hbox[3]), 10);

  //=============== Drawing Area ===============

  info->darea[0]= gtk_drawing_area_new();
  gtk_container_add (GTK_CONTAINER (info->frame[4]), info->darea[0]);

  info->cr_image[0] = cairo_image_surface_create_from_png (image3);
  info->cr_image[1] = cairo_image_surface_create_from_png (image4);
  info->cr_image[2] = cairo_image_surface_create_from_png (image5);
  info->cr_image[3] = cairo_image_surface_create_from_png (image6);

  g_signal_connect(G_OBJECT(info->darea[0]), "draw", G_CALLBACK(desenhar), info);  

  //---------- Mover com rato ----------

  gtk_widget_set_events (info->darea[0], GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

  g_signal_connect (G_OBJECT(info->darea[0]), "motion-notify-event", G_CALLBACK (mouse_motion), info);
  g_signal_connect (G_OBJECT(info->darea[0]), "button_press_event", G_CALLBACK (mouse_motion), info);
  g_signal_connect (G_OBJECT(info->darea[0]), "button_release_event", G_CALLBACK (mouse_motion), info);

  //=============== Pause, Play, RESET, Ver Velocidade ===============

  info->button[3]= gtk_button_new ();
  info->image[0]= gtk_image_new_from_file (image0);
  gtk_button_set_image (GTK_BUTTON(info->button[3]), info->image[0]);
  gtk_widget_set_size_request (info->button[3], 40, 40);
  gtk_box_pack_start (GTK_BOX(info->hbox[2]), info->button[3], FALSE, FALSE, 0);
  g_signal_connect (info->button[3], "clicked", G_CALLBACK(pausa), NULL);

  info->button[4]= gtk_button_new ();
  info->image[1]= gtk_image_new_from_file (image1);
  gtk_button_set_image (GTK_BUTTON(info->button[4]), info->image[1]);
  gtk_widget_set_size_request (info->button[4], 40, 40);
  gtk_box_pack_start (GTK_BOX(info->hbox[2]), info->button[4], FALSE, FALSE, 10);
  g_signal_connect (info->button[4], "clicked", G_CALLBACK(play), NULL);

  info->button[5]= gtk_button_new_with_label ("RESET");
  gtk_widget_set_size_request (info->button[5], 40, 40);
  gtk_widget_override_font (info->button[5], pango_font_description_from_string("bold"));
  gtk_box_pack_start (GTK_BOX(info->hbox[2]), info->button[5], FALSE, FALSE, 0);
  g_signal_connect (info->button[5], "clicked", G_CALLBACK(reset_val), info);

  info->label[6]= gtk_label_new (string_gvel);
  gtk_widget_override_font (info->label[6], pango_font_description_from_string("bold"));
  gtk_box_pack_start (GTK_BOX(info->hbox[2]), info->label[6], TRUE, TRUE, 0);
  

  //=============== Frame da Posiçao ===============

  info->frame[5]= gtk_frame_new (" Posição do círculo grande ");
  gtk_box_pack_start (GTK_BOX(info->hbox[3]), info->frame[5], FALSE, FALSE, 0);
  gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &info->frames_color);
  gtk_frame_set_label_align (GTK_FRAME(info->frame[5]), 0.5, 1);

  info->vbox[4]= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(info->frame[5]), info->vbox[4]);
  gtk_container_set_border_width (GTK_CONTAINER (info->vbox[4]), 10);


  //=============== Scale X ===============

  info->label[0]= gtk_label_new ("X");
  gtk_box_pack_start (GTK_BOX(info->vbox[4]), info->label[0], FALSE, FALSE, 0);

  info->hbox[4]= gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(info->vbox[4]), info->hbox[4], TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->hbox[4]), 0);

  info->scale[0]= criar_scale(7, G_POS_X_INI, G_RAIO_INI, 800, 20, 0, info);
  gtk_box_pack_start (GTK_BOX(info->hbox[4]), info->scale[0], TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(info->scale[0]), "value_changed", G_CALLBACK(obter_valores), info);

  /* info->entry[0] = criar_entry ("200", 50, 600);
     gtk_widget_set_size_request (info->entry[0], 20, 20);
     gtk_box_pack_end (GTK_BOX (info->hbox[4]), info->entry[0], FALSE, FALSE, 5); */


  //=============== Scale Y ===============

  info->label[1]= gtk_label_new ("Y");
  gtk_box_pack_start (GTK_BOX(info->vbox[4]), info->label[1], FALSE, FALSE, 0);

  info->hbox[5]= gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(info->vbox[4]), info->hbox[5], TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->hbox[5]), 0);

  info->scale[1]= criar_scale(8, G_POS_Y_INI, G_RAIO_INI, 500, 20, 0, info);
  gtk_box_pack_start (GTK_BOX(info->hbox[5]), info->scale[1], TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(info->scale[1]), "value_changed", G_CALLBACK(obter_valores), info);

  /* info->entry[1] = criar_entry ("200", 50, 400);
     gtk_widget_set_size_request (info->entry[1], 20, 20);
     gtk_box_pack_end (GTK_BOX (info->hbox[5]), info->entry[1], FALSE, FALSE, 5); */
  

  //=============== Easter Egg ===============
  
  info->image[3]= gtk_image_new_from_file (image7);
  gtk_box_pack_start (GTK_BOX(info->hbox[3]), info->image[3], FALSE, FALSE, 0);


  //=============== Check Buttons ===============

  info->vbox[3]= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_end (GTK_BOX(info->hbox[3]), info->vbox[3], FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->vbox[3]), 0);

  info->button[7] = gtk_check_button_new_with_label ("Mostrar velocidade");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(info->button[7]), FALSE);
  gtk_box_pack_start (GTK_BOX(info->vbox[3]), info->button[7], FALSE, TRUE, 5);
  g_signal_connect (info->button[7], "clicked", G_CALLBACK(mostrar_velocidade), info);

  info->button[6] = gtk_check_button_new_with_label ("Esconder círculos pequenos");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(info->button[6]), FALSE);
  gtk_box_pack_start (GTK_BOX(info->vbox[3]), info->button[6], FALSE, TRUE, 5);
  g_signal_connect (info->button[6], "clicked", G_CALLBACK(esconder_pequenos), NULL);

  return FALSE;
}



//=============== MAIN ===============

int main(int argc, char **argv){

  gtk_init (&argc, &argv);

  data *info;

  srand (time(NULL));

  //---------- Inicializar valores ----------

  info = (data*) calloc(1, sizeof(data));

  info->p_pos_x = (gdouble *) malloc(N_BOLAS_MAX * sizeof(gdouble));
  info->p_pos_y = (gdouble *) malloc(N_BOLAS_MAX * sizeof(gdouble));
  info->p_vel_x = (gdouble *) malloc(N_BOLAS_MAX * sizeof(gdouble));
  info->p_vel_y = (gdouble *) malloc(N_BOLAS_MAX * sizeof(gdouble));

  info->g_pos_x = G_POS_X_INI;
  info->g_pos_y = G_POS_Y_INI;
  info->g_raio = G_RAIO_INI;
  info->g_massa = G_MASSA_INI;
  info->g_vel = G_VEL_INI;
  gerar_vel(info->g_vel, &info->g_vel_x, &info->g_vel_y);

  info->n_bolas = N_BOLAS_INI;
  info->p_raio = P_RAIO_INI;
  info->p_massa = P_MASSA_INI;
  info->p_vel = P_VEL_INI;

  len_string = strlen (string_gvel);

  gdk_rgba_parse (&info->g_cor, "rgb(0, 0, 150)");
  gdk_rgba_parse (&info->p_cor, "rgb(60, 60, 60)");
  gdk_rgba_parse (&info->frames_color, "gray89");
  gdk_rgba_parse (&info->darea_color, "white");
  info->screen_size = gdk_screen_get_default ();

  //----------------------------------------


  criar_estrutura(info);
  
  g_timeout_add (10, (GSourceFunc) mover, info);


  gtk_widget_show_all (info->window);
  gtk_widget_hide (info->label[6]);
  gtk_widget_hide (info->image[3]);

  gtk_main ();

  free(info->p_pos_x);
  free(info->p_pos_y);
  free(info->p_vel_x);
  free(info->p_vel_y);
  free(info);
  return 0;
}
