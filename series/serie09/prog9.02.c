#include <stdio.h>
#include <gtk/gtk.h>

double xis;
char valor[30];

gboolean cb_somar(GtkWidget *widget, GtkWidget *label1){
  ++xis;
  sprintf(valor, "%lf", xis);

  //define novo texto da label1
  gtk_label_set_text(GTK_LABEL(label1), valor);

  return FALSE;
}

gboolean cb_subtrair(GtkWidget *widget, gpointer label1){
  --xis;
  sprintf(valor, "%lf", xis);
  gtk_label_set_text(label1, valor);

  return FALSE;
}

gboolean cb_multiplicar(GtkWidget *widget, gpointer label1){
  xis*=2;
  sprintf(valor, "%lf", xis);
  gtk_label_set_text(label1, valor);

  return FALSE;
}

gboolean cb_dividir(GtkWidget *widget, gpointer label1){
  xis/=3;
  sprintf(valor, "%lf", xis);
  gtk_label_set_text(label1, valor);

  return FALSE;
}


int main(int argc, char **argv){
  
  GtkWidget *window, *vbox, *label1, *hbox, *bsomar, *bsubtrair, *bmultiplicar, *bdividir;

  sscanf(argv[1], "%lf", &xis);

  gtk_init(&argc, &argv);

  //criar janela, dar dimensoes, colocar no centro

  window= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 500, 200);
  gtk_window_set_title  (GTK_WINDOW(window), "Calculadora da treta");
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  //associar botao destroy ao fecho do programa

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

  //criar box vertical e inserir na janela

  vbox= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);
 
  //criar label com nº e inserir no inicio da box vertical

  label1= gtk_label_new (argv[1]);
  gtk_box_pack_start (GTK_BOX(vbox), label1, TRUE, FALSE, 0);

  //criar box horizontal e inserir no fim da box vertical

  hbox= gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  gtk_box_pack_end (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

  //criar 4 botoes e inserir na box horizontal

  //cria botao
  bsomar= gtk_button_new_with_label("+");
  //define tamanho
  gtk_widget_set_size_request (bsomar, 80, 40);
  //associa clique do botao à funçao de soma
  g_signal_connect (G_OBJECT(bsomar), "clicked", G_CALLBACK(cb_somar), label1);
  //inserir botao no inicio da box horizontal
  gtk_box_pack_start (GTK_BOX(hbox), bsomar, TRUE, FALSE, 0);

  bsubtrair= gtk_button_new_with_label("-");
  gtk_widget_set_size_request (bsubtrair, 80, 40);
  g_signal_connect (G_OBJECT(bsubtrair), "clicked", G_CALLBACK(cb_subtrair), label1);
  gtk_box_pack_start (GTK_BOX(hbox), bsubtrair, TRUE, FALSE, 0);

  bmultiplicar= gtk_button_new_with_label("x");
  gtk_widget_set_size_request (bmultiplicar, 80, 40);
  g_signal_connect (G_OBJECT(bmultiplicar), "clicked", G_CALLBACK(cb_multiplicar), label1);
  gtk_box_pack_start (GTK_BOX(hbox), bmultiplicar, TRUE, FALSE, 0);

  bdividir= gtk_button_new_with_label("/");
  gtk_widget_set_size_request (bdividir, 80, 40);
  g_signal_connect (G_OBJECT(bdividir), "clicked", G_CALLBACK(cb_dividir), label1);
  gtk_box_pack_start (GTK_BOX(hbox), bdividir, TRUE, FALSE, 0);

  //mostrar widgets e entrar no ciclo de espera para execuçao de tarefas

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
