#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void showhelp(int *f, double *x){
  int t, a=1;

  while(a==1){
    printf("=========================\n\n Cálculo da derivada de uma função.");
    printf("\n\nFunções disponíveis:");
    printf("\n1: sin(x)");
    printf("\n2: cos(2x)");
    printf("\n3: tan(x)");
    printf("\n4: arcsin(x)");
    printf("\n5: arccos(x)");
    printf("\n6: log(x)");
    printf("\n7: log10(x)");
    printf("\n8: exp(3x)");
    printf("\n9: 3*cos(2x)*sin(5x)");
    printf("\n\n Formato: <nº da função> <valor de x>\n\n");

    printf("Escolha uma função e um valor para x: ");
    t= scanf("%d %lf", f, x);
   
    if(t!=2 || !(*f<10 && *f>0)){
      printf("Erro na leitura dos dados.\n\n");
      exit(-1);
    }
  
    a=0;

    if(*f==4 && !(*x>=-1 && *x<=1)){
      printf("A função não está definida nesse valor.\n\n");
      a=1;
    } 
    if(*f==5 && !(*x>=-1 && *x<=1)){
      printf("A função não está definida nesse valor.\n\n");
      a=1;
    }
    if(*f==6 && *x<=0){
      printf("A função não está definida nesse valor.\n\n");
      a=1;
    }
    if(*f==7 && *x<=0){
      printf("A função não está definida nesse valor.\n\n");
      a=1;
    }
  }
}

//Função derivada

double derivada(double (*f) (double), double x){ 
  double d, h;
  
  h= 1E-10;
  d= (f(x+h) - f(x)) / h;
  
  return d;
}

//Funções definidas

double cos2(double x){ 
  double f; 
  f= cos(2*x);
  return f; 
} 

double log10(double x){ 
  double f; 
  f=log(x)/log(10); 
  return f; 
}

double exp3(double x){ 
  double f; 
  f=exp(3*x);  
  return f; 
}

double cossin(double x){ 
  double f; 
  f=3*cos(2*x)*sin(5*x); 
  return f;
}

//MAIN

int main(){
  int f;
  double x, y, z;

  while(1){
  
    showhelp(&f, &x);

    switch (f){
    case 1:
      y= derivada(sin, x);
      z= cos(x);
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;

    case 2:
      y= derivada(cos2, x);
      z= (-2)*sin(2*x);
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;

    case 3:
      y= derivada(tan, x);
      z= 1+(tan(x)*tan(x));
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;
	   	 
    case 4:
      y= derivada(asin, x);
      z= 1/(sqrt(1-x*x));
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;

    case 5:
      y= derivada(acos, x);
      z= -1/((sqrt(1-x*x)));
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;

    case 6:
      y= derivada(log, x);
      z= 1/x;
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;
      
    case 7:
      y= derivada(log10, x);
      z= 1/(x*log(10));      
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;

    case 8:
      y= derivada(exp3, x);
      z= 3*exp(3*x);
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;

    case 9:
      y= derivada(cossin, x);
      z= (-6)*sin(2*x)*sin(5*x)+15*cos(5*x)*cos(2*x);
      printf("\n\nDerivada calculada: %lf\nDerivada exata: %lf\nErro: %lf\n\n", y, z, fabs(y-z));
      break;
    }
  }

  return 0;
}
