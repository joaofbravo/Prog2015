#include<stdio.h>
#include<stdlib.h>

void showhelp(){
  printf("\nREESCRITA DE UM FICHEIRO (com até 100 carateres por linha)");
  printf("\nConversões disponíveis:");
  printf("\n- maiúsculas para minúsculas:\t 'M2m'");
  printf("\n- minúsculas para maiúsculas:\t 'm2M'");
  printf("\n\n ./<programa> <Tipo de Conversao> <file_de_leitura> <file_de_escrita>\n\n");
  
  exit(-1);
}

int main(int argc, char **argv){
  int i;
  char s[101];
  FILE *f1, *f2;

      /*
	Ativar para verificar se o prog funciona, cria file_de_leitura : teste.txt
	
	FILE *f3;
	f3=fopen("teste.txt","wt");
	fprintf(f3, "ISTO e um TeStE. aA123");
	fclose(f3);
      */
  
  if(argc!=4)
    showhelp();
  if(strcmp(argv[1], "M2m")!=0 && strcmp(argv[1], "m2M")!=0)
    showhelp();
  
  f1=fopen(argv[2], "rt");
  f2=fopen(argv[3], "wt");
  
  if(f1==NULL || f2==NULL){
    printf("Erro na abertura dos ficheiros!\n");
    showhelp();
  }
  
  //Ciclo com fgets
  while(fgets(s, 101, f1)!=NULL){
    
    for(i=0; s[i]!=0; ++i){
      if((strcmp(argv[1], "m2M")==0) && (s[i]>='a') && (s[i]<='z'))
	s[i]-=32;
      
      if((strcmp(argv[1], "M2m")==0) && (s[i]>='A') && (s[i]<='Z'))
	s[i]+=32;
    }
 
    fprintf(f2,"%s", s);
  }
  
  fclose(f1);
  fclose(f2);
  return 0;
}
