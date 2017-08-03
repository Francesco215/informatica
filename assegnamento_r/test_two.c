/*
  \file
  \authors informatica (CDS Fisica) 2016/17
  \brief assegnamento2/progetto di recupero: secondo file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "drop.h"

/* dimensioni area di caduta */
#define N 25
#define M 41

/* numero passi simulazione */
#define NSTEP 30

/* attesa */
#define ATTESA usleep(100000);

/* test di simulazione senza ostacoli con le 4 adiacenze NONE CROSS DIAGONAL BOTH */
int main (void) {
  int i, j, k;
  char **mat;

  /* Test 2.1 */
  fprintf(stdout,"Test 2.1: \n");
  /* creazione, inizializzazione e stampa */
  mat = new_matrix(N,M);
  init_matrix(mat,N,M);
  fprint_matrix(stdout,mat,N,M);
    
  /* simulazione adj NONE */
    for (k=0;k< NSTEP; k++) {
      /* calcolo prossimo passo */
      /* modifica matrice */
      if ( step(&i,&j,NONE, mat,N,M) == -1 ) break;
      /* altrimenti ho un elemento da riempire */
      mat[i][j] = FULL;
      /* stampa */
      system("clear");
      printf("Drop step %d di %d\n", k + 1, NSTEP);
      fprint_matrix(stdout,mat,N,M);
      printf("NONE riempita posizione %d, %d\n",i, j);
      /* attesa eventuale */
      #ifdef WAIT
      ATTESA 
      #endif
    }
  
   free_matrix(&mat,N);

  /* Test 2.2 */
  fprintf(stdout,"Test 2.2: \n");
  /* creazione, inizializzazione e stampa */
  mat = new_matrix(N,M);
  init_matrix(mat,N,M);
  fprint_matrix(stdout,mat,N,M);

  /* simulazione adj NONE */
     for (k=0;k< NSTEP; k++) {
   /* calcolo prossimo passo */
   /* modifica matrice */
   if ( step(&i,&j,CROSS, mat,N,M) == -1 ) break;
   /* altrimenti ho un elemento da riempire */
   mat[i][j] = FULL;
   /* stampa */
   system("clear");
   printf("Drop step %d di %d\n", k + 1, NSTEP);
   fprint_matrix(stdout,mat,N,M);
   printf("CROSS riempita posizione %d, %d\n",i, j);
   /* attesa eventuale */
   #ifdef WAIT
   ATTESA 
   #endif
   }
  
   free_matrix(&mat,N);

  /* Test 2.3 */
  fprintf(stdout,"Test 2.3: \n");
  /* creazione, inizializzazione e stampa */
  mat = new_matrix(N,M);
  init_matrix(mat,N,M);
  fprint_matrix(stdout,mat,N,M);

  /* simulazione adj NONE */
     for (k=0;k< NSTEP; k++) {
   /* calcolo prossimo passo */
   /* modifica matrice */
   if ( step(&i,&j,DIAGONAL, mat,N,M) == -1 ) break;
   /* altrimenti ho un elemento da riempire */
   mat[i][j] = FULL;
   /* stampa */
   system("clear");
   printf("Drop step %d di %d\n", k + 1, NSTEP);
   fprint_matrix(stdout,mat,N,M);
   printf("DIAGONAL riempita posizione %d, %d\n",i, j);
   /* attesa eventuale */
   #ifdef WAIT
   ATTESA 
   #endif
   }
  
   free_matrix(&mat,N);

  /* Test 2.4 */
  fprintf(stdout,"Test 2.4: \n");
  /* creazione, inizializzazione e stampa */
  mat = new_matrix(N,M);
  init_matrix(mat,N,M);
  fprint_matrix(stdout,mat,N,M);

  /* simulazione adj NONE */
     for (k=0;k< NSTEP; k++) {
   /* calcolo prossimo passo */
   /* modifica matrice */
   if ( step(&i,&j,BOTH, mat,N,M) == -1 ) break;
   /* altrimenti ho un elemento da riempire */
   mat[i][j] = FULL;
   /* stampa */
   system("clear");
   printf("Drop step %d di %d\n", k + 1, NSTEP);
   fprint_matrix(stdout,mat,N,M);
   printf("BOTH riempita posizione %d, %d\n",i, j);
   /* attesa eventuale */
   #ifdef WAIT
   ATTESA 
   #endif
   }
  
   free_matrix(&mat,N);
  return 0;

}
