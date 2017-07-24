/*
  \file
  \authors informatica (CDS Fisica) 2016/17
  \brief secondo file di test
 */
#include <stdio.h>
#include <unistd.h>
#include "myrand.h"
#include "drop.h"

/* seme */
#define SEED 42

/* numero passi simulazione */
#define NSTEP 30

/* attesa */
#define ATTESA usleep(100000);


int main (void) {
  int i, j, k;


  /* Test 2.1 */
  fprintf(stdout,"Test 2.1: \n");
  /* inizializzazione della matrice e del generatore pseudocasuale e stampa*/
  init_all(SEED);
  
  print_matrix();

  /* Test 2.2 */
  fprintf(stdout,"Test 2.2: \n");
  /* simulazione */
     for (k=0;k< NSTEP; k++) {
   /* calcolo prossimo passo */
   /* modifica matrice */
   if ( step(&i,&j) == -1 ) break;
   /* altrimenti ho un elemento da riempire */
   mat[i][j] = FULL;
   /* stampa */
   system("clear");
   printf("Drop step %d di %d\n", k + 1, NSTEP);
   print_matrix();
   printf("riempita posizione %d, %d\n",i, j);
   /* attesa eventuale */
   #ifdef WAIT
   ATTESA 
   #endif
   }

  return 0;

}
