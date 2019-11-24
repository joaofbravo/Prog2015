#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void showhelp(){
  printf("\nConfiguração de uma rede de 2048 spins.");
  printf("\nEste programa recebe o número de configurações distintas a gerar da rede\ne retorna a magnetização de cada uma, a magnetização média e a magnetização média por spin.");
  printf("\n\n ./<programa> <nº de configurações>\n\n");
  
  exit(-1);
}

void gerar(double *spin, double *m1){
  int i;
  *m1=0;

  for(i=0; i<2048; ++i){
    spin[i]= rand() % 2 - 0.5;
    *m1=*m1+spin[i];   
  }
}

int main(int argc, char **argv){
  int n, i, t;  
  double *spin, m1=0, m2=0, m3;
    
  if(argc!=2) showhelp(); 
  
  t=sscanf(argv[1], "%d", &n);
  
  if(t!=1 || !(n>0)){
    printf("Erro na leitura dos dados.\n");
    showhelp();
  }

  spin=(double*)malloc(2048*sizeof(double));

  srand(time(NULL));  

  for(i=1; i<=n; ++i){
    gerar(spin, &m1);
    m2=m2+m1;
    printf("(%dª configuração) magnetização: %.1lf\n", i, m1);
  }

  m2= m2/n;
  m3= m2/2048;

  printf("\nMagnetização média: %lf\nMagnetização média por spin: %lf\n\n", m2, m3);

  free(spin);
  return 0;
}
