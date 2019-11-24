#include<stdio.h>
int main()
{
  FILE *f1;
f1= fopen("jc03.01.txt","wt");


int a, b, c, teste;
printf("Tabuada?");
teste = scanf(" %d", &a);
printf("Leu: %d , (com teste: %d)\n\n", a, teste);

if(teste!=1)
{
printf("erro\n");
return -1;
}

c=0;
while(c<=10)
{
b=a*c;
printf("%d*%2d= %d\n", a, c, b);
fprintf(f1,"%d*%2d= %d\n", a, c, b);
c=c+1;
}
fclose(f1);
return 0;

}
