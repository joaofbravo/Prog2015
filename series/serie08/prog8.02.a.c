#include<stdio.h>

int main(){
  int i;
  FILE *f1;
  short int v[65536];
  
  f1= fopen("spins.txt", "wb");
  
  for(i=0; i<65536; ++i)
    v[i]=i;    
  
  fwrite(v, sizeof(short int), 65536, f1);
    
  fclose(f1);
  return 0;
}
