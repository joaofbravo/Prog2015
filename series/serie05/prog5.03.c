#include<stdio.h>
#include<stdlib.h>

void showhelp(){
  printf("\nNúmeros racionais na forma N/M");
  printf("\n(Para N menor ou igual a M)\n");
  printf("\n  ./<programa> <N> <M>\n\n");

  exit (-1);
}

void gerador(int n, int m, double *v){
  int i=0, j, k;
 
  for(k=1; k<=m; ++k){
    for(j=1; j<=n; ++j){
      v[i]= (double) j / (double) k;
      ++i;
    }
  }
}

void ordenador(int n, int m, double *v){
  int i, j, t;
  double v0;

  while(1){
    t=0;

    for(i=0; i<n*m-1; ++i){
      if(v[i]>v[i+1]){
	v0=v[i];
	v[i]=v[i+1];
	v[i+1]=v0;
	t=1;
      }
    }
    if(t==0) break;
  }
}

int eliminador(int n, int m, double *v){

  int i1, i2=0;
  
  for(i1=1; i1<n*m; ++i1){
    if(v[i1]!=v[i2]){
      ++i2;
      v[i2]=v[i1];
    }
  }
  
  return i2+1;
}


int main(int argc, char **argv){
  int n, m, t, tamanho, i;
  double *v;

  if(argc!=3)
    showhelp();

  t= sscanf(argv[1], "%d", &n);
  t=t+ sscanf(argv[2], "%d", &m);
  
  if(t!=2){
    printf("Erro na leitura dos dados.\n");
    showhelp();
  }
  
  if(n>m)
    showhelp();
 

  v=(double*)malloc(n*m*sizeof(double));
  
  gerador(n, m, v);
  ordenador(n, m, v);
  tamanho= eliminador(n, m, v);

  
  v=(double*)realloc(v, tamanho*sizeof(double));

  FILE *f1;
  f1=fopen("dados.txt", "wt");
  
  for(i=0; i<tamanho; ++i){
    fprintf(f1,"%.5lf  ", v[i]);
    printf("%.5lf  ", v[i]);
    
    if( (i+1)%10 ==0 ){
      fprintf(f1,"\n");
      printf("\n");
    }
  }
  
  printf("\n\n");  
  fclose(f1);
  free(v);
  return 0;
}
