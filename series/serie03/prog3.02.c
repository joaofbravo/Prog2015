#include<stdio.h>

//MDC
int mdc(int a, int b){
  int x, y, z;
  x=a;
  y=b;
  z=1; //Para o ciclo iniciar sempre.
  
  while(z!=0){
    z=x%y;
    x=y;
    y=z;
  }
  
  return x;
}

//MMC
int mmc(int a, int b){
  return (a*b)/mdc(a,b); 
}

int main(){
  int a, b, t, m1, m2, q;
  q=1;
  
  printf("Cálculo de MDC e MMC.\n");
  
  while(q==1){
    printf("\nQuais os números que quer usar? ");
    t= scanf("%d %d", &a, &b);
    
    if(t!=2){
      printf("Erro.\n\n");
      return -1;
    }
    
    m1= mdc(a, b);
    m2= mmc(a, b);
    
    printf("Máximo divisor comum: %d \nMenor múltiplo comum: %d\n\n", m1, m2);
    
    printf("Deseja inserir novos valores? Sim (1), Não (outro valor) ");
    scanf("%d", &q);
  }
  
  printf("\n\n");
  return 0;
}
