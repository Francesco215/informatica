#include <stdio.h>
#include <stdlib.h>


/*
Mette in un vettore una seguenza presa dallo standard input terminata da uno stop
e la iserisce in un vettore

gli si fornisce un puntatore a cui viene fatto puntare il vettore della sequenza e
uno stop che termina la sequenza

*/
static int *vettore;
int MkVector(int stop){
	static int passi=0;
	int a,b,c;
	scanf("%d",&a);
	if(a==stop){
		vettore=(int *)malloc((passi-1)*sizeof(int));
		return 0;
	}
	b=a;
	c=passi;
	passi++;
	MkVector(stop);
	vettore[c]=b;
	if(c==0) return passi;
	return 0;
}

int main(void){
	int passi=MkVector(0);
	for(int i=0;i<passi;i++) printf("%d  ",vettore[i]);
	printf("\n");
	return 0;
}
