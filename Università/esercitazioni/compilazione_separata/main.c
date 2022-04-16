#include "funzioni.h"

int main(void){
	lista a;
	a.prossimo=NULL;
	for(int i=0;i<5;i++){
		appizza_nuovo(&a);
	}
	leggi(&a);


	return 0;
}
