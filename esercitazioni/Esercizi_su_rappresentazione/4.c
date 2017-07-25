#include <stdio.h>
//char alfabeto[]={a,b,c,d,e,f,g,h,i,l,m,n,o,p,q,r,s,t,u,v,z,A,B,C,D,E,F,G,H,I,L,M,N,O,P,Q,R,S,T,U,V,Z};
char input,carattere;
int ASCII;
int main(void){
	printf("convertitore codice in codice ASCII\n inserisci C se vuoi converire da carattere a ASCII,\n inserisci A se vuoi converire da ASCII a carattere\n");
	input=getchar();
	int shih=getchar();
	if(input=='C'){
		printf("inserisci il carattere\n");
		carattere=getchar();
		printf("il suo codice ascii è %d",carattere);
	}
	if(input=='A'){
		printf("inserisci il codice ASCII\n");
		scanf("%d",&ASCII);
		printf("\n         il suo carattere è %c\n",ASCII);
	}
	return 0;
}

