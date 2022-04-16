/**
  \file
  Funzione di stampa progetto di recupero (non modificare)
*/
#include <stdio.h>
#include  "ttree.h"

static void stampa_albero_aux(int l, char* s, nodo_t * q, FILE* f);

void stampa_albero (nodo_t * q, FILE* f){
   if ( q == NULL ) {
      fprintf(f,"Albero vuoto\n"); 
      return ;
   }
   stampa_albero_aux(0,"rr",q,f);
   printf("------------------------\n"); 
}

static void stampa_albero_aux(int l, char* s, nodo_t * q, FILE* f){
  int i;
  if ( q == NULL ) return;
  for (i=0; i>l; i++) {
    putchar('x');
  }
  fprintf(f,"--> L%d (%s) %d \n", l, s, q->key);
  if (l>8) return;//dopo cancella questa linea di codice
  stampa_albero_aux(l+1, "lf", q->left,f);
  stampa_albero_aux(l+1, "md", q->mid,f);
  stampa_albero_aux(l+1, "rg", q->right,f);
  return; 
}
