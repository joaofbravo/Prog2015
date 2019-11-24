/*  gb_styles.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "gb_styles.h"

//GdkColor  *
GdkRGBA *
gb_rgba_set_color (gchar *str1)
{
  GdkRGBA *cor1 = NULL;

  if (str1) 
    {
      cor1 = (GdkRGBA *) malloc (sizeof (GdkRGBA));
      gdk_rgba_parse (cor1, str1);
      //gdk_color_parse (str1, cor1);
    }

  return cor1 ;
}

void
gb_style_set (StylesStruct *sty1        , 
              gchar        *font1       ,
              gchar        *bg_normal   ,
              gchar        *fg_normal   ,
              gchar        *bg_prelight ,
              gchar        *fg_prelight )
{
  sty1->bg_normal = gb_rgba_set_color (bg_normal);
  sty1->fg_normal = gb_rgba_set_color (fg_normal);
  sty1->bg_prelight = gb_rgba_set_color (bg_prelight);
  sty1->fg_prelight = gb_rgba_set_color (fg_prelight);
  if (font1) sty1->font = strdup(font1);
}

void
gb_widget_style_set (GtkWidget    *w   ,
                     StylesStruct *sty )
{
  // (??) Old versions
  //if (sty->font) gtk_widget_modify_font(w, pango_font_description_from_string(sty->font));
  //if (!sty->bg_normal) gtk_widget_modify_bg (w, GTK_STATE_NORMAL, sty->bg_normal);
  //if (!sty->fg_normal) gtk_widget_modify_fg (w, GTK_STATE_NORMAL, sty->fg_normal);
  //if (!sty->bg_normal) gtk_widget_modify_bg (w, GTK_STATE_PRELIGHT, sty->bg_prelight);
  //if (!sty->fg_normal) gtk_widget_modify_fg (w, GTK_STATE_PRELIGHT, sty->fg_prelight);


  if (sty->font) gtk_widget_override_font (w, pango_font_description_from_string(sty->font));
  if (!sty->bg_normal) gtk_widget_override_background_color (w, GTK_STATE_NORMAL, sty->bg_normal);
  if (!sty->fg_normal) gtk_widget_override_background_color (w, GTK_STATE_NORMAL, sty->fg_normal);
  if (!sty->bg_prelight) gtk_widget_override_background_color (w, GTK_STATE_PRELIGHT, sty->bg_prelight);
  if (!sty->fg_prelight) gtk_widget_override_background_color (w, GTK_STATE_PRELIGHT, sty->fg_prelight);
}


StylesStruct **
gb_styles_new (void)
{
  gint           qt, i1 ;
  StylesStruct **sty    ;

  qt = (gint) Sty_End;

  sty = (StylesStruct **) malloc(qt * sizeof(StylesStruct *));
  for (i1 = 0 ; i1 < qt ; ++i1)
    sty[i1] = (StylesStruct *) malloc(sizeof(StylesStruct));

  gb_style_set(sty[Sty_Msg1], "Tahoma bold 14", NULL, "#00008B00", NULL, NULL);
  gb_style_set(sty[Sty_About1], "Lucida bold 18px", NULL, "#00008B00", NULL, NULL);
  gb_style_set(sty[Sty_About2], "Lucida bold 14px", NULL, "#03030300", NULL, NULL);
  gb_style_set(sty[Sty_TitleMain], "Lucida bold 20px", NULL, "#00640000", NULL, NULL);
  gb_style_set(sty[Sty_Button1], "Lucida bold 12px", NULL, "#00640000", NULL, NULL);
  gb_style_set(sty[Sty_Frame1], "Lucida 9px", NULL, "darkblue", NULL, NULL);
  gb_style_set(sty[Sty_Frame2], "Lucida bold 12px", NULL, "magenta", NULL, NULL);

  return sty;
}
