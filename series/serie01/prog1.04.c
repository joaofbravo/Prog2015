#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
  int teste, t, a, b, n, j;
  n= 1000;
  j=1;
  srand(time(NULL));

  while(j==1){
    b=rand() % (n+1);

    printf("\nAdivinhe o numero gerado de 0 a 1000:\nPara desistir, escreva uma letra.\n");
    teste= scanf("%d", &a);

    if(teste != 1){
      printf("Desistiu!\n\n");
      return -1;
    }
    
    t=0;

             //Ciclo para valores errados.
    
    while(a !=b){
             //Valor gerado: printf("%d\n", b);
      
      if (a < b && a >= 0)
	printf("Mais acima! Tente outra vez.\n");

      if (a > b && a <= n)
	printf("Mais abaixo! Mais uma vez.\n");

      if (a < 0)
	printf("Só números positivos!\n");

      if (a > n)
	printf("Excedeu o valor maximo.\n");
      
      t=t+1;

      if(t%5 == 0)
	printf("Esforça-te mais!!\n");

      teste= scanf("%d", &a);

      if(teste != 1){
	printf("Desistiu!\n\n");
	return -1;
      }
    }

             //Para o valor certo.
    
    if (a == b)
      printf("Parabens! Acertou.\nErrou %d vezes.\n\n  Deseja voltar a jogar?\nSim (1) Nao (outro valor)  ", t);

    teste= scanf("%d", &j);

    if(teste != 1){
      printf("ERRO!\n\n");
      return -1;
    }
  }
  
  return 0;
}
