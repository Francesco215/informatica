/* 
\file
  \authors informatica (CDS Fisica) 2016/17
  \brief assegnamento1: intestazione delle funzioni di generazione dei numeri
                        pseudocasuali
 */

/* protezione inclusioni multiple */
#ifndef __MYRAND__H
#define __MYRAND__H

/* contiene l'ultimo numero generato */
int lastnumber;

/** inserisce il valore iniziale del seme nella variabile globale lastnumber 
  \param seed il valore del seme

*/
void my_srand(int seed);

/** genera il prossimo valore a partire dal valore contenuto nella variabile globale lastnumber

    \retval n il prossimo numero della sequenza pseudocasuale compreso fra 0 e 9999 

*/
int my_rand(void);

#endif
