/*  gb_window.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#include "ShowGtkBox.h"
#include "gb_error.h"
#include "gb_styles.h"
#include "gb_auxil.h"
#include "gb_window.h"


void
gb_vbox_info_show_info (ShowGtkBoxStruct  *gb   ,
                        gchar             *str0 ,
                        gchar             *str1 ,
                        gchar             *str2 )
{
  if (str0)
    gtk_label_set_text (GTK_LABEL (gb->w->vbi_label[0]), str0);
  if (str1)
    gtk_label_set_text (GTK_LABEL (gb->w->vbi_label[1]), str1);
  if (str2)
    gtk_label_set_text (GTK_LABEL (gb->w->vbi_label[2]), str2);
}

static gboolean
gb_button_hv_change (GtkWidget         *w  ,
                     ShowGtkBoxStruct  *gb )
{
  gb->w->flag_box_hv = (gb->w->flag_box_hv + 1) % 2;
  gtk_button_set_label (GTK_BUTTON (w), InfoError_GetText (0, (gb->w->flag_box_hv == 0 ? 13 : 12)));

  return FALSE;
}

static gboolean
gb_button_homo_change (GtkWidget         *w  ,
                       ShowGtkBoxStruct  *gb )
{
  gb->w->flag_box_homo = (gb->w->flag_box_homo + 1) % 2;
  gtk_button_set_label (GTK_BUTTON (w), InfoError_GetText (0, (gb->w->flag_box_homo == 0 ? 15 : 16)));

  return FALSE;
}

static gboolean
gb_button_fill (GtkWidget         *w  ,
                ShowGtkBoxStruct  *gb )
{
  gb->w->flag_box_fill = (gb->w->flag_box_fill + 1) % 2;
  gtk_button_set_label (GTK_BUTTON (w), InfoError_GetText (0, (gb->w->flag_box_fill == 0 ? 15 : 16)));

  return FALSE;
}

static gboolean
gb_button_expand (GtkWidget         *w  ,
                  ShowGtkBoxStruct  *gb )
{
  gb->w->flag_box_expand = (gb->w->flag_box_expand + 1) % 2;
  gtk_button_set_label (GTK_BUTTON (w), InfoError_GetText (0, (gb->w->flag_box_expand == 0 ? 15 : 16)));

  return FALSE;
}

static gboolean
gb_cbox_create_function (GtkWidget         *w  ,
                         ShowGtkBoxStruct  *gb )
{
  BoxCreateFunctionSet  opt_fcreate ;

  opt_fcreate = gtk_combo_box_get_active (GTK_COMBO_BOX (gb->w->cb_bxcont));

  if (opt_fcreate == BoxCF_Container)
    {
      gtk_widget_set_sensitive (gb->w->bt_expand, FALSE);
      gtk_widget_set_sensitive (gb->w->bt_fill, FALSE);
      gtk_widget_set_sensitive (gb->w->sp_padd, FALSE);
    }
  else
    {
      gtk_widget_set_sensitive (gb->w->bt_expand, TRUE);
      gtk_widget_set_sensitive (gb->w->bt_fill, TRUE);
      gtk_widget_set_sensitive (gb->w->sp_padd, TRUE);
    }

  return FALSE;
}



static gboolean
gb_button_exit (GtkWidget         *w  ,
                ShowGtkBoxStruct  *gb )
{
  gb_exit(gb->w->win, gb);

  return FALSE;
}

/******************************************************/

gboolean
gb_vpb_is_child (ShowGtkBoxStruct  *gb   ,
                 gint               num  ,
                 gint               npar )
{
  gint i1 ;

  i1 = num;
  while (i1 > 0)
    {
      if (gb->w->vpb[i1]->parent == npar)
        return TRUE;
      i1 = gb->w->vpb[i1]->parent;
    }
  return FALSE;
}

void
gb_vpb_children_flag (ShowGtkBoxStruct  *gb   , 
                      gint               npar )
{
  gint i1 ;

  for (i1 = 1 ; i1 < gb->w->qt_vpb ; ++i1)
    gb->w->vpb[i1]->flag = 0;

  for (i1 = 1 ; i1 < gb->w->qt_vpb ; ++i1)
    if (gb_vpb_is_child (gb, i1, npar))
      gb->w->vpb[i1]->flag = 1;
}

gint 
gb_vpb_parent_alive (ShowGtkBoxStruct  *gb  , 
                     gint               num )
{
  while (num > 0)
    {
      if (gb->w->vpb[num]->flag == 0)
	break;
      num = gb->w->vpb[num]->parent;
    }

  return num;
}

static gboolean
gb_button_undo (GtkWidget         *w  ,
                ShowGtkBoxStruct  *gb )
{
  gint  n1, cb_par, n_par ;
  gchar boxDestroyStr[64] ;

  if (gb->w->qt_vpb == 1)
    return FALSE;

  n1 = gb->w->qt_vpb - 1;
  cb_par = gtk_combo_box_get_active (GTK_COMBO_BOX (gb->w->cb_parent));
  n_par = gb->w->vpb[n1]->parent;
  sprintf (boxDestroyStr, "gtk_widget_destroy (%s);", gb->w->vpb[n1]->name);

  gtk_widget_destroy (gb->w->vpb[n1]->box);
  gtk_widget_destroy (gb->w->vpb[n1]->frame);
  gtk_combo_box_text_remove (GTK_COMBO_BOX_TEXT (gb->w->cb_parent), n1);
  free (gb->w->vpb[n1]->name);
  free (gb->w->vpb[n1]);
  gb->w->vpb = (ShowGtkBoxVBoxes **) realloc (gb->w->vpb, n1 * sizeof (ShowGtkBoxVBoxes *));
  --gb->w->qt_vpb;

  gb_vbox_info_show_info (gb, boxDestroyStr, "", "");

  if (n1 == cb_par)
    gtk_combo_box_set_active (GTK_COMBO_BOX (gb->w->cb_parent), n_par);

  if (gb->w->qt_vpb == 1)
    gtk_widget_set_sensitive (gb->w->bt_undo, FALSE);
  else
    {

    }

  return FALSE;
}

static gboolean
gb_button_exec (GtkWidget         *w  ,
                ShowGtkBoxStruct  *gb )
{
  gboolean              opt_homo, opt_exp, opt_fill, opt_vert ;
  gint                  space_val, padd_val, n_vpb ;
  gchar                 frName[64], boxNewStr[128], boxContStr[128], boxHomoStr[64] ;
  BoxCreateFunctionSet  opt_fcreate ;

  opt_vert = (gb->w->flag_box_hv == 0 ? FALSE : TRUE);
  opt_homo = (gb->w->flag_box_homo == 0 ? FALSE : TRUE);

  space_val = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (gb->w->sp_space));

  opt_fcreate = (BoxCreateFunctionSet) gtk_combo_box_get_active (GTK_COMBO_BOX (gb->w->cb_bxcont));
  //printf ("----> %d\n", opt_fcreate);

  if (opt_fcreate != BoxCF_Container)
    {
      opt_exp = (gb->w->flag_box_expand == 0 ? FALSE : TRUE);
      opt_fill = (gb->w->flag_box_fill == 0 ? FALSE : TRUE);
      padd_val = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (gb->w->sp_padd));
    }
  n_vpb = gtk_combo_box_get_active (GTK_COMBO_BOX (gb->w->cb_parent));
  if ((n_vpb == 0) && (gb->w->qt_vpb > 1))
    return FALSE;

  if (gb->w->qt_vpb == 1)
    {}  //gtk_widget_set_sensitive (gb->w->cb_parent, FALSE);

  // Create box name and info-labels

  sprintf (frName, "%s%d%s%d_", (opt_vert ? "V" : "H"), gb->w->qt_vpb, (opt_homo ? "O" : "o"), space_val);
  if (opt_fcreate == BoxCF_Container)
    {
      strcat (frName, "C");
      sprintf (boxContStr, "gtk_container_add (GTK_CONTAINER (%s), %s);", gb->w->vpb[n_vpb]->name, frName);
    }
  else
    {
      sprintf (&frName[strlen(frName)], "%s%s%s%d", (opt_fcreate == BoxCF_PackStart ? "S" : "E" ),
  	       (opt_exp ? "X" : "x"), (opt_fill ? "F" : "f"), padd_val);

      sprintf (boxContStr, "gtk_box_pack_%s (GTK_BOX (%s), %s, %s, %s, %d);", 
	       (opt_fcreate == BoxCF_PackStart ? "start" : "end" ), gb->w->vpb[n_vpb]->name, 
	       frName, (opt_exp ? "TRUE" : "FALSE"), (opt_fill ? "TRUE" : "FALSE"), padd_val);
    }
  sprintf (boxNewStr, "box_%s = gtk_box_new (GTK_ORIENTATION_%s, %d);", frName, 
           (opt_vert ? "VERTICAL" : "HORIZONTAL"), space_val);
  sprintf (boxHomoStr, "gtk_box_set_homogeneous (GTK_BOX (%s), %s)", frName, (opt_homo ? "TRUE" : "FALSE"));

  // Create space for new box (vpb)

  gb->w->vpb = (ShowGtkBoxVBoxes **) realloc (gb->w->vpb, (gb->w->qt_vpb + 1) * sizeof (ShowGtkBoxVBoxes *));
  gb->w->vpb[gb->w->qt_vpb] = (ShowGtkBoxVBoxes *) calloc (1, sizeof (ShowGtkBoxVBoxes));

  // Create new box (and frame)

  gb->w->vpb[gb->w->qt_vpb]->name = strdup (frName);
  gb->w->vpb[gb->w->qt_vpb]->vh = (opt_vert ? BoxO_V : BoxO_H);
  gb->w->vpb[gb->w->qt_vpb]->parent = n_vpb;
  gb->w->vpb[gb->w->qt_vpb]->homo = opt_homo;
  gb->w->vpb[gb->w->qt_vpb]->space = space_val;
  gb->w->vpb[gb->w->qt_vpb]->func = opt_fcreate;
  gb->w->vpb[gb->w->qt_vpb]->expand = opt_exp;
  gb->w->vpb[gb->w->qt_vpb]->fill = opt_fill;
  gb->w->vpb[gb->w->qt_vpb]->padd = padd_val;

  if (opt_vert)
    {
      gb->w->vpb[gb->w->qt_vpb]->vh = BoxO_V;
      //gb->w->vpb[gb->w->qt_vpb]->box = gtk_vbox_new (opt_homo, space_val);
      gb->w->vpb[gb->w->qt_vpb]->box = gtk_box_new (GTK_ORIENTATION_VERTICAL, space_val);
      gtk_box_set_homogeneous (GTK_BOX (gb->w->vpb[gb->w->qt_vpb]->box), opt_homo);
    }
  else
    {
      gb->w->vpb[gb->w->qt_vpb]->vh = BoxO_H;
      //gb->w->vpb[gb->w->qt_vpb]->box = gtk_hbox_new (opt_homo, space_val);
      gb->w->vpb[gb->w->qt_vpb]->box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, space_val);
      gtk_box_set_homogeneous (GTK_BOX (gb->w->vpb[gb->w->qt_vpb]->box), opt_homo);
    }

  gb->w->vpb[gb->w->qt_vpb]->frame = gtk_frame_new (frName);
  gtk_container_set_border_width (GTK_CONTAINER (gb->w->vpb[gb->w->qt_vpb]->frame), 3);
  gtk_container_add (GTK_CONTAINER (gb->w->vpb[gb->w->qt_vpb]->frame), gb->w->vpb[gb->w->qt_vpb]->box);
  gtk_widget_show_all (gb->w->vpb[gb->w->qt_vpb]->frame);

  // Insert box 

  if (opt_fcreate == BoxCF_Container)
    gtk_container_add (GTK_CONTAINER (gb->w->vpb[n_vpb]->box), gb->w->vpb[gb->w->qt_vpb]->frame);
  else if (opt_fcreate == BoxCF_PackStart)
    gtk_box_pack_start (GTK_BOX (gb->w->vpb[n_vpb]->box), gb->w->vpb[gb->w->qt_vpb]->frame, opt_exp, opt_fill, padd_val);
  else
    gtk_box_pack_end (GTK_BOX (gb->w->vpb[n_vpb]->box), gb->w->vpb[gb->w->qt_vpb]->frame, opt_exp, opt_fill, padd_val);

  // Create new entry in combo box 'parent'

  gtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (gb->w->cb_parent), gb->w->qt_vpb, frName, frName);

  gb_vbox_info_show_info (gb, boxNewStr, boxHomoStr, boxContStr);

  if (gb->w->qt_vpb == 1)
    {
      gtk_combo_box_set_active (GTK_COMBO_BOX (gb->w->cb_parent), 1);
      gtk_widget_set_sensitive (gb->w->bt_undo, TRUE);
    }
  else
    gtk_combo_box_set_button_sensitivity (GTK_COMBO_BOX (gb->w->cb_parent), GTK_SENSITIVITY_AUTO);

  ++gb->w->qt_vpb;

  if (gb->w->flag_mostra == 1)
    {
      printf ("NewName:  %s\n", frName);
      printf ("opt_vert: %s\n", (opt_vert ? "Vertical" : "Horizontal"));
      printf ("opt_homo: %s\n", (opt_homo ? "TRUE" : "FALSE"));
      printf ("space:    %d\n", space_val);
      printf ("fcreate:  %s\n", (opt_fcreate == BoxCF_Container ? "Container" : 
				 (opt_fcreate == BoxCF_PackStart ? "PackStart" : "PackEnd" )));
      printf ("BoxPar:   Num: %d  ;  Orient: %s  ;  box: %p  ;  frame: %p\n", 
	      n_vpb, (gb->w->vpb[n_vpb]->vh ? "Vertical" : "Horizontal"), 
	      gb->w->vpb[n_vpb]->box, gb->w->vpb[n_vpb]->frame);
      printf ("opt_exp:  %s\n", (opt_fcreate == BoxCF_Container ? "---" : (opt_exp  ? "TRUE" : "FALSE")));
      printf ("opt_fill: %s\n", (opt_fcreate == BoxCF_Container ? "---" : (opt_fill ? "TRUE" : "FALSE")));
      if (opt_fcreate == BoxCF_Container) 
	printf ("padd:     ---\n"); 
      else 
	printf ("padd:     %d\n", padd_val);
      printf ("frName:   %s\n", frName);
      printf ("boxNwStr: %s\n", boxNewStr);
      printf ("boxCtStr: %s\n", boxContStr);

      printf ("\n");
    }

  return FALSE;
}

void
db_main_window_new (ShowGtkBoxStruct *gb)
{
  gint           i1                   ;
  GtkWidget     *menu, *item, *w1     ;
  GtkWidget     *vbox, *vbox2, *hbox2 ;
  GtkWidget     *frame, *sep1, *label ;
  GtkAdjustment *adj                  ;

  //gb->w->vbox = gtk_vbox_new (FALSE, 0);
  gb->w->vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (gb->w->vbox), FALSE);
  gtk_container_add (GTK_CONTAINER(gb->w->win), gb->w->vbox);

  // Create MenuBar

  gb->w->mbar = gtk_menu_bar_new ();
  gtk_menu_bar_set_pack_direction (GTK_MENU_BAR (gb->w->mbar), GTK_PACK_DIRECTION_LTR);
  gtk_box_pack_start (GTK_BOX (gb->w->vbox), gb->w->mbar, FALSE, TRUE, 0);

  gb->w->mfile = gtk_menu_new();
  menu = gtk_menu_item_new_with_mnemonic (" _File ");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu), gb->w->mfile);
  gtk_menu_shell_append (GTK_MENU_SHELL (gb->w->mbar), menu);
  item = gtk_menu_item_new_with_mnemonic (" E_xit ");
  gtk_menu_shell_append (GTK_MENU_SHELL (gb->w->mfile), item);

  gb->w->mhelp = gtk_menu_new ();
  menu = gtk_menu_item_new_with_mnemonic (" _Help ");
  //gtk_menu_item_set_right_justified (GTK_MENU_ITEM (menu), TRUE);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu), gb->w->mhelp);
  gtk_menu_shell_append (GTK_MENU_SHELL (gb->w->mbar), menu);
  item = gtk_menu_item_new_with_mnemonic (" _Help ");
  gtk_menu_shell_append (GTK_MENU_SHELL (gb->w->mhelp), item);
  item = gtk_menu_item_new_with_mnemonic (" _Acerca ");
  gtk_menu_shell_append (GTK_MENU_SHELL (gb->w->mhelp), item);
  g_signal_connect (item, "activate", G_CALLBACK (gb_about), gb);

  // Cabecalho 

  w1 = gb_label_new (gb, Sty_TitleMain, InfoError_GetText (0, 8), gb->w->vbox, FALSE);
  gtk_box_pack_start (GTK_BOX (gb->w->vbox), w1, FALSE, TRUE, 10);

  // 'Box' horizontal que contem a area de testes e as opcoes

  //gb->w->hbox1 = gtk_hbox_new (FALSE, 10);
  gb->w->hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_box_set_homogeneous (GTK_BOX (gb->w->hbox1), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (gb->w->hbox1), 5);
  //gtk_container_add (GTK_CONTAINER (gb->w->vbox), gb->w->hbox1);
  gtk_box_pack_start (GTK_BOX (gb->w->vbox), gb->w->hbox1, TRUE, TRUE, 0);

  gb->w->ftests = gtk_frame_new (InfoError_GetText (0, 9));
  gb->w->vpb[0]->name = strdup (InfoError_GetText (0, 9));
  gb->w->vpb[0]->frame = gb->w->ftests;
  gb->w->vpb[0]->box = gb->w->ftests;
  gtk_frame_set_label_align (GTK_FRAME (gb->w->ftests),(gfloat) 0.5, (gfloat) 0.5);
  gtk_frame_set_shadow_type (GTK_FRAME (gb->w->ftests), GTK_SHADOW_IN);
  gtk_box_pack_start (GTK_BOX (gb->w->hbox1), gb->w->ftests, TRUE, TRUE, 0);

  //vbox = gtk_vbox_new (FALSE, 0);
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (vbox), FALSE);
  gtk_box_pack_end (GTK_BOX (gb->w->hbox1), vbox, FALSE, TRUE, 0);

  frame = gtk_frame_new (InfoError_GetText (0, 10));
  //gtk_frame_set_label_align (GTK_FRAME (frame), (gfloat) 0.5, (gfloat) 0.5);
  //gtk_widget_set_style (frame, gb->style->frame);
  //gtk_widget_override_background_color(frame, GTK_STATE_NORMAL, gb->sty[Sty_Frame1]->fg_normal);
  //gtk_widget_override_background_color(gtk_frame_get_label_widget (GTK_FRAME (frame)), GTK_STATE_NORMAL, gb->sty[Sty_Frame1]->bg_normal);
  gtk_widget_override_color (frame, GTK_STATE_NORMAL, gb->sty[Sty_Frame1]->fg_normal);
  gtk_widget_override_font (frame, pango_font_description_from_string(gb->sty[Sty_Frame1]->font));

  //gtk_container_add (GTK_CONTAINER (vbox), frame);
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);
  
  //vbox = gtk_vbox_new (FALSE, 0);
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (vbox), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  frame = gtk_frame_new (InfoError_GetText (0, 11));
  gtk_frame_set_label_align (GTK_FRAME (frame), (gfloat) 0.5, (gfloat) 0.5);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, TRUE, 0);

  //vbox2 = gtk_vbox_new (FALSE, 0);
  vbox2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (vbox2), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (vbox2), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox2);

  gb->w->flag_box_hv = 1;
  gb->w->bt_hv = gtk_button_new_with_label (InfoError_GetText (0, 12));
  g_signal_connect (G_OBJECT (gb->w->bt_hv), "clicked", G_CALLBACK (gb_button_hv_change), gb);
  gtk_box_pack_start (GTK_BOX (vbox2), gb->w->bt_hv, FALSE, TRUE, 0);

  //sep1 = gtk_hseparator_new ();
  sep1 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (vbox2), sep1, FALSE, TRUE, 5);

  //hbox2 = gtk_hbox_new (TRUE, 0);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (hbox2), TRUE);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox2, FALSE, TRUE, 0);

  frame = gtk_frame_new (InfoError_GetText(0, 14));
  gtk_frame_set_label_align (GTK_FRAME (frame), (gfloat) 0.5, (gfloat) 0.5);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 1);
  gtk_container_add (GTK_CONTAINER (hbox2), frame);
 
  gb->w->flag_box_homo = 0;
  gb->w->bt_homo = gtk_button_new_with_label (InfoError_GetText (0, 15));
  g_signal_connect (G_OBJECT (gb->w->bt_homo), "clicked", G_CALLBACK (gb_button_homo_change), gb);
  gtk_container_set_border_width (GTK_CONTAINER (gb->w->bt_homo), 2);
  gtk_container_add (GTK_CONTAINER (frame), gb->w->bt_homo);

  frame = gtk_frame_new (InfoError_GetText (0, 17));
  gtk_frame_set_label_align (GTK_FRAME (frame), (gfloat) 0.5, (gfloat) 0.5);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 1);
  gtk_container_add (GTK_CONTAINER (hbox2), frame);
 
  adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 100.0, 1.0, 1.0, 0.0);
  gb->w->sp_space = gtk_spin_button_new (adj, 1.0, 0);
  gtk_container_add (GTK_CONTAINER (frame), gb->w->sp_space);
  
  // Escolha da funcao de integracao da 'box' ('gtk_container_add', 'gtk_box_pack_start', 'gtk_box_pack_end')

  frame = gtk_frame_new (InfoError_GetText (0, 18));
  gtk_frame_set_label_align (GTK_FRAME (frame), (gfloat) 0.5, (gfloat) 0.5);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, TRUE, 4);

  //hbox2 = gtk_hbox_new (FALSE, 0);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (hbox2), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 3);
  gtk_container_add (GTK_CONTAINER (frame), hbox2);

  gb->w->cb_bxcont = gtk_combo_box_text_new ();
  gtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (gb->w->cb_bxcont), BoxCF_Container, 
			     "gtk_container_add", "gtk_container_add");
  gtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (gb->w->cb_bxcont), BoxCF_PackStart, 
			     "gtk_box_pack_start", "gtk_box_pack_start");
  gtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (gb->w->cb_bxcont), BoxCF_PackEnd, 
			     "gtk_box_pack_end", "gtk_box_pack_end");
  gtk_combo_box_set_active (GTK_COMBO_BOX (gb->w->cb_bxcont), BoxCF_Container);
  gtk_container_add (GTK_CONTAINER (hbox2), gb->w->cb_bxcont);
  g_signal_connect (G_OBJECT (gb->w->cb_bxcont), "changed", G_CALLBACK (gb_cbox_create_function), gb);

  // Combo Box com as 'boxes' criadas que por sua vez podem conter outras 'boxes'

  frame = gtk_frame_new (InfoError_GetText (0, 19));
  gtk_frame_set_label_align (GTK_FRAME (frame), (gfloat) 0.5, (gfloat) 0.5);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, TRUE, 4);

  //hbox2 = gtk_hbox_new (FALSE, 0);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (hbox2), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 3);
  gtk_container_add (GTK_CONTAINER (frame), hbox2);

  gb->w->cb_parent = gtk_combo_box_text_new ();
  gtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (gb->w->cb_parent), 0, InfoError_GetText (0, 9), 
			     InfoError_GetText (0, 9));
  gtk_combo_box_set_active (GTK_COMBO_BOX (gb->w->cb_parent), 0);
  //gtk_container_add (GTK_CONTAINER (hbox2), gb->w->cb_parent);
  gtk_box_pack_start (GTK_BOX (hbox2), gb->w->cb_parent, TRUE, TRUE, 0);

  // Opcao "Expand": box, label e button

  //hbox2 = gtk_hbox_new (FALSE, 0);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (hbox2), FALSE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox2, FALSE, TRUE, 2);
  label = gtk_label_new (InfoError_GetText (0, 20));
  gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 2);
  gb->w->bt_expand = gtk_button_new_with_label (InfoError_GetText (0, 15));
  gtk_widget_set_size_request (gb->w->bt_expand, 62, 29);
  g_signal_connect (G_OBJECT (gb->w->bt_expand), "clicked", G_CALLBACK (gb_button_expand), gb);
  gtk_box_pack_end (GTK_BOX (hbox2), gb->w->bt_expand, FALSE, TRUE, 2);
  gb->w->flag_box_expand = 0;
  
  // Opcao "Fill": box, label e button

  //hbox2 = gtk_hbox_new (FALSE, 0);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (hbox2), FALSE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox2, FALSE, TRUE, 2);
  label = gtk_label_new (InfoError_GetText (0, 21));
  gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 2);
  gb->w->bt_fill = gtk_button_new_with_label (InfoError_GetText (0, 16));
  gtk_widget_set_size_request (gb->w->bt_fill, 62, 29);
  g_signal_connect (G_OBJECT (gb->w->bt_fill), "clicked", G_CALLBACK (gb_button_fill), gb);
  gtk_box_pack_end (GTK_BOX (hbox2), gb->w->bt_fill, FALSE, TRUE, 2);
  gb->w->flag_box_fill = 1;

  // Opcao "Padding": box, label e spin

  //hbox2 = gtk_hbox_new (FALSE, 0);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (hbox2), FALSE);
  gtk_box_pack_start (GTK_BOX (vbox), hbox2, FALSE, TRUE, 2);
  label = gtk_label_new (InfoError_GetText (0, 22));
  gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 2);

  adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 100.0, 1.0, 1.0, 0.0);
  gb->w->sp_padd = gtk_spin_button_new (adj, 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (gb->w->sp_padd), TRUE);
  gtk_widget_set_size_request (gb->w->sp_padd, 62, 29);
  gtk_box_pack_end (GTK_BOX (hbox2), gb->w->sp_padd, FALSE, TRUE, 2);

  // Separador

  //sep1 = gtk_hseparator_new ();
  sep1 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (vbox), sep1, FALSE, TRUE, 5);

  // Botoes: "Aplicar" e "Desfazer"

  gb->w->bt_exec = gtk_button_new_with_label (InfoError_GetText (0, 23));
  //gtk_widget_set_style (GTK_BIN (gb->w->bt_exec)->child, wtb->style->button);
  gtk_container_set_border_width (GTK_CONTAINER (gb->w->bt_exec), 2);
  g_signal_connect (G_OBJECT (gb->w->bt_exec), "clicked", G_CALLBACK (gb_button_exec), gb);
  gtk_box_pack_end (GTK_BOX (vbox), gb->w->bt_exec, FALSE, TRUE, 0);
  
  gb->w->bt_undo = gtk_button_new_with_label (InfoError_GetText (0, 24));
  //gtk_widget_set_style (GTK_BIN (gb->w->bt_undo)->child, wtb->style->button);
  gtk_container_set_border_width (GTK_CONTAINER (gb->w->bt_undo), 2);
  g_signal_connect (G_OBJECT (gb->w->bt_undo), "clicked", G_CALLBACK (gb_button_undo), gb);
  gtk_box_pack_end (GTK_BOX (vbox), gb->w->bt_undo, FALSE, TRUE, 0);
  
  // Combo Box delete
  /*
  frame = gtk_frame_new (InfoError_GetText (0, 29));
  gtk_frame_set_label_align (GTK_FRAME (frame), (gfloat) 0.5, (gfloat) 0.5);
  gtk_box_pack_end (GTK_BOX (vbox), frame, FALSE, TRUE, 4);

  //hbox2 = gtk_hbox_new (FALSE, 0);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (hbox2), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 3);
  gtk_container_add (GTK_CONTAINER (frame), hbox2);
  */
  /* zona de teste */
  /*
  {
    GtkTreeStore *TStore ;

    TStore = gtk_tree_store_new (2, G_TYPE_INT, G_TYPE_STRING); // GDK_TYPE_PIXBUF);

    gb->w->cb_delete = gtk_combo_box_text_new ();

    gtk_box_pack_start (GTK_BOX (hbox2), gb->w->cb_delete, TRUE, TRUE, 0);
  }
  */
  /* fim de zona de teste */

  /*
  gb->w->cb_delete = gtk_combo_box_text_new ();
  gtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (gb->w->cb_delete), 0, "", "");
  gtk_combo_box_set_active (GTK_COMBO_BOX (gb->w->cb_delete), 0);
  //gtk_container_add (GTK_CONTAINER (hbox2), gb->w->cb_delete);
  gtk_box_pack_start (GTK_BOX (hbox2), gb->w->cb_delete, TRUE, TRUE, 0);

  gb->w->bt_delete = gtk_button_new_with_label (InfoError_GetText (0, 30));
  gtk_container_set_border_width (GTK_CONTAINER (gb->w->bt_delete), 2);
  gtk_widget_set_size_request (gb->w->bt_delete, 38, 26);
  g_signal_connect (G_OBJECT (gb->w->bt_delete), "clicked", G_CALLBACK (gb_button_delete), gb);
  gtk_box_pack_end (GTK_BOX (hbox2), gb->w->bt_delete, FALSE, TRUE, 0);
  */
  // Area final com box de escrita e botao sair

  //hbox2 = gtk_hbox_new (FALSE, 0);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (hbox2), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 8);
  gtk_box_pack_end (GTK_BOX (gb->w->vbox), hbox2, FALSE, TRUE, 0);

  //sep1 = gtk_hseparator_new ();
  sep1 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_end (GTK_BOX (vbox), sep1, FALSE, TRUE, 0);

  frame = gtk_frame_new (NULL);
  gtk_box_pack_start (GTK_BOX (hbox2), frame, TRUE, TRUE, 0);

  //gb->w->vbox_info = gtk_vbox_new (FALSE, 0);
  gb->w->vbox_info = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_set_homogeneous (GTK_BOX (gb->w->vbox_info), FALSE);
  gtk_container_add (GTK_CONTAINER (frame), gb->w->vbox_info);

  gb->w->bt_exit = gtk_button_new_with_label (InfoError_GetText (0, 25));
  gtk_container_set_border_width (GTK_CONTAINER (gb->w->bt_exit), 10);
  gtk_widget_set_size_request (gb->w->bt_exit, 138, 46);
  g_signal_connect (G_OBJECT (gb->w->bt_exit), "clicked", G_CALLBACK (gb_button_exit), gb);
  gtk_box_pack_end (GTK_BOX (hbox2), gb->w->bt_exit, FALSE, TRUE, 0);

  for (i1 = 0 ; i1 < 3 ; ++i1)
    {
      //hbox2 = gtk_hbox_new (FALSE, 0);
      hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
      gtk_box_set_homogeneous (GTK_BOX (hbox2), FALSE);
      gtk_box_pack_start (GTK_BOX (gb->w->vbox_info), hbox2, FALSE, TRUE, 2);
      gb->w->vbi_label[i1] = gtk_label_new ("");
      gtk_box_pack_start (GTK_BOX (hbox2), gb->w->vbi_label[i1], FALSE, TRUE, 7);
    }
  gb_vbox_info_show_info (gb, InfoError_GetText (0, 26), InfoError_GetText (0, 27), ""); //, InfoError_GetText (0, 28));

  gtk_widget_set_sensitive (gb->w->bt_expand, FALSE);
  gtk_widget_set_sensitive (gb->w->bt_fill, FALSE);
  gtk_widget_set_sensitive (gb->w->sp_padd, FALSE);
  gtk_widget_set_sensitive (gb->w->bt_undo, FALSE);
  //gtk_widget_set_sensitive (gb->w->cb_delete, FALSE);
}
