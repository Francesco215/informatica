#include <stdio.h>

void max(double *vec,double *pmax,int *pind){
	int i=0;
	while(vec[i]!='\0'){
		if (vec[i]>*pmax){
			*pmax=vec[i];
		}
	i++;
	}
}

int main(void){
	double vettore[5]={1,2,3,6,8};
	double *max;
	int *ind;
	max(vettore,&max,&ind);
	printf("%f %lf \n",*max,max);
	return 0;
}
