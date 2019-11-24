#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int contador(char *v, char c1){
  int i=0;
  int cont=0;
  
  while(v[i]!=0){
    if(v[i]==c1)
      cont++;
    i++;
  }
  return cont;
}

int posicao(char *v, char c1){
  int i, x;
  i=0;
  
  x=strlen(v);
  
  while(v[i]!=0){
    if(v[i]==c1)
      break;
    i++;
  }
  
  if(i==x)
    return -1;
  else
    return i;
}

char* troca(char *v, char c1, char c2){
  int i, x;
  i=0;
  char *p;
  
  x=strlen(v);
  p=(char*)malloc((x+1)*sizeof(char));
  strcpy(p, v);
  
  while(p[i]!=0){
    if(p[i]==c1)
      p[i]=c2;
    i++;
  }
  return p;
}

int main (int argc, char**argv){

  int c, p;
  char *z;

  if(argc!=4){
    printf(" <programa> <string> <carater> <carater>\n\n");
    return -1;
  }
  
  c=contador(argv[1], argv[2][0]);
  p=posicao(argv[1], argv[2][0]);
  z=troca(argv[1], argv[2][0], argv[3][0]);
  
  printf("\n%s repete-se %d vezes em %s\n", argv[2], c, argv[1]);
  
  if(p==-1)
    printf("-1 -> %s não se encontra em %s\nA string permanece inalterada.\n\n", argv[2], argv[1]);
  else{
    printf("A posição da primeira ocorrência de %s em %s é %d\n", argv[2], argv[1], p);
    printf("Nova string: %s\n\n", z);
  }
  
  return 0;
}
