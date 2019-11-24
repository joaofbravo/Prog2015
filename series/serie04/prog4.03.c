#include<stdio.h>
#include<stdlib.h>
  
void show_help(){
  printf("\nTabela Periodica dos elementos (18 primeiros elementos)\n");
  printf("\nPara receber toda a informacao de um elemento escreva:\n");
  printf("\t<Nome do elemento>\n\n");
  printf("\nPara saber o valor de uma propriedade de um elemento escreva:\n");
  printf("\t<Nome do elemento> <Propriedade>\n\n");
  printf("\nPara saber o valor de uma propriedade para todos os elementos escreva:\n");
  printf("\t<Propriedade>\n\n");
  printf("Elementos:\t\tPropriedades:\n");
  printf("Hidrogenio\t\tnome\n");
   printf("Helio\t\t\tsimbolo\n");
   printf("Litio\t\t\tnumero_atomico\n");
   printf("Berilio\t\t\tmassa_atomica\n");
   printf("Boro\t\t\tponto_fusao\n");
   printf("Carbono\t\t\tponto_ebulicao\n");
   printf("Azoto\t\t\traio_atomico\n");
   printf("Oxigenio\t\tenergia_ionizacao\n");
   printf("Fluor\n");
   printf("Neon\n");
   printf("Sodio\n");
   printf("Magnesio\n");
   printf("Aluminio\n");
   printf("Silicio\n");
   printf("Fosforo\n");
   printf("Enxofre\n");
   printf("Cloro\n");
   printf("Argon\n\n");
   
  exit (-1);
}

typedef struct {
  char       nome[11];
  char       simbolo[3];
  int          n_atomico;
  double    massa_atom;
  double    pfusao;
  double    pebulicao;
  double    raio;
  double    energia1;        
} elem;

int main(int argc, char **argv){

  int i;

  if(argc!=3 && argc!=2)
    show_help();

  elem elemento[18] = {
    {"Hidrogenio", "H", 1, 1.00794, -259.2, -252.87, 25, 1312},
    {"Helio", "He", 2, 4.002602, -272.2, -268.93, 31, 2372},
    {"Litio", "Li", 3, 6.941, 180.5, 1342, 145, 520},
    {"Berilio", "Be", 4, 9.01218, 1287, 2469, 105, 899},
    {"Boro", "B", 5, 10.811, 2075, 4000, 85, 801},
    {"Carbono", "C", 6, 12.0107, 3550, 4289, 70, 1086},
    {"Azoto", "N", 7, 14.0067, -210, -198.79, 65, 1402},
    {"Oxigenio", "O", 8, 15.9994, -222.8, -182.97, 60, 1314},
    {"Fluor", "F", 9, 18.9984, -219.62, -188.12, 50, 1618},
    {"Neon", "Ne", 10, 20.1797, -248.6, -246.08, 38, 2081},
    {"Sodio", "Na", 11, 22.98976, 97.80, 883, 180, 496},
    {"Magnesio", "Mg", 12, 24.305, 650, 1090, 150, 738},
    {"Aluminio", "Al", 13, 26.981539, 660.32, 2519, 125, 578},
    {"Silicio", "Si", 14, 28.0855, 1414, 3265, 110, 786},
    {"Fosforo ", "P", 15, 30.973762, 44.15, 280.5, 100, 1012},
    {"Enxofre", "S", 16, 32.065, 115.21, 444.6, 100, 1000},
    {"Cloro", "Cl", 17, 35.453, -101.5, -34.04, 100, 1251},
    {"Argon", "Ar", 18, 39.948, -189.35, -185.85, 71, 1521}
  };

  for(i=0; i<18; ++i){
    if(argc==2 && strcmp(argv[1], elemento[i].nome)==0){
      printf ("\n  Nome:                           %s\n", elemento[i].nome);
      printf ("  Simbolo Quimico:                %s\n", elemento[i].simbolo);
      printf ("  Numero Atomico:                 %d\n", elemento[i].n_atomico);
      printf ("  Massa Atomica:                  %lf\n", elemento[i].massa_atom);
      printf ("  Ponto de Fusao:                 %lf\n", elemento[i].pfusao);
      printf ("  Ponto de Ebulicao:              %lf\n", elemento[i].pebulicao);
      printf ("  Raio Atomico:                   %lf\n", elemento[i].raio);
      printf ("  Energia de Primeira Ionizacao:  %lf\n", elemento[i].energia1);
    }
    
    if(argc==3 && strcmp(argv[1], elemento[i].nome)==0){
      if(strcmp(argv[2], "nome")==0)
	printf ("  Nome: %s\n", elemento[i].nome);
      if(strcmp(argv[2], "simbolo")==0)
	printf ("  Simbolo: %s\n", elemento[i].simbolo);
      if(strcmp(argv[2], "numero_atomico")==0)
	printf ("  Numero Atomico: %d\n", elemento[i].n_atomico);
      if(strcmp(argv[2], "massa_atomica")==0)
	printf ("  Massa Atomica: %lf\n", elemento[i].massa_atom);
      if(strcmp(argv[2], "ponto_fusao")==0)
	printf ("  Ponto de Fusao: %lf\n", elemento[i].pfusao);
      if(strcmp(argv[2], "ponto_ebulicao")==0)
	printf ("  Ponto de Ebulicao: %lf\n", elemento[i].pebulicao);
      if(strcmp(argv[2], "raio_atomico")==0)
	printf ("  Raio Atomico: %lf\n", elemento[i].raio);
      if(strcmp(argv[2], "energia_ionizacao")==0)
	printf ("  Energia de Primeira Ionizacao: %lf\n", elemento[i].energia1);
    }
}
  
  if(argc==2){
    if(strcmp(argv[1], "nome")==0){
      for(i=0;i<18;i++)
	printf ("%s\n", elemento[i].nome);
    }
    if(strcmp(argv[1], "simbolo")==0){
      for(i=0;i<18;i++)
	printf ("%s: %s\n", elemento[i].nome, elemento[i].simbolo);
    }
    if(strcmp(argv[1], "numero_atomico")==0){
      for(i=0;i<18;i++)
	printf ("%s: %d\n", elemento[i].nome, elemento[i].n_atomico);
    }
    if(strcmp(argv[1], "massa_atomica")==0){
      for(i=0;i<18;i++)
	printf ("%s: %lf\n", elemento[i].nome, elemento[i].massa_atom);
    }
    if(strcmp(argv[1], "ponto_fusao")==0){
      for(i=0;i<18;i++)
	printf ("%s: %lf\n", elemento[i].nome, elemento[i].pfusao);
    }
    if(strcmp(argv[1], "ponto_ebulicao")==0){
      for(i=0;i<18;i++)
	printf ("%s: %lf\n", elemento[i].nome, elemento[i].pebulicao);
    }
    if(strcmp(argv[1], "raio_atomico")==0){
      for(i=0;i<18;i++)
	printf ("%s: %lf\n", elemento[i].nome, elemento[i].raio);
    }
    if(strcmp(argv[1], "energia_ionizacao")==0){
      for(i=0;i<18;i++)
	printf ("%s: %lf\n", elemento[i].nome, elemento[i].energia1);
    }
  }

  printf("\n");
  return 0;
}
