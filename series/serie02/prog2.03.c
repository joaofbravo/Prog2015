#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int x, y, a;
  char *v, *p;

  x= strlen(argv[1]);
  y= strlen(argv[2]);
     
  printf("1º Argumento= %s (tamanho: %d)\n2º Argumento= %s (tamanho: %d)\n\n", argv[1], x, argv[2], y);

  v=(char*)malloc((x+y+1)*sizeof(char));

  strcpy(v, argv[1]);
  strcat(v, argv[2]);

  printf("1º + 2º: %s\n\n", v);

  p=(char*)malloc((y+x+1)*sizeof(char));

  strcpy(p, argv[2]);
  strcat(p, argv[1]);

  printf("2º + 1º: %s\n\n", p);

  a= strcmp(v, p);

  if(a==0)
    printf("Os argumentos são iguais.\n\n");
  
  if(a<0)
    printf("O 1º argumento é menor que o 2º.\n\n");
  
  if(a>0)
    printf("O 2º argumento é menor que o 1º.\n\n");

  free(v);
  free(p);
  return 0;
}
