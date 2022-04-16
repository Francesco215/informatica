/*
  \file
  \authors informatica (CDS Fisica) 2017/18
  \brief PR: terzo file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ttree.h"


#define N 16
int keys[N] = {
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
  int i,j,n;
  nodo_t * root=NULL;
  
  /* Test 3.1 */
  fprintf(stdout,"Test 3.1: \n");

  /* costruzione albero */
  for (i = 0; i< N; i++){
    inserisci(keys[i],&root);
  }

 /* cancellazione  di tutti i nodi in ordine di inserzione */
 
  for (i=0; i<N; i++){
    fprintf(stdout,"\ncancello %d -----------------------\n",keys[i]);
    cancella(keys[i],&root);
  
    stampa_albero(root,stdout);
 
  }

  /* test cancellazione random */

  /* costruzione albero */
  for (i = 0; i< N; i++){
    inserisci(keys[i],&root);
  }

  srand(time(NULL));

  /* cancellazione in ordine casuale di tutti i nodi */
  n = N;
  for (i=0; i<N; i++){
    j = rand()%n;
    fprintf(stdout,"\ncancello %d -----------------------\n",keys[j]);
    cancella(keys[j],&root);
    stampa_albero(root,stdout);
    keys[j]=keys[n-1];
    n--;
  }

  return 0;

}
