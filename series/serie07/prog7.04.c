#include <stdio.h>
#include <stdlib.h>

void showhelp(){
  printf("\nContagem de caracteres de texto");
  printf("\nInstrucoes: ./<nome_programa> <ficheiro_leitura>\n\n");
  exit(-1);
}


int main(int argc, char **argv){
  int n, a=0, b, d=0, i, e, q=0;
  int *c;
  FILE *f1;
   
   if(argc != 2){
    printf("\nNúmero de argumentos dados invalido.\n");
    showhelp();
  }
 
 f1=fopen(argv[1], "rt");
   if(f1==NULL){
    printf("\nFicheiro inexistente.\n");
    showhelp();
  }

  c= (int*)malloc(256*sizeof(int));
 
  while((n=fgetc(f1)) != EOF){
    c[n]++;
    a++;                                       //Numero total de caracteres
  }
  
  printf("\nNumero total de caracteres de texto= %d\n\n", a);

  for(i=0; i<256; ++i){ 
  if((i>64 && i<91) || (i>96 && i<123))
      d=d+c[i];                               //Numero total de letras

    if(c[i]!=0){
      if(i<33 || i>126)
      	printf("Código da tabela ASCII: %d (x %d)\n", i, c[i]);    
      else{
	printf("%c: %3d\t\t", i, c[i]);
	++q;
	if(q %5 == 0)
	  printf("\n");
      }
    }
  }
  
   //Numero total de vogais
  b= c['A']+c['E']+c['I']+c['O']+c['U']+c['a']+c['e']+c['i']+c['o']+c['u'];  
  printf("\n\nNumero total de vogais: %d\n", b);

   //Numero total de consoantes
  e= d-b;                                                                     
  printf("Numero total de consoantes: %d\n\n", e);
 
  free(c);
  fclose(f1);
  return 0;
  }

