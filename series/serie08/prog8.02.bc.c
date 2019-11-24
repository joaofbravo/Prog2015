#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

void showhelp(){
printf("\nConfiguração de uma rede linear de spins (1/2).");
printf("\nEste programa recebe uma possível configuração da rede\ne retorna a linha em que ela se encontra em ""spins.txt"".");
printf("\n\n ./<programa> <configuração com 16 posições>\n\n");
  
 exit(-1);
}

int main(int argc, char **argv){
  int i, n=0, t;
  unsigned short int a;

  if(argc!=2) showhelp();
  if(strlen(argv[1])!=16){
    printf("Insira uma configuração com 16 posições.\n");
    showhelp();
  }
  for(i=0; i<16; ++i){ 
    if(!(argv[1][i]=='0' || argv[1][i]=='1')){ 
      printf("Use apenas 0 e 1.\n");
      showhelp(); 
    }
  } 

  FILE *f1;
  f1= fopen("spins.txt", "rb");

  if(f1==NULL){
    printf("Falha ao abrir o ficheiro!\n");
    showhelp();
  }
  
  for(i=0; i<16; ++i)
    n=n + (argv[1][i] - 48) * pow(2, 15-i);
      
  printf("\nEsta configuração encontra-se na linha %d.\n", n);
    
  t=fseek(f1, n*sizeof(short int), SEEK_SET);

  if(t!=0) showhelp();

  fread(&a, sizeof(short int), 1, f1);

  printf("Leitura do ficheiro retorna a linha: %d\n\n", a);    

  fclose(f1);
  return 0;
}
