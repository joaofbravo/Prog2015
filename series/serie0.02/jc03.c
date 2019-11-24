#include <stdio.h>
int main()
{
  int teste1, n, i;
  float x0, x, u;
  printf("Quais os valores de xo, u e n?");
  teste1=scanf("%f %f %d", &x0, &u, &n);
    printf("Leu: %f %f %d (com teste: %d)\n\n",x0, u, n, teste1);
    if(teste1 !=3){
      printf("ERRO!\n");
      return -1;
    }
    i=0;
    x=x0;
    while(i <= n){
      printf("Iteração:%2d x=%f\n", i, x);
      x=u*x;
      ++i;
    }
    return 0;
}
