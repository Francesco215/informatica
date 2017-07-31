#include <stdio.h>
#include <stdlib.h>

typedef struct lista_s{
	double elemento;
	struct lista_s *next;
}lista;

double leggi_nuovo_valore(void){
	double lett;
	scanf("%lf",&lett);
	return lett;
}
lista *start=NULL,*nuovo=NULL;

double val;
int main(void){
	//Creo la lista prendendo la roba da standard input e ogni elemento lo metto per primo
	start=malloc(sizeof(lista));
	nuovo=malloc(sizeof(lista));
	*start=*nuovo;
	while((val=leggi_nuovo_valore())!=0){
		if(((*nuovo).next=malloc(sizeof(lista)))==NULL){
			fprintf(stderr, "memoria esaurita\n");
			return EXIT_FAILURE;
		}
		(*nuovo).elemento=val;
		*nuovo=*(*nuovo).next;
	}
	(*nuovo).next=NULL;
	//lo stampo
	lista *segno;
	segno=start;
	while((*segno).next!=NULL){
		printf("%lf\n",(*segno).elemento);
		*segno=*(*segno).next;
	}
	printf("%lf\n",(*segno).elemento);
return 0;
}
