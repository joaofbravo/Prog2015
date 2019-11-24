/*****************************************************
 *                                                   *
 *      ComboBox                                     *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2014                        *
 *                                                   *
 *****************************************************/

#include <stdio.h>
#include <gtk/gtk.h>

#define CBOX_QT    12  // Número de entradas
#define CBOX_INIT   5  // Entrada a activar no início

//char cb_text[CBOX_QT][16] = {"0","1","2","3","4","5","6","7","8","9","10","11"};
char cb_text[CBOX_QT][16] = {
  "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
  "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

GtkWidget *label2,  *label3, *cbBox ;


gboolean 
cb_cbox_function (GtkWidget *w    ,
                  gpointer   data )
{
  gchar       str1[32]  ;
  static gint conta = 1 ;
  gint        opt1      ;

  opt1 = gtk_combo_box_get_active (GTK_COMBO_BOX (w));

  sprintf (str1, "Opção escolhida: %d - %s", opt1, cb_text[opt1]);
  gtk_label_set_text (GTK_LABEL(label2), str1);
  sprintf (str1, "Número de alterações: %d", conta++);
  gtk_label_set_text (GTK_LABEL(label3), str1);

  return FALSE;
}

GtkWidget *
create_ComboBox_with_Model (void)
{
  gint              i1          ;
  GtkWidget        *cbBox       ;
  GtkListStore     *cbBoxList   ;
  GtkCellRenderer  *cbBoxColumn ;

  cbBoxList = gtk_list_store_new (1, G_TYPE_STRING);
  for (i1 = 0 ; i1 < CBOX_QT ; ++i1)
    {
      gtk_list_store_insert_with_values (cbBoxList, NULL, -1, 0, cb_text[i1], -1);
      
      // Equivalente à linha anterior
      // GtkTreeIter       iter;
      // gtk_list_store_insert (cbBoxList, &iter, -1);
      // gtk_list_store_set (cbBoxList, &iter, 0, cb_text[i1], -1);
    }

  cbBox = gtk_combo_box_new_with_model (GTK_TREE_MODEL(cbBoxList));
  g_object_unref (cbBoxList);
  gtk_widget_set_size_request (cbBox, 52, 29);

  cbBoxColumn = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(cbBox), cbBoxColumn, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT(cbBox), cbBoxColumn, "text", 0, NULL);

  gtk_combo_box_set_active (GTK_COMBO_BOX (cbBox), CBOX_INIT);

  return cbBox;
}

int
main (int argc, char **argv)
{
  GtkWidget *win, *vbox, *hbox1, *hbox2, *hbox3, *label ;

  gtk_init (&argc, &argv);

  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (win), "GTK3-Ex: 'ComboBox'");
  gtk_window_set_default_size (GTK_WINDOW(win), 400, 300);
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  g_signal_connect (win, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  // vbox

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 20);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  // label 

  label = gtk_label_new ("Exemplo - Combo Box");
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, TRUE, 0);

  hbox3 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox3), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (hbox3), 10);
  gtk_box_pack_start (GTK_BOX (vbox), hbox3, FALSE, TRUE, 0);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX (hbox3), hbox2, FALSE, TRUE, 0);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX (hbox3), hbox2, FALSE, TRUE, 0);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER (hbox3), hbox2);

  // Combo Box Text

  cbBox = create_ComboBox_with_Model ();
  gtk_box_pack_start (GTK_BOX (hbox2), cbBox, FALSE, TRUE, 0);
  g_signal_connect (G_OBJECT (cbBox), "changed", G_CALLBACK (cb_cbox_function), NULL);
  
  // label2, label3

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_container_set_border_width (GTK_CONTAINER (hbox1), 10);
  gtk_container_add (GTK_CONTAINER (vbox), hbox1);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX (vbox), hbox2, FALSE, TRUE, 0);
  label3 = gtk_label_new ("Número de alteracoes: 0");
  gtk_box_pack_start (GTK_BOX (hbox2), label3, FALSE, TRUE, 0);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX (vbox), hbox2, FALSE, TRUE, 0);
  label2 = gtk_label_new ("Opção escolhida: ");
  gtk_box_pack_start (GTK_BOX (hbox2), label2, FALSE, TRUE, 0);

  gtk_widget_show_all (win);
  gtk_main ();

  return 0;
}
