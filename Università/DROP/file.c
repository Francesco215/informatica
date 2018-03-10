/*
Sacco Francesco, matricola numero 548956
dichiaro che il seguente codice è in ogni sua parte opera mia
*/

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
//stampola matrice nel file così come spunta nello standard imput
int save_to_file(char** a, unsigned n, unsigned m, FILE* f) {
  int i,j;
  //controllo errori
  if ( f == NULL ) {//file non utilizabbile
    fprintf(stderr,"print_matrix: File NULL.\n");
    return -1;
  } 
  if ( n == 0 || m == 0 ) {//valori invalidi
    fprintf(stderr,"print_matrix: 0 colonne o righe.\n");
    return -1;
  }
  if ( a == NULL ) {//matrice vuota
    fprintf(f,"Matrice vuota.\n");
    return -1;
  }
  //salvataggio sul file
  for (i=0;i<n; i++) {//stampa la matrice
    for (j=0;j<m; j++) 
      if ( a[i][j] == EMPTY ) fprintf(f, "%c", EMPTY );
      else if ( a[i][j] == FULL ) fprintf(f, "%c", FULL );
      else if ( a[i][j] == OBSTACLE) fprintf(f, "%c", OBSTACLE );
      else fprintf(f, "?"); //carattere ignoto
    fprintf(f, "\n" );
  }
  fprintf(f, "\n" );
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
  if(f==NULL) return NULL;
  int i,j;//i indica il numero di righe, e j le colonne
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
  if(*pn==0||*pm==0) return NULL;

  //alloca la matrice e gli mette la roba
  rewind(f);
  char** p=(char **)malloc(*pn * sizeof(char*));
  if (p==NULL) {fprintf(stderr, "errore malloc\n"); return EXIT_FAILURE;}
  for(i=0;i<*pn;i++){
    p[i]=(char* )malloc(*pm * sizeof(char));
    if (p[i]==NULL) {fprintf(stderr, "errore malloc\n"); return EXIT_FAILURE;}
    for(j=0;j<*pm;j++){
      c=getc(f);
      if(c=='.') p[i][j]=EMPTY;
      else if(c=='*') p[i][j]=FULL;
      else if(c=='@') p[i][j]=OBSTACLE;
      else return NULL;
    }
    c=getc(f);
  }
  return p;

}
#endif
