/*
  \file
  \authors informatica (CDS Fisica) 2016/17
  \brief assign2/progetto di recupero: terzo file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myrand.h"
#include "drop.h"

/* dimensioni della matrice */
#define N 15
#define M 15

/* lunghezza delle stringhe degli oggetti di test */


/* lunghezza massima della stringa generata */
#define K 100
/* output file */
#define FILE1 "out_test3.txt"

/* stringhe corrette che rappresentano oggetti */
char* good[] = {
  "1 1 3 4",
  "2 4 7 4",
  "5 7 8 8",
  "5 8 10 14",
  NULL,
};

/* stringhe scorrette che rappresentano oggetti */
char * bad[] = {
  "51 7 8 9000",
  "567 89 0 4",
  "-1 5 6 7",
  NULL
};

/* test sulla conversione di ostacoli e sul piazzamento degli ostacoli 
   nell'area di caduta*/
int main (void) {

  /* controllo conversioni da stringa a oggetto e viceversa */
  int i;
  char s[K + 1];
  obstacle_t * p;
  FILE* f;
  char ** mat;

  /* Test 3.1 */
  fprintf(stdout,"Test 3.1: \n");

  /*test su ostacoli ben formati */
  for (i=0; good[i]!=NULL;i++) {
  	p = string_to_obstacle(good[i]);
    
  	if ( p == NULL || obstacle_to_string(p,s,K) == NULL )  {
       		fprintf(stderr,"test 3.1.1 --> fallito!\n");
       		return EXIT_FAILURE;
  	}

  	/* sono uguali ? */
  	if ( strcmp(good[i],s) != 0 ) {
       		fprintf(stderr,"test 3.1.2 --> fallito!\n");
       		return EXIT_FAILURE;
  	}
        fprintf(stdout, "%s = %s\n", good[i], s);
	/* l'oggetto puntato da p non serve piu' */
	free(p);
   }

  /*test su ostacoli mal formati */
  for (i=0;  bad[i]!=NULL;i++) {
  	p = string_to_obstacle(bad[i]);
  	if ( p != NULL )  {
       		fprintf(stderr,"test 3.1.3 --> fallito!\n");
       		return EXIT_FAILURE;
  	}

  	
        fprintf(stdout, "%s = bad\n", bad[i]);
   }


  /* Test 3.2 */
  fprintf(stdout,"Test 3.2: \n");
 
  /*inserisco gli ostacoli ben formati in un'area di caduta */
  mat = new_matrix(N,M);
  init_matrix(mat,N,M);

  for (i=0;  good[i]!=NULL;i++) {
  	p = string_to_obstacle(good[i]);
        fprintf(stdout, "%s\n",good[i]);
        put_obstacle_in_matrix(p,mat,N,M);
        fprint_matrix(stdout,mat,N,M);
	/* l'ostacolo puntato da p non serve piu' */
	free(p);
	
  }

  f = fopen(FILE1,"w");
  if ( f == NULL ) {
       		fprintf(stderr,"test 3.2.1 --> fallito!\n");
       		return EXIT_FAILURE;
  	}

  fprint_matrix(f,mat,N,M);

  /* deallochiamo la matrice e chiudiamo il file */
  free_matrix(&mat,N);
  fclose(f);
  
  return 0;

}
