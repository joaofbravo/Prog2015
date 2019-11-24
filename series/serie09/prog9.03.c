#include <stdio.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>

gboolean desenhar(GtkWidget *widget, cairo_t *cr, gpointer a){
  static double x=100, y=100, tam=100, m=3, n=3;

  GtkAllocation tamanho;

  //obter tamanho da janela  
  gtk_widget_get_allocation(widget, &tamanho);

  cairo_arc(cr, x, y, tam, 0, 2*M_PI);
  cairo_set_source_rgb(cr, 0.2, 0.8, 0.5);
  cairo_fill(cr);
  cairo_stroke(cr);

  x=x+m;
  y=y+n;

  if((x+tam)>tamanho.width){
    m=-m;
    x=tamanho.width - tam;
  }
  
  if((y+tam)>tamanho.height){
    n=-n;
    y=tamanho.height - tam;
  }

  if((x-tam)<0){
    m=-m;
    x=tam;
  }

  if((y-tam)<0){
    n=-n;
    y=tam;
  }

  tam+=0.05;

  return FALSE;
}

gboolean mover(GtkWidget *widget){

  //Teste se drawing area já foi criada e se ainda nao foi apagada
  if ((!GTK_IS_WIDGET(widget)) || (!gtk_widget_get_window (widget)))
    return FALSE;
  
  //redesenhar circulo
  gtk_widget_queue_draw(widget);

  //Funçao timeout tem que ter return TRUE para continuar a ser executada
  return TRUE;
}


int main(int argc, char **argv){

  GtkWidget *window, *darea;

  gtk_init(&argc, &argv);

  //criar janela, dar dimensoes, colocar no centro

  window= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 700, 500);
  gtk_window_set_title (GTK_WINDOW(window), "Círculo em movimento");
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  //associar botao destroy ao fecho do programa

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

  //criar drawing area

  darea= gtk_drawing_area_new();
  gtk_container_add (GTK_CONTAINER(window), darea);

  //desenhar circulo na drawing area

  g_signal_connect (G_OBJECT(darea), "draw", G_CALLBACK(desenhar), NULL);

  //mover circulo em intervalos de 10 ms por ciclo temporal de redesenho

  g_timeout_add (10, (GSourceFunc) mover, darea);

  //mostrar widgets e entrar no ciclo de espera para execuçao de tarefas

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
