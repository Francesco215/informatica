/*
  \file
  \authors informatica (CDS Fisica) 2017/18
  \brief PR quarto file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include "ttree.h"

#define FILEDUMP "dump.txt"
#define FILE1 "out41.txt"
#define FILE2 "out42.txt"
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
  FILE * fd;
  nodo_t * root = NULL;

  
  /* Test 4.1 */
  fprintf(stdout,"Test 4.1: \n");
  
   /* costruzione albero */
  for (i = 0; i< N; i++){
    inserisci(keys[i],&root);
  }
  /* stampa albero */
  stampa_albero(root,stdout);

  /* salva stampa su file */
  if ( ( fd = fopen(FILE1,"w") ) == NULL ) {
    perror("fopen:");
    return EXIT_FAILURE ;
  }

    stampa_albero(root,fd);
    fclose(fd);

  /* scrittura su file */
  if ( ( fd = fopen(FILEDUMP,"w") ) == NULL ) {
    perror("fopen:");
    return EXIT_FAILURE ;
  }

  /* scrittura su file descriptor non valido */
  if ( scrivi_albero(NULL,root) != -1 )
    return EXIT_FAILURE;
      printf("aaaa\n");


  if ( scrivi_albero(fd,root) != 0 )
    return EXIT_FAILURE;

  /* fine scrittura */
  free_albero(&root);
  fclose(fd);

  /* lettura da file */
  if ( ( fd = fopen(FILEDUMP,"r") ) == NULL ) {
    perror("fopen:");
    return EXIT_FAILURE ;
  }

  leggi_albero(fd,&root);

  /* fine lettura */
  fclose(fd);
  
  /* stampa albero */
  stampa_albero(root,stdout);

  /* salva stampa su file */
  if ( ( fd = fopen(FILE2,"w") ) == NULL ) {
    perror("fopen:");
    return EXIT_FAILURE ;
  }

  stampa_albero(root,fd);

  fclose(fd);


  free_albero(&root);



  return 0;
}

