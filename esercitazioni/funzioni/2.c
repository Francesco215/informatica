#include <stdio.h>

void invert(void){
	char a;
	if((a=getchar())!='\n'){
		invert();
	}
	putchar(a);
}

int main(void){
	invert();
	printf("\n");
	return 0;
}

