#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void show_help (int status)
{
  switch(status)
    {
    case 0:
      printf("\nERRO: Número de argumentos inválido.\n"); break;
    case 1:
      printf("\nERRO: Introduziu um valor 'x0' inválido.\n"); break;
    case 2:
      printf("\nERRO: Introduziu um valor 'v0' inválido.\n"); break;
    case 3:
      printf("\nERRO: Introduziu um valor de 'm' inválido [toma valor diferente de 0] .\n"); break;
    case 4:
      printf("\nERRO: Introduziu um valor de 'K' inválido.\n"); break;
    case 5:
      printf("\nERRO: Introduziu um valor de 'b' inválido [toma valor maior de 0].\n"); break;
    case 6:
      printf("\nERRO: Introduziu um valor de 't0' inválido.\n"); break;
    case 7:
      printf("\nERRO: Introduziu um valor de 't1' inválido.\n"); break;
    case 8:
      printf("\nERRO: O tempo final tem que ser maior que o inicial.\n"); break;
    case 9:
      printf("\nERRO: Falha ao abrir ficheiro.\n"); break;
    }
  printf("\nEscreva o programa na forma:\n");
  printf("\n\t./s9_01 ['x0'] ['v0'] ['m'] ['K'] ['b'] ['t0'] ['t1']\n\n");
  printf("NOTA:\n-> Os valores a introduzir são números reais;\n-> O tempo final tem que ser maior que o inicial.\n\n");
  exit(status);
}

double test (char *v,double x,int i)
{
  int t=sscanf(v,"%lf",&x);
  if(t!=1) show_help(i);
  return x;
}

/*********************************************************************************************************************************/

double lambda_ (double b,double m)
{
  return (b/(2*m));
}
    
double w0_ (double K,double m)
{
  return sqrt(K/m);
}

double omega_ (double w0,double lambda)
{
  return sqrt(w0*w0-lambda*lambda);
}

double beta_ (double w0,double lambda)
{
  return sqrt(lambda*lambda-w0*w0);
}

double phi_ (double x0,double v0,double omega,double lambda)
{
  return atan((-v0+lambda*x0)/(omega*x0));
}

/*********************************************************************************************************************************/

double A_ (double x0,double v0,double omega,double lambda)
{
  return sqrt((x0*x0)+((v0*v0+lambda*lambda*x0*x0+2*lambda*x0*v0)/(omega*omega)));
}

double C_ (double x0,double v0,double beta,double lambda,int i)
{
  if(i==1) return ((v0+(lambda+beta)*x0)/(2*beta));
  else return x0;
}

double D_ (double x0,double v0,double beta,double lambda, int i)
{
  if(i==1) return ((-v0-(lambda-beta)*x0)/(2*beta));
  else return (v0+lambda*x0);
}

/**********************************************************************************************************************************/

double delta_ (double t0, double t1)
{
  return (t1-t0)*1E-5;
}

double dif (double x0,double v0,double m,double K,double b,double t0,double t1)
{
  FILE *file;
  file=fopen("Osc_H.txt","wt");
  if(file==NULL) show_help(9);

  double delta=delta_(t0,t1),w0=w0_(K,m),lambda=lambda_(b,m);

  if(w0>lambda)
    {
      double omega=omega_(w0,lambda),A=A_(x0,v0,omega,lambda),phi=phi_(x0,v0,omega,lambda);
      while(t0<t1)
	{
	  printf(" %lf  %lf\n",t0,x0);
	  fprintf(file," %lf  %lf \n",t0,x0);
	  
	  x0=A*exp(-1*lambda*t0)*cos(omega*t0+phi);
	  t0+=delta;
        }
      fclose(file);
    }
  else if(w0<lambda)
    {
      double beta=beta_(w0,lambda),C=C_(x0,v0,beta,lambda,1),D=D_(x0,v0,beta,lambda,1);
      while(t0<t1)
	{
	  printf(" %lf  %lf  %lf\n",t0,x0);
	  fprintf(file," %lf  %lf  %lf\n",t0,x0);
	  x0=exp(-lambda*t0)*(C*exp(beta*t0)+D*exp(-beta*t0));
	  t0+=delta;
        }
      fclose(file);
    }
  else
    { 
      double C=C_(x0,v0,0,lambda,2),D=D_(x0,v0,0,lambda,2);
      while(t0<t1)
	{
	  printf(" %lf  %lf\n",t0,x0);
	  fprintf(file," %lf  %lf \n",t0,x0);
	  x0=exp(-lambda*t0)*(C+D*t0);
	  t0+=delta;
        }
      fclose(file);
    }
}

/**********************************************************************************************************************************/

int main(int argc,char **argv)
{
  if(argc!=8) show_help(0);
  double x0,v0,m,K,b,t0,t1;
  x0=test(argv[1],x0,1);
  v0=test(argv[2],v0,2);
  m=test(argv[3],m,3);
  if(m==0.) show_help (3);
  K=test(argv[4],K,4);
  b=test(argv[5],b,5);
  if(b<0) show_help(5);
  t0=test(argv[6],t0,6);
  t1=test(argv[7],t1,7);
  if(t0>=t1) show_help(8);

  dif(x0,v0,m,K,b,t0,t1);

  return 0;
}
