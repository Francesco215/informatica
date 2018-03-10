#include <stdio.h>
#include <stdlib.h>

typedef struct lista_s{
	double numero;
	struct lista_s *next;
}lista;

double leggi_nuovo_valore(void){
	double lett;
	scanf("%lf",&lett);
	return lett;
}
/*
void append(lista *lis,double stop){
	static int val;
	static int i=0;
	if (i==0) val=leggi_nuovo_valore();
	i++;
	if(val==0){
		return;
	}
	lis->next=(lista *)malloc(sizeof(lista));
	(*lis).numero=val;
	val=leggi_nuovo_valore();
	append((*lis).next,stop);
}
*/
void print_lista(lista *lis){
	if (lis==NULL) return;
	printf("%lf\n",(*lis).numero);
	print_lista((*lis).next);
}


lista *start=NULL,*nuovo=NULL;
double val;

int main(void){
	//Creo la lista prendendo la roba da standard input e ogni elemento lo metto per primo
	while((val=leggi_nuovo_valore())!=0){
		if(start==NULL) {
			start=(lista *)malloc(sizeof(lista));
			start->next=NULL;
			start->numero=val;
			nuovo=start;
		}
		else{
			nuovo->next=(lista *)malloc(sizeof(lista));
			nuovo=nuovo->next;
			nuovo->next=NULL;
			nuovo->numero=val;
		}
	}
	//lo stampo
	print_lista(start);
return 0;
}



