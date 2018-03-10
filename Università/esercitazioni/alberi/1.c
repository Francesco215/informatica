#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct albero_s{
	int nummero;
	struct albero_s * sinistra;
	struct albero_s * destra;
	short mark;
}albero;


void albero_random(albero* alb ,unsigned from, unsigned to, unsigned level){
	alb->mark=0;
	if(level>0){
		alb->sinistra=(albero *)malloc(sizeof(albero));
		alb->destra=(albero *)malloc(sizeof(albero));
		albero_random(alb->sinistra,from,to,level-1);
		albero_random(alb->destra,from,to,level-1);
	}
	alb->nummero=rand()%(to-from)+from;
	return;
}

int conta_occorrenze(albero* alb, int n){
	static unsigned i=0;
	if(n==alb->nummero) i++;
	if(alb->sinistra!=NULL) i=conta_occorrenze(alb->sinistra,n);
	if(alb->destra!=NULL) i=conta_occorrenze(alb->destra,n);
	return i;
}


int main(void){
	srand(time(NULL));
	albero tree;
	albero_random(&tree,0,30,20);
	printf("%d\n",conta_occorrenze(&tree,5));
}

