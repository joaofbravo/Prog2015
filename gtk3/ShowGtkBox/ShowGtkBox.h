#ifndef __SHOW_GTK_BOX_H__
#define __SHOW_GTK_BOX_H__ 1

#define WIN_GEOM_DEF_WIDTH   1000
#define WIN_GEOM_DEF_HEIGHT   700
#define WIN_GEOM_DEF_POSX      10
#define WIN_GEOM_DEF_POSY      10

#include "gb_styles.h"

typedef enum
{ 
  BoxO_0, BoxO_H, BoxO_V
} BoxOrientSet ;

typedef enum
{ 
  BoxCF_Container, BoxCF_PackStart, BoxCF_PackEnd
} BoxCreateFunctionSet ;

typedef struct
{
  char                 *name   ;
  BoxOrientSet          vh     ;
  gint                  parent ;
  gint                  flag   ;
  GtkWidget            *frame  ;
  GtkWidget            *box    ;

  gboolean              homo   ;
  gint                  space  ;
  BoxCreateFunctionSet  func   ;
  gboolean              expand ;
  gboolean              fill   ;
  gint                  padd   ;
} ShowGtkBoxVBoxes ;

typedef struct
{
  long int            geom[4] ;
  GtkWidget          *win     ;
  GtkWidget          *vbox    ;

  GtkWidget          *mbar    ;
  GtkWidget          *mfile   ;
  GtkWidget          *mhelp   ;

  GtkWidget          *hbox1   ;
  GtkWidget          *ftests  ;
  GtkWidget          *vb_opts ;
  GtkWidget          *bt_hv   ;
  GtkWidget          *bt_homo ;
  GtkWidget          *sp_space ;

  GtkWidget          *cb_bxcont ;
  GtkWidget          *cb_parent ;

  GtkWidget          *bt_expand ;
  GtkWidget          *bt_fill   ;
  GtkWidget          *sp_padd   ;

  GtkWidget          *bt_exec   ;
  GtkWidget          *bt_undo   ;

  GtkWidget          *bt_exit   ;
  GtkWidget          *vbox_info ;
  GtkWidget          *vbi_label[3] ;

  gint                flag_box_hv ;
  gint                flag_box_homo ;
  gint                flag_box_expand ;
  gint                flag_box_fill ;

  gint                flag_mostra   ;
  gint                qt_sty  ;

  gint                qt_vpb ;
  ShowGtkBoxVBoxes  **vpb    ;
} ShowGtkBoxWindow ;

typedef struct
{

  ShowGtkBoxWindow   *w   ;
  StylesStruct      **sty ;
  
} ShowGtkBoxStruct ;

#endif /* __SHOW_GTK_BOX_H__ */
