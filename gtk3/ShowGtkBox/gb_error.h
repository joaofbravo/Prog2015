#ifndef __GB_ERROR_H__
#define __GB_ERROR_H__ 1

#include <gtk/gtk.h>

#include "ShowGtkBox.h"

extern void
InfoError_start (gchar *fname);

extern gchar *
InfoError_GetText (gint  grp ,
                   gint  num );

extern void
InfoError_show (int         exit_value ,
                int         mode       ,
                int         grp        ,
                int         num        ,
                char       *info       ,
                GtkWidget  *win        );

extern gboolean
gb_exit (GtkWidget         *win ,
         ShowGtkBoxStruct  *gb  );

extern gboolean
gb_about (GtkWidget         *w  ,
          ShowGtkBoxStruct  *gb );

#endif /* __GB_ERROR_H__ */
