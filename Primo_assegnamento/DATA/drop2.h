/* 
\file
  \authors informatica (CDS Fisica) 2016/17
  \brief intestazione delle funzioni da implementare
 */

/* protezione inclusioni multiple */
#ifndef __DROP__H
#define __DROP__H

/* altezza (N) e larghezza (M) dell'area di caduta */
#define N 15
#define M 20


/* matrice globale mat in cui ogni elemento rappresenta una sottoarea nell'area di caduta */
char mat[N][M] ;  

/* valori possibili per la matrice globale mat, EMPTY contraddistingue un'area vuota, FULL un'area un cui si e' gia' sedimentata una
particella e quindi non attraversabile */
#define EMPTY ' '
#define FULL '*'



/* inizializza la matrice mat ed il generatore pseudocasuale

   \param seed il seme della generazione

   \SPECIFICA
   1) la matrice mat[][] che rappresenta l'area di caduta viene inizializzata assegnando EMPTY ad ogni elemento
   2) il generatore psudocasuale viene inizializzato fissando il seme a seed (se seed >0) oppure il seme uguale a time(NULL) (se seed è <= 0) 
*/
void init_all (int seed);

/* stampa la matrice mat sullo standard output utilizzando il carattere spazio (EMPTY) per le posizioni vuote e il carattere '*' (FULL) per le posizioni piene (i caratteri utilizzati nelle macro che li definiscono)
*/
void print_matrix (void);

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
int step (int* next_i, int* next_j);
#endif
