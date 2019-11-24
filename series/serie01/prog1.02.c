#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
  int n, teste, t, i, i1, i2;
  double max, v0;

  printf("Quantos numeros reais aleatorios quer gerar e ate que valor? ");
  teste = scanf("%d %lf", &n, &max);
  printf("Leu: N=%d MAX=%lf  (com teste: %d)\n\n", n, max, teste);

  if(teste != 2){
   printf("ERRO!");
   return -1;
 }
  
 double v[n];
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
 
 FILE *fich;
 fich = fopen("prog1.02", "wt");

 for(i2=0; i2<n; ++i2){
 printf("%lf ", v[i2]);
 fprintf(fich, "%lf ", v[i2]);
 }

 printf("\n\n"); 
 fclose(fich);
 return 0;
}
