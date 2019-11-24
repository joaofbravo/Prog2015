#include<stdio.h>

int main(){
  int i;
  FILE *f1;
    
  f1= fopen("spins.txt", "wt");
  for(i=0; i<65536; ++i)
    fprintf(f1, "%d\n", i);
    
  fclose(f1);
  return 0;
}
