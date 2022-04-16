/*
  \file
  \authors informatica (CDS Fisica) 2017/18
  \brief PR: secondo file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include "ttree.h"

/* numero valori da inserire */
#define N 16000
/* valori intervallo generazione casuale */
#define A (-200)
#define B (201)



int main (void) {
  /* albero vuoto */
  nodo_t* root = NULL;
  int i, x;
  

  /* Test 2.1 */
  fprintf(stdout,"Test 2.1: \n");

  /* stress test inserimento/stampa free*/
  srand(time(NULL));

  /* test inserimento*/
  for (i = 0; i< N; i++){
    x = A + rand()%B;
    inserisci(x,&root);
  }

  stampa_albero(root,stdout);

   free_albero(&root);

   return 0;

}

