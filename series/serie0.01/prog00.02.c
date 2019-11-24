#include <stdio.h>
int
main()
{   
  int a,b;
  while( a <= 10 )
{
    b= 5*a;
    printf("5 * %2d = %d \n", a, b);
    a=a+1;
}
  return 0;
}

