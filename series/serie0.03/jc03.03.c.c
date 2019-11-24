#include<stdio.h>
#include<math.h>

int main()
{
  double x, r, x0, xref, primeiro;
  int i, teste;
  printf("x0 e r:");
  teste=scanf("%lf %lf", &x, &r);
  printf("Leu x0=%lf e r=%lf, (com teste: %d)\n\n", x, r, teste);

  if(teste!=2)
    {printf("erro");
      return -1;
    }
  x0=x;
  for(i=0; i<=1000; i++)
    {
      x = r*x*(1-x);
      
      if(fabs(x-x0)<1.e-6)
	break;
    	  x0=x;
     }

  xref=x;
  for(i=0; i<=64; i++)
    {
      x = r*x*(1-x);
		printf("%lf\n", x);	   
      if(fabs(x-xref)<1.e-6)
	      break;
} 
  i=i+1;
  printf("\nValores: %d\n", i);
 return 0;
}
