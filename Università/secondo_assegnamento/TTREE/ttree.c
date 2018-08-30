/** \file ttree.c
       \author Francesco Sacco
     Si dichiara che il contenuto di questo file e' in ogni sua parte opera
     originale dell'autore.  */

/* protezione inclusioni multiple */

#ifndef __TTREE__H
#define __TTREE__H
#include <stdio.h>
#include <stdlib.h>



/** tipo del nodo del t-tree: un t-tree è un albero con chiavi intere con tre figli (left, mid, right) che verifica la seguente proprietà
-- il sottoalbero radicato in left contiene tutte le chiavi maggiori della chiave nel nodo
-- il sottoalbero radicato in mid è una lista contenente tutti i nodi con valore di chiave uguale al nodo
-- il sottoalbero radicato in right contiene tutte le chiavi minori della chiave del nodo */
typedef struct nodo {
  /** chiave del nodo */
  int key; 
  /* puntatori ai nodi figli */
  struct nodo *left, *mid, *right;
} nodo_t;


/*inizializza una chiave con l'intero x a l'attacca al puntatore "*indirizzo"
    \param x chiava da inerire
    \param indirizzo puntatore al puntatore del nodo in cui si inerisce il nuovo nodo
*/
                  
void attacca(int x,nodo_t ** indirizzo){
  //alloco la memoria e la faccio puntare da indirizzo
  *indirizzo=(nodo_t *)malloc(sizeof(nodo_t));
  if(indirizzo==NULL){fprintf(stderr, "Errore fatale\n");exit(EXIT_FAILURE);}
  //inizializzo il nuovo nodo
  (**indirizzo).key=x;
  (**indirizzo).left=NULL;
  (**indirizzo).mid=NULL;
  (**indirizzo).right=NULL;
}

/** Inserisce una nuova chiave nell'albero mantenendo l'ordinamento
    \param x chiave da inserire
    \param proot puntatore al puntatore alla radice del albero
 */

void inserisci (int x, nodo_t ** proot){
  if(proot==NULL) return;
  //non appena si arriva alla punta dell'albero si ci attacca un nuovo nodo
  if (*proot==NULL) {attacca(x,proot); return;}
  //queste 3 linee di codice servono a capire in che direzione andare
  if(x>(**proot).key) inserisci(x,&(** proot).left);
  if(x==(**proot).key) inserisci(x,&((**proot).mid));
  if(x<(**proot).key) inserisci(x,&((**proot).right));
}

/** ritorna il puntatore al nodo più grande (o piccolo) di un sottoalbero con radice root
  \param root puntatore al sottoalbero con radice root
  \retval puntatore al nodo col valore più grande (o piccolo)
*/
nodo_t ** cerca_max(nodo_t ** root){
  //vado a sinistra finchè non trovo il nodo con lavore massimo
  if((**root).left==NULL) return root;
  //restituisco il puntatore al puntatore al massimo
  return cerca_max(&((**root).left));
}
nodo_t ** cerca_min(nodo_t ** root){//funziona come la funzione di prima
  if((**root).right==NULL) return root;
  return cerca_min(&((**root).right));
}

/** Cancella UNA SOLA OCCORRENZA della chiave nell'albero (se presente) 
    mantenendo l'ordinamento
    \param x chiave da cancellare
    \param proot puntatore al puntatore alla radice del albero
 */
void cancella (int x, nodo_t ** proot){
  //questa riga serve per fermare la funzione se non trova il nodo con la chiave x
  if((*proot)==NULL) return;
  //queste due linee servono per cercare il nodo con la chiave x
  if((**proot).key>x) {cancella(x,&((**proot).right)); return;}
  if((**proot).key<x) {cancella(x,&((**proot).left)); return;}
  //dentro questo è quello che succede se si trova la chiave x
  //manca if((**proot).key==x){...} perchè questa è l'ultima possibilità restante per x
  if((**proot).mid!=NULL) {cancella(x,&((**proot).mid)); return;}
  //adesso siamo nella situazione in cui siamo all'ultimo nodo con la chiave x
  //se non ha sottoalberi dealloco la memoria (CONTROLLA!!!)
  if((**proot).left==NULL && (**proot).right==NULL) {free(*proot); (*proot)=NULL; return;}
  //se ha almeno un sottoalbero
  nodo_t * temp;
  temp=*proot;
  if((**proot).left==NULL)  {*proot=(**proot).right; free(temp); return;}
  if((**proot).right==NULL)  {*proot=(**proot).left; free(temp); return;}
  /* adesso siamo nel caso in cui **root ha sia un sottoalbero destro che sinistro,
  ma non ne ha uno centrale*/
  nodo_t **max=NULL,**min=NULL;//inizializzo le due variabili ausilarie **max e **min
  max=cerca_max(&(**proot).right);//trovo il massimo **max del sottoalbero di **proot
  min=cerca_min(max);//trovo il minimo **min del sottoalbero di **max
  /*faccio puntare a **min.right la cella a destra di **proot a meno che non sia
  il *max, perchè senò entrerebbe in un loop  */
  if(*max!=(**proot).right) (**min).right=(**proot).right;
  //faccio puntare il sottoalbero a sinistra di **proot dal puntatore sinistro di **max
  (**max).left=(**proot).left;
  free(*proot);//libero la memoria del nodo cancellato
  *proot=*max;//faccio puntare *proot al nodo **max
  *max=NULL;//faccio puntare *max a niente  
}

/** libera tutta la memoria occupata dall'albero
    \param proot puntatore alla radice del quad-tree da deallocare 
           (la radice va settata a NULL all'interno della funzione)
 */
void free_albero (nodo_t ** root){
  //vado in tutti i nodi possibili
  if((**root).right!=NULL) free_albero(&((**root).right));
  if((**root).mid!=NULL) free_albero(&((**root).mid));
  if((**root).left!=NULL) free_albero(&((**root).left));
  //dealloco la memoria e punto a NULL
  if(*root!=NULL) {free(*root);*root=NULL;}
}
/** serializza l'albero su file in un formato a caratteri a scelta dell ostudente (da descrivere e motivare nella relazione 
    \param f file dove scrivere (gia' aperto in scrittura...)
    \param root radice dell'albero da serializzare

    \retval 0 se tutto e' andato bene
    \retval -1 se si e' verificato un errore 
 */
int scrivi_albero(FILE* f, nodo_t* root){
  if(f==NULL || ferror(f)!=0) return -1;//controllo errori
  if (root==NULL) return 0;//fermo la ricorsione quando si arriva alla fine
  fprintf(f,"%d\n",root->key);//stampo la chiave
  //vado prima nel sottoalbero sinistro, poi quello destro e poi quello centrale
  scrivi_albero(f,root->left);
  scrivi_albero(f,root->mid);
  scrivi_albero(f,root->right);
  return 0;
}

/** serializza l'albero su file in un formato a caratteri a scelta dell ostudente (da descrivere e motivare nella relazione 
    \param f file dove scrivere (gia' aperto in scrittura...)
    \param proot puntatore alla variabile che conterra' la radice dell'albero (*proot non viene modificato in caso di errore)

    \retval 0 se tutto e' andato bene
    \retval -1 se si e' verificato un errore 
 */
int leggi_albero(FILE* f, nodo_t** root){
  if(f==NULL || ferror(f)!=0) return -1;//controllo errori
  int chiave;//valore temporaneo da assegnargli valore con lo scanf
  while(fscanf(f,"%d",&chiave)!=EOF){
  inserisci(chiave,root);//inserisco la chiave nell'albero con la funzione inserisci()
  }
  return 0;
}

/**
  Stampare tutti i numeri interi distinti x contenuti nell'albero in ordine crescente (se x occorre più volte nell'albero deve essere stampato una sola volta).
  \param root radice dell'albero
*/

void ordine (nodo_t * root){
  if(root->right!=NULL) ordine(root->right);// stampo il sottoalbero destro
  printf("%d\n",root->key);//poi quello centrale
  if(root->left!=NULL)  ordine(root->left);//poi quello sinistro
  return;
}

/*
  La funzione fa esattamente quello che le funzioni cerca fanno,
  solo che ritorna un vettore che serve quando si fa la ricorsione
  \param root radice dell'albero
  \param cerca indica quale delle funzioni "cerca" si vuole usare
  \param livello indica in che livello dell'albero si è
  \retval vett[] vettore a quattro indici:
    vett[0],vett[1],vett[2] indicano rispettivamente il numero di nodi nei sottoalberi di
    sinistra, centro e destra, mentre vett[3] indica la somma di tutte le chiavi dei nodi
    del sottoalbero di root 
*/
int * cerca_aux(nodo_t * root, int cerca, unsigned int livello){
  //vett è il vettore da ritornare mentre sott_vett è il vettore ritornato dai sottoalberi
  int *vett,*sott_vett;
  vett=(int *)calloc(4,sizeof(int));//alloco la memoria per vett
  //gestione errori di allocazione
  if(vett==NULL){fprintf(stderr, "Errore fatale\n");exit(EXIT_FAILURE);}
  vett[3]=root->key;// inizializzo assegno a vett[3] il valore della chiave del nodo
  if (root->left!=NULL){//nel caso in cui il nodo di sinistra non è nullo
    //assegno a sott_vett il vettore ritornato da cerca_aux(root->left)
    sott_vett=cerca_aux(root->left,cerca,livello +1);
    /*qui uso il fatto che il numero di nodi sotto un sottoalbero è uguale alla somma
    del numero di nodi sotto ogni sotto-sottoalbero + 1 */
    vett[0]=1+sott_vett[0]+sott_vett[1]+sott_vett[2];
    //a vett[3] gli sommo la somma di tutti i vettori nel sottoalbero di sinistra
    vett[3]=vett[3]+sott_vett[3];
    //libero la memoria allocata quando si chiama la funzione cerca_aux(root->left)
    free(sott_vett);
  }
  if (root->mid!=NULL) {//il funzionamento è identico a quello dell'if di prima di prima
    sott_vett=cerca_aux(root->mid,cerca,livello+1);
    vett[1]=1+sott_vett[0]+sott_vett[1]+sott_vett[2];
    vett[3]=vett[3]+sott_vett[3];
    free(sott_vett);
  }
  if (root->right!=NULL){//il funzionamento è identico a quello dell'if di prima di prima
    sott_vett=cerca_aux(root->right,cerca,livello+1);
    vett[2]=1+sott_vett[0]+sott_vett[1]+sott_vett[2];
    vett[3]=vett[3]+sott_vett[3];
    free(sott_vett);
  }
  //verifico se la condizione per la funzione cerca1 è verificata
  if(vett[1]<vett[0] && cerca==1) printf("%d\n",root->key);
  //verifico se la condizione per la funzione cerca2 è verificata
  if(vett[3]/(1+vett[0]+vett[1]+vett[2])<5 && cerca==2) printf("%d\n",root->key);
  //verifico se la condizione per la funzione cerca3 è verificata
  if((livello+vett[0]+vett[2])%3==0 && cerca==3) printf("%d\n",root->key);
  return vett;
}

/**
  Dato un nodo y, sia M(y) il numero di nodi nel sottoalbero mid di y e L(y) il numero di nodi nel sottoalbero left di y. 
  Stampare le chiavi di tutti i nodi y tali che M(y)<L(y).
  \param root radice dell'albero
*/
void cerca1 (nodo_t * root){
  free(cerca_aux(root,1,0));
}

/**
  Dato un nodo y, sia A(y) la media dei valori contenuti nel sottoalbero radicato in y (compreso il valore in y). 
  Stampare le chiavi di tutti i nodi y tali che A(y)<5.
  \param root radice dell'albero
*/
void cerca2 (nodo_t * root){
  free(cerca_aux(root,2,0));
}

/**
  Dato un nodo y, sia H(y) il suo livello, L(y) il numero di nodi contenuti nel suo sottoalbero left, R(y) il numero di nodi contenuti nel suo sottoalbero right.
  Stampare le chiavi dei nodi y tali che L(y)+R(y)+H(y) è multiplo di 3.
  \param root radice dell'albero
*/
void cerca3 (nodo_t * root){
  free(cerca_aux(root,3,0));
}

#endif


