//////////////////// Includes //////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



//////////////////// Fixed And Global Variables ////////////////////////////////////////////////////



#if defined (_WIN32)
gchar *image_png_file1 = "images\\image1.png";
gchar *image_png_file2 = "images\\image2.png";
#else
gchar *image_png_file1 = "images/image1.png";
gchar *image_png_file2 = "images/image2.png";
#endif


#define              RADIUS_INI             25
#define              RADIUS_2_INI           2.5
#define              CIRCLE_CENTER_X        200
#define              CIRCLE_CENTER_Y        200
#define              VEL_INI                2.5   
#define              VEL_2_INI              5 

#define              BIGMASS                200
#define              SMALLMASS              20
#define              NCIRCLES               100  


// window info
GtkWindowType        wtype     = GTK_WINDOW_TOPLEVEL        ;
GtkWindowPosition    wpos      = GTK_WIN_POS_CENTER         ;
glong                wxlen     = 1000                       ;
glong                wylen     = 750                        ;

// orientation
GtkOrientation       overt     = GTK_ORIENTATION_VERTICAL   ;
GtkOrientation       ohori     = GTK_ORIENTATION_HORIZONTAL ;

// drawing area
glong                daxlen    = 650                        ;
glong                daylen    = 500                        ;   
         
// button size
glong                bxlen     = 100                        ;
glong                bylen     = 40                         ;

// colors
GdkRGBA              colorblack1                            ;
GdkRGBA              colorwhite1                            ;
GdkRGBA              colorranho1                            ;

// other variables
gint                 xx1       = 0                          ;  // iterator small circles initial position
gint                 toggle    = 0                          ;  // show/hide small circles
gint                 showvel   = 0                          ;  // show/hide velocity label
gint                 mode      = 0                          ;  // modes
gint                 collisioncolor = -1                    ;  // mode 2
gint                 tgraphic  = 0                          ;  // show graphic
gint                 dographic = 0                          ;  // do graphic
gint                 gtime     = 0                          ;  // time
gint                 mode4test = 0                          ;  // test for mode 4



//////////////////// Struct Data ///////////////////////////////////////////////////////////////////
     
       
     
typedef struct       
{  
  // basic strutures .............................                  
  GtkWidget      *window           ;    // window widget
  gchar          *wtitle           ;    // window title
  GtkWidget      *box[12]          ;    // boxes   
  GtkWidget      *sep[3]           ;    // separators
  GtkWidget      *label[6]         ;    // labels
  GtkWidget      *frame[12]        ;    // frames
  GtkWidget      *button[6]        ;    // butons 
  GtkAdjustment  *adj[3]           ;    // adjustments for scales
  GtkWidget      *scale[3]         ;    // scales
  GtkWidget      *spinbutton[6]    ;    // spinbutton
  GtkWidget      *dialog[2]        ;    // dialogs
  GtkWidget      *cbox             ;    // combo box
  GtkWidget      *link             ;    // link widget

  // image .......................................
  cairo_surface_t  *image1         ; 
  cairo_surface_t  *image2         ; 

  // toolbar .....................................
  GtkWidget      *toolbar          ;    // toolbar and stuff
  GtkToolItem    *tb_about, *tb_help, *tb_sep, *tb_exit;

  // menu -> language ............................
  GtkWidget      *menubar, *file, *menu_file;    // menubar and stuff
  GtkWidget      *english, *portuguese, *german, *french, *japanese;

  // drawing area and graphic ....................
  GtkWidget      *area             ;    // drawing area
  GtkAllocation  darea_alloc       ;    // drawing area allocation
  GtkWidget      *window_g         ;    // window for graphic
  GtkWidget      *graphic          ;    // graphic area
  gdouble        *gr_vel           ;    // graphic velocity

  gdouble        move              ;    // move when press play

  // mode 3 ......................................
  gint           rasto             ;    // iterator
  gdouble        *rastox           ;    // rasto x
  gdouble        *rastoy           ;    // rasto y

  // move with mouse .............................
  gint           flag_move         ;    // "0" (release) | "1" (press -> big circle) | "2" (press -> small circle)
  gdouble        press[2]          ;    // press position
  gdouble        mousepos[2]       ;    // mouse position
  gdouble        delta[2]          ;    // distance from mouse to center of big circles
  gint           delta_i1          ;    // identify i1

  // big circle ..................................
  gdouble        radius            ;    // circle radius
  gdouble        radius2           ;    // circle radius ^2
  gdouble        center[2]         ;    // circles' center coordinates
  gdouble        vel_              ;    // velocity of big circle [modul]
  gdouble        vel[2]            ;    // velocity of big circle [vector]

  // small circles ............................... 
  gint           ncircles          ;    // number of circles
  gdouble        radius_2          ;    // small circle radius
  gdouble        *centerx_2        ;    // x position of small circles
  gdouble        *centery_2        ;    // y position of small circles
  gdouble        vel_2             ;    // velocity of small circles
  gdouble        *velx_2           ;    // x component of velocity of small circles
  gdouble        *vely_2           ;    // y component of velocity of small circles

  // mass of both circles ........................
  gdouble        bigmass           ;    // mass of big circle
  gdouble        smallmass         ;    // mass of small circles

  gdouble        e                 ;    // restitution coefficient
  gint           lang              ;    // Actual langue
} data;


// struct for language .............................................................................


typedef struct
{
  gchar *wtitle;
  gchar *language, *english, *portuguese, *german, *french, *japanese;
  gchar *tool_about, *tool_help;
  gchar *exit, *exit_button1, *exit_button2; 
  gchar *button0, *button1, *button2, *button3, *button4, *button5;
  gchar *frame2, *frame5, *frame6_9, *frame7_10, *frame8; 
  gchar *label0, *label1, *label2, *label3, *label5;
} language;

language langue[5] = {
  {"Brownian Motion",
   "Language", "English", "Portuguese", "German", "French", "Japanese",
   " ✔ About", "Help [❓] ",
   "Exit", "Yes", "Cancel",
   "▶ Play", " ▌▌ Pause", " ◼ Reset", "Graphic", "Show/Hide Velocity", "Show/Hide Small Circles",
   "Position", "Radius", "Big Circle", "Small Circle", "Initial Velocity",
   "Big Circle Mass", "Small Circle Mass", "Number of Small Circles", "Brownian Motion", "Sure you want to quit?"},
  {"Movimento Browniano",
   "Idioma", "Inglês", "Português", "Alemão", "Francês", "Japonês",
   " ✔ Sobre", "Ajuda [❓] ",
   "Sair", "Sim", "Cancelar",
   "▶ Play", " ▌▌ Pausa", " ◼ Reiniciar", "Gráfico", "Mostrar/Esconder Velocidade", "Mostrar/Esconder Velocidade",
   "Posição", "Raio", "Círculo Grande", "Círculo Pequeno", "Velocidade Inicial",
   "Massa do Círculo Grande", "Massa do Círculo Pequeno", "Número de Círculos Pequenos", "Movimento Browniano", "Tem a certeza que quer sair?"},
  {"Brownsche Bewegung",
   "Sprache", "Englisch", "Portugiesisch", "Deutsche", "Französisch", "Japanisch",
   " ✔ Über", "Hilfe [❓] ",
   "Ausgang", "Ja", "Absagen",
   "▶ Play", " ▌▌ Pause", " ◼ Zurücksetzen", "Grafik", "Karte anzeigen/Ausblenden\nGeschwindigkeit", "Karte anzeigen/Ausblenden\nkleine Kreise",
   "Position", "Radius", "Großen Kreis", "Kleine Kreise", "Anfangsgeschwindigkeit",
   "Große Kreis Messe", "Kleine Kreis Massen", "Anzahl Kleiner Kreise", "Brownsche Bewegung", "Sicher, dass Sie aufhören wollen ?"},
  {"Le mouvement brownien",
   "Langue", "Anglais", "Portugais", "Allemand", "Français", "Japonais",
   " ✔ Sur", "Aidez-moi [❓] ",
   "Sortie", "Oui", "Annuler",
   "▶ Play", " ▌▌ Pause", " ◼ Réinitialiser", "Graphique", "Afficher/Masquer Velocity", "Afficher/Masquer les \nPetits Cercles", 
   "Position", "Rayon", "Grand Circle", "Petite Circle", "Vitesse Initiale", 
   "Grand Cercle Masse", "Petite Circle Masse", "Nombre de Petits Cercles", "Mouvement Brownien", "Bien sûr, vous voulez arrêter de fumer?"},
  {"ブラウン運動",
   "言語", "英語", "「ポルトガル語", "ドイツ語", "フランス語", "日本語",
   " ✔ 約", "助けて [❓] ", 
   "出口", "はい", "キャンセル",
   "► 演奏する", " ▌▌ 一時停止", " ◼ リセット", "グラフィック", "表示/非表示速度", "表示/小さな円を隠します",
   "位置", "半径", "ビッグサークル", "小円", "初期速度",
   "ビッグサークルマス", "小さな円マス", "小円の数", "ブラウン運動", "確かにあなたが終了したいですか？"},
};
 


//.................. Combo Box Text ................................................................


gchar *cb_text[5] = 
  {"Default", " ♪ ♬ FIESTA ♩ ♫", " ☕ Pimball ☀", "☢ Ranhoca ☠", "⚠ DANGER!! ⚠"};



//////////////////// Functions /////////////////////////////////////////////////////////////////////



//.................. Random ........................................................................


gdouble random01 (void)
{
  return ((double)rand()/(double)RAND_MAX);
}


//.................. Quit Button ...................................................................


// quit button test ..............................
gboolean quick_message (data *info) 
{
  gchar *message;
  gint result;
   
  info->dialog[0] = gtk_dialog_new_with_buttons (langue[info->lang].exit, GTK_WINDOW (info->window), GTK_DIALOG_DESTROY_WITH_PARENT, langue[info->lang].exit_button1, GTK_RESPONSE_ACCEPT, langue[info->lang].exit_button2, GTK_RESPONSE_REJECT, NULL);
  gtk_window_set_default_size (GTK_WINDOW (info->dialog[0]), 150, 100);
  gtk_window_set_modal (GTK_WINDOW (info->dialog[0]), TRUE);

  if (mode4test == 1)
    {
      gtk_window_set_title (GTK_WINDOW (info->dialog[0]), "  ⚠  ☠☢  ☣☠☣  ☢☠  ⚠");
      message ="\t⚠ Olhe lá, tem a certeza que deseja prosseguir?\n\n\tAs imagens seguintes poderão ferir as susceptibilidades do utilizador.\t";
    }
  else
    message = langue[info->lang].label5;
  info->label[5] = gtk_label_new (message);
  gtk_box_pack_start (GTK_BOX (gtk_bin_get_child (GTK_BIN (info->dialog[0]))), info->label[5], TRUE, FALSE, 10);
  gtk_widget_show_all (info->dialog[0]);

  result = gtk_dialog_run (GTK_DIALOG (info->dialog[0]));
  gtk_widget_destroy (info->dialog[0]);

  if (result == GTK_RESPONSE_ACCEPT)
    return TRUE;
  else
    return FALSE;
}


// quit button ...................................
gboolean quit_button (GtkWidget *widget, data *info) 
{
  gboolean test;

  test = quick_message (info);
  if (!test)
    return TRUE;

  gtk_main_quit();

  return FALSE;
}


//.................. About button ..................................................................


gboolean about_button (GtkWidget *widget, data *info)
{
  gchar *message;
  gint result;

  info->dialog[1] = gtk_dialog_new_with_buttons (langue[info->lang].tool_about, GTK_WINDOW (info->window), GTK_DIALOG_DESTROY_WITH_PARENT, langue[info->lang].exit_button2, GTK_RESPONSE_ACCEPT, NULL);
  gtk_window_set_default_size (GTK_WINDOW (info->dialog[1]), 300, 200);
  gtk_window_set_modal (GTK_WINDOW (info->dialog[1]), TRUE);

  message = langue[info->lang].label3;
  info->label[3] = gtk_label_new (message);
  gtk_widget_override_font (info->label[3], pango_font_description_from_string ("Tahoma bold 14"));
  gtk_box_pack_start (GTK_BOX (gtk_bin_get_child (GTK_BIN (info->dialog[1]))), info->label[3], TRUE, FALSE, 0);

  info->link = gtk_link_button_new ("http://arjuna.tecnico.ulisboa.pt/IC");
  gtk_box_pack_start (GTK_BOX (gtk_bin_get_child (GTK_BIN (info->dialog[1]))), info->link, FALSE, FALSE, 10);

  message = "© Tóino e Murtólia ™";
  info->label[4] = gtk_label_new (message);
  gtk_box_pack_end (GTK_BOX (gtk_bin_get_child (GTK_BIN (info->dialog[1]))), info->label[4], TRUE, FALSE, 0);

  gtk_widget_show_all (info->dialog[1]);

  result = gtk_dialog_run (GTK_DIALOG (info->dialog[1]));
  gtk_widget_destroy (info->dialog[1]);
 
  if (result == GTK_RESPONSE_ACCEPT)
    return TRUE;
  else
    return FALSE;
}


//.................. Help button ...................................................................


gboolean help_button (GtkWidget *widget, data *info)
{
  gint i;
  gchar *str1;

  str1 = (char*) malloc (50 * sizeof (char));

  sprintf (str1, "xdg-open brownian.pdf");

  i = system (str1);
  if (i != 0)
    printf ("Error executing '%s'.\n", str1);

  free (str1);
  return FALSE;
}


//.................. Play button ...................................................................


gboolean play_button (GtkWidget *widget, gpointer pointer, data *info)
{
  info->move = 1;
  return FALSE;
}


//.................. Pause button ..................................................................


gboolean pause_button (GtkWidget *widget, gpointer pointer, data *info)
{
  info->move = 0;
  return FALSE;
} 


//.................. Toggle Button ..................................................................


gboolean toggle_button (GtkWidget *widget, data *info)
{
  if (widget == info->button[5])
    {
      if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))         
	toggle = 1;
      else
	toggle = 0;
    }
  else if (widget == info->button[4])
    {
      if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))         
	showvel = 1;
      else
	showvel = 0;
    }
  return FALSE;
}


//.................. Combo box .....................................................................


gboolean combo_box (GtkWidget *widget, data *info)
{
  gint x, i;
  gboolean test;

  x = gtk_combo_box_get_active (GTK_COMBO_BOX(info->cbox));
  switch (x)
    {
    case 0: // default mode ................................
      gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[2]), RADIUS_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[3]), RADIUS_2_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[4]), VEL_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[5]), VEL_2_INI);
      gtk_adjustment_set_value (info->adj[2], NCIRCLES);
      gtk_widget_set_sensitive (info->spinbutton[2], TRUE);
      gtk_widget_set_sensitive (info->spinbutton[3], TRUE);
      info->move = 1;
      mode = 0;
      break;
    case 1: // fiesta mode .................................
      gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[2]), 50);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[3]), 5);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[5]), 10);
      gtk_adjustment_set_value (info->adj[2], 10 * NCIRCLES);
      gtk_widget_set_sensitive (info->spinbutton[2], TRUE);
      gtk_widget_set_sensitive (info->spinbutton[3], TRUE);
      info->move = 1;
      mode = 1;
      break;
    case 2: // croquetes mode ..............................
      gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[2]), RADIUS_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[3]), RADIUS_2_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[4]), VEL_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[5]), VEL_2_INI);
      gtk_adjustment_set_value (info->adj[2], NCIRCLES);
      gtk_widget_set_sensitive (info->spinbutton[2], TRUE);
      gtk_widget_set_sensitive (info->spinbutton[3], TRUE);
      info->move = 1;
      mode = 2;
      break;
    case 3: // ranhoca mode ................................
      gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[2]), RADIUS_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[3]), RADIUS_2_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[4]), 1);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[5]), 1);
      gtk_adjustment_set_value (info->adj[2], NCIRCLES);
      gtk_widget_set_sensitive (info->spinbutton[2], TRUE);
      gtk_widget_set_sensitive (info->spinbutton[3], TRUE);
      info->rasto = 0;
      info->move = 1;
      mode = 3;
      break;
    case 4: // cuaca mode ..................................
      i = mode;
      mode4test = 1;
      info->move = 0;
      gtk_window_set_resizable (GTK_WINDOW (info->window), TRUE);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[2]), 50);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[3]), 5);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[4]), VEL_INI);
      gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[5]), VEL_2_INI);
      gtk_adjustment_set_value (info->adj[2], 0);
      gtk_widget_set_sensitive (info->spinbutton[2], FALSE);
      gtk_widget_set_sensitive (info->spinbutton[3], FALSE);

      test = quick_message (info);    
      info->move = 1;

      if (test == TRUE)
	mode = 4;
      else
	gtk_combo_box_set_active (GTK_COMBO_BOX(info->cbox), i);

      mode4test = 0;

      break;
    }

  return FALSE;
}


//.................. Change Language ...............................................................


gboolean change_language (GtkWidget *widget, data *info)
{
  gint i;
  gchar *v;

  if (widget == info->portuguese)
    info->lang = 1;
  else if (widget == info->english)
    info->lang = 0;
  else if (widget == info->german)
    info->lang = 2;
  else if (widget == info->french)
    info->lang = 3;
  else if (widget == info->japanese)
    info->lang = 4;

  i = info->lang;

  v = (char *) malloc (200 * sizeof (char));

  gtk_window_set_title (GTK_WINDOW (info->window), langue[i].wtitle);
  gtk_menu_item_set_label (GTK_MENU_ITEM (info->file), langue[i].language);
  strcpy (v, langue[i].english);
  strcat (v, "  [English]");
  gtk_menu_item_set_label (GTK_MENU_ITEM (info->english), v);
  strcpy (v, langue[i].portuguese);
  strcat (v, "  [Português]");
  gtk_menu_item_set_label (GTK_MENU_ITEM (info->portuguese), v);
  strcpy (v, langue[i].german);
  strcat (v, "  [Deutsche]");
  gtk_menu_item_set_label (GTK_MENU_ITEM (info->german), v);
  strcpy (v, langue[i].french);
  strcat (v, "  [Français]");
  gtk_menu_item_set_label (GTK_MENU_ITEM (info->french), v);
  strcpy (v, langue[i].japanese);
  strcat (v, "  [日本語]");
  gtk_menu_item_set_label (GTK_MENU_ITEM (info->japanese), v);
  gtk_tool_button_set_label (GTK_TOOL_BUTTON (info->tb_about), langue[i].tool_about);
  gtk_tool_button_set_label (GTK_TOOL_BUTTON (info->tb_help), langue[i].tool_help);
  gtk_button_set_label (GTK_BUTTON (info->button[0]),langue[i].button0);
  gtk_button_set_label (GTK_BUTTON (info->button[1]),langue[i].button1);
  gtk_button_set_label (GTK_BUTTON (info->button[2]),langue[i].button2);
  gtk_button_set_label (GTK_BUTTON (info->button[3]),langue[i].button3);
  gtk_button_set_label (GTK_BUTTON (info->button[4]),langue[i].button4);
  gtk_button_set_label (GTK_BUTTON (info->button[5]),langue[i].button5);
  gtk_frame_set_label (GTK_FRAME(info->frame[2]), langue[i].frame2);
  gtk_frame_set_label (GTK_FRAME(info->frame[5]), langue[i].frame5);
  gtk_frame_set_label (GTK_FRAME(info->frame[6]), langue[i].frame6_9);
  gtk_frame_set_label (GTK_FRAME(info->frame[9]), langue[i].frame6_9);
  gtk_frame_set_label (GTK_FRAME(info->frame[7]), langue[i].frame7_10);
  gtk_frame_set_label (GTK_FRAME(info->frame[10]), langue[i].frame7_10);
  gtk_frame_set_label (GTK_FRAME(info->frame[8]), langue[i].frame8);
  gtk_label_set_text (GTK_LABEL(info->label[0]),langue[i].label0);
  gtk_label_set_text (GTK_LABEL(info->label[1]), langue[i].label1);
  gtk_label_set_text (GTK_LABEL(info->label[2]),langue[i].label2);

  info->move = 0;

  free (v);
  return FALSE;
}


//.................. Move Mouse ....................................................................


gboolean move_mouse (GtkWidget *widget, GdkEvent *event, data *info)
{
  gdouble  dist, r2_2;
  gint i1;

  if (event->type == GDK_MOTION_NOTIFY)
    {
      //printf ("Event: Motion Notify\n");
      info->mousepos[0] = ((GdkEventMotion*)event)->x;
      info->mousepos[1] = ((GdkEventMotion*)event)->y;

      // big circle
      if (info->flag_move == 1)
        {
          if (info->mousepos[0] + info->delta[0] + info->radius > info->darea_alloc.width)
            info->center[0] = info->darea_alloc.width - info->radius;
          else if (info->mousepos[0] + info->delta[0] - info->radius < 0)
            info->center[0] = info->radius;
	  else
            info->center[0] = info->mousepos[0] + info->delta[0];

          if (info->mousepos[1] + info->delta[1] + info->radius > info->darea_alloc.height)
            info->center[1] = info->darea_alloc.height - info->radius;
          else if (info->mousepos[1] + info->delta[1] - info->radius < 0)
            info->center[1] = info->radius;
          else
            info->center[1] = info->mousepos[1] + info->delta[1];
	}

      // small circles
      else if (info->flag_move == 2) 
	{
	  i1 = info->delta_i1;

	  if (info->mousepos[0] + info->delta[0] + info->radius_2 > info->darea_alloc.width)
	    info->centerx_2[i1] = info->darea_alloc.width - info->radius_2;
	  else if (info->mousepos[0] + info->delta[0] - info->radius_2 < 0)
	    info->centerx_2[i1] = info->radius_2;
	  else
	    info->centerx_2[i1] = info->mousepos[0] + info->delta[0];

	  if (info->mousepos[1] + info->delta[1] + info->radius_2 > info->darea_alloc.height)
	    info->centery_2[i1] = info->darea_alloc.height - info->radius_2;
	  else if (info->mousepos[1] + info->delta[1] - info->radius_2 < 0)
	    info->centery_2[i1] = info->radius_2;
	  else
	    info->centery_2[i1] = info->mousepos[1] + info->delta[1];
	}
    }

  else if (event->type == GDK_BUTTON_PRESS)
    {
      //printf ("Event: Button Press\n");
      info->press[0] = ((GdkEventButton*)event)->x;
      info->press[1] = ((GdkEventButton*)event)->y;

      info->delta[0] = info->center[0] - info->press[0];
      info->delta[1] = info->center[1] - info->press[1];
      dist = pow (info->delta[0], 2) + pow (info->delta[1], 2);
      if (dist < info->radius2)
	{
          info->flag_move = 1;
          info->center[0] = info->press[0] + info->delta[0];
          info->center[1] = info->press[1] + info->delta[1];
	  return FALSE;
	}

      r2_2 = pow (info->radius_2, 2);
      
      for (i1 = 0; i1 < info->ncircles ; i1++)
	{
	  info->delta[0] = info->centerx_2[i1] - info->press[0];
	  info->delta[1] = info->centery_2[i1] - info->press[1];
	  dist = pow (info->delta[0], 2) + pow (info->delta[1], 2);
	  if (dist < r2_2)
	    {
	      info->flag_move = 2;
	      info->centerx_2[i1] = info->press[0] + info->delta[0];
	      info->centery_2[i1] = info->press[1] + info->delta[1];
	      info->delta_i1 = i1;
	      return FALSE;
	    }
       	}
    }
  
  else if (event->type == GDK_BUTTON_RELEASE)
    {
      //printf ("Event: Button Release\n");
      info->flag_move = 0;
    }

  return FALSE;
}


//.................. Initial position of small circles ..............................................


void small_circles_init (data *info, gint i)
{
  gint j, x;   //iterator

  for (j = 0; j < 10 * NCIRCLES; j++)
    {
      if (i == 0)
	{
	  info->centerx_2[j] = (random01()) * ((double)info->darea_alloc.width - (4 * info->radius_2)) + 2* info->radius_2;
	  info->centery_2[j] = (random01()) * ((double)info->darea_alloc.height - (4 * info->radius_2)) + 2* info->radius_2;
	}
      
      // small circles initial velocity ..........
      
      if ((i == 0) || (i == 1))
	{
	  x = (random01()) * 2 * M_PI;
	  info->velx_2[j] = info->vel_2 * cos (x);
	  info->vely_2[j] = info->vel_2 * sin (x);
	}
    }
}


//.................. Button Change .................................................................


// spin button change ............................
gboolean button_changed (GtkWidget *widget, data *info)
{ 
  gdouble v1;

  if (widget == info->spinbutton[0])
    info->center[0] = gtk_spin_button_get_value (GTK_SPIN_BUTTON (widget));
  else if (widget == info->spinbutton[1])
    info->center[1] = gtk_spin_button_get_value (GTK_SPIN_BUTTON (widget));
  else if (widget == info->spinbutton[2])
    {
      info->radius = gtk_spin_button_get_value (GTK_SPIN_BUTTON (widget));
      info->radius2 = info->radius*info->radius;
    }
  else if (widget == info->spinbutton[3])
    info->radius_2 =  gtk_spin_button_get_value (GTK_SPIN_BUTTON (widget));
  else if (widget == info->spinbutton[4])
    {
      info->move = 0;
      v1 = gtk_spin_button_get_value (GTK_SPIN_BUTTON (widget));
      info->vel[0] = sqrt (pow (v1, 2) / 2);
      info->vel[1] = sqrt (pow (v1, 2) / 2);
    }
  else if (widget == info->spinbutton[5])
    {
      info->move = 0;
      info->vel_2 = gtk_spin_button_get_value (GTK_SPIN_BUTTON (widget));
      small_circles_init (info, 1);
    }
  else if (widget == info->scale[2])
    info->ncircles = (gint) gtk_adjustment_get_value (info->adj[2]);
  else if (widget == info->scale[0])
    info->bigmass = gtk_adjustment_get_value (info->adj[0]);
  else if (widget == info->scale[1])
    info->smallmass = gtk_adjustment_get_value (info->adj[1]);

  return FALSE;
}


//.................. Reset button ..................................................................


gboolean reset_button (GtkWidget *widget, gpointer pointer, data *info)
{
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[0]), CIRCLE_CENTER_X);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[1]), CIRCLE_CENTER_Y);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[2]), RADIUS_INI);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[3]), RADIUS_2_INI);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[4]), VEL_INI);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[5]), VEL_2_INI);
  gtk_adjustment_set_value (info->adj[0], BIGMASS);
  gtk_adjustment_set_value (info->adj[1], SMALLMASS);
  gtk_adjustment_set_value (info->adj[2], NCIRCLES);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (info->button[4]), FALSE); 
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (info->button[5]), FALSE); 
  gtk_combo_box_set_active (GTK_COMBO_BOX(info->cbox), 0);

  info->vel[0] = sqrt (pow (VEL_INI, 2)/2);
  info->vel[1] = sqrt (pow (VEL_INI, 2)/2);

  info->move = 0;
  small_circles_init (info, 0);
  xx1 = 1;
  showvel = 0;
  toggle = 0;
  mode = 0;

  return FALSE;
}


//.................. Collision functions ...........................................................


void collision (data *info, gint i, gint i2)
{
  gdouble alpha, beta, theta, phi, e;
  gdouble x1, y1, m1, u1, u1x, u1y, v1, v1x, v1y;
  gdouble x2, y2, m2, v2;
  //gdouble energy;

  e = info->e;
  x1 = info->centerx_2[i];
  y1 = info->centery_2[i];
  m1 = info->smallmass;
  if (i2 == -1)
    {
      x2 = info->center[0];
      y2 = info->center[1];
      u1x = info->velx_2[i] - info->vel[0];
      u1y = info->vely_2[i] - info->vel[1];
      m2 = info->bigmass;
    }
  else // collision between small circles ..................
    {
      x2 = info->centerx_2[i2];
      y2 = info->centery_2[i2];
      u1x = info->velx_2[i] - info->velx_2[i2];
      u1y = info->vely_2[i] - info->vely_2[i2];
      m2 = info->smallmass;
    } // ...................................................

  u1 = sqrt (pow (u1x, 2) + pow (u1y, 2)); 

  //energy = 0.5*m1*pow((sqrt(pow(info->velx_2[i],2)+pow(info->vely_2[i],2))),2) + 0.5*m2*pow((sqrt(pow(info->vel[0],2)+pow(info->vel[1],2))),2) ;
  //printf (" %lf \n", energy);
  
  alpha = atan2 (y1 - y2 , x1 - x2);
  beta = atan2 (u1y , u1x);
  theta = (alpha - beta);
  phi = atan2 (((m1 + m2) * tan (theta)) , (m1 - e * m2)) - theta;
  v1 = sin (theta) / sin (theta + phi) * u1;
  v1x = v1 * cos (beta - phi);
  v1y = v1 * sin (beta - phi);
  v2 = (m1 / (m1 + m2)) * (1 + e) * cos (theta) * u1;
  
  if (i2 == -1)
    {
      info->velx_2[i] = v1x + info->vel[0];
      info->vely_2[i] = v1y + info->vel[1];
      info->vel[0] = v2 * cos (alpha) + info->vel[0];
      info->vel[1] = v2 * sin (alpha) + info->vel[1];
    }
  else // collision between small circles ..................
    {
      info->velx_2[i] = v1x + info->velx_2[i2];
      info->vely_2[i] = v1y + info->vely_2[i2];
      info->velx_2[i2] = v2 * cos (alpha) + info->velx_2[i2];
      info->vely_2[i2] = v2 * sin (alpha) + info->vely_2[i2];
    } // ...................................................

  //energy = 0.5*m1*pow((sqrt(pow(info->velx_2[i],2)+pow(info->vely_2[i],2))),2) + 0.5*m2*pow((sqrt(pow(info->vel[0],2)+pow (info->vel[1], 2))), 2);
  //printf (" %lf \n", energy);
}


//.................. Graph and button ..............................................................


// destroy graph function ............................................
gboolean destroy_graph (GtkWidget *widget, GtkWidget *window)
{
  dographic = 0;
  return FALSE;
}


// graph draw event ..................................................
gboolean graphic (GtkWidget *widget, cairo_t *cr, data *info)
{
  gint i;

  gchar str1[40];

  // draw line ...................................
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_move_to (cr, 0, 300);
  cairo_line_to (cr, 500, 300);
  
  // draw velocity ...............................
  for (i = 1; i <= tgraphic; i++)
    { 
      cairo_move_to (cr, i - 1, 300 - info->gr_vel[i-1] * 50); 
      cairo_line_to (cr, i, 300 - info->gr_vel[i] * 50);
    }
  cairo_stroke (cr);
  
  if (mode == 4)
    {
      cairo_set_source_surface (cr, info->image2, tgraphic - 25, 275 - info->gr_vel[tgraphic] * 50);
      cairo_paint (cr);
    }

  cairo_move_to (cr, 400, 320);
  sprintf (str1, " %.2lf s ", gtime * 0.02);
  cairo_set_font_size (cr, 14.);
  cairo_show_text (cr, str1);
  
  cairo_move_to (cr, 400, 335);
  sprintf (str1, " %.2lf pixel/s ", info->vel_ * 50);
  cairo_set_font_size (cr, 14.);
  cairo_show_text (cr, str1);

  return FALSE;
}


// graph button ......................................................
gboolean graph_button (GtkWidget *widget, data *info)
{
  dographic = 1;

  if (info->window_g  == NULL)
    {
      info->window_g = gtk_window_new (wtype);
      gtk_window_set_resizable (GTK_WINDOW (info->window_g), FALSE);
      gtk_window_set_title (GTK_WINDOW (info->window_g), langue[info->lang].button3);
      gtk_window_set_position (GTK_WINDOW (info->window_g), wpos);
      
      g_signal_connect (G_OBJECT (info->window_g), "destroy", G_CALLBACK (destroy_graph), info->window_g);
      
      info->graphic = gtk_drawing_area_new ();
      gtk_container_add (GTK_CONTAINER (info->window_g), info->graphic);
      gtk_widget_set_size_request (info->graphic, 500, 350);
      gtk_widget_override_background_color (info->graphic, GTK_STATE_NORMAL, &colorwhite1);
      g_signal_connect (G_OBJECT (info->graphic), "draw", G_CALLBACK (graphic), info);
      
      gtk_widget_show_all (info->window_g);
    }
  return FALSE;
}


//.................. Draw event ....................................................................


gboolean draw_event (GtkWidget *widget, cairo_t *cr, data *info)
{
  gchar str1[10];
  gint i, i1;
  gdouble a, b, c;  // iterator ..................
  //gdouble energy;


  // scalar value of velocity ..............................
  info->vel_ = sqrt(info->vel[0]*info->vel[0] + info->vel[1]*info->vel[1]);

  // graphic ...............................................
  if (dographic == 1)
    {
      if (info->move == 1)
	{
	  gtk_widget_queue_draw (info->window_g);
	  
	  if (tgraphic < 499)
	    tgraphic ++;

	  info->gr_vel[tgraphic] = info->vel_;

	  if (tgraphic == 499)
	    for (i = 0; i < tgraphic; i++)
	      info->gr_vel[i] = info->gr_vel[i+1];
	  
	  gtime ++;
	}
    }
  else
    {
      tgraphic = 0;
      gtime = 0;
      info->window_g = NULL;
    }
 

  // get allocation of drawing area ........................
  gtk_widget_get_allocation (info->area, &info->darea_alloc);


  // spin buttons range ....................................
  gtk_spin_button_set_range (GTK_SPIN_BUTTON (info->spinbutton[0]), info->radius, info->darea_alloc.width - info->radius);
  gtk_spin_button_set_range (GTK_SPIN_BUTTON (info->spinbutton[1]), info->radius, info->darea_alloc.height - info->radius);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[0]), info->center[0]);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[1]), info->center[1]);


  // modes for big circle ............................................
  switch (mode)
    {
    case 0: // default mode ................................
      gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &colorwhite1);
      cairo_set_source_rgb (cr, 0, 0.7, 0.7);
      cairo_move_to (cr,info->center[0], info->center[1]);
      cairo_arc (cr, info->center[0], info->center[1], info->radius, 0, 2*M_PI);
      cairo_fill (cr);
      cairo_set_source_rgb (cr, 0, .4, .4);
      cairo_move_to (cr,info->center[0], info->center[1]);
      cairo_arc (cr, info->center[0], info->center[1], info->radius/10 * 9, 0, 2*M_PI);
      cairo_fill (cr);
      cairo_stroke (cr);
      break;
    case 1: // fiesta mode .................................
      gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &colorwhite1);
      for (i = 10; i >= 1; i--)
	{
	  a = (random01());
	  b = (random01());
	  c = (random01());
	  cairo_set_source_rgb (cr, a, b, c);
	  cairo_move_to (cr,info->center[0], info->center[1]);
	  cairo_arc (cr, info->center[0], info->center[1], info->radius/10 * i, 0, 2*M_PI);
	  cairo_fill (cr);
     	  cairo_stroke (cr);
	}
      break;
    case 2: // pimball mode ................................
      gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &colorwhite1);

      if (collisioncolor != -1)
	{
	  a = (random01());
	  b = (random01());
	  c = (random01());
	  cairo_set_source_rgb (cr, a, b, c);
	  cairo_move_to (cr,info->center[0], info->center[1]);
	  cairo_arc (cr, info->center[0], info->center[1], info->radius, 0, 2*M_PI);
	  cairo_fill (cr);
	  cairo_stroke (cr);
	}
      else 
	{
	  cairo_set_source_rgb (cr, 1, 1, 1);
	  cairo_move_to (cr,info->center[0], info->center[1]);
	  cairo_arc (cr, info->center[0], info->center[1], info->radius, 0, 2*M_PI);
	  cairo_fill (cr);
 	  cairo_stroke (cr);
	}
      break;
    case 3: // ranhoca mode ................................
      gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &colorranho1);

      a = info->rasto;
      info->rastox[info->rasto] = info->center[0];
      info->rastoy[info->rasto] = info->center[1];
      if (info->rasto < 999)
	++info->rasto;

      for (i = 0; i < info->rasto ; i++)
	{
	  cairo_set_source_rgb (cr, 0.8 - i * 0.0003, 0.8 - i * 0.0003, 0);
	  if (i == info->rasto - 1)
	    cairo_set_source_rgb (cr, 0.4, 0.4, 0);
	  cairo_move_to (cr,info->rastox[i], info->rastoy[i]);
	  cairo_arc (cr, info->rastox[i], info->rastoy[i], info->radius, 0, 2*M_PI);
	  cairo_fill (cr);
	  cairo_stroke (cr);
	}

      if (info->rasto == a)
	{
	  for(i = 0; i < info->rasto ; i++)
	    {
	      info->rastox[i] = info->rastox[i+1];
	      info->rastoy[i] = info->rastoy[i+1];
	    }
	}

      break;
    case 4: // danger mode .................................
      gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &colorwhite1);

      cairo_set_source_surface (cr, info->image1, info->center[0] - 100, info->center[1] - 100);
      cairo_paint (cr);
      break;
    }


  // write velocity ........................................
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_move_to (cr, info->center[0] - 20, info->center[1] + 5);
  sprintf (str1, " %.2lf ", info->vel_ * 50);
  cairo_set_font_size (cr, 14.);
  if (showvel == 1)
    cairo_show_text (cr, str1);


  // big circle stays inside drawing area ..................
  if (info->center[0] + info->radius >= info->darea_alloc.width)
    info->center[0] = info->darea_alloc.width - info->radius;
  if (info->center[1] + info->radius >= info->darea_alloc.height)
    info->center[1] = info->darea_alloc.height - info->radius;


  // small circles init ..............................................
  if (xx1 == 0)
    {
      small_circles_init (info, 0);
      xx1 = 1;
    }
  for (i = 0; i < info->ncircles; i++)
    {
      // put conditions so big circle and small circle dont intercept in case move == 0
      while ((info->radius + info->radius_2) > (sqrt (pow (fabs (info->centerx_2[i]-info->center[0]),2) + (pow (fabs (info->centery_2[i]-info->center[1]),2)))))
	{
	  info->centerx_2[i] = (random01()) * ((double)info->darea_alloc.width - (4 * info->radius_2)) + 2 * info->radius_2;
	  info->centery_2[i] = (random01()) * ((double)info->darea_alloc.height - (4 * info->radius_2)) + 2 * info->radius_2;
	}

      // show circles only if toggle == 0 ............................
      if (toggle == 0)
	{
  	  cairo_arc (cr, info->centerx_2[i], info->centery_2[i], info->radius_2, 0, 2*M_PI);

	  // modes for big circle ....................................
	  switch (mode)
	    {		
	    case 0: // default mode ........................	
	      cairo_set_source_rgb (cr, 0.3, 0.3, 0.3);
	      cairo_fill (cr);
	      cairo_stroke (cr);
	      break;
	    case 1: // fiesta mode .........................
	      a = (random01());
	      b = (random01());
	      c = (random01());
	      cairo_set_source_rgb (cr, a, b, c);
	      cairo_fill (cr);
	      cairo_stroke (cr);
	      break;
	    case 2: // pimball mode ........................
	      cairo_set_source_rgb (cr, 0, 0, 0);
	      if (i == collisioncolor)
		{
		  a = (random01());
		  b = (random01());
		  c = (random01());
		  cairo_set_source_rgb (cr, a, b, c);
		  collisioncolor = -1;
		}
	      cairo_fill (cr);
	      cairo_stroke (cr);
	      break;
	    case 3: // ranhoca mode ........................
	      cairo_set_source_rgb(cr,0.3,0.3,0);
	      cairo_fill (cr);
	      cairo_stroke (cr);
	      break;
	    case 4: // danger mode .........................
	      cairo_set_source_surface (cr, info->image2, info->centerx_2[i] - 25, info->centery_2[i] - 25);
	      cairo_paint (cr);	    
	      break;   
	    }
	}
    }

  // check energy ................................
  /*energy = 0.5*info->bigmass*pow((sqrt(pow(info->vel[0],2)+pow(info->vel[1],2))),2);
  for (i1 = 0; i1 < info->ncircles ; i1++)
    {
      energy += 0.5*info->smallmass*pow((sqrt(pow(info->velx_2[i1],2)+pow(info->vely_2[i1],2))),2);
    }
    printf (" %lf \n", energy);*/

  // move circles ....................................................
  if (info->move == 1)
    {
      for (i1 = 0; i1 < 100; i1++)
      	{
	  info->center[0] += info->vel[0] / 100;
	  info->center[1] += info->vel[1] / 100;

	  if ((info->center[0] + info->radius + info->vel[0] / 100 >= info->darea_alloc.width) || (info->center[0] <= info->radius))
	    info->vel[0] = -info->vel[0] * info->e;

	  if ((info->center[1] + info->radius >= info->darea_alloc.height) || (info->center[1] <= info->radius))
	    info->vel[1] = -info->vel[1] * info->e;

	  for (i = 0; i < info->ncircles; i++)
	    {
	      info->centerx_2[i] += info->velx_2[i] / 100;
	      info->centery_2[i] += info->vely_2[i] / 100;
	      if ((info->centerx_2[i] + info->radius_2 >= info->darea_alloc.width) || (info->centerx_2[i] <= info->radius_2))
		info->velx_2[i] = -info->velx_2[i] * info->e;
	      if ((info->centery_2[i] + info->radius_2 >= info->darea_alloc.height) || (info->centery_2[i] <= info->radius_2))
		info->vely_2[i] = -info->vely_2[i] * info->e;

	      // collision .................................
	      if ((info->radius + info->radius_2) >= (sqrt (pow (fabs (info->centerx_2[i] - info->center[0]),2) + (pow (fabs (info->centery_2[i] - info->center[1]),2)))))
		{
		  collision (info, i, -1);
		  collisioncolor = i;
		}
	     
	      // collision between small circles ...........
	      /*for (i2 = 0; i2 < info->ncircles; i2++)
		{
		  if (i2 == i)
		    continue;
		  else
		  if ((info->radius_2 * 2) >= (sqrt (pow (fabs (info->centerx_2[i] - info->centerx_2[i2]),2) + (pow (fabs (info->centery_2[i] - info->centery_2[i2]),2)))))
		    collision (info, i, i2);
		      }*/
	    }
	}
    }

  // check energy ................................
  /*energy = 0.5*info->bigmass*pow((sqrt(pow(info->vel[0],2)+pow(info->vel[1],2))),2);
  for (i1 = 0; i1 < info->ncircles ; i1++)
    {
      energy += 0.5*info->smallmass*pow((sqrt(pow(info->velx_2[i1],2)+pow(info->vely_2[i1],2))),2);
    }
    printf (" %lf \n", energy);*/
  
  return FALSE;
}


//.................. Time Handler ..................................................................


gboolean time_handler (data *info)
{

  if ((!GTK_IS_WIDGET (info->area)) || (!gtk_widget_get_window (info->area)))
    return FALSE;

  gtk_widget_queue_draw (info->area);
 
  return TRUE;
}


//.................. Data New ......................................................................


data *data_new (void)
{
  data *info;

  info = (data *) calloc (1, sizeof (data));

  info->flag_move = 0;
  info->radius = RADIUS_INI;
  info->radius2 = info->radius * info->radius;
  info->center[0] = CIRCLE_CENTER_X;
  info->center[1] = CIRCLE_CENTER_Y;
  info->radius_2 = RADIUS_2_INI;
  info->ncircles = NCIRCLES;
  info->vel[0] = sqrt (pow (VEL_INI, 2)/2);
  info->vel[1] = sqrt (pow (VEL_INI, 2)/2);
  info->vel_2 = VEL_2_INI;
  info->bigmass = BIGMASS;
  info->smallmass = SMALLMASS;
  info->lang = 0;
  info->wtitle = langue[info->lang].wtitle;
  
  info->image1 = cairo_image_surface_create_from_png (image_png_file1);
  info->image2 = cairo_image_surface_create_from_png (image_png_file2);

  info->e = 1;
  info->move = 0;

  info->gr_vel = (gdouble*) malloc (500 * sizeof (gdouble));
  info->rastox = (gdouble*) malloc (1000 * sizeof (gdouble));
  info->rastoy = (gdouble*) malloc (1000 * sizeof (gdouble));
  info->centerx_2 = (gdouble*) malloc (1000 * sizeof (gdouble));
  info->centery_2 = (gdouble*) malloc (1000 * sizeof (gdouble));
  info->velx_2 = (gdouble*) malloc (1000 * sizeof (gdouble));
  info->vely_2 = (gdouble*) malloc (1000 * sizeof (gdouble));

  return info;
}


//.................. Create Whole Structure ........................................................


void create_structure (data *info)
{
  // create window .......................................................................
  info->window = gtk_window_new (wtype);
  gtk_window_set_default_size (GTK_WINDOW (info->window), wxlen, wylen);
  gtk_window_set_title (GTK_WINDOW (info->window), info->wtitle);
  gtk_window_set_position (GTK_WINDOW (info->window), wpos);
  g_signal_connect (G_OBJECT(info->window), "destroy", G_CALLBACK (gtk_main_quit), NULL);



  // create initial box ........................................................
  info->box[0] = gtk_box_new (overt, 0);
  gtk_container_add (GTK_CONTAINER (info->window), info->box[0]);



  // create box 7 -> toolbar .............................................................
  info->box[7] = gtk_box_new (ohori, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[7]), 0);
  gtk_box_pack_start (GTK_BOX (info->box[0]), info->box[7], FALSE, FALSE, 0);


  // create toolbar ............................................................
  info->toolbar = gtk_toolbar_new ();
  gtk_toolbar_set_style (GTK_TOOLBAR (info->toolbar), GTK_TOOLBAR_ICONS);
  gtk_container_set_border_width (GTK_CONTAINER (info->toolbar), 0);

  info->tb_about = gtk_tool_button_new (NULL, " ✔ About");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (info->tb_about), NULL);
  gtk_toolbar_insert (GTK_TOOLBAR (info->toolbar), info->tb_about, -1);
  g_signal_connect (G_OBJECT (info->tb_about), "clicked", G_CALLBACK (about_button), info);

  info->tb_help = gtk_tool_button_new (NULL, " Help [❓] ");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (info->tb_help), NULL);
  gtk_toolbar_insert (GTK_TOOLBAR (info->toolbar), info->tb_help, -1);
  g_signal_connect (G_OBJECT (info->tb_help), "clicked", G_CALLBACK (help_button), info);

  info->tb_sep = gtk_separator_tool_item_new ();
  gtk_toolbar_insert (GTK_TOOLBAR (info->toolbar), info->tb_sep, -1);

  info->tb_exit = gtk_tool_button_new (NULL, "Quit");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (info->tb_exit), "application-exit");
  gtk_toolbar_insert (GTK_TOOLBAR (info->toolbar), info->tb_exit, -1);
  g_signal_connect (G_OBJECT (info->tb_exit), "clicked", G_CALLBACK (quit_button), info);

  gtk_box_pack_start (GTK_BOX (info->box[7]), info->toolbar, FALSE, TRUE, 0);


  // Menu for language ...........................
 
  info->menubar = gtk_menu_bar_new ();

  info->file = gtk_menu_item_new_with_mnemonic ("_Language");                   
  gtk_menu_shell_append (GTK_MENU_SHELL (info->menubar),info->file);

  info->menu_file = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (info->file), info->menu_file);

  info->english= gtk_menu_item_new_with_label ("English [English]");
  gtk_menu_shell_append (GTK_MENU_SHELL(info->menu_file), info->english);
  g_signal_connect (G_OBJECT (info->english), "activate", G_CALLBACK (change_language), info);
  info->portuguese = gtk_menu_item_new_with_label ("Portuguese [Português]");
  gtk_menu_shell_append (GTK_MENU_SHELL(info->menu_file),info->portuguese);
  g_signal_connect (G_OBJECT (info->portuguese), "activate", G_CALLBACK (change_language), info);
  info->german = gtk_menu_item_new_with_label ("German [Deutsche]");
  gtk_menu_shell_append (GTK_MENU_SHELL(info->menu_file), info->german);
  g_signal_connect (G_OBJECT (info->german), "activate", G_CALLBACK (change_language), info);
  info->french = gtk_menu_item_new_with_label ("French [Fraiçais]");
  gtk_menu_shell_append (GTK_MENU_SHELL(info->menu_file), info->french);
  g_signal_connect (G_OBJECT (info->french), "activate", G_CALLBACK (change_language), info);
  info->japanese = gtk_menu_item_new_with_label ("Japanese [日本語]");
  gtk_menu_shell_append (GTK_MENU_SHELL(info->menu_file), info->japanese);
  g_signal_connect (G_OBJECT (info->japanese), "activate", G_CALLBACK (change_language), info);
 
  gtk_box_pack_start (GTK_BOX (info->box[7]), info->menubar, FALSE, FALSE, 3);



  // create separator ....................................................................
  info->sep[0] = gtk_separator_new (ohori);
  gtk_box_pack_start (GTK_BOX (info->box[0]), info->sep[0], FALSE, TRUE, 0);

 

  // create box 1 ........................................................................
  info->box[1] = gtk_box_new (ohori, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[1]), 0);
  gtk_box_pack_start (GTK_BOX (info->box[0]), info->box[1], TRUE, TRUE, 0);

  // create box 2 with frame and drawing area ..................................
  info->box[2] = gtk_box_new (overt, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[2]), 10);
  gtk_box_pack_start (GTK_BOX (info->box[1]), info->box[2], TRUE, TRUE, 0);


  info->frame[0] = gtk_frame_new ("");
  gtk_frame_set_label_align (GTK_FRAME (info->frame[0]), 0.5, 1);
  gtk_box_pack_start (GTK_BOX (info->box[2]), info->frame[0], TRUE, TRUE, 0); 
  
  info->area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (info->area, daxlen, daylen);
  gtk_container_add (GTK_CONTAINER (info->frame[0]), info->area);

  gtk_widget_set_events (info->area, GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

  // functions for moving mouse ................................................
  g_signal_connect (G_OBJECT (info->area), "motion-notify-event", G_CALLBACK (move_mouse), info);
  g_signal_connect (G_OBJECT (info->area), "button_press_event", G_CALLBACK (move_mouse), info);
  g_signal_connect (G_OBJECT (info->area), "button_release_event", G_CALLBACK (move_mouse), info);
  g_signal_connect (G_OBJECT (info->area), "draw", G_CALLBACK (draw_event), info);  
 


  // create separator ....................................................................
  info->sep[1] = gtk_separator_new (overt);
  gtk_box_pack_start (GTK_BOX (info->box[1]), info->sep[1], FALSE, TRUE, 10);



  // boxes for the buttons .....................................................
  info->box[9] = gtk_box_new (ohori, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[9]), 0);
  gtk_box_pack_end (GTK_BOX (info->box[2]), info->box[9], TRUE, FALSE, 0);
  

  // buttons .........................................................
  info->button[0] = gtk_button_new_with_label (" ▶ Play");
  gtk_widget_set_size_request (info->button[0], bxlen, bylen);
  gtk_box_pack_start (GTK_BOX (info->box[9]), info->button[0], FALSE, FALSE, 5);
  g_signal_connect (G_OBJECT (info->button[0]), "clicked", G_CALLBACK (play_button), info);

  info->button[1] = gtk_button_new_with_label (" ▌▌ Pause");
  gtk_widget_set_size_request (info->button[1], bxlen, bylen);
  gtk_box_pack_start (GTK_BOX (info->box[9]), info->button[1], FALSE, FALSE, 5);
  g_signal_connect (G_OBJECT (info->button[1]), "clicked", G_CALLBACK (pause_button), info);

  info->button[2] = gtk_button_new_with_label (" ◼ Reset");
  gtk_widget_set_size_request (info->button[2], bxlen, bylen);
  gtk_box_pack_start (GTK_BOX (info->box[9]), info->button[2], FALSE, FALSE, 5);
  g_signal_connect (G_OBJECT (info->button[2]), "clicked", G_CALLBACK (reset_button), info);

  info->button[3] = gtk_button_new_with_label (" Graphic");
  gtk_widget_set_size_request (info->button[3], bxlen, bylen);
  gtk_box_pack_start (GTK_BOX (info->box[9]), info->button[3], FALSE, FALSE, 5);
  g_signal_connect (G_OBJECT (info->button[3]), "clicked", G_CALLBACK (graph_button), info);


  // toggle button show/hide velocity ................................
  info->button[4] = gtk_toggle_button_new_with_label ("Show/Hide velocity");
  gtk_widget_set_size_request (info->button[4], bxlen, bylen);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (info->button[4]), FALSE);
  gtk_box_pack_start (GTK_BOX (info->box[9]), info->button[4], FALSE, FALSE, 5);
  g_signal_connect (G_OBJECT (info->button[4]), "clicked", G_CALLBACK (toggle_button), info);

  // combo box .......................................................
  gint i1;

  info->cbox = gtk_combo_box_text_new ();
  gtk_widget_set_size_request (info->cbox, bxlen, bylen);
  for (i1 = 0; i1 < 5; ++i1)
    gtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (info->cbox), i1, NULL, cb_text[i1]);
  gtk_combo_box_set_active (GTK_COMBO_BOX (info->cbox), 0);
  gtk_box_pack_start (GTK_BOX (info->box[9]),info->cbox, FALSE, TRUE, 0);
  g_signal_connect (G_OBJECT (info->cbox), "changed", G_CALLBACK (combo_box), info);
  

    
  // create box 4 with frames and spinbuttons ............................................
  info->box[4] = gtk_box_new (overt, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[4]), 10);
  gtk_box_pack_end (GTK_BOX (info->box[1]), info->box[4], TRUE, TRUE, 0);


  // position ..................................................................
  info->box[5] = gtk_box_new (overt, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[5]), 10);

  info->frame[2] = gtk_frame_new (" Position ");
  gtk_frame_set_label_align (GTK_FRAME(info->frame[2]), 0.5 , 1);
  gtk_box_pack_start (GTK_BOX (info->box[4]), info->frame[2], FALSE, TRUE, 10);

  gtk_container_add (GTK_CONTAINER (info->frame[2]), info->box[5]);

  // position X ......................................................
  info->frame[3] = gtk_frame_new (" X ");
  gtk_frame_set_label_align (GTK_FRAME(info->frame[3]), 0.5 , 0.5);
  gtk_box_pack_start (GTK_BOX (info->box[5]), info->frame[3], FALSE, TRUE, 5);

  info->spinbutton[0] = gtk_spin_button_new_with_range (0, 500, 1);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spinbutton[0]), 2);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[0]), CIRCLE_CENTER_X);
  gtk_container_add (GTK_CONTAINER (info->frame[3]), info->spinbutton[0]);
  g_signal_connect (G_OBJECT (info->spinbutton[0]), "value-changed", G_CALLBACK (button_changed),info);

  // position Y ......................................................
  info->frame[4] = gtk_frame_new (" Y ");
  gtk_frame_set_label_align (GTK_FRAME (info->frame[4]), 0.5 , 0.5);
  gtk_box_pack_start (GTK_BOX (info->box[5]), info->frame[4], FALSE, TRUE, 5);

  info->spinbutton[1] = gtk_spin_button_new_with_range (0, 500, 1);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spinbutton[1]), 2);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[1]), CIRCLE_CENTER_Y);
  gtk_container_add (GTK_CONTAINER (info->frame[4]), info->spinbutton[1]);
  g_signal_connect (G_OBJECT (info->spinbutton[1]), "value-changed", G_CALLBACK (button_changed), info);


  // radius ....................................................................
  info->box[6] = gtk_box_new (overt, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[6]), 10);

  info->frame[5] = gtk_frame_new (" Radius ");
  gtk_frame_set_label_align (GTK_FRAME(info->frame[5]), 0.5 , 1);
  gtk_box_pack_start (GTK_BOX (info->box[4]), info->frame[5], FALSE, TRUE, 10);

  gtk_container_add (GTK_CONTAINER (info->frame[5]), info->box[6]);

  // big ball ........................................................
  info->frame[6] = gtk_frame_new (" Big Circle ");
  gtk_frame_set_label_align (GTK_FRAME (info->frame[6]), 0.5 , 0.5);
  gtk_box_pack_start (GTK_BOX (info->box[6]), info->frame[6], FALSE, TRUE, 5);

  info->spinbutton[2] = gtk_spin_button_new_with_range (25, 50, 0.5);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON(info->spinbutton[2]), 2);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[2]), RADIUS_INI);
  gtk_container_add (GTK_CONTAINER (info->frame[6]), info->spinbutton[2]);
  g_signal_connect (G_OBJECT (info->spinbutton[2]), "value-changed", G_CALLBACK (button_changed), info);

  // small ball ......................................................
  info->frame[7] = gtk_frame_new (" Small Circles ");
  gtk_frame_set_label_align (GTK_FRAME(info->frame[7]), 0.5 , 0.5);
  gtk_box_pack_start (GTK_BOX (info->box[6]), info->frame[7], FALSE, TRUE, 5);

  info->spinbutton[3] = gtk_spin_button_new_with_range (1, 5, 0.5);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spinbutton[3]), 2);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[3]), RADIUS_2_INI);
  gtk_container_add (GTK_CONTAINER (info->frame[7]), info->spinbutton[3]);
  g_signal_connect (G_OBJECT (info->spinbutton[3]), "value-changed", G_CALLBACK (button_changed), info);


  // velocity ..................................................................
  info->box[8] = gtk_box_new (overt, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[8]), 10);

  info->frame[8] = gtk_frame_new (" Initial Velocity ");
  gtk_frame_set_label_align (GTK_FRAME (info->frame[8]), 0.5 , 1);
  gtk_box_pack_start (GTK_BOX (info->box[4]), info->frame[8], FALSE, TRUE, 10);

  gtk_container_add (GTK_CONTAINER (info->frame[8]), info->box[8]);

  // bola grande .....................................................
  info->frame[9] = gtk_frame_new (" Big Circle ");
  gtk_frame_set_label_align (GTK_FRAME(info->frame[9]), 0.5 , 0.5);
  gtk_box_pack_start (GTK_BOX (info->box[8]), info->frame[9], FALSE, TRUE, 5);

  info->spinbutton[4] = gtk_spin_button_new_with_range (0.5, 5, 0.25);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spinbutton[4]), 2);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[4]), VEL_INI);
  gtk_container_add (GTK_CONTAINER (info->frame[9]), info->spinbutton[4]);
  g_signal_connect (G_OBJECT (info->spinbutton[4]), "value-changed", G_CALLBACK (button_changed), info);

  // bola pequena ....................................................
  info->frame[10] = gtk_frame_new (" Small Circles ");
  gtk_frame_set_label_align (GTK_FRAME(info->frame[10]), 0.5 , 0.5);
  gtk_box_pack_start (GTK_BOX (info->box[8]), info->frame[10], FALSE, TRUE, 5);

  info->spinbutton[5] = gtk_spin_button_new_with_range (0.5, 15, 0.5);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (info->spinbutton[5]), 2);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (info->spinbutton[5]), VEL_2_INI);
  gtk_container_add (GTK_CONTAINER (info->frame[10]), info->spinbutton[5]);
  g_signal_connect (G_OBJECT (info->spinbutton[5]), "value-changed", G_CALLBACK (button_changed), info);


  // toggle show/hide circles ........................................
  info->button[5] = gtk_toggle_button_new_with_label (" Show/Hide Small Circles ");
  gtk_widget_set_size_request (info->button[5], bxlen, bylen);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (info->button[5]), FALSE);
  gtk_box_pack_start (GTK_BOX (info->box[4]), info->button[5], FALSE, FALSE, 5);
  g_signal_connect (G_OBJECT (info->button[5]), "clicked", G_CALLBACK (toggle_button), info);


  // create separator ..........................................................
  info->sep[2] = gtk_separator_new (ohori);
  gtk_box_pack_start (GTK_BOX (info->box[0]), info->sep[2], FALSE, TRUE, 10);



  // create box 3 ........................................................................
  info->box[3] = gtk_box_new (ohori, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[3]), 10);
  gtk_box_pack_start (GTK_BOX (info->box[0]), info->box[3], TRUE, FALSE, 0);

  // box for frames with scales ................................................
  info->box[10] = gtk_box_new (overt, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[10]), 10);

  info->frame[11] = gtk_frame_new ("");
  gtk_frame_set_label_align (GTK_FRAME (info->frame[11]), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX (info->box[3]), info->frame[11], TRUE, TRUE, 10);
  
  gtk_container_add (GTK_CONTAINER (info->frame[11]), info->box[10]);


  info->label[2] = gtk_label_new (" Number of Small Circles ");
  gtk_box_pack_start (GTK_BOX (info->box[10]), info->label[2], TRUE, FALSE, 0);

  info->adj[2] = (GtkAdjustment *) gtk_adjustment_new (100, 0, 10*NCIRCLES, 1., 10, 0); 
  info->scale[2] = gtk_scale_new (ohori, info->adj[2]);
  gtk_scale_set_value_pos (GTK_SCALE (info->scale[2]), GTK_POS_TOP);
  gtk_scale_set_digits (GTK_SCALE (info->scale[2]), 0);
  gtk_box_pack_start (GTK_BOX (info->box[10]), info->scale[2], FALSE, FALSE, 3);
  g_signal_connect (G_OBJECT (info->scale[2]), "value-changed", G_CALLBACK (button_changed), info);


  info->box[11] = gtk_box_new (overt, 0);
  gtk_container_set_border_width (GTK_CONTAINER (info->box[10]), 3);

  info->frame[1] = gtk_frame_new ("");
  gtk_frame_set_label_align (GTK_FRAME (info->frame[1]), 0.5, 0.5);
  gtk_box_pack_start (GTK_BOX (info->box[10]), info->frame[1], TRUE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (info->frame[1]), info->box[11]);


  info->label[0] = gtk_label_new (" Big Circle Mass ");
  gtk_box_pack_start (GTK_BOX (info->box[11]), info->label[0], FALSE, FALSE, 0);

  info->adj[0] = (GtkAdjustment *) gtk_adjustment_new (BIGMASS, 100, 2000, 1, 10, 0); 
  info->scale[0] = gtk_scale_new (ohori, info->adj[0]);
  gtk_scale_set_value_pos (GTK_SCALE (info->scale[0]), GTK_POS_TOP);
  gtk_box_pack_start (GTK_BOX (info->box[11]), info->scale[0], FALSE, FALSE, 3);
  g_signal_connect (G_OBJECT (info->scale[0]), "value-changed", G_CALLBACK (button_changed), info);

  info->label[1] = gtk_label_new (" Small Circles Mass ");
  gtk_box_pack_start (GTK_BOX (info->box[11]), info->label[1], FALSE, FALSE, 0);

  info->adj[1] = (GtkAdjustment *) gtk_adjustment_new (SMALLMASS, 10, 100, 1, 10, 0); 
  info->scale[1] = gtk_scale_new (ohori, info->adj[1]);
  gtk_scale_set_value_pos (GTK_SCALE (info->scale[1]), GTK_POS_TOP);
  gtk_box_pack_start(GTK_BOX (info->box[11]), info->scale[1], FALSE, FALSE, 3);
  g_signal_connect (G_OBJECT (info->scale[1]), "value-changed", G_CALLBACK (button_changed), info);



  // colors ..............................................................................
  gdk_rgba_parse (&colorwhite1, "#FFFFFF");
  gdk_rgba_parse (&colorblack1, "#000000");
  gdk_rgba_parse (&colorranho1, "#CCCC00");

  gtk_widget_override_background_color (info->frame[0], GTK_STATE_NORMAL, &colorwhite1);
  gtk_widget_override_background_color (info->frame[2], GTK_STATE_NORMAL, &colorwhite1);
  gtk_widget_override_font (info->frame[2], pango_font_description_from_string("Tahoma bold 11"));
  gtk_widget_override_font (info->frame[3], pango_font_description_from_string("Tahoma bold 9"));
  gtk_widget_override_font (info->frame[4], pango_font_description_from_string("Tahoma bold 9"));
  gtk_widget_override_background_color (info->frame[5], GTK_STATE_NORMAL, &colorwhite1);
  gtk_widget_override_font (info->frame[5], pango_font_description_from_string("Tahoma bold 11"));
  gtk_widget_override_font (info->frame[6], pango_font_description_from_string("Tahoma bold 9"));
  gtk_widget_override_font (info->frame[7], pango_font_description_from_string("Tahoma bold 9"));
  gtk_widget_override_background_color (info->frame[8], GTK_STATE_NORMAL, &colorwhite1);
  gtk_widget_override_font (info->frame[8], pango_font_description_from_string("Tahoma bold 11"));
  gtk_widget_override_font (info->frame[9], pango_font_description_from_string("Tahoma bold 9"));
  gtk_widget_override_font (info->frame[10], pango_font_description_from_string("Tahoma bold 9"));
  gtk_widget_override_background_color (info->frame[11], GTK_STATE_NORMAL, &colorwhite1);
  gtk_widget_override_font (info->frame[11], pango_font_description_from_string("Tahoma bold 11"));
  gtk_widget_override_font (info->frame[1], pango_font_description_from_string("Tahoma bold 9"));
}



//////////////////// Main Function /////////////////////////////////////////////////////////////////



int main (int argc, char **argv)
{
  data *info;
  info = (data *) data_new();

  gtk_init (&argc,&argv);
  
  create_structure (info);

  g_timeout_add (20, (GSourceFunc) time_handler, info);

  gtk_widget_show_all (info->window);
  gtk_main ();

  free (info->gr_vel);
  free (info->rastox);
  free (info->rastoy);
  free (info->centerx_2);
  free (info->centery_2);
  free (info->velx_2);
  free (info->vely_2);

  return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
