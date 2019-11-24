#include <stdio.h>
#include <math.h>

int
main()
{
int teste;
double a, b, c, d, x1,x2, y,z;
 printf("Quais os valores de a, b e c?\n");
teste= scanf("%lf, %lf, %lf", &a, &b, &c);
printf("Leu:%lf, %lf, %lf (com teste: %d)\n", a, b,c,teste);
if(teste != 3){
printf("ERRO!\n");
return -1;
}
printf("A equação é %lfx²+%lfx+%lf=0\n",a,b,c);
d= (b*b)-4*a*c;
 printf("Discriminante: %lf\n", d);
if(d>0){
  x1=(-b+sqrt(d))/(2*a);
  x2=(-b-sqrt(d))/(2*a);
printf("As soluçoes sao %lf, %lf\n", x1, x2);
}
if(d==0){
  x1=(-b+sqrt(d))/(2*a);
printf("x=%lf\n Raiz dupla!", x1);
 }
 if(d<0) {

   x1=sqrt(-d)/(2*a);
   y=-b/(2*a);
   x2=sqrt(-d)/(2*a);
   printf("As soluçoes sao: %lf+%lfi e %lf-%lfi\n", y, x1, y, x2);
 }
 return 0;
}



