#include <stdio.h>
#include <stdlib.h>

typedef struct lista_c{
	double valore;
	struct lista_c *prossimo;
}lista;


//mette la lista l2 in coda a l1
void appizza(lista *l1,lista *l2);
//legge la lista l
void leggi(lista *l);

void appizza_nuovo(lista *l1);
