#include<stdio.h>
int
 main()
{

  int a,b,c, teste;
  printf("Valor? \n");
  teste=scanf("%d", &a);
  printf("Leu: %d (com teste: %d)\n\n", a, teste);

  if( teste !=1 || a<0 || a>=50 )
{
  printf("Que rebelde...\n");
    return -1;
 }

b=0;
 while( b <=10 )
   {
    c= a * b;
     printf(" %d * %d = %d \n", a, b,c);
     b=b+1;
   }
 return 0;


}


