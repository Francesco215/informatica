#include <stdio.h>
int cerca(int *vec,int x){
	int i=0;
	while(vec[i]!='\0'){
		if (vec[i]==x) return 1;
		i++;
	}
	return 0;

}

int vettore[5]={1,2,3,6,8};
int main(void){
	printf("%d\n",cerca(vettore,6));
	return 0;

}

