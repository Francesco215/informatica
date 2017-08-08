#ifndef __FILE__H
#define __FILE__H

#include <stdio.h>
#include "drop.h"
#include <string.h>
#include <stdlib.h>
/** salva su file l'attuale matrice di simulazione secondo un formato compatto a scelta dello studente
    (deve essere descritto nella relazione) 
    \param mat puntatore alla matrice
    \param n numero di righe
    \param m numero di colonne
    \param f file dove scrivere (già aperto in scrittura)

    \retval 0 se tutto è andato bene
    \retval -1 se si è verificato un errore

*/
int save_to_file (char** mat, unsigned n, unsigned m, FILE* f){
    fprint_matrix (f,mat,n,m);
    fclose(f);
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
  char s[50];
  unsigned i;
  for(i=1;fgets(s,50,f)!=NULL;i++){
    if(i==1) *pm=strlen(s);
    if(*pm!=strlen(s)){
      fprintf(stderr,"righe di lunghezza diversa\n");
      return NULL;}
      fgets(s,50,f);
      (*pn)=i;
  }

  char** p=(char **)malloc(*pn * sizeof(char*));
  for(int i=0;i<*pn;i++){
    p[i]=(char* )malloc(*pm * sizeof(char));
    fgets(s,50,f);
    printf("%s\n",s);
    for(int j=0;j<*pm;j++){
      if(s[j]=='.') p[i][j]=EMPTY;
      if(s[j]=='*') p[i][j]=FULL;
      if(s[j]=='@') p[i][j]=OBSTACLE;
    }
  }
  return p;

}
#endif
