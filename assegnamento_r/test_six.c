/*
  \file
  \authors informatica (CDS Fisica) 2016/17
  \brief progetto di recupero: sesto file di test
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myrand.h"
#include "drop.h"
#include "file.h"

/* limite stringa conversioni */
#define K 100

/* file di input (contiene ostacoli) */
#define INFILE1 "data6.txt"


/* dimensioni della matrice (area di caduta) */
#define N 20
#define M 35


/* numero passi simulazione */
#define NSTEP 10

/* attesa */
#define ATTESA usleep(100000);

/* output file */
#define OUTFILE1 "out_test6_1.txt"

/* primo output file */
#define OUTFILE2 "out_test6_2.txt"

/* secondo output file */
#define OUTFILE3 "out_test6_3.txt"


/* controlliamo scritture e letture da file */
int main (void) {
   int i, j, k;
   /* conterranno le dimensioni rilette da file */
   unsigned n,m;
  /* per le conversioni di stringa */
  char s[K];
  /* per salvare temporaneamente gli ostacoli */
  obstacle_t * p;
  FILE* f;
  lista_t* l=NULL, *plist;
  /* matrici per la simulazione e il confronto delle scritture su file */
  char** mat, ** mat2;

  /* Test 5.1 */
  fprintf(stdout,"Test 5.1: lettura ostacoli da file \n");

  /*leggere ostacoli da file e inserirli in lista ordinata*/
  /* aprire il file che contiene gli ostacoli in lettura */
  f = fopen(INFILE1,"r");

  if ( f == NULL ) {
       	fprintf(stderr,"test 5.1.1 --> fallito!\n");
       	return EXIT_FAILURE;
  }
fgets(s,K,f);
  while (s!= NULL ) {
        p = string_to_obstacle(s);
        fgets(s,K,f);
        /* scarta gli ostacoli mal formati */
	if (p != NULL ) l = put_obstacle_in_list(p,l);
        
  }
 
  fprint_list(stdout,l);
  fclose(f);

  /* Test 5.2 */
  fprintf(stdout,"Test 5.2: simulazione \n");

   mat = new_matrix(N,M);
   init_matrix(mat,N,M);

  /* inserimento ostacoli nella matrice */
  for(plist = l; plist != NULL; plist = plist->next)
     put_obstacle_in_matrix(plist->pobj,mat,N,M);
  /* libero la lista degli ostacoli */

  free_list(&l);
   /* simulazione adj BOTH*/
   for (k=0;k< NSTEP; k++) {
     /* calcolo prossimo passo */
     /* modifica matrice */
     if ( step(&i,&j,BOTH, mat,N,M) == -1 ) break;
     /* altrimenti ho un elemento da riempire */
     mat[i][j] = FULL;
     /* stampa */
     system("clear");
     printf("Drop step %d di %d\n", k + 1, NSTEP);
     fprint_matrix(stdout,mat,N,M);
     fprintf(stdout,"%s riempita posizione %d, %d\n", "BOTH", i, j);
     /* attesa eventuale */
#ifdef WAIT
       ATTESA 
#endif
   }

  /* Test 5.3 */
  fprintf(stdout,"Test 5.3: lettura e scrittura su file \n");

  /* aprire il primo file di output in scrittura */
   f = fopen(OUTFILE1,"w");
   if ( f == NULL ) {
       	fprintf(stderr,"test 5.3.1 --> fallito!\n");
       	return EXIT_FAILURE;
  }
   /* scrittura su file della matrice mat */
   i = save_to_file(mat,N,M,f);
   if ( i != 0 ) {
       	fprintf(stderr,"test 5.3.2 --> fallito!\n");
       	return EXIT_FAILURE;
  }

  fclose(f);
  

   /* ri-apre  il file in lettura */
   f = fopen(OUTFILE1,"r");
   if ( f == NULL ) {
       	fprintf(stderr,"test 5.3.3 --> fallito!\n");
       	return EXIT_FAILURE;
  }

  /* legge da file e crea una nuova matrice mat2 */
   mat2 = read_from_file (&n,&m,f);
   fclose (f);

  /* aprire il secondo file di output in scrittura */
   f = fopen(OUTFILE2,"w");
   if ( f == NULL ) {
       	fprintf(stderr,"test 5.3.4 --> fallito!\n");
       	return EXIT_FAILURE;
  }
  /* scrive sul secondo file la matrice mat2 appena letta */
   i = save_to_file(mat2,n,m,f);
   if ( i != 0 ) {
       	fprintf(stderr,"test 5.3.5 --> fallito!\n");
       	return EXIT_FAILURE;
  }
   
   /* le due matrici mat mat2 sono uguali ? */
   if (n != N || m != M ) {
       	fprintf(stderr,"test 5.3.6 --> fallito!\n");
       	return EXIT_FAILURE;
   }
   for (i=0; i<N; i ++)  
     for (j=0; j<M; j ++)  
      if (mat[i][j] != mat2[i][j])  {
       	fprintf(stderr,"mat [%d][%d] test 5.3.7 --> fallito!\n",i,j);
       	return EXIT_FAILURE;
  }

   free_matrix(&mat,n); 
   free_matrix(&mat2,N);
   fclose(f);
  return 0;
}
