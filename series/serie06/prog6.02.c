#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void showhelp(){
  printf("\nGerador de números complexos aleatórios.");
  printf("\n(com valores em [-6, 15])");
  printf("\n\n ./<programa> <nº de complexos a gerar>\n\n");
  
  exit(-1);
}

typedef struct
{
  double r;
  double i;
  double norma;
} complexo;

//Funções Gerador, Ordenador, Print e Troca

void gerador(int n, complexo **c){
  int q;

  for(q=0; q<n; ++q){
    c[q]->r= ((double)rand() / (double)RAND_MAX) *21 -6;
    c[q]->i= ((double)rand() / (double)RAND_MAX) *21 -6;
    c[q]->norma= sqrt((c[q]->r*c[q]->r)+(c[q]->i*c[q]->i));
  }
}

void ordenador(int n, complexo **c){
  int q, w=1;
  complexo *c0;
  
  while(w==1){
    w=0;

    for(q=0; q<n-1; ++q){
      if(c[q]->norma < c[q+1]->norma){
       c0=c[q];
       c[q]=c[q+1];
       c[q+1]=c0;

       w=1;
     }
   }
 }
}

void print(int n, complexo **c){
  int q;

  printf("\n===============\nComplexos ordenados:\n\n");
  
  for(q=0; q<n; ++q)
    printf("%dº: %8.5lf + %8.5lf i \tNorma: %8.5lf\n", q+1, c[q]->r, c[q]->i, c[q]->norma);
}

void troca(int a, int b, complexo **c){
  complexo *c0;

  c0=c[a-1];
  c[a-1]=c[b-1];
  c[b-1]=c0;
}


//MAIN

int main(int argc, char **argv){
  int n, t, q, w, a, b;
  complexo **c;  

  switch(argc){
    case 2:
    
    t= sscanf(argv[1], "%d", &n);
    if(t!=1 || !(n>0)){
      printf("Erro na leitura dos dados.\n");
      showhelp();
    }
    
    c=(complexo**)malloc(n*sizeof(complexo));
    for(q=0; q<n; ++q)
      c[q]=(complexo*)malloc(n*sizeof(complexo));
    
    srand(time(NULL));

    //Gerar, ordenar e escrever os complexos
    
    gerador(n, c);
    ordenador(n, c);
    print(n, c);
    
    //Ciclo para troca/escrita
    
    while(1){
      printf("\nDeseja trocar a ordem de dois complexos?\nSim (1) Não(outro valor): ");

      t= scanf("%d", &w);
      if(t!=1 || w!=1)
       break;

     printf("\nQuais? (digite o número de cada): ");

     t= scanf("%d %d", &a, &b);
     if(t!=2 || !(a<=n && a>0) || !(b<=n && b>0)){
       printf("\nErro na leitura dos valores.\n\n");
       break;
     }

     if(a==b)
       printf("\nIsso não vai trocar nada...\n");
     if(a!=b)
       troca(a, b, c);
     print(n, c);
   }

   break;

   default:
   showhelp();
 }

 for(q=0; q<n; ++q)
  free(c[q]);
free(c);

return 0;
}
