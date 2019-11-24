#include<stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv){
  double a, b, t;

  if(argc!=4){
    printf("<programa> <nº> <+ - x / ^> <nº>");
    return -1;
  }
  
  /* a=(double) *argv[1]; */     //Não usar isto, pois usa código ascii
  /* b=(double) *argv[3]; */
  
  t= sscanf (argv[1], "%lf", &a);
  t= t + sscanf (argv[3], "%lf", &b);

  if(t!=2){
    printf("<programa> <nº> <+ - x / ^> <nº>");
    return -1;
  }
  
  if(strcmp(argv[2],"+")==0)
    printf("%lf + %lf = %lf\n\n", a, b, a+b);
  
  if(strcmp(argv[2],"-")==0)
    printf("%lf - %lf = %lf\n\n", a, b, a-b);
  
  if(strcmp(argv[2],"x")==0)
    printf("%lf x %lf = %lf\n\n", a, b, a*b);
  
  if(strcmp(argv[2],"/")==0)
    printf("%lf / %lf = %lf\n\n", a, b, a/b);
  
  if(strcmp(argv[2],"^")==0)
    printf("%lf ^ %lf = %lf\n\n", a, b, pow(a,b));
  
  return 0;
}
