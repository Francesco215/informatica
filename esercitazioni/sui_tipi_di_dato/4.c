#include <stdio.h>

int main(void){
	char a,b=0;
	while(b==0){
		if(a==','){b=1;}
		a=getchar();
	}
	while(a!='\n'){
		putchar(a);
		putchar('\n');
		a=getchar();
	}
	return 0;
}

