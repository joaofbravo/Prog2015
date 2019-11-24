#include<stdio.h>
#include<math.h>

int main()
{
  double x, r, x0;
  int i, teste;
  printf("x0 e r:");
  teste=scanf("%lf %lf", &x0, &r);
  printf("Leu x0=%lf e r=%lf, (com teste: %d)\n\n", x0, r, teste);

  if(teste!=2)
    {printf("erro");
      return -1;
    } 

  x=x0;
  for(i=0; i<=100; i++)
    {
      printf("%d: x= %lf\n", i, x);
      x = r*x*(1-x);
      
      if(fabs(x-x0)<1.e-6)
	break;
    	  x0=x;
     }

 return 0;
}
