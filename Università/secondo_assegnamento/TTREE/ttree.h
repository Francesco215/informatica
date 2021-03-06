/**
\file
  \authors informatica (CDS Fisica) 2017/18
  \brief Progetto di Recupero: intestazione delle funzioni da implementare
*/

/* protezione inclusioni multiple */

#ifndef __TTREE__H
#define __TTREE__H
#include <stdio.h>



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
                  
void attacca(int x,nodo_t ** indirizzo);

/** Inserisce una nuova chiave nell'albero mantenendo l'ordinamento
    \param x chiave da inserire
    \param proot puntatore al puntatore alla radice del albero

 */
void inserisci (int x, nodo_t ** proot);


/** Cancella UNA SOLA OCCORRENZA della chiave nell'albero (se presente) 
    mantenendo l'ordinamento
    \param x chiave da cancellare
    \param proot puntatore al puntatore alla radice del albero

 */
void cancella (int x, nodo_t ** proot);

/** libera tutta la memoria occupata dall'albero
    \param proot puntatore alla radice del quad-tree da deallocare 
           (la radice va settata a NULL all'interno della funzione)
 */
void free_albero (nodo_t ** root);

/** serializza l'albero su file in un formato a caratteri a scelta dell ostudente (da descrivere e motivare nella relazione 
    \param f file dove scrivere (gia' aperto in scrittura...)
    \param root radice dell'albero da serializzare

    \retval 0 se tutto e' andato bene
    \retval -1 se si e' verificato un errore 
 */
int scrivi_albero(FILE* f, nodo_t* root);

/** serializza l'albero su file in un formato a caratteri a scelta dell ostudente (da descrivere e motivare nella relazione 
    \param f file dove scrivere (gia' aperto in scrittura...)
    \param proot puntatore alla variabile che conterra' la radice dell'albero (*proot non viene modificato in caso di errore)

    \retval 0 se tutto e' andato bene
    \retval -1 se si e' verificato un errore 
 */
int leggi_albero(FILE* f, nodo_t** root);

/**
	Stampare tutti i numeri interi distinti x contenuti nell'albero in ordine crescente (se x occorre più volte nell'albero deve essere stampato una sola volta).
	\param root radice dell'albero
*/

void ordine (nodo_t * root);

/**
	Dato un nodo y, sia M(y) il numero di nodi nel sottoalbero mid di y e L(y) il numero di nodi nel sottoalbero left di y. 
	Stampare le chiavi di tutti i nodi y tali che M(y)<L(y).
	\param root radice dell'albero
*/
void cerca1 (nodo_t * root);

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

