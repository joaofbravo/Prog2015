#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void showhelp(){
  printf("\nREESCRITA DE UM FICHEIRO (com até 255 carateres por linha)");
  printf("\nO ficheiro de escrita terá as linhas escritas do fim para o princípio.");
  printf("\n\n ./<programa> <file_de_leitura> <file_de_escrita>\n\n");
  
  exit(-1);
}

void inversao(int c, char *s){
  int i;
  char s0;
 
  for(i=0; i<c/2; ++i){
    s0=s[i];
    s[i]=s[c-i-1];
    s[c-i-1]=s0;
  }
}


int main(int argc, char **argv){
  int i, comp;
  char s[256];
  FILE *f1, *f2;

  if(argc!=3)
    showhelp();
  
  f1=fopen(argv[1], "rt");
  f2=fopen(argv[2], "wt");
 
  if(f1==NULL || f2==NULL){
    printf("Falha ao abrir os ficheiros!\n");
    showhelp();
  }
  
  //Ciclo com fgets para inverter e escrever

  while(fgets(s, 256, f1)!=NULL){
    comp=strlen(s);
    
    if(s[comp]==10){
      if(s[comp-1]==13)
	inversao(comp-1, s);
      else
	inversao(comp, s);
    }
    else
      inversao(comp, s);
    
    fprintf(f2,"%s", s);
    printf("%s", s);
  }
  
  printf("\n\n");
  fclose(f1);
  fclose(f2);
  return 0;
}
