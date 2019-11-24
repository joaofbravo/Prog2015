/*****************************************************
 *                                                   *
 *      Minimização de Window - Event                *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2014                        *
 *                                                   *
 *****************************************************/

#include <gtk/gtk.h>

gchar *winTitle = "GTK3: Minimizar Janela" ;
int    xlen     = 400 ;
int    ylen     = 200 ;


gboolean 
func_minimize (GtkWidget           *w     ,
	       GdkEventWindowState *event ,
	       gpointer             data  )
{
  g_print ("func_minimize - WindowState: %d\n", event->new_window_state);
  if (event->new_window_state & GDK_WINDOW_STATE_ICONIFIED)
    {
      if (event->new_window_state & GDK_EXPOSE)
	g_print ("  Event: GDK_EXPOSE\n");
    }

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW (window), winTitle);
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT(window), "window-state-event", G_CALLBACK(func_minimize), NULL);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
