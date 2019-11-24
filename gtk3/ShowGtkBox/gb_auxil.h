#ifndef __GB_AUXIL_H__
#define __GB_AUXIL_H__ 1

#include <gtk/gtk.h>

#include "ShowGtkBox.h"
#include "gb_styles.h"

extern GtkWidget *
gb_label_new (ShowGtkBoxStruct  *gb   ,
              StyleNameEnum      esty ,
              gchar             *text ,
              GtkWidget         *box  ,
              gboolean           flag );

#endif  /* __GB_AUXIL_H__ */
