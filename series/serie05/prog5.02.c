#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void showhelp(){
  printf("\nEstudo de percolação numa rede retangular");
  printf("\n   ./<programa> <linhas da matriz> <colunas da matriz> <probabilidade>\n\n");

  exit (-1);
}

void fill1(int m, int n, double p, int **v){
  int i, j, z;

  for(i=0; i<m; ++i){
    for(j=0; j<n; ++j){
      if((((double) rand ()) / ((double) RAND_MAX)) <= p)
	v[i][j]=1;
      else
	v[i][j]=0;

      printf("%d ", v[i][j]);

      if(j==n-1)
	printf("\n");      
    }
  }
}

int main(int argc, char **argv){
  int m, n, t, q, w, z=0;
  double p;
  int **v;

  if(argc!=4)
    showhelp();

  t= sscanf(argv[1], "%d", &m);
  t=t+ sscanf(argv[2], "%d", &n);
  t=t+ sscanf(argv[3], "%lf", &p);
 
  if(t!=3 || m<0 || n<0 || !(p>=0 && p<=1)){
    printf("Erro na leitura dos dados.\n");
    showhelp();
  }
  
  v=(int**)malloc(m*sizeof(int*));
  for(q=0; q<m; ++q)
    v[q]=(int*)malloc(n*sizeof(int));

  srand(time(NULL));
  
  while(1){   
    printf("\n");
    fill1(m, n, p, v);
    printf("\n");
    
    printf("Deseja fazer um novo preenchimento? Sim(1) Não(outro valor): ");
    scanf("%d", &z);
    if(z!=1) break;
  }
  
  for(w=0; w<m; ++w)
    free(v[w]);
  free(v);  
  return 0;
}
