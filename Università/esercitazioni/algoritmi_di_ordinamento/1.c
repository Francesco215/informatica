#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void scambio(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

void quicksort_ricorsivo(int* array,int iniz,int fine){
	if(iniz>=fine) return;
	printf("%d %d\n",iniz,fine);
	int j=iniz,k=j;
	for(int i=iniz;i<fine;i++){
		if(array[i]<=array[fine]) k++,scambio(array+j+k,array+i);
		if(array[i]<array[fine]) k--,j++,scambio(array+j+k,array+j);
	}
	quicksort_ricorsivo(array,j+k+1,fine);
	quicksort_ricorsivo(array,0,j+k+1);
	return;
}

void quicksort(int* array){
	quicksort_ricorsivo(array,0,sizeof(array)/sizeof(array[0]));
}

int vettore[10]={5,2,87,4,5,9,0,1,6,7};

int main(void){
	quicksort(vettore);
	//for(int i=0;i<10;i++) printf("----%d----\n",vettore[i]);
}
