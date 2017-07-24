/*
  \file
  \authors informatica (CDS Fisica) 2016/17
  \brief asegnamento2/progetto di recupero: quinto file di test
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


/* numero passi simulazione */
#define NSTEP 100

/* attesa */
#define ATTESA usleep(100000);

/* output file */
#define FILE1 "out_test5.txt"

/* ostacoli simulazione drop */
char* obst3[] = {
  "12 7 18 9",
  "18 20 19 34",
  "7 27 9 29",
  "16 22 18 27",
  "15 12 15 12",
  "15 13 15 14",
  NULL,
};

/* adiacenze (per la stampa) */
char * adjx[] = {
  "NONE",
  "CROSS",
  "DIAGONAL",
  "BOTH",
  NULL,
};

/* test di simulazione CON ostacoli con le 4 adiacenze NONE CROSS DIAGONAL BOTH */
int main (void) {

  int i,j,k;

  obstacle_t * p;
  /* lista inizialmente vuota */
  lista_t * lista = NULL;
  lista_t* plist;
  /* puntatore alla matrice */
  char ** mat;
  adj_t ad;
  FILE* f;
  
  /* Test 5.1 */
  fprintf(stdout,"Test 5.1: \n");

  /*conversione ostacoli e inserimento in lista */
  for (i=0; obst3[i]!=NULL;i++) {
  	p = string_to_obstacle(obst3[i]);
	lista = put_obstacle_in_list(p,lista);
   }

   f = fopen(FILE1,"w");
   if ( f == NULL ) {
     fprintf(stderr,"test 5.1.3 --> fallito!\n");
     return EXIT_FAILURE;
   }

   mat = new_matrix(N,M);

   for(ad=NONE; ad <= BOTH; ad++) {
     init_matrix(mat,N,M);
     /* inserimento ostacoli nella matrice */
     for(plist = lista; plist != NULL; plist = plist->next)
        put_obstacle_in_matrix(plist->pobj,mat,N,M);
     /* alla prima iterazione la scrivo anche su file */
     if (ad == NONE) fprint_matrix(f,mat,N,M);
     /* simulazione adj NONE CROSS DIAGONAL e BOTH */
     for (k=0;k< NSTEP; k++) {
       /* calcolo prossimo passo */
       /* modifica matrice */
       if ( step(&i,&j,ad, mat,N,M) == -1 ) break;
       /* altrimenti ho un elemento da riempire */
       mat[i][j] = FULL;
       /* stampa */
       system("clear");
       printf("Drop step %d di %d\n", k + 1, NSTEP);
       fprint_matrix(stdout,mat,N,M);
       fprintf(stdout,"%s riempita posizione %d, %d\n", adjx[ad], i, j);
       /* attesa eventuale */
#ifdef WAIT
       ATTESA 
#endif
	 }
   }


  
   free_list(&lista);
   free_matrix(&mat,N);
   fclose(f);

  return 0;

}
