#include<stdio.h>
int
main()
{
  float a, b, c, d;
    while( a<100.1)
 {
   b= a *1.8 +32;
   printf( "%6.2f ºC sao %6.2f ºF \n", a, b);
   a=a+1;
}
    return 0;
}
