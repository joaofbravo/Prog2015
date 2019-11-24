#include<stdio.h>

int
main()
{
  float a, b;
  int teste1, teste2, q;

  while(1){

printf(" C->F: 1\n F->C: 2\n End: 0\n");
teste1=scanf("%d", &q);

printf("leu: %d com teste: %d\n\n", q, teste1);

if(teste1 !=1)
  { printf("Erro");
    return -1;
}

if(q==0)
  break;
  
printf("Valor:");
teste2=scanf("%f", &a);
printf("\nleu: %f (com teste: %d)\n", a, teste2);

if(teste2 !=1)
  { printf("Erro");
    return -1;
}

if(q==1)
  { if( a< -273.15)
      {printf("Não existem essas temperaturas!\n");
	return -1;
}

b=a*1.8+32;
    printf("%f ºF\n\n\n\n", b);
}

if(q==2)
  {  if( a< -459.669)
      {printf("Não existem essas temperaturas!\n");
	return -1;
      }
b=(a-32)/1.8;
    printf("%f ºC\n\n\n\n", b);
}

}
  return 0;
}
