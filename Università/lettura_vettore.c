#include <stdio.h>
#include <stdlib.h>


/*
Mette in un vettore una seguenza presa dallo standard input terminata da uno stop
e la iserisce in un vettore

gli si fornisce un puntatore a cui viene fatto puntare il vettore della sequenza e
uno stop che termina la sequenza

*/
int MkVector(int *V,int stop){
	static int passi=0;
	int a,b,c;
	scanf("%d",&a);
	if(a==stop){
		V=(int *)malloc((passi-1)*sizeof(int));
		return 0;
	}
	b=a;
	c=passi;
	passi++;
	MkVector(V,stop);
	printf("%d,%d\n",c,b);
	V[c]=b;
	if(c==0) return passi;
	return 0;
}
int *vettore;
int main(void){
	int passi=MkVector(vettore,0);
	for(int i=0;i<passi;i++) printf("%d  ",vettore[i]);
	printf("\n");
	return 0;
}
