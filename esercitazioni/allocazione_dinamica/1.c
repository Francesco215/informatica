#include <stdio.h>
#include <stdlib.h>

double *vettore;
int l;
int main(void){
	printf("inserire la lunghezza del vettore\n");
	scanf("%d",&l);
	if((vettore=malloc(sizeof(double)*l))==0){
		fprintf(stderr, "a scafazzaisti\n");
		return EXIT_FAILURE;
	}
	printf("inserisci %d numeri da mettere nel vettore\n",l);
	for(int i=0;i<l;i++){
		scanf("%lf",&vettore[i]);
	}
	for(int i=0;i<l;i++){
		printf("%lf\n",vettore[i]);
	}
}
