/*  ShowGtkBox.c  */

/* Notas para ver (III. Theming in GTK+)

     * style
     * CSS
     * etc

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "ShowGtkBox.h"
#include "gb_window.h"
#include "gb_error.h"

#define GB_MOSTRA_TESTES  0

#if GB_MOSTRA_TESTES == 1
static void
gb_show_data (ShowGtkBoxStruct *gb)
{
  printf ("gb->w->geom[0]: %ld\n", gb->w->geom[0]);
  printf ("gb->w->geom[1]: %ld\n", gb->w->geom[1]);
  printf ("gb->w->geom[2]: %ld\n", gb->w->geom[2]);
  printf ("gb->w->geom[3]: %ld\n", gb->w->geom[3]);
}
#endif

static void
gb_help (int status)
{
  printf ("\n");
  printf ("  ShowGtkBox [Options]\n");
  printf ("    Options:\n");
  printf ("      -geometry WIDTHxHEIGHT+XOFF+YOFF : Ver \"man X\". Example: -geometry 800x600+80+80\n");
  printf ("\n");

  exit(status);
}

static ShowGtkBoxStruct *
gb_get_args (int argc, char **argv)
{
  int               n1, i1, geom[5], test ;
  //char             *ptr      ;
  ShowGtkBoxStruct *gb       ;

  if ((argc > 1) && ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)))
    gb_help(0);

  gb = (ShowGtkBoxStruct *) calloc (1, sizeof(ShowGtkBoxStruct));
  gb->w = (ShowGtkBoxWindow *) calloc (1, sizeof(ShowGtkBoxWindow));
  gb->w->qt_sty = (gint) Sty_End;

  gb->w->vpb = (ShowGtkBoxVBoxes **) malloc (sizeof (ShowGtkBoxVBoxes *));
  gb->w->vpb[0] = (ShowGtkBoxVBoxes *) calloc (1, sizeof (ShowGtkBoxVBoxes));
  gb->w->vpb[0]->vh = BoxO_0;
  gb->w->qt_vpb = 1;

  gb->sty = gb_styles_new ();

  gb->w->geom[0] = WIN_GEOM_DEF_WIDTH;
  gb->w->geom[1] = WIN_GEOM_DEF_HEIGHT;
  gb->w->geom[2] = WIN_GEOM_DEF_POSX;
  gb->w->geom[3] = WIN_GEOM_DEF_POSY;

  n1 = 1;
  while(n1 < argc)
    {
      test = 0;
      if ((strcmp (argv[n1], "-geometry") == 0) && ((n1+1) < argc))
	{
          geom[0] = sscanf (argv[++n1], "%dx%d+%d+%d", &geom[1], &geom[2], &geom[3], &geom[4]);
          for (i1 = 1 ; i1 <= geom[0] ; ++i1)
	    {
              gb->w->geom[i1-1] = geom[i1];
	    }
	  if (geom[0] > 0)
            test = 1;
	}
      if (strcmp (argv[n1], "-v") == 0)
	{
          gb->w->flag_mostra = 1;
	  test = 1;
	}
      if (test == 0)
	InfoError_show (1, 1, 1, 1, argv[n1], NULL);
      ++n1;
    }

#if GB_MOSTRA_TESTES > 0
  gb_show_data (gb);
#endif

  InfoError_start(NULL);

  return gb;
}

int 
main (int argc, char **argv)
{
  ShowGtkBoxStruct *gb ;

  gb = gb_get_args (argc, argv);
  gtk_init (&argc, &argv);

  gb->w->win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position (GTK_WINDOW (gb->w->win), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (gb->w->win), gb->w->geom[0], gb->w->geom[1]);

  g_signal_connect (gb->w->win, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  //g_signal_connect (gb->w->win, "delete_event", G_CALLBACK (gb_exit), gb);

  db_main_window_new (gb);

  gtk_widget_show_all (gb->w->win);
  gtk_main ();

  return 0;
}
