/**
\file
  \authors informatica (CDS Fisica) 2017/18
  \brief Progetto di Recupero: intestazione delle funzioni da implementare
*/

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


/** FORNITA DAI DOCENTI -- NON MODIFICARE
  Funzione che stampa il t-tree su stdout
  \param root radice dell'albero da stampare
  \param f file stream dove stampare
*/
void stampa_albero (nodo_t * root, FILE* f);

/*inizializza una chiave con l'intero x a l'attacca al puntatore "*indirizzo"
    \param x chiava da inerire
    \param indirizzo puntatore al puntatore del nodo in cui si inerisce il nuovo nodo
*/
                  
void attacca(int x,nodo_t ** indirizzo){
  //alloco la memoria e la faccio puntare da indirizzo
  *indirizzo=(nodo_t *)malloc(sizeof(nodo_t));
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
  if((**root).left==NULL) return root;
  return cerca_max(&((**root).left));
}
nodo_t ** cerca_min(nodo_t ** root){
  if((**root).right==NULL) return root;
  return cerca_min(&((**root).right));
}

/** Serve per rendere il codice della funzione "cancella" più leggibile,
  consiglio di leggersi prima quella funzione.

  cancella il nodo **proot nel caso in cui **proot.mid==0 e 
  **proot.left,**proot.right !=0 mantenendo l'ordinamento dell'albero
    \param proot puntatore al puntatore del nodo
  */
void cancella_aux(nodo_t ** proot){
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
  /*se ha entrabi i sottoalberi uso la funzione cancella_aux per
    rendere il codice più leggibile */
  cancella_aux(proot);  
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
  if(f==NULL) return -1;
  if (root==NULL) return 0;
  fprintf(f,"%d\n",root->key);
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
  if(f==NULL) return -1;
  int chiave;
  while(fscanf(f,"%d",&chiave)!=EOF){
  inserisci(chiave,root);
  }
  return 0;
}

/**
  Stampare tutti i numeri interi distinti x contenuti nell'albero in ordine crescente (se x occorre più volte nell'albero deve essere stampato una sola volta).
  \param root radice dell'albero
*/

void ordine (nodo_t * root){
  if(root->right!=NULL) ordine(root->right);
  printf("%d\n",root->key);
  if(root->left!=NULL)  ordine(root->left);
  return;
}
/*
int * conta_nodi(nodo_t * root){
  int *conto;
  conto=(int *)malloc(sizeof(int)*3);
  for (int i=0;i<3;i++) conto[i]=0;
  if (root->left!=NULL){
    conto[0]++;
    for (int i=0;i<3,i++) conto[0]=conto[0]+conta_nodi(root->left)[i];
    free(conta_nodi(root->left));}
  if (root->mid!=NULL) {
    conto[1]++;
    for (int i=0;i<3,i++) conto[1]=conto[1]+conta_nodi(root->mid)[i];
    free(conta_nodi(root->mid));}
  if (root->right!=NULL) {
    conto[2]++;
    for (int i=0;i<3,i++) conto[2]=conto[2]+conta_nodi(root->right)[i];
    free(conta_nodi(root->right));}
  return conto;
}*/

/*
  La funzione fa esattamente quello che cerca1 fa, solo che ritorna un vettore che serve
  quando si fa la ricorsione
  \param root radice dell'albero
  \retval conto[] vettore a due indici, conto[0] indica L(y) mentre conto[1] indica M(y)
*/
int * cerca1_aux(nodo_t * root){
  /*conto è il vettore da ritornare mentre temp assume i valori
  ritornati dai nodi più in basso*/
  int *conto,*temp;
  conto=(int *)malloc(sizeof(int)*3);//alloco la memoria per conto
  conto[0]=0;conto[1]=0;conto[2]=0;// inizializzo il vettore
  if (root->left!=NULL){//nel caso in cui il nodo di sinistra non è nullo
    //assegno a temp il vettore ritornato da cerca1_aux(root->left)
    temp=cerca1_aux(root->left);
    conto[0]=1+temp[0]+temp[1]+temp[2];
    free(temp);
  }
  if (root->mid!=NULL) {
    temp=cerca1_aux(root->mid);
    conto[1]=1+temp[0]+temp[1]+temp[2];
    free(temp);
  }
  if (root->right!=NULL){
    temp=cerca1_aux(root->right);
    conto[1]=1+temp[0]+temp[1]+temp[2];
    free(temp);
  }
  if(conto[1]<conto[0]) printf("%d\n",root->key);
  return conto;
}

/**
  Dato un nodo y, sia M(y) il numero di nodi nel sottoalbero mid di y e L(y) il numero di nodi nel sottoalbero left di y. 
  Stampare le chiavi di tutti i nodi y tali che M(y)<L(y).
  \param root radice dell'albero
*/
void cerca1 (nodo_t * root){
  free(cerca1_aux(root));
}

/**
  Dato un nodo y, sia A(y) la media dei valori contenuti nel sottoalbero radicato in y (compreso il valore in y). 
  Stampare le chiavi di tutti i nodi y tali che A(y)<5.
  \param root radice dell'albero
*/
void cerca2 (nodo_t * root);

/**
  Dato un nodo y, sia H(y) il suo livello, L(y) il numero di nodi contenuti nel suo sottoalbero left, R(y) il numero di nodi contenuti nel suo sottoalbero right.
  Stampare le chiavi dei nodi y tali che L(y)+R(y)+H(y) è multiplo di 3.
  \param root radice dell'albero
*/
void cerca3 (nodo_t * root);

#endif


