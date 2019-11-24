/* Serie 8 - António Fernandes */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void show_help(int status)
{
  switch(status)
    {
    case 0:
      printf("\nERRO: Número de argumentos inválido.\n"); break;
    case 1:
      printf("\nERRO: Introduziu um valor lambda inválido.\n"); break;
    case 2:
      printf("\nERRO: Introduziu um valor inicial de x inválido.\n"); break;
    case 3:
      printf("\nERRO: Introduziu um valor do tempo inicial inválido.\n"); break;
    case 4:
      printf("\nERRO: Introduziu um valor do tempo final inválido.\n"); break;
    case 5:
      printf("\nERRO: O tempo final tem que ser maior que o inicial.\n"); break;
    case 6:
      printf("\nERRO: Falha ao abrir ficheiro.\n"); break;
    }
  printf("\nEscreva o programa na forma:\n");
  printf("\n\t./s8_01 [lambda] [valor inicial de x] [tempo inicial] [tempo final]\n\n");
  printf("NOTA:\n-> Os valores a introduzir são números reais.\n-> O tempo final tem que ser maior que o inicial\n\n");
  exit(status);
}

double test(char *v,double a,int i)
{
  int t;
  t=sscanf(v,"%lf",&a);
  if(t!=1) show_help(i);
  return a;
}

double incremento(double ti, double tf)
{
  return (tf-ti)*1E-5;
}

double dif(double lbd,double x0,double delta)
{
  return (x0-lbd*x0*delta);
}

int main(int argc,char **argv)
{
  if(argc!=5) show_help(0);
  double lbd,x0,ti,tf;
  lbd=test(argv[1],lbd,1);
  x0=test(argv[2],x0,2);
  ti=test(argv[3],ti,3);
  tf=test(argv[4],tf,4);
  printf("\n lambda: %lf    x0: %lf    ti: %lf    tf: %lf\n\n",lbd,x0,ti,tf);
  if(tf<=ti) show_help(5);

  FILE *file;
  file=fopen("Eq_Dif.txt","wt");
  if(file==NULL) show_help(6);
  
  double delta=incremento(ti,tf); 
  while(ti<tf)
    {
      printf(" %lf  %lf\n",ti,x0);
      fprintf(file," %lf  %lf\n",ti,x0);
      x0=dif(lbd,x0,delta);
      ti+=delta;
    }
  fclose(file);
  return 0;
}
