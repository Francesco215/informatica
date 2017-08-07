/* 
\file
  \authors informatica (CDS Fisica) 2016/17
  \brief progetto di recupero: intestazione delle funzioni da implementare
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "myrand.h"
#include <math.h>
#include <string.h>


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

/** (FORNITA DAI DOCENTI)
    alloca una nuova matrice che rappresenta l'area di caduta utilizzando 
    la rappresentazione con array di puntatori a righe
    (senza inizializzarla) 
   
   \param n numero di righe
   \param m numero di colonne

   \retval NULL se si e' verificato un errore (setta errno)
   \retval p il puntatore alla matrice allocata
*/
char ** new_matrix (unsigned n, unsigned m);

/** (FORNITA DAI DOCENTI) 
   stampa la matrice mat sul file "f" (gia' aperto) usando 
   -- il carattere '.' (EMPTY) per le posizioni vuote
   -- il carattere '*' (FULL) per le posizioni piene 
   -- il carattere '@' (OBJECT) per le posizioni occupate dagli ostacoli
(i caratteri utilizzati nelle macro che li definiscono)

   \param f il file in cui stampare (gia' aperto in scrittura)
   \param mat il puntatore alla matrice
   \param n numero di righe
   \param n numero di colonne
*/
void fprint_matrix (FILE* f, char** mat, unsigned n, unsigned m);

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
   \retval 0 se le coordinate sono state calcolate correttamente
   \retval -1 se il punto di caduta iniziale P0
    al centro della prima riga è già FULL  
    in questo caso non viene modificato il valore di *next_i *next_j

*/

int step (int* next_i, int* next_j, adj_t ad, char** mat, int n, int m){ 
  static int a=0,c=0;
  //cose da fare quando cade il primo fiocco
  if(c==0) srand(time(NULL));
  c=1;
  //cose da fare quando inizia a cadere un fiocco
  if(a==0){
    *next_i=0;
    *next_j=m/2;
    a++;
  }
  //gestione parametri invalidi
  if(mat==NULL||n<=0||m<=0){
    fprintf(stderr,"parametri non validi\n");
    return EXIT_FAILURE;
  }
  //entrata bloccata
  if(mat[0][m/2]==FULL) return -1;
  //ho toccato il fondo del barile
  if(*next_i==n-1) return 0;

  //controllo[0] vale 1 se ci sono elementi lungo la croce, altrimenti 0
  //controllo[1] vale 1 se ci sono elementi lungo la diagonale, altrimenti 0
  int controllo[2]={0,0};
  if(*next_i!=0){
    if(mat[(*next_i)+1][*next_j]!=EMPTY || mat[(*next_i)-1][*next_j]!=EMPTY || mat[*next_i][(*next_j)+1]!=EMPTY || mat[*next_i][(*next_j)-1]!=EMPTY) controllo[0]=1;
    if(mat[(*next_i)+1][(*next_j)+1]!=EMPTY || mat[(*next_i)-1][(*next_j)-1]!=EMPTY || mat[(*next_i)-1][(*next_j)+1]!=EMPTY || mat[(*next_i)+1][(*next_j)-1]!=EMPTY) controllo[1]=1;
  }else{//l'ho dovuto fare senò va in segmentation
    if(mat[(*next_i)+1][*next_j]!=EMPTY || mat[*next_i][(*next_j)+1]!=EMPTY || mat[*next_i][(*next_j)-1]!=EMPTY) controllo[0]=1;
    if(mat[(*next_i)+1][(*next_j)+1]!=EMPTY || mat[(*next_i)+1][(*next_j)-1]!=EMPTY) controllo[1]=1;
  }
  if(ad==CROSS && controllo[0]==1) return 0;
  if(ad==DIAGONAL && controllo[1]==1) return 0;
  if(ad==BOTH && (controllo[0]==1 || controllo[1]==1)) return 0;
  if(ad==NONE && mat[(*next_i)+1][(*next_j)+1]!=EMPTY && mat[(*next_i)+1][*next_j]!=EMPTY && mat[(*next_i)+1][(*next_j)-1]!=EMPTY) return 0;

  //ysnp è un vettore che indica le posizioni libere
  int ysnp[3]={1,1,1};
  if(*next_j==0 || mat[(*next_i)+1][(*next_j)-1]!=EMPTY) ysnp[0]=0;
  if(*next_j==m-1 || mat[(*next_i)+1][(*next_j)+1]!=EMPTY) ysnp[2]=0;
  if(mat[(*next_i)+1][*next_j]!=EMPTY) ysnp[1]=0;
  int len=ysnp[0]+ysnp[1]+ysnp[2];

  //asd è un vettore con tutti gli esiti possibili per *next_j
  int asd[len];
  int j=0;
  for(int i=0;i<3;i++){
    if(ysnp[i]!=0){
      if(i==0) asd[j]=(*next_j)-1;
      if(i==1) asd[j]=*next_j;
      if(i==2) asd[j]=(*next_j)+1;
      j++;
    }
  }
  //faccio il passettino
  *next_j=asd[rand()%len];
  (*next_i)++;
  //ricorsione
  if(step(next_i,next_j,ad,mat,n,m)==0) return 0,a=0;
  else return -1,a=0;
}



/** legge la rappresentazione di un ostacolo come stringa di 4 estremi interi 
    
    \param s la stringa contenente gli estremi (es. "0 0 3 4")

    \retval p il puntatore alla nuova struttura obstacle_t creata (se la conversione ha avuto successo)
    \retval NULL altrimenti
*/

obstacle_t * string_to_obstacle (char * s){
  if(s==NULL){
    fprintf(stderr,"argomento invalido\n");
    return EXIT_FAILURE;
  }
  unsigned pos[4];
  char *segno2,*segno1;
  for(int j=0;j<4;j++){
    if(j==0) segno1=s;
    if(j!=3) segno2=strchr(segno1,' ');
    else segno2=strchr(s,'\0');
    int len=segno2-segno1;
    int n=0;
    for(int i=0;i<len;i++){
      n=n+(*(segno1+i)-'0')*pow(10,len-i-1);
    }
    pos[j]=n;
    segno1=segno2+1;
  }
  if(pos[0]<=pos[2] && pos[1]<=pos[3]){
    obstacle_t *rettangolo;
    if((rettangolo=(obstacle_t *)malloc(sizeof(obstacle_t)))==NULL){
      fprintf(stderr,"malloc torna null\n");
      return EXIT_FAILURE;
    }  
    rettangolo->s_i=pos[0];
    rettangolo->s_j=pos[1];
    rettangolo->d_i=pos[2];
    rettangolo->d_j=pos[3];
    return rettangolo;
  } 
  return NULL;
}

/** crea la rappresentazione di un ostacolo come stringa con i 4 estremi (es. "0 0 3 4" rapresenta i due estremi (0,0) superiore sinistro e (3,4) inferiore destro)
    \param po puntatore all'ostacolo 
    \param s puntatore all'array di caratteri dove scrivere la stringa risultato della conversione
    \param n lunghezza dell'array s

    \retval s il puntatore al primo carattere della stringa (se la conversione ha avuto successo)
    \retval NULL altrimenti
*/
char * obstacle_to_string (obstacle_t * po, char* s, int n){ //mettere controllo errori
  sprintf(s, "%d %d %d %d",po->s_i,po->s_j,po->d_i,po->d_j);
  return s;

}

/** inserisce nella matrice di caduta l'ostacolo s marcando gli elementi corrispondenti all'ostacolo con OBSTACLE 
  \param s puntatore all'ostacolo da inserire
   \param mat puntatore alla matrice
   \param n numero di righe
   \param m numero di colonne

  \retval 0 se tutto è andato bene
  \retval -1 se l'ostacolo è incompatibile con l'area di caduta (es. le coordinate sono maggiori del numero di righe/colonne)
*/
int put_obstacle_in_matrix (obstacle_t * s,char ** mat, unsigned n, unsigned m){
  if((s->d_i)<n && (s->s_i)<=(s->d_i) && (s->d_j)<m && (s->s_j)<=(s->d_j)){
    for(int i=(s->s_i);i<=(s->d_i);i++){
      for(int j=(s->s_j);j<=(s->d_j);j++) mat[i][j]=OBSTACLE;
    }
    return 0;
  }
  return -1;
}

/** inserisce un ostacolo nella lista mantenendo l'ordinamento crescente 
  \param p l'ostacolo da inserire (viene inserito direttamente senza effettuare copie)
  \param l il puntatore alla testa della lista

  \retval l il puntatore alla nuova testa della lista (dopo l'inserimento)
*/

lista_t * put_obstacle_in_list (obstacle_t* p,lista_t* l){
  if(p==NULL) return l; //se il puntatore è nullo me lo levo dalle palle

/*questo blocco che inizia qua e finisce alla riga 313 serve per determinare se un ostacolo
è "maggiore" o "minore" di un altro, restiruisce comp=1 se p>l->pobj o se l==NULL,
comp=-1 se p<l->pobj e comp=0 se p==l->pobj
*/
  short comp=0;
  if(l!=NULL){
    unsigned pos[2][4];
    pos[0][0]=p->s_i,pos[1][0]=(l->pobj)->s_i;
    pos[0][1]=p->s_j,pos[1][1]=(l->pobj)->s_j;
    pos[0][2]=p->d_i,pos[1][2]=(l->pobj)->d_i;
    pos[0][3]=p->d_j,pos[1][3]=(l->pobj)->d_j;
    for(int i=0;i<4;i++){
      if(pos[0][i]>pos[1][i]) comp=-1;
      if(pos[0][i]<pos[1][i]) comp=1;
      if(comp!=0) break;
    }
    if(comp==0) return l;
  }else comp=1;

  // se p<l->pobj allora ripeti l'operazione col prossimo
  if(comp==-1) l->next=put_obstacle_in_list(p,l->next);
  
  // quando arrivo alla fine, o quando incontro un'elemento più piccolo
  if(comp==1){    
    if(l!=NULL){// se si trova nel mezzo  
      lista_t *temp;
      temp=l;
      l=(lista_t *)malloc(sizeof(lista_t));
      if(l==NULL){
        fprintf(stderr, "fatal error\n");
        return EXIT_FAILURE;
      }    
      l->pobj=p;
      l->next=temp;  
    }
    if(l==NULL){//se si trova alla fine o se è il primo elemento in assoluto
      l=(lista_t *)malloc(sizeof(lista_t));
      l->next=NULL;
      l->pobj=p;
    }
  }
 return l;
}

/** libera la memoria occupata dalla lista mettendo a NULL il puntatore alla lista 
   \param plist puntatore al puntatore della lista da deallocare
*/
void free_list (lista_t ** plist){
  if(*plist==NULL) return;
  free_list(&(*plist)->next);
  free(*plist);
  *plist=NULL;
}

/** stampa la lista degli ostacoli su file (FORNITA DAI DOCENTI)
  \param f file da utilizzare
  \param puntatore alla testa della lista degli ostacoli
*/

void fprint_list (FILE* f, lista_t * l);
#endif
