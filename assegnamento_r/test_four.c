/*
  \file
  \authors informatica (CDS Fisica) 2016/17
  \brief assign2/progetto di recupero: quarto file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myrand.h"
#include "drop.h"

/* dimensioni della matrice */
#define N 20
#define M 35

/* lunghezza massima della stringa generata */
#define K 100
/* output file */
#define FILE1 "out_test4.txt"

/* ostacoli da inserire nella lista ordinata */
char* obst1[] = {
  "12 1 18 4",
  "18 20 19 34",
  "5 17 8 19",    
  "13 1 18 4",
  "18 22 19 34",
  "5 17 18 19",
  "12 1 19 4",
  "17 20 19 34",
  "5 2 8 3",
  NULL,
};

/* ostacoli da inserire nella lista ordinata e nella matrice*/
char* obst2[] = {
  "12 1 18 4",
  "18 20 19 34",
  "5 27 8 29",
  "16 18 18 22",
  NULL,
};




int main (void) {

  int i;
  char s[K];
  obstacle_t * p;
  FILE* f;
  /* lista inizialmente vuota */
  lista_t * lista = NULL;
  lista_t* plist;
  /* puntatore alla matrice */
  char ** mat;

  /* Test 4.1 */
  /* creazione della lista degli ostacoli ordinata */
  fprintf(stdout,"Test 4.1: \n");

  /*conversione ostacoli e inserimento in lista */
  for (i=0; obst1[i]!=NULL;i++) {
  	p = string_to_obstacle(obst1[i]);
  	if ( p == NULL || obstacle_to_string(p,s,K) == NULL )  {
   		fprintf(stderr,"test 4.1.1 --> fallito!\n");
   		return EXIT_FAILURE;
    }

  	/* sono uguali ? */
  	if ( strcmp(obst1[i],s) != 0 ) {
  		fprintf(stderr,"test 4.1.2 --> fallito!\n");
   		return EXIT_FAILURE;
  	}
    fprintf(stdout, "%s = %s\n", obst1[i], s);   
  	lista = put_obstacle_in_list(p,lista);
  }
  fprintf(stdout,"Lista ordinata: \n");
  fprint_list(stdout,lista);
  free_list(&lista);
   


  /* Test 4.2 */
  fprintf(stdout,"Test 4.2: \n");
 
  /*conversione ostacoli e inserimento in lista */
  for (i=0; obst2[i]!=NULL;i++) {
  	p = string_to_obstacle(obst2[i]);

  	if ( p == NULL || obstacle_to_string(p,s,K) == NULL )  {
       		fprintf(stderr,"test 4.2.1 --> fallito!\n");
       		return EXIT_FAILURE;
  	}

  	/* sono uguali ? */
  	if ( strcmp(obst2[i],s) != 0 ) {
       		fprintf(stderr,"test 4.2.2 --> fallito!\n");
       		return EXIT_FAILURE;
  	}
        fprintf(stdout, "%s = %s\n", obst2[i], s);
        
	lista = put_obstacle_in_list(p,lista);
   }
  f = fopen(FILE1,"w");
  if ( f == NULL ) {
    fprintf(stderr,"test 4.2.3 --> fallito!\n");
    return EXIT_FAILURE;
  }

   fprint_list(f,lista);
  
   mat = new_matrix(N,M);
   init_matrix(mat,N,M);

   for(plist = lista; plist != NULL; plist = plist->next)
     put_obstacle_in_matrix(plist->pobj,mat,N,M);


   fprint_matrix(f,mat,N,M);
   free_list(&lista);
   free_matrix(&mat,N);
   fclose(f);
  return 0;

}
