#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void showhelp(){
  printf("\nCálculo de todos os nºs primos até N.");
  printf("\n\n ./<programa> <N>\n\n");
  
  exit(-1);
}

void eliminador(int *v, int max, int n){
  int i, q;
  
  for(i=2; i<=max; ++i){
    q=i;

    if(v[i]!=0){
      while((q=q+i)<=n)    
	v[q]=0;
    }
  }
}

void print(int *v, int n){
  int i, q=0;

  printf("\nNúmeros primos até %d:\n\n", n);

  for(i=2; i<=n; ++i){
    if(v[i]!=0){
      printf("%d\t", i);
      
      ++q;
      
      if((q % 10) ==0)
	printf("\n");
    }
  }
  printf("\n\n");
}


int main(int argc, char **argv){
  int t, i, n, *v, max;

  switch(argc){
  case 2:
    
    t= sscanf(argv[1], "%d", &n);
    if(t!=1 || !(n>0)){
      printf("Erro na leitura dos dados.\n");
      showhelp();
    }
    
    if(n==1){
      printf("Não existem nºs primos menores que 2.\n\n");
      return 0;
    }
    
    v=(int*)malloc((n+1)*sizeof(int));

    for(i=0; i<=n; ++i)
      v[i]=1;

    max= sqrt(n);
    eliminador(v, max, n);
    print(v, n);

    break;

  default:
    showhelp();
  }

  return 0;
}
