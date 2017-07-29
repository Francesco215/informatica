#include <stdio.h>
#include <stdlib.h>

double *vettore,*a,l=1;

/*int main(void){
	double* vettore[2]={vettore0,vettore1};
	for(int i=-1;l!=0;i++){
		if(i==-1){
			scanf("%lf",&l);
			if((vettore[1]=malloc(sizeof(double)))==NULL){
				fprintf(stderr, "a scafazzaisti\n");
				return EXIT_FAILURE;
			}
		}else{
			free(vettore[i%2]);
			vettore[i%2]=realloc(vettore[(i+1)%2],sizeof(vettore[(i+1)%2])+sizeof(double));
			//free(vettore[0])
			//vettore[0]=realloc(vettore[1],sizeof(vettore[1])+sizeof(double))
			if(vettore[i%2]==NULL){
				fprintf(stderr, "a scafazzaisti\n");
				return EXIT_FAILURE;
			}
			vettore[i%2][i]=l;
			scanf("%lf",&l);
		}
	}
	return 0;
}*/

int main(void){
	a=malloc(sizeof(double));
	while(l!=0){
		vettore=a;
		free(a);
		a=realloc(vettore,sizeof(vettore)+sizeof(double));
		if(a==NULL){
			fprintf(stderr, "memoria esaurita");
			return EXIT_FAILURE;
		}
		scanf("%lf",&l);
		a[sizeof(a)/sizeof(double)-1]=l;
	}
	for (int i = 0; i < sizeof(vettore)/sizeof(double); ++i) printf("%lf  ",vettore[i]);

}
