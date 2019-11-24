#include <stdio.h>
int main()
{
  int a, b, c, i;
  FILE *f1;
  f1=fopen("jc03.01.txt", "rt");
  for(i=0; i<=10;++i)
{
  fscanf(f1,"%d*%2d= %d\n", &a, &c, &b);
  printf("%d*%2d= %d\n", a,c,b);
 }

  fclose(f1);
  return 0;
}
