#include <stdio.h>
#include <stdlib.h>


typedef struct lista_c{
	double valore;
	struct lista_c *prossimo;
}lista;

//mette la lista l2 in coda a l1
void appizza(lista *l1,lista *l2){
	if (l1->prossimo==NULL) l1->prossimo=l2;
	else appizza(l1->prossimo,l2);

}
//legge la lista l
void leggi(lista *l){
	printf("%lf\n",l->valore);
	if (l->prossimo!=NULL) leggi(l->prossimo);
	return;
}

void appizza_nuovo(lista *l1){
	if (l1->prossimo!=NULL) appizza_nuovo(l1->prossimo);
	else{
		lista *l2;
		l2=(lista *)malloc(sizeof(lista));
		scanf("%lf",&(l2->valore));
		l2->prossimo=NULL;
		l1->prossimo=l2;
	}
	return;
}
