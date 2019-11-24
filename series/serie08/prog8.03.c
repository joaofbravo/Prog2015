#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>
#include<sys/stat.h>
#include<locale.h>
#include<string.h>

void showhelp(){
  printf("\nPrograma que mostra ficheiros contidos numa diretoria.\n");
  printf("(Pode também mostrar o tamanho em bytes e a data em que foi alterado pela última vez)\n");
  printf("\n\tFicheiros: ./<programa> <diretoria>\n");
  printf("\n\tFicheiros com info: ./<programa> <-l> <diretoria>");
  printf("\n\n(para a própria diretoria, deixar esse parâmetro em branco)\n\n");
  
  exit(-1);
}

int main(int argc, char **argv){
 
#ifdef _WIN32
#define darinfo stat
  char b[2] = "\\";

#else
#define darinfo lstat 
  char b[2] = "/";

#endif

  DIR *d1;
  struct dirent *finfo;             //informaçoes ficheiros da diretoria
  struct stat fstat;                //informaçoes internas ao ficheiro
  struct tm *ftime; 
  char tempo[20], *a;
  int c, d;

  setlocale(LC_TIME, "pt_PT.UTF_8");

  switch(argc){
  case 1:
    d1=opendir("./");
     
    if(d1==NULL){
      printf("Falha ao abrir a diretoria.\n");
      showhelp();
    }
   
    while((finfo=readdir(d1)) != NULL)
      printf("%s\n", finfo->d_name);       //retorna nomes dos ficheiros

    break;

  case 2:
    if(strcmp(argv[1],"-l")==0){
      d1=opendir("./");                    //abre a diretoria "atual"

      if(d1==NULL){
	printf("\nFalha ao abrir a diretoria.\n");
	showhelp();
      }

      while((finfo=readdir(d1)) != NULL){
	darinfo(finfo->d_name, &fstat);    //dá informaçoes sobre o ficheiro para a struct fstat
        
	ftime = localtime(&fstat.st_mtime);  //dá informaçoes sobre a data para a struct ftime

        strftime(tempo, 20, "%b %d %H:%M", ftime);

	printf(" %9ld\t %s\t %s\n", fstat.st_size, tempo, finfo->d_name);
      }
    }    
    else{
      d1=opendir(argv[1]);
           
      if(d1==NULL){
	printf("\nFalha ao abrir a diretoria.\n");
	showhelp();
      }
      
      while((finfo=readdir(d1)) != NULL)
	printf("%s\n", finfo->d_name);
    }
    break;

  case 3:
    if(strcmp(argv[1],"-l")!=0)
      showhelp();

    d1=opendir(argv[2]);
   
    if(d1==NULL){
      printf("\nFalha ao abrir a diretoria.\n");
      showhelp();
    }
    
    c= strlen(argv[2]) + 100;
    a= (char *)malloc(c*sizeof(char));
    
    while((finfo=readdir(d1)) != NULL){  
      d= strlen(argv[2]) + 2 + strlen(finfo->d_name);
      
      if(d > c){
	a= (char *)realloc(a, c*sizeof(char));
	c=d;      
      }
	
      strcpy(a, argv[2]);               //Para saber info de um ficheiro que nao esta na directoria "actual"
      strcat(a, b);                     //é necessario colocar nome_da_diretoria/nome_do_ficheiro (argv[2]/finfo->d_name)
      strcat(a, finfo->d_name);              
      
      darinfo(a, &fstat);               //dá info sobre argv[2]/finfo->d_name 
      
      ftime = localtime(&fstat.st_mtime);
      
      strftime(tempo, 20, "%b %d %H:%M", ftime);
      
      printf("%9ld\t %s\t %s\n", fstat.st_size, tempo, finfo->d_name);
    }

    free(a);
    break;

  default:
    showhelp();
  }

  closedir(d1);
  return 0;
}
