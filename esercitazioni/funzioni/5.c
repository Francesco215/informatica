#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int somma(int n){
	static int *vettore;
	static int passi=0;
	int a,b,c;
	scanf("%d",&a);
	if(a==0){
		vettore=(int *)malloc((passi-1)*sizeof(int));
		return 1;
	}
	b=a;
	c=passi;
	passi++;
	int k=somma(n);
	vettore[c]=b;
	if (k==0) return 0;
	if(c==passi/2 && vettore[c]==n) return 1;
	if(c<passi/2 && vettore[c]+vettore[passi-c-1]==n) return 1;
	if(c>passi/2) return 1;
	return 0;
}

int main(void){
	printf("%d\n",somma(10));

	return 0;
}

