#include "ttree.h"

const int chiavi[13]={1,7,-8,4,-10,80,22,-56,15,15,15,13,14};

int main(void){
	nodo_t *radice=NULL;
	for (int i=0;i++;i<13) inserisci(chiavi[i],&radice);
	stampa_albero(radice,stdout);
}
