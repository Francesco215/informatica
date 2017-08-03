/*
  \file
  \authors informatica (CDS Fisica) 2016/17
  \brief assegnamento2/progetto di recupero: primo file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include "myrand.h"
#include "drop.h"

/* numeri di righe/colonne (Test1.1) */
#define N1 10
#define M1 20
#define N2 1000
#define M2 2000

/* verifica del generatore (Test2.1)*/
#define NTRIAL 1000
#define NHIST 19

/* seme */
#define SEED 42



int main (void) {
  int i, k;
  int hist[NHIST] = {0};
  char** a, **b;
 
  /* Test 1.1 */
  fprintf(stdout,"Test 1.1: \n");
 
  /* valori malformati */
  init_matrix(NULL,N1,M1);
  init_matrix(a,0,M1); 

  a = new_matrix(N1,M1);
  printf("suca\n");
  /* inizializzazione della matrice a EMPTY*/
  init_matrix(a,N1,M1);
 
  /* stampa */
  fprint_matrix(stdout,a,N1,M1);
  free_matrix(&a,N1);
  if (a != NULL) {
      fprintf(stderr,"Test 1.1: a puntatore non nullo \n");
    return EXIT_FAILURE;
  }
    /* Test 1.2 */
  fprintf(stdout,"Test 1.2: \n");

  a = new_matrix(N2,M2);
  b = new_matrix(N1,M2);
  
  /* inizializzazione della matrice a EMPTY*/
  init_matrix(a,N2,M2);
  init_matrix(b,N1,M2);

  /* stampa */
  fprint_matrix(stdout,a,N2,M2);
  fprint_matrix(stdout,b,N1,M2);
  free_matrix(&a,N2);
  free_matrix(&b,N1);
  
  if ( a != NULL || b != NULL ) {
    fprintf(stderr,"Test 1.1: a o b puntatore non nullo \n");
    return EXIT_FAILURE;
  }

 /* Test 1.2 */
  fprintf(stdout,"Test 1.2: istogramma \n");

  my_srand(SEED);
  
  for (i=0; i<NTRIAL; i++) {
    k = my_rand()%NHIST;
    hist[k]++;
  }

  /* stampa dell'istogramma */
  for (i=0; i<NHIST; i++) {
    printf("%d ", hist[i]);
  }
  putchar('\n');
 
  return 0;
}
  
