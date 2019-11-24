#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void show_help(){
  printf("\nOPERAÇÕES COM COMPLEXOS.    <Operação> <Real1> <Imaginário1> <Real2> <Imaginário2>\n");
  printf("\nOperações disponíveis:\nAdição\t\t'+'");
  printf("\nSubtração\t'-'");
  printf("\nProduto\t\t'x'");
  printf("\nDivisão\t\t'/'");
  printf("\nMódulo\t\t'mod'\t(Introduza apenas um número complexo)\n\n");

  exit (-1);
}

typedef struct{
  double r;
  double i;
} complexo;

double modulo(complexo *v){
  return sqrt((v->r * v->r) + (v->i * v->i));
}

void adicao(complexo *a, complexo *b, complexo *c){
  c->r= a->r + b->r;
  c->i= a->i + b->i;
}

void diferenca(complexo *a, complexo *b, complexo *c){
  c->r= a->r - b->r;
  c->i= a->i - b->i;  
}

void produto(complexo *a, complexo *b, complexo *c){
  c->r= a->r * b->r - a->i * b->i;
  c->i= a->r * b->i + a->i * b->r;  
}

void divisao(complexo *a, complexo *b, complexo *c){
  c->r= ((a->r * b->r) + (a->i * b->i)) / ((b->r * b->r) + (b->i * b->i));
  c->i= ((a->i * b->r) - (a->r * b->i)) / ((b->r * b->r) + (b->i * b->i));
}

int main(int argc, char **argv){
  
  int t;
  double mod1;
  complexo a, b, c;
  
  if(argc!=4 && argc!=6)
    show_help();
  if(!((strcmp(argv[1],"+")==0) || (strcmp(argv[1],"-")==0) || (strcmp(argv[1],"x")==0) || (strcmp(argv[1],"/")==0) || (strcmp(argv[1],"mod")==0)))
    show_help();
  
  if(argc==6){
    if(strcmp(argv[1],"mod")==0)
      show_help();  

    t= sscanf(argv[2], "%lf", &a.r);
    t= t+sscanf(argv[3], "%lf", &a.i);
    t= t+sscanf(argv[4], "%lf", &b.r);
    t= t+sscanf(argv[5], "%lf", &b.i);
    
    if(t!=4)
      show_help();

    if(strcmp(argv[1],"+")==0){
      adicao(&a, &b, &c);
      
      printf("%.3lf+%.3lfi + %.3lf+%.3lfi = %.3lf+%.3lfi\n\n", a.r, a.i, b.r, b.i, c.r, c.i);
    }

    if(strcmp(argv[1],"-")==0){
      diferenca(&a, &b, &c);
    
      printf("%.3lf+%.3lfi - %.3lf+%.3lfi = %.3lf+%.3lfi\n\n", a.r, a.i, b.r, b.i, c.r, c.i);
    }

    if(strcmp(argv[1],"x")==0){
      produto(&a, &b, &c);
      
      printf("%.3lf+%.3lfi x %.3lf+%.3lfi = %.3lf+%.3lfi\n\n", a.r, a.i, b.r, b.i, c.r, c.i);
    }

    if(strcmp(argv[1],"/")==0){
      divisao(&a, &b, &c);
      
      printf("%.3lf+%.3lfi / %.3lf+%.3lfi = %.3lf+%.3lfi\n\n", a.r, a.i, b.r, b.i, c.r, c.i);
    }
  }

  if(argc==4){
    if(strcmp(argv[1],"mod")!=0)
      show_help();

    t= sscanf(argv[2], "%lf", &a.r);
    t= t+sscanf(argv[3], "%lf", &a.i);
    
    if(t!=2)
      show_help();

    mod1=modulo(&a);
    
    printf("Módulo de %.3lf+%.3lfi = %.5lf \n\n", a.r, a.i, mod1);
  }   
  
  return 0;
}
