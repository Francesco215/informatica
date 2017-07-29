#include <stdio.h>

void max(double *vec,double *pmax,int *pind){
	for(int i=0;vec[i]!='\0';i++){
		if (vec[i]>*pmax){
			*pmax=vec[i];
			*pind=i;
		}
	}
}

double vettore[]={1,2,12,6,8,3,1,13,8,9,2,0};
double Max;
int ind;

int main(void){
	max(vettore,&Max,&ind);
	printf("%f %d \n",Max,ind);
	return 0;
}
