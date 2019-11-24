#include <stdio.h>
#include <math.h>

//Conversor de argumento:

double conv(double x){
  x= fmod(x,2*M_PI);
  if(x<0)
    x=x+2*M_PI;
  return x;
}

//Fatorial:

double fatorial(int a){
  if (a==0)  return 1;
  return a*fatorial(a-1);
}

//Cosseno:

double cos1(double x){
  double z1, z2, q;
  int i=0; 
  z2=0;
  q=1;
  
  while(1){
    z1= (q*pow(x,2*i))/fatorial(2*i);
    i=i+1;
    z2=z2+z1;
    q=-q; 

    if(fabs(z1)<1e-10)
      break;
  }
  
  return z2;
}


int main(){
  double x, x1, y, w;
  int teste;
  
  printf("Cálculo de cos(x).\nQual o valor de x (em radianos)? ");
  teste=scanf("%lf", &x);
 
  if(teste!=1){
    printf("ERRO!\n\n");
    return -1;
  }

  x1=x;
  
  x= conv(x);
  y= cos1(x);
  w= cos(x);
  
  printf("\ncos(%lf)=%.10lf \n[Valor calculado pela Biblioteca]:  %.10lf \n\n", x1, y, w);

  return 0;
}
