#include<stdio.h>
#include<math.h>

int main(int argc, char **argv){
  int i, t1;
  double x, y;

  if(argc!=2){
    printf("Número incorreto de argumentos.\n\n");
    return -1;
  }

  t1= sscanf(argv[1], "%lf", &x);

  if(t1!=1){
    printf("Tem que introduzir um número.\n\n");
    return -1;
    }

  FILE *f1;
  f1=fopen("Bernoulli.dat", "wt");

  for(i=0; i<100; ++i){
    x=modf(x, &y);
    
    printf("%2dª iterada:      %.10lf\n", i, x);
    fprintf(f1, "%dª iterada:      %.10lf\n", i, x);
    
    x=2*x;
  }
  
  printf("\n");
  fclose(f1);
  return 0;
}
