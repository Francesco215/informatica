/*
  \file
  \authors informatica (CDS Fisica) 2016/17
  \brief primo file di test
 */
#include <stdio.h>
#include "myrand.h"
#include "drop.h"

/* verifica del generatore */
#define NTRIAL 1000
#define NHIST 19

/* seme */
#define SEED 42



int main (void) {
  int i, a;
  int hist[NHIST] = {0};

  /* Test 1.1 */
  fprintf(stdout,"Test 1.0: \n");

  my_srand(SEED);
  for (i=0; i<NTRIAL; i++) {
    a = my_rand()%NHIST;
    hist[a]++;
  }

  /* stampa dell'istogramma */
  for (i=0; i<NHIST; i++) {
    printf("%d ", hist[i]);
  }
  putchar('\n');
  

  /* Test 1.2 */
  fprintf(stdout,"Test 1.1: \n");
  /* inizializzazione della matrice e del generatore pseudocasuale e stampa*/
  init_all(SEED);
  
  print_matrix();


  return 0;

}
