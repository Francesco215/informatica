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
  int i;
  nodo_t * root=NULL;
  
  /* Test 5 */
  /* costruzione albero */
  for (i = 0; i< N; i++){
    inserisci(keys[i],&root);
  }
  
  cerca3(root);
  
  return 0;

}
