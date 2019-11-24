//Este programa é merdoso.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void showhelp(){
  printf("\nCalculo do valor do Integral num intervalo!\n");
  printf("Funçoes disponiveis:\n");
  printf("1.sin(x)\t2.5cos(3*x)e^(-0.1x)\n3.RAIZ(x)\t4.3x^3-2x\n5.e^x\t\t6.(1/RAIZ(PI))*e^(-x^2)\n");
    }

double integral(double(*f)(double), double x1, double x2){
int i;
double a, b, d, c, x, y=0, x3, x4;

  if(x1==x2)
    return 0;

  if(x2<x1){
    x3=x2;
    x4=x1;
  }
  else{
    x3=x1;
    x4=x2;
  }

  d= (fabs(x4)-fabs(x3))/1e6;
  a= x3;
  b= x3+d;

  while(a < x4){
    x=d*f((a+b)/2);
    y=y+x;    
    a=b;
    b=b+d;
  }

  if(x2<x1)
    return -y;

  return y;
}


double composta1(double x){
  double a;
  a= 5*cos(3*x)*exp(-0.1*x);
  return a; 
}

double composta2(double x){
  double a;
  a= 3*x*x*x - 2*x;
  return a;
}

double composta3(double x){
  double a;
  a=(1/sqrt(M_PI))*exp(-x*x);
  return a;
}

int main(){
  int f,t;
  double x1, x2, a;
  
while(1){
  showhelp();

  printf("Qual a funçao que pretende utilizar?\n");
  t= scanf("%d", &f);
  if(t!=1 || !(f>0 && f<7)){
    printf("ERRO!\n");
    return -1;
  }
  while(getchar()!=10);

  printf("Quais os limites de Integracao?\n");
  t=scanf("%lf %lf", &x1, &x2);
  if(t!=2){
    printf("ERRO!\n");
    return -1;
  }
  while(getchar()!=10);

  switch(f){
  case 1:
    a=integral(sin, x1, x2);
    break;
  case 2:
    a=integral(composta1, x1, x2);
    break;
  case 3:
    a=integral(sqrt, x1, x2);
    break;
  case 4:
    a=integral(composta2, x1, x2);
    break;
  case 5:
    a=integral(exp, x1, x2);
     break;
  case 6:
    a=integral(composta3, x1, x2);
    break;
  }

  printf("Valor do Integral=%lf\n", a);

  }

}
