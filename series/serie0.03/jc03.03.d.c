#include<stdio.h>
#include<math.h>

int main()
{
  FILE *f1;
  f1=fopen("jc03.03.e.txt", "wt");

  double x, r, x0, xref, xinicial;
  int i, teste;
  printf("x0 e r:");
  teste=scanf("%lf %lf", &x, &r);
  printf("Teste: %d\n\n", teste);

  if(teste!=2)
    {printf("erro");
      return -1;
    }
  xinicial=x;
  x0=x;
  for(i=0; i<=1000; i++)
    {
      x = r*x*(1-x);
      
      if(fabs(x-x0)<1.e-6)
	break;
    	  x0=x;
     }

  xref=x;
  for(i=1; i<=64; i++)
    {
      x = r*x*(1-x);
		   
      if(fabs(x-xref)<1.e-6)
	break;
    }

  printf("x0=%lf r=%lf Periodo:%d\n", xinicial, r, i);
  fprintf(f1,"x0=%lf r=%lf Periodo:%d\n", xinicial, r, i);

  for(i=1; i<=64; i++)
    {
      x = r*x*(1-x);
      printf("%lf\n", x);
      fprintf(f1,"%lf\n", x);	   
      if(fabs(x-xref)<1.e-6)
	break;
} 
 return 0;
}
