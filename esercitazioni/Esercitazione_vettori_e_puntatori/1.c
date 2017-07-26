#include <stdio.h>
#include <stdlib.h>

static int *vettore;
static int passi=0;
//prende una sequenza di nummeri da standard input terminata da 0 e sputa un vettore
void MkVector(void){
	int a,b,c;
	scanf("%d",&a);
	if(a==0){
		vettore=(int *)malloc((passi-1)*sizeof(int));
		return;
	}
	b=a;
	c=passi;
	passi++;
	MkVector();
	vettore[c]=b;
}

int main(void){
	MkVector();
	for(int i=0;i<passi;i++) printf("%d  ",vettore[i]);
	return 0;
}
