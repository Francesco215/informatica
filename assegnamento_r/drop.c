/* 
\file
  \authors informatica (CDS Fisica) 2016/17
  \brief progetto di recupero: intestazione delle funzioni da implementare
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "myrand.h"

/* protezione inclusioni multiple */
#ifndef __DROP__H
#define __DROP__H

/* ATTENZIONE: l'area di caduta e' rappresentata con una matrice di puntatori 
   a righe e NON e' globale come era nel primo assegnamento */



/** tipo delle 4 adiacenze 
    con cui stiamo lavorando (nessuna, croce, diagonale, entrambe) */
typedef enum {NONE, CROSS, DIAGONAL, BOTH} adj_t;

/** valori possibili per la matrice che rappresenta l'area di caduta, EMPTY contraddistingue un'area vuota, FULL un'area un cui si e' gia' sedimentata una
particella e OSTACLE rappresenta un'area occupata da un ostacolo. FULL ed OBSTACLE non sono attraversabili*/
#define EMPTY '.'
#define FULL '*'
#define OBSTACLE '@'

/** ogni ostacolo e' quadrato o rettangolare e definito dalle coordinate dell'estremo in alto a sinistra e in basso a destra all'interno della matrice che rappresenta l'area di caduta. s_i deve sempre essere minore o uguale di d_i e s_j minore uguale di d_j */
typedef struct {
  unsigned s_i, s_j; /* coordinate dell'angolo in alto a sinistra */
  unsigned d_i, d_j; /* coordinate dell'angolo in basso a destra */
} obstacle_t;

/** Lista degli ostacoli, sempre ordinata in senso crescente. L'ordinamento 
e' definito come segue:

L'ostacolo [(x1,y1),(t1,q1)] precede [(x2,y2),(t2,q2)] se vale che
se x1!= x2 e x1 < x2 oppure
se x1 == x2 e y1!= y2 e y1 < y2 oppure
se x1 == x2 e y1 == y2 e t1!= t2 e t1 < t2 oppure
se x1 == x2 e y1 == y2 e t1 == t2 e q1!= q2 e q1 < q2
*/
typedef struct list  {
  obstacle_t * pobj; /* puntatore all'ostacolo */
  struct list * next; /* puntatore al prossimo elemento della lista */
} lista_t;

/** inizializza la matrice mat settando tutti i valori a EMPTY
   
   \param mat puntatore alla matrice 
   \param n numero di righe
   \param m numero di colonne
*/

void init_matrix (char** mat, unsigned n, unsigned m){
  if(mat==NULL||n==0||m==0){
    fprintf(stderr,"matrice malformata\n");
    mat=NULL;
    return;
  }
  for(int a=0;a<n;a++){
    for (int b=0;b<m;b++){
      mat[a][b]=EMPTY;
    }
  }
  
}

/** libera la memoria occupata dalla matrice e mette a NULL il puntatore pmat

    \param pmat puntatore al puntatore alla matrice da liberare
    \param n numero di righe
 */
void free_matrix (char*** pmat, unsigned n){
  for(int i=0;i<n;i++) free((*pmat)[i]);
  free(*pmat);
  *pmat=NULL;
}

/** calcola la caduta della prossima particella restituendo le coordinate (i,j) del prossimo elemento dell'area da mettere a FULL
 
   \param next_i l'indirizzo della variabile dove scrivere il valore della coordinata i
   \param next_j l'indirizzo della variabile dove scrivere il valore della coordinata j
   \param ad tipo di adiacenza con cui stiamo lavorando (croce, diagonale o entrambe)
   \param mat puntatore alla matrice 
   \param n numero di righe della matrice
   \param m numero di colonne della matrice

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
   2) U e' vuoto
   3) ho almeno una cella piena nell'intorno di (i,j) definito da dall'adiacenza "ad" ovvero
      a) nessuno (NONE): in questo caso mi fermo solo se (i+1,j), (i+1,j-1) e (i+1,j+1) sono gia' piene (U e' vuoto)
      b) croce (CROSS):
                (i-1,j)
     (i,j-1)     <i,j>    (i,j+1)
                (i+1,j)  
      c) diagonale (DIAGONAL)
     (i-1,j-1)            (i-1,j+1)
                 <i,j>    
     (i+1,j-1)            (i+1,j+1)
     d) croce e diagonale insieme (BOTH)
     (i-1,j-1)   (i-1,j)        (i-1,j+1)
      (i,j-1)     <i,j>          (i,j+1)
     (i+1,j-1)   (i+1,j)        (i+1,j+1)

   In tutti i casi --> restituisco in *next_i 
   il valore di i e in *next_j il valore di j

   \retval 0 se le coordinate sono state calcolate correttamente
   \retval -1 se il punto di caduta iniziale P0
    al centro della prima riga è già FULL  
    in questo caso non viene modificato il valore di *next_i *next_j

*/ 
int step (int* next_i, int* next_j, adj_t ad, char** mat, int n, int m){
  static int a=0;
  if(a==0){
    *next_i=0;
    *next_j=m/2;
    a=4;
    srand(time(NULL));
  }
  //gestione parametri invalidi
  if(mat==NULL||n<=0||m<=0){
    fprintf(stderr,"parametri non validi\n");
    return -1;
  }
  //entrata bloccata
  if(mat[0][m/2]==FULL) return -1;
  //calcolo passi
  (*next_i)++;

  //ysnp è un vettore che indica le posizioni libere
  int ysnp[3]={(*next_j)-1,*next_j,(*next_j)+1};
  if(*next_j==0 || mat[*next_i][(*next_j)-1]==FULL) ysnp[0]=1;
  if(*next_j==m-1 || mat[*next_i][(*next_j)+1]==FULL) ysnp[2]=1;
  if(mat[*next_i][*next_j]==FULL) ysnp[1]=1;
  int len=ysnp[0]+ysnp[1]+ysnp[2];
  int asd[len];
  for(int i=0;i<len;i++){
    int j=0;
    if(ysnp[i]!=1){
      asd[j]=ysnp[i];
      j++;
    }
  }
  *next_j=asd[rand()%len];

  if(*next_i==n-1) return 0;//lo metto prima per evitare la segmentation
  // controllo[0] vale 0 se non vi sono elementi lungo la croce, 1 se ce ne sono 
  // controllo[1] vale 0 se non vi sono elementi lungo la diagonale, 1 se ce ne sono
  int controllo[2]={0,0};
  if(mat[(*next_i)+1][*next_j]==FULL || mat[(*next_i)-1][*next_j]==FULL || mat[*next_i][(*next_j)+1]==FULL || mat[*next_i][(*next_j)-1]==FULL) controllo[0]=1;
  if(mat[(*next_i)+1][(*next_j)+1]==FULL || mat[(*next_i)-1][(*next_j)-1]==FULL || mat[(*next_i)-1][(*next_j)+1]==FULL || mat[(*next_i)+1][(*next_j)-1]==FULL) controllo[1]=1;

  //calcolo quando fermarmi
  if(ad==NONE && (mat[(*next_i)+1][*next_j]==FULL||mat[(*next_i)+1][*next_j]==OBSTACLE)) return 0; //controlla se è corretto
  if(ad==CROSS && controllo[0]==1) return 0;
  if(ad==DIAGONAL && controllo[1]==1) return 0;
  if(ad==BOTH && controllo[0]==1 && controllo[1]==1)return 0;
  printf("%d  %d\n",*next_j,*next_i);
  step(next_i,next_j,ad,mat,n,m);
  a=0;
}



/** legge la rappresentazione di un ostacolo come stringa di 4 estremi interi 
    (es. "0 0 3 4" rapresenta i due estremi (0,0) superiore sinistro e (3,4) inferiore destro)
    e crea sullo heap la corrispondente struttura obstacle_t 
    controllando anche che le due coordinate siano consistenti ovvero detta (si,sj) la coordinata in alto a sinistra e (di,dj) 
    quella in basso a destra deve essere vero che
    si <= di && sj <= dj 

    \param s la stringa contenente gli estremi (es. "0 0 3 4")

    \retval p il puntatore alla nuova struttura obstacle_t creata (se la conversione ha avuto successo)
    \retval NULL altrimenti
*/
obstacle_t * string_to_obstacle (char * s);

/** crea la rappresentazione di un ostacolo come stringa con i 4 estremi (es. "0 0 3 4" rapresenta i due estremi (0,0) superiore sinistro e (3,4) inferiore destro)
    \param po puntatore all'ostacolo 
    \param s puntatore all'array di caratteri dove scrivere la stringa risultato della conversione
    \param n lunghezza dell'array s

    \retval s il puntatore al primo carattere della stringa (se la conversione ha avuto successo)
    \retval NULL altrimenti
*/
char * obstacle_to_string (obstacle_t * po, char* s, int n);

/** inserisce nella matrice di caduta l'ostacolo s marcando gli elementi corrispondenti all'ostacolo con OBSTACLE 
  \param s puntatore all'ostacolo da inserire
   \param mat puntatore alla matrice
   \param n numero di righe
   \param m numero di colonne

  \retval 0 se tutto è andato bene
  \retval -1 se l'ostacolo è incompatibile con l'area di caduta (es. le coordinate sono maggiori del numero di righe/colonne)
*/
int put_obstacle_in_matrix (obstacle_t * s,char ** mat, unsigned n, unsigned m);

/** inserisce un ostacolo nella lista mantenendo l'ordinamento crescente 
  \param p l'ostacolo da inserire (viene inserito direttamente senza effettuare copie)
  \param l il puntatore alla testa della lista

  \retval l il puntatore alla nuova testa della lista (dopo l'inserimento)

*/
lista_t * put_obstacle_in_list (obstacle_t* p,lista_t* l);

/** libera la memoria occupata dalla lista mettendo a NULL il puntatore alla lista 
   \param plist puntatore al puntatore della lista da deallocare
*/
void free_list (lista_t ** plist);

/** stampa la lista degli ostacoli su file (FORNITA DAI DOCENTI)
  \param f file da utilizzare
  \param puntatore alla testa della lista degli ostacoli
*/

void fprint_list (FILE* f, lista_t * l);
#endif