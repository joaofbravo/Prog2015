#include<stdio.h>
int
 main()
{

  int teste;
  float a,b;
 
  printf("Valor? \n");
  teste=scanf("%f", &a);
  printf("Leu: %f (com teste: %d)\n\n", a, teste);

if( teste !=1)
{
  printf("Mas tu és estúpido?\n");
    return -1;
 }

 b=a*1.8+32;
 printf("%fºC sao %fºF \n", a,b);

 return 0;


}


