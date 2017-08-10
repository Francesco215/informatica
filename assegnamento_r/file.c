#ifndef __FILE__H
#define __FILE__H

#include <stdio.h>
#include "drop.h"
#include <string.h>
#include <stdlib.h>
#include "myrand.h"
/** salva su file l'attuale matrice di simulazione secondo un formato compatto a scelta dello studente
    (deve essere descritto nella relazione) 
    \param mat puntatore alla matrice
    \param n numero di righe
    \param m numero di colonne
    \param f file dove scrivere (già aperto in scrittura)

    \retval 0 se tutto è andato bene
    \retval -1 se si è verificato un errore

*/

int save_to_file(char** a, unsigned n, unsigned m, FILE* f) {
  fprint_matrix(f,a,n,m);
  return 0;
}

/** legge da file la matrice di simulazione secondo il formato compatto a scelta dello studente
    (deve essere descritto nella relazione) e crea una nuova matrice 
    
    \param pn alla fine della lettura conterrà il numero di righe
    \param pm alla fine della lettura conterrà numero di colonne
    \param f file dal quale leggere  (già aperto in lettura)

    \retval p (puntatore alla nuova matrice) se tutto è andato bene
    \retval NULL se si è verificato un errore (in questo caso *pn e *pm non vengono modificati)

*/
char** read_from_file (unsigned * pn, unsigned* pm, FILE * f){
  int i,j;
  char c='a';
  //serve per vedere quant'è grossa la matrice
  for(i=0;c!=EOF;i++){
    j=0;
    int k=0;
    for(j=0;c!='\n'&&c!=EOF;i++){
      c=getc(f);
      if(k>*pm) *pm=k;
      k++;
      if(c=='\n') (*pn)++;
    }
    c=getc(f);
  }

  //alloca la matrice e gli mette la roba
  rewind(f);
  char** p=(char **)malloc(*pn * sizeof(char*));
  for(i=0;i<*pn;i++){
    p[i]=(char* )malloc(*pm * sizeof(char));
    for(j=0;j<*pm;j++){
      c=getc(f);
      if(c=='.') p[i][j]=EMPTY;
      if(c=='*') p[i][j]=FULL;
      if(c=='@') p[i][j]=OBSTACLE;
    }
    c=getc(f);
  }
  return p;

}
#endif
