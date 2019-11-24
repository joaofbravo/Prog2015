#include<stdio.h>
#include<math.h>

void showhelp(){
  printf("\nConfiguração de uma rede linear de 16 spins (1/2).");
  printf("\nPode inverter os spins que quiser.\n");
}

void gerador(unsigned short int x){
  int i;

  for(i=0; i<16; ++i)
    x= x | (unsigned short int)((rand() % 2) *pow(2, i));
}

void print(unsigned short int x){
  int i;
  printf("\n");

  for(i=15; i>=0; --i){
    if((x & (unsigned short int)pow(2, i))!=0)
      printf("1");
    else
      printf("0");  
  }
  printf("\n");
}


int main(){
  int t, q, a, i;
  unsigned short int x=0;
  
  showhelp();
  gerador(x);
  print(x);
  
  //Ciclo para troca/escrita
    
  while(1){
    printf("\nDeseja trocar um spin?\nSim (1) Não(outro valor): ");

    t= scanf("%d", &q);
    if(t!=1 || q!=1){
      printf("\n");
      return 0;
    }
    while(getchar()!=10);

    printf("\nQual? (digite a posição do spin): ");

    t= scanf("%d", &a);
    if(t!=1 || !(a<=16 && a>0)){
      printf("\nErro na leitura dos valores.\n\n");
      return -1;
    }
    while(getchar()!=10);
    
    x= x ^ (unsigned short int)pow(2, 16-a);

    print(x);
  }
}
