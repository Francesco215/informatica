/* 
\file
  \authors informatica (CDS Fisica) 2016/17
  \brief intestazione delle funzioni da implementare
 */
#include <stdio.h>
#include "myrand.h"

#ifndef __DROP__H
#define __DROP__H

#define N 41
#define M 50 
#define EMPTY ' '
#define FULL '*'

char mat[N][M]; 

void init_all (int seed){
  for(int i=0;i<=N;i++){
    for(int j=0;j<=M;j++){mat[i][j]=0;}
  }
  my_srand(seed);
}

void print_matrix (void){
  for(int i=0;i<=N;i++){
    for(int j=0;j<=M;j++){
      if(mat[i][j]==0){printf("%c",EMPTY);}
      else{printf("%c",FULL);}
    }
    printf("\n");
  }
}

/** calcola la caduta della prossima particella restituendo le coordinate (i,j) del prossimo elemento dell'area da mettere a FULL
 
   \param next_i l'indirizzo della variabile dove scrivere il valore della coordinata i
   \param next_j l'indirizzo della variabile dove scrivere il valore della coordinata j

   \SPECIFICA 
   il prossimo elemento da riempire viene calcolato simulando la caduta di una particella 
   a partire dalla posizione P0 di coordinate ( 0, M/2 ),
   ad ogni passo, se mi trovo nella posizione Pi = (i,j) considero l'insieme U delle celle non ancora piene fra la tre celle
              (i+1,j-1) (i+1,j) (i+1,j-1)
   e scelgo in modo equiprobabile fra le celle in U, ad esempio nel caso in cui le tre celle contengano rispettivamente
              EMPTY EMPTY FULL
   U = { (i+1,j-1), (i+1,j) }
   e scelgo fra i due elementi di U con probabilità 1/2.

   La caduta della particella si arresta quando di verifica uno dei due seguenti casi:
   1) sono arrivato all'ultima riga (la N-1) (quindi mi sedimento sul fondo)
   2) ho almeno una cella piena nell'intorno di (i,j)
              
                     (i,j-1)     (i,j)    (i,j+1)
                                (i+1,j)  

    in entrambi i casi restituisco in *next_i il valore di i e in 
    *next_j il valore di j

   \retval 0 se le coordinate sono state calcolate correttamente
   \retval -1 se il punto di caduta iniziale P0
    al centro della prima riga è già FULL in questo caso non viene modificato il valore di *next_i *next_j
*/ 
int step (int* next_i, int* next_j){
  //creo un wile loop che mi fa cadere il fiocco di neve mentre non confina con nessun altro fiocco di neve
  char giu=1;
  char fdestra=1;
  char mdestra=1;
  char fsinistra=1;
  char msinistra=1;
  if((mat[*next_i+1][*next_j]!=1)&&(*next_i<N-1)){giu=0;}
  if(mat[*next_i][*next_j+1]!=1){fdestra=0;}
  if(*next_j<M-1){mdestra=0;}
  if(mat[*next_i][*next_j-1]!=1){fsinistra=0;}
  if(*next_j>=0){msinistra=0;}
  //fiocchi accanto al fiocco, il fiocco viene bloccato ne viene creato uno nuovo all'origine
  if(fsinistra+giu+fdestra>0){
    *next_i=0;
    *next_j=M/2;
    mat[*next_i][*next_j]=1;
  }//caso in cui non ci nono fiocchi a lato
  else{
    //caso in cui il fiocco cade indisturbato
    if((mdestra==0)&&(msinistra==0)){
      int scelta=my_rand()%3;
      if(scelta==0){
        mat[*next_i][*next_j]=0;
        next_i++;
        mat[*next_i][*next_j]=1;
      }
      if(scelta==1){
        mat[*next_i][*next_j]=0;
        next_j++;
        mat[*next_i][*next_j]=1;
      }
      if(scelta==2){
        mat[*next_i][*next_j]=0;
        next_j--;
        mat[*next_i][*next_j]=1;
      }
    }
    //caso in cui il fiocco ha un muro a destra
    if(mdestra==1){
      int scelta=my_rand()%2;
      if(scelta==0){
        mat[*next_i][*next_j]=0;
        next_i++;
        mat[*next_i][*next_j]=1;
      }
      if(scelta==1){
        mat[*next_i][*next_j]=0;
        next_j--;
        mat[*next_i][*next_j]=1;
      }
    }
    //caso in cui il fiocco ha un muro a sinistra
    if(msinistra==1){
      int scelta=my_rand()%2;
      if(scelta==0){
        mat[*next_i][*next_j]=0;
        next_i++;
        mat[*next_i][*next_j]=1;
      }
      if(scelta==1){
        mat[*next_i][*next_j]=0;
        next_j++;
        mat[*next_i][*next_j]=1;
      }
    }
  }
}
#endif
