#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void showhelp(){
  printf("\nGerador de N números reais aleatórios num intervalo [Min, Max].");
  printf("\n\nTenha em atenção que:\nN é um inteiro positivo.\nMax é maior ou igual a Min.");
  printf("\n\n    <Programa> <N> <Mínimo> <Máximo>\n\n");

  exit (-1);
}


void gerador(double *v, int n, double min, double max){
  int i;
  double x;

  x= max - min;

  for(i=0; i<n; ++i)
    v[i]= ((double)rand() / (double)RAND_MAX) * x + min;
}


void ordenador(double *v, int n){
  int i, t, x;
  double v0;

  x= n - 1;

  while(1){
    t=0;
    for(i=0; i<x; ++i){
      if(v[i]>v[i+1]){
	v0=v[i];
	v[i]=v[i+1];
	v[i+1]=v0; 
	
	t=1;
      }
    }
    if(t==0) break;
  }
}


int main(int argc, char **argv){

  int n, t, i, cont, q;
  double min, max, *v;

  if(argc!=4){
    printf("Cuidado com o número de argumentos.\n");
    showhelp();
  }

  t= sscanf(argv[1], "%d", &n);
  t= t + sscanf(argv[2], "%lf", &min);
  t= t + sscanf(argv[3], "%lf", &max);
  
  if(t!=3 || !(n>0) || min>max){
    printf("Os seus valores não são plausíveis.\n");    
    showhelp();
  }
  
  FILE *f1;
  f1=fopen("testeBravo.bin", "wb");
  
  if(f1==NULL){
    printf("Falha ao abrir ficheiro.\n");
    showhelp();
  }

  v= (double*)malloc(n*sizeof(double));
  
  cont=1;

  srand(time(NULL));


  //El ciclo begins
  while(1){
    if(cont==2){
      printf("\nQuais os novos valores? <números a gerar> <mínimo> <máximo>\n");
      
      t=scanf("%d %lf %lf", &n, &min, &max);
      
      if(t!=3 || !(n>0) || min>max){
	printf("\nTenha em atenção os seus valores.\n");    
	showhelp();
      }
      while(getchar()!=10);  
      
      v=(double*)realloc(v, n*sizeof(double));
    }
    
    fwrite(&n, sizeof(int), 1, f1);
    fwrite(&min, sizeof(double), 1, f1);
    fwrite(&max, sizeof(double), 1, f1);
  
      
    gerador(v, n, min, max);
    ordenador(v, n);


    printf("\n");
    for(i=0; i<n; ++i){
      printf("%10.5lf   ", v[i]);
      
      if(((i+1)%5) == 0)
	printf("\n");

    fwrite(&v[i], sizeof(double), 1, f1);
    }

  
    printf("\n\nDeseja gerar novos números? Sim(1) Não(outro valor)\n");  
    
    t=scanf("%d", &q);

    if(t!=1 || q!=1)
      break;

    if(cont==1) cont=2;
  }

  printf("\n\n");
  free(v);
  fclose(f1);
  return 0;
}
