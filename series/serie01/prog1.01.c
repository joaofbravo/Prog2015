#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main(){

double x, y, razao, r;
int n, i, teste, cont;
srand(time(NULL));

 printf("Quantos pontos quer gerar? ");
 teste=scanf("%d", &n);
 printf("\nLeu: %d (com teste: %d)\n\n", n, teste);

 if(teste != 1){
   printf("ERRO!");
   return -1;
}

cont=0;

 for(i=0; i<n; ++i){
 x=((double)rand())/((double)RAND_MAX)-0.5;
 y=((double)rand())/((double)RAND_MAX)-0.5;
 if(sqrt((x*x)+(y*y))<=0.5)
   cont= cont+1;
 }
 
 razao= (double)cont/(double)n;
 r=razao*4;
 printf("Caem %d pontos no circulo e a razao é %lf. \nRazao*4= %lf\n\n", cont, razao, r);

 //O valor da razao*4 vai ser aproximadamente pi.
 
 return 0;
}
