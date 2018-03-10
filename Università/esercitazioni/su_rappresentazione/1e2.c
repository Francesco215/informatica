#include <stdio.h>
#include <limits.h>
#include <math.h>
int main(void){
	if (SHRT_MIN==-pow(2,sizeof(short)*8-1) && SHRT_MAX==pow(2,sizeof(short)*8-1)-1){
		printf("la lunghezza di short è giusta\n");
	}else printf("la lunghezza di short è sbagliata\n");
	if(INT_MIN==-pow(2,sizeof(int)*8-1) && INT_MAX==pow(2,sizeof(int)*8-1)-1){
		printf("la lunghezza di int è giusta\n");
	}else printf("la lunghezza di int è sbagliata\n");
	if (LONG_MIN==-pow(2,sizeof(long)*8-1) && LONG_MAX==pow(2,sizeof(long)*8-1)-1){
		printf("la lunghezza di long è giusta\n");
	}else printf("la lunghezza di long è sbagliata\n");

	return 0;
}
