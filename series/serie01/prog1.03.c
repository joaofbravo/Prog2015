#include <stdio.h>
#include <math.h>

void fibon(int *v, int p){
  int i1;
    v[0]=0;
    v[1]=1;
   
    for(i1=2; i1<p; ++i1)
      v[i1]=v[i1-1]+v[i1-2];
}

int main(){
  int n, teste, i1;
  
  printf("Quer calcular quantos valores? ");
  teste=scanf("%d", &n);
  printf("Leu: %d, (com teste: %d)\n\n", n, teste);

  if(teste != 1){
   printf("ERRO!\n\n");
   return -1;
  }
  
  if(n>45){
    printf("Valor maximo excedido (45).\n\n");
    return -1;
 }

  if(n<0){
    printf("Não há quantidades negativas!\n\n");
    return -1;
  }
  
  int v[n];
  fibon(v, n);

  for(i1=1; i1<=n; ++i1) {
    printf("%9d ", v[i1-1]);

    if(i1%8 == 0)
      printf("\n");
 }
  
  printf("\n\n");
  return 0;
}
