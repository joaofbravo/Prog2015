/*****************************************************
 *                                                   *
 *      Opções de abertura de uma janela             *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2014                        *
 *                                                   *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER ;

gchar              *winTitleDef1 = "Opcoes de criacao de janelas - Use '-h' para ajuda." ;
gchar              *winTitleDef2 = "Opcoes de criacao de janelas" ;
gchar              *winTitle ;

long int            xlen        = 600 ;
long int            ylen        = 400 ;

void 
help (int status)
{
  printf ("\n\n  gtk01_02 <args>\n");
  printf ("    -t=<type>   : 'top'    (GTK_WINDOW_TOPLEVEL) ; 'pop' (GTK_WINDOW_POPUP)\n");
  printf ("    -p=<pos>    : 'none'   (GTK_WIN_POS_NONE)    ; 'center' (GTK_WIN_POS_CENTER)\n");
  printf ("                  'mouse'  (GTK_WIN_POS_MOUSE)\n");
  printf ("                  'parent' (GTK_WIN_POS_CENTER_ON_PARENT) - nao se aplica...\n");
  printf ("    -x=<num>    : Comprimento da janela\n");
  printf ("    -y=<num>    : Largura da janela\n");
  printf ("    -c=<titulo> : Titulo da janela.\n");
  printf ("\n\n");
  exit (status);
}

void
get_args (int argc, char **argv)
{
  int  n1, test ;

  winTitle = (argc == 1 ? winTitleDef1 : winTitleDef2);

  n1 = 1;
  while (n1 < argc)
    {
      test = 0;
      if ((strcmp (argv[n1], "-h") == 0) || (strcmp (argv[n1], "-?") == 0))
	help (0);
      if (strncmp (argv[n1], "-t=", 3) == 0)
        {
          test = 1;
          if (strcmp (&argv[n1][3], "top") == 0)
            winType = GTK_WINDOW_TOPLEVEL;
          else if (strcmp (&argv[n1][3], "pop") == 0)
	    winType = GTK_WINDOW_POPUP;
	  else
	    test = 0;
	}
      if (strncmp (argv[n1], "-p=", 3) == 0)
        {
          test = 1;
          if (strcmp (&argv[n1][3], "none") == 0)
            winPos = GTK_WIN_POS_NONE;
          else if (strcmp (&argv[n1][3], "center") == 0)
            winPos = GTK_WIN_POS_CENTER;
          else if (strcmp (&argv[n1][3], "mouse") == 0)
            winPos = GTK_WIN_POS_MOUSE;
          else if (strcmp (&argv[n1][3], "parent") == 0)
	    {
              printf ("Nao se aplica porque esta e a primeira janela\n");
              exit (1);
	    }
	  else
	    test = 0;
	}
      if (strncmp (argv[n1], "-x=", 3) == 0)
        {
          test = 1;
          if (sscanf (&argv[n1][3], "%ld", &xlen) != 1)
	    {
              printf ("\n\n  Comprimento incorrecto: '%s'\n", argv[n1]);
	      help (-1);
	    }
	}
      if (strncmp (argv[n1], "-y=", 3) == 0)
        {
          test = 1;
          if (sscanf (&argv[n1][3], "%ld", &ylen) != 1)
	    {
              printf ("\n\n  Largura incorrecta: '%s'\n", argv[n1]);
	      help (-1);
	    }
	}
      if (strncmp (argv[n1], "-c=", 3) == 0)
        {
          test = 1;
          winTitle = &argv[n1][3];
	}
      if (test == 0)
	{
          printf ("\n\n  Argumento desconhecido: '%s'\n", argv[n1]);
	  help (-1);
	}
      ++n1;
    }  
}


int
main (int argc, char **argv)
{
  GtkWidget *window ;

  get_args (argc, argv);

  gtk_init (&argc, &argv);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW (window), winTitle);
  gtk_window_set_position (GTK_WINDOW (window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show (window);
  gtk_main ();

  return 0;
}
