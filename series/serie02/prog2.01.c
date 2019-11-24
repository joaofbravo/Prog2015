#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv){

  int n, teste1, teste2, t, i, i1, i2, z, cont;
  double max, v0;
  double *v;
  FILE *fich;
  
  z=1;
  cont=1;  

  while(z==1){

    if(argc!=3 || cont>1){
      if(argc!=1 && cont==1)
	printf("Número errado de argumentos.\n");

      printf("Quantos numeros reais aleatorios quer gerar e ate que valor? ");
      teste1 = scanf("%d %lf", &n, &max);
      printf("Leu: N=%d MAX=%lf  (com teste: %d)\n\n", n, max, teste1);
     
      if(teste1 != 2){
	printf("ERRO!\n\n");
	return -1;
      }
    }
    else{
      sscanf(argv[1], "%d", &n);
      sscanf(argv[2], "%lf", &max);
    }
 
    if(cont==1)
      v=(double*)malloc(n*sizeof(double));
    else   
      v=(double*)realloc(v,n*sizeof(double));
   
    srand(time(NULL));
    
    for(i=0; i<n; ++i)
      v[i]=((double)rand())/((double)RAND_MAX) * max;

    while(1){
      t=0;
      for(i1=0; i1<n-1; ++i1){
	if(v[i1]<v[i1+1]){
	  v0=v[i1];
	  v[i1]=v[i1+1];
	  v[i1+1]=v0;
	  t=1;
	}
      }
      if(t == 0) break;
    }
 
    fich = fopen("prog1.02", "wt");

    for(i2=0; i2<n; ++i2){
      printf("%lf ", v[i2]);
      fprintf(fich, "%lf ", v[i2]);
    }

    printf("\n\nDeseja introduzir novos valores? \n Sim (1) Nao (outro valor):  ");
    teste2=scanf("%d", &z); 
 
    if(teste2 !=1){
      printf("Erro.\n\n");
      return -1;
    }

    printf("\n"); 
    
    if(z!=1)
      break;
    
    cont=cont+1;
  }

  fclose(fich);
  free(v); 
  return 0;
}
