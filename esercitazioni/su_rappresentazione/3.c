#include <stdio.h>
#include <math.h>

unsigned long N;
long B=0;

int main(void){
	printf("inserisci il nummero\n");
	scanf("%ld",&N);
	printf("in esadecimale %lx\nin ottale %lo \n",N,N);

	//mettere le cose in binario
	//i commenti all'interno del loop vanno sbloccati se il numero diventa troppo grosso
	int k=N;
	for(int i=sizeof(long)*8;i>-1;i--){
		if (pow(2,i+1)>k && k>=pow(2,i)){
			//printf("%d",1);
			k=k-pow(2,i);
			B=B+pow(10,i);
		}//else printf("%d",0);
	}
	printf("%ld\n",B);
	return 0;
}
