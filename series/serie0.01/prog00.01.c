#include<stdio.h>

int main(){
  int t, q;
  char a, b;
  double x, y;

  while(1){
    while(1){
      printf("Quer C ou F? ");
  
      t=scanf("%s", &a);
      if(t!=1 || !(a=='C' || a=='F'))
	printf("Escreva C ou F.\n");

      while(getchar()!=10);

      if(t==1 && (a=='C' || a=='F')) break;
    }

    if(a=='C'){

      while(1){
	printf("Quantos graus? ");
    
	t=scanf("%lf", &x);
    
	if(t!=1 || x<-273.15)
	  printf("Digite um valor maior ou igual a -273.15.\n");
     
	while(getchar()!=10);
    
	if(t==1 && x>=-273.15)
	  break;
      }

      y= x *1.8 + 32;
      b='F';
    }
    
    if(a=='F'){
      while(1){
	printf("Quantos graus? ");
    
	t=scanf("%lf", &x);
    
	if(t!=1 || x<0)
	  printf("Digite um valor maior ou igual a 0.\n");
        
	while(getchar()!=10);
    
	if(t==1 && x>=0)
	  break;
      }
  
      y= (x - 32) / 1.8;
      b='C';
    }
    
    printf("%lf %c = %lf %c \n\n", x, a, y, b);

    printf("Deseja converter novos valores? Sim(1) Não(outro valor) ");

    t=scanf("%d", &q);
    if(t!=1 || q!=1) break;

    while(getchar()!=10);
  }

  return 0;
}
