/* 
\file
  \authors informatica (CDS Fisica) 2016/17
  \brief intestazione delle funzioni da implementare
 */

/* protezione inclusioni multiple */

#include <math.h>
/* contiene l'ultimo numero generato */
int lastnumber;

/** inserisce il valore iniziale del seme nella variabile globale lastnumber 
  \param seed il valore del seme

*/
void my_srand(int seed){
	lastnumber=seed;
}

/** genera il prossimo valore a partire dal valore contenuto nella variabile globale lastnumber

    \retval n il prossimo numero della sequenza pseudocasuale compreso fra 0 e 9999 

*/
int my_rand(void){
	int M=pow(2,31)-1;
	int a=pow(7,5);
	return (lastnumber*a)%M;
	my_srand(lastnumber);
}



