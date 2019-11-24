/*  gb_error.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#include "ShowGtkBox.h"
#include "gb_styles.h"
#include "gb_auxil.h"
#include "gb_error.h"

#define InfoError_GRP_NUM  2

//static gint           qt_sty ;
//static StylesStruct **sty    ;


char *
InfoError_Data0[] = {
/* 000 */ "",
/* 001 */ "Tem a certeza que quer sair?",
/* 002 */ "***** Criação de 'boxes' em GTK+ *****",
/* 003 */ "Programação",
/* 004 */ "Mestrado em Engenharia Física Tecnológica",
/* 005 */ "Instituto Superior Técnico",
/* 006 */ "Versão 3.1 - Dezembro de 2012 (2002)",
/* 007 */ "Samuel Eleutério - sme@ist.utl.pt",
/* 008 */ "Programa para testar 'Boxes' em GTK+",
/* 009 */ " Window ",
/* 010 */ " Opções ",
/* 011 */ " Tipo de Box ",
/* 012 */ "Vertical",
/* 013 */ "Horizontal",
/* 014 */ "homog",
/* 015 */ "FALSE",
/* 016 */ "TRUE",
/* 017 */ "space",
/* 018 */ " Função ",
/* 019 */ " Parent ",
/* 020 */ "Expand:",
/* 021 */ "Fill:",
/* 022 */ "Padding:",
/* 023 */ "Aplicar",
/* 024 */ "Desfazer",
/* 025 */ "Sair",
/* 026 */ "Região em que se mostra o último comando executado",
/* 027 */ "para a criação de uma 'box'.",
/* 028 */ "",
/* 029 */ "Apagar",
/* 030 */ "Ok",
/* 031 */ 
/* 032 */ 
/* 033 */ 
/* 034 */ 
/* 035 */ 
/* 036 */ 
          NULL};
char *
InfoError_Data1[] = {
/* 000 */ "",
/* 001 */ "Argumento inválido: \"%s\"",
/* 002 */ "",
          NULL};

char **
InfoErrorData[InfoError_GRP_NUM] = {InfoError_Data0, InfoError_Data1};

/*

  *** gb_show_error ****
      exit_value : Se for menor ou igual a zero, termina o programa com "exit(exit_value)";
            mode : Como se apresenta o erro:
                     0 - Não dá erro (Informacao);
                     1 - Erro na linha de comandos;
                     2 - Erro em janela, termina em "OK";
                     3 - Erro em janela, com "Sim" ou "Não"
             grp : Número do grupo de erros
             num : Número do erro dentro do grupo
            info : Informação a acrescentar na impressão do erro
 */

void
InfoError_start (gchar *fname)
{
}

gchar *
InfoError_GetText (gint  grp ,
                   gint  num )
{
  return InfoErrorData[grp][num];
}

void
InfoError_show (gint        exit_value ,
                gint        mode       ,
                gint        grp        ,
                gint        num        ,
                gchar      *info       ,
                GtkWidget  *win        )
{
  char      *buff                          ;
  GtkWidget *dialog, *label, *content_area ;

  if (info)
    {
      buff = (char *) malloc (strlen(InfoErrorData[grp][num]) + strlen(info) + 10);
      sprintf(buff, InfoErrorData[grp-1][num], info);
    }
  else
    buff = strdup (InfoErrorData[grp-1][num]);
  

  if (mode == 0)
    printf ("INFO-%d-%d-%s\n", grp, num, buff);
  else if (mode == 1)
    printf ("ERR-%d-%d-%s\n", grp, num, buff);
  else if ((mode == 2) || (mode == 3))
    {
      dialog = gtk_dialog_new_with_buttons ("Message", GTK_WINDOW(win), 
					    GTK_DIALOG_DESTROY_WITH_PARENT,
					    "_OK", GTK_RESPONSE_ACCEPT,
					    NULL);
      content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
      label = gtk_label_new (buff);
      g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);
      gtk_container_add (GTK_CONTAINER (content_area), label);
      gtk_widget_show_all (dialog);
    }

  if (exit_value < 1)
    exit (-exit_value);
}

gboolean
gb_exit (GtkWidget         *win ,
         ShowGtkBoxStruct  *gb  )
{
  gint       value ;
  GtkWidget *dialog, *carea, *hbox ;

  dialog = gtk_dialog_new_with_buttons ("Message", GTK_WINDOW(gb->w->win), 
					GTK_DIALOG_DESTROY_WITH_PARENT,
					"_Sim", GTK_RESPONSE_ACCEPT,
					"_Não", GTK_RESPONSE_REJECT,
					NULL);


  //gtk_window_set_default_size (GTK_WINDOW (dialog), 800, 200);
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
  gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_NO);

  carea = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  //hbox = gtk_hbox_new (TRUE,20);
  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  gtk_box_set_homogeneous (GTK_BOX (hbox), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 20);
  gtk_box_pack_start (GTK_BOX (carea), hbox, FALSE, TRUE, 20);

  gb_label_new(gb, Sty_Msg1, InfoErrorData[0][1], hbox, TRUE);

  gtk_widget_show_all (dialog);

  value = gtk_dialog_run (GTK_DIALOG (dialog));

  gtk_widget_destroy (dialog);
  if (value == GTK_RESPONSE_ACCEPT)
    gtk_main_quit ();

  return TRUE;
}

gboolean
gb_about (GtkWidget         *w  ,
          ShowGtkBoxStruct  *gb )
{
  GtkWidget *dialog, *carea, *vbox, *sep ;

  dialog = gtk_dialog_new_with_buttons ("Message", GTK_WINDOW(gb->w->win), 
					GTK_DIALOG_DESTROY_WITH_PARENT,
					"_OK", GTK_RESPONSE_ACCEPT,
					NULL);


  gtk_window_set_default_size (GTK_WINDOW (dialog), 400, 300);
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
  gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_NO);

  carea = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
  gtk_box_set_homogeneous (GTK_BOX (vbox), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
  gtk_box_pack_start (GTK_BOX (carea), vbox, FALSE, TRUE, 0);

  gb_label_new (gb, Sty_About1, InfoErrorData[0][2], vbox, TRUE);
  gb_label_new (gb, Sty_About1, InfoErrorData[0][3], vbox, TRUE);
  gb_label_new (gb, Sty_About2, InfoErrorData[0][4], vbox, TRUE);
  gb_label_new (gb, Sty_About2, InfoErrorData[0][5], vbox, TRUE);
  gb_label_new (gb, Sty_About2, InfoErrorData[0][6], vbox, TRUE);
  gb_label_new (gb, Sty_About2, InfoErrorData[0][7], vbox, TRUE);

  sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_end (GTK_BOX (carea), sep, FALSE, TRUE, 10);

  gtk_widget_show_all (dialog);

  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);

  return TRUE;
}
