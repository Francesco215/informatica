#include <stdio.h>
#include <stdlib.h>

double *vettore,l=1;


int main(void){
	int a=0;
	if((vettore=malloc(0))==NULL){
		fprintf(stderr, "memoria esaurita\n");
		return EXIT_FAILURE;
	}
	while(l!=0){
		a++;
		vettore=realloc(vettore,sizeof(vettore)+sizeof(double));
		if(vettore==NULL){
			fprintf(stderr, "memoria esaurita\n");
			return EXIT_FAILURE;
		}
		scanf("%lf",&l);
		vettore[a-1]=l;
	}
	for (int i=0;i<a-1;i++){
		printf("%lf ",vettore[i]);
	}

}
