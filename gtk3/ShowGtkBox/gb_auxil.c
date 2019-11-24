/*  gb_auxil.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#include "ShowGtkBox.h"
#include "gb_styles.h"
#include "gb_auxil.h"

GtkWidget *
gb_label_new (ShowGtkBoxStruct  *gb   ,
              StyleNameEnum      esty ,
              gchar             *text ,
              GtkWidget         *box  ,
              gboolean           flag )
{
  GtkWidget *label ;

  label = gtk_label_new(text);

  if (gb->sty[esty]->font)
    gtk_widget_override_font(label, pango_font_description_from_string(gb->sty[esty]->font));
  if (gb->sty[esty]->fg_normal)
    gtk_widget_override_background_color(label, GTK_STATE_NORMAL, gb->sty[esty]->fg_normal);

  if (flag)
    gtk_container_add(GTK_CONTAINER(box), label);

  return label;
}
