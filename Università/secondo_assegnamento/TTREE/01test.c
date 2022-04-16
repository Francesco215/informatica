/*
  \file
  \authors informatica (CDS Fisica) 2017/18
  \brief PR: primo file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include "ttree.h"


#define N 16

const int keys[N] = {
  12,
  45,
  56,
  78,
  4,
  56,
  9,
  6,
  9,
  -9,
3,
-22,
3,
9,
56,
51,
};


int main (void) {
  /* albero vuoto */
  nodo_t* root = NULL;
  int i;
  

  /* Test 1.1 */
  fprintf(stdout,"Test 1.1: \n");

  /* chiamata errata */
  inserisci(0,NULL);

  /* albero vuoto */
  stampa_albero(root,stdout);

  /* test inserimento*/
  for (i = 0; i< N; i++){
    inserisci(keys[i],&root);
  }

  stampa_albero(root,stdout);
  /* Test 1.2 */
  fprintf(stdout,"Test 1.2: \n");

  /* deallocazione albero e annullamento puntatore */
  free_albero(&root);
 
  if ( root != NULL ) return 1;

  return 0;

}

