#include<stdio.h>

void convert(int r, int n, char *c){
  int i, j, q, d=1, x;
  char c0;
  
  if(r==2){
    for(i=0; i<8; ++i)
      c[i]='0';
    
    c[i]=0;
  }
  if(r==16){
    for(i=0; i<2; ++i)
      c[i]='0';
    
    c[i]=0;
  }
  if(r==8){
    for(i=0; i<3; ++i)
      c[i]='0';
 
    c[i]=0;
  }


  for(j=0; d!=0; ++j){
    d=n/r;
    x=n%r;
    n=d;
    
    if(x >= 10)
      c[j]= 'A' - 10 + x;
    else
      c[j]= '0' + x;
  }
  
  for(q=0; q<i/2;++q){
    c0=c[q];
    c[q]=c[i-q-1];
    c[i-q-1]=c0;
  }
}


int main(){
  int i;
  char b[9], o[4], h[3];

  for(i=0; i<256; ++i){
    convert(2, i, b);
    convert(8, i, o);
    convert(16, i, h);

    printf("%3d  %8s  %3s  %2s\n", i, b, o, h);
  }

  printf("\n");
  return 0;
}
