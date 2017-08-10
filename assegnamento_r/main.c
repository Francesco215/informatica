#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "myrand.h"
#include "drop.h"
#include "file.h"


int n_iter=0;
adj_t adiacenza=NONE;
FILE* infile=NULL;
unsigned N=0,M=0;
FILE* ostacoli=NULL;
FILE* outfile=NULL;
char **mat;
lista_t* lista=NULL;

char* help="inserire aiuto";
int dim=0,f=0;
int main(int argc, char **argv){
	//inizializzazione argomenti
	for(int i=1;i<argc;i++){
		int n=atoi(argv[i]);
		if(n!=0 && strcmp(argv[i-1],"-n")==0) N=n,dim++;
		else if(n!=0 && strcmp(argv[i-1],"-m")==0) M=n,dim++;
		else if(strcmp(argv[i-1],"-a")==0){
			if(strcmp(argv[i],"NONE")==0) adiacenza=NONE;
			else if(strcmp(argv[i],"CROSS")==0) adiacenza=CROSS;
			else if(strcmp(argv[i],"DIAGONAL")==0) adiacenza=DIAGONAL;
			else if(strcmp(argv[i],"BOTH")==0) adiacenza=BOTH;
			else {
				fprintf(stderr, "Argomento per l'adiacenza invalido\n");
				return EXIT_FAILURE;
			}
		}
		else if(strcmp(argv[i-1],"-f")==0) {
			infile=fopen(argv[i],"r");
			mat=read_from_file(&N,&M,infile);
			f=2;
		}
		else if(strcmp(argv[i-1],"-u")==0) ostacoli=fopen(argv[i],"r");
		else if(strcmp(argv[i-1],"-o")==0) outfile=fopen(argv[i],"w");	
		else if(n!=0) n_iter=n;
		else if(strcmp(argv[i],"help")==0 || strcmp(argv[i],"Help")==0 || strcmp(argv[i],"HELP")==0) printf("%s\n",help);
	}




	//controllo errori
	if(f+dim>2){
		fprintf(stderr, "Argomenti invalidi, inzerire o solo il file di imput o solo la dimenzione della matrice\n");
		return EXIT_FAILURE;
	}
	if(n_iter==0){
		fprintf(stderr, "inserire il numero di passi\n");
		return EXIT_FAILURE;
	}
	if(f+dim<2){
		fprintf(stderr, "inserire le dimenzioni della matrice o il file di imput\n");
	}


	//inizializzo la matrice
	if(infile==NULL){
		mat=new_matrix(N,M);
		init_matrix(mat,N,M);
	}


	//caso in cui c'è il file degli ostacoli
	if(ostacoli!=NULL && infile==NULL){
		char c,s[50];
		int n_righe=0;
		obstacle_t* p;
		
		while((c=getc(ostacoli))!=EOF){
			if(c=='\n') n_righe++;
		}
		rewind(ostacoli);
		printf("--------%d\n",n_righe);
		for(int i=1;i<n_righe;i++){
			printf("i=%d\n",i);
			fgets(s,50,ostacoli);
			p=string_to_obstacle(s);
			put_obstacle_in_list(p,lista);
			put_obstacle_in_matrix(p,mat,N,M);
		}
		fprint_list(stdout,lista);
	}



	//caso in cui c'è l'infile
	if(infile!=NULL && ostacoli==NULL && M==0 && N==0) mat=read_from_file(&N,&M,infile);
	//faccio i passi e stampo la matrice
	for(int passi=0;passi<n_iter;passi++){
		int i,j;
		if(step(&i,&j,adiacenza,mat,N,M)==-1) break;
		mat[i][j]=FULL;
		system("clear");
   	fprint_matrix(stdout,mat,N,M);
   	printf("Drop step %d di %d\n",passi+1,n_iter);
    printf("riempita posizione %d, %d\n",i,j);
	}
	if(outfile!=NULL){
		save_to_file(mat,N,M,outfile);
	}
	
	return 0;
}
