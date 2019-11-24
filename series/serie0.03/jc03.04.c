#include <stdio.h>
int main(){

  FILE *f1;
  f1=fopen("jc03.03.e.txt","rt");
  
  double a,b, d;
  int c, i;
  fscanf(f1, "x0=%lf r=%lf Periodo:%d\n", &a, &b, &c);
  printf("x0=%lf r=%lf Periodo:%d\n\n", a, b, c);

  for(i=1; i<=c; i++){
    fscanf(f1,"%lf", &d);
    printf("%lf ", d);
    if(i % 4 ==0)
      printf("\n");
  }

  fclose(f1);
  return 0;
}
