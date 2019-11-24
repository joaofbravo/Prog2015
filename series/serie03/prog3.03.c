#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Função strlen:
int comp(char *v){
  int i=0;
  
  while(v[i]!=0)
    i++;
  
  return i;
}

//Função strcpy:
char* copia(char *v, char *c){
  int i=0;
  
  while(c[i]!=0){
    if(v[i]!=c[i])
      v[i]=c[i];
    
    i++;
  }
  
  v[i]=0;
  return v;
}

//Função strcat:
char* cat1(char *v, char *c){
  int i, j;
  i=0;
  j=0;
  
  while(v[i]!=0)
    ++i;
  
  while(c[j]!=0){
    v[i]=c[j];
    i++;
    j++;
  }
  
  v[i]=0;
  return v;
}

//Função strcat só com strlen e strcpy:
char* cat2(char *v, char *c){
  int x;
  
  x=strlen(v);
  strcpy(v+x, c);
  
  return v;
}

int main(int argc, char **argv){

  int x, y;
  char *p;
  
  if(argc!=3){
    printf("Dê 3 argumentos.\n\n");
    return -1;
  }
  
  x=comp(argv[1]);
  y=comp(argv[2]);
  
  p=(char*)malloc((x+y+1)*sizeof(char));
  
  copia(p,argv[1]);
  
  printf("\nComprimento de %s: %d \nComprimento de %s: %d\n", argv[1], x, argv[2], y);
  printf("Cópia de %s para uma nova string: %s\n", argv[1], p);
  
  cat1(p, argv[2]);
  printf("Concatenamento 1 de %s e %s: %s\n", argv[1], argv[2], p); 

  copia(p,argv[1]);
  
  cat2(p, argv[2]);
  printf("Concatenamento 2 de %s e %s: %s\n\n", argv[1], argv[2], p);

  free(p);
  return 0;
}
