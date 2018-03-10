#include <stdio.h>
#include <stdlib.h>

int main(void){
	FILE *lettura, *scrittura;
	lettura=fopen("./inputfile","r");
	scrittura=fopen("./outputfile","w");
	if(lettura==NULL){
		fprintf(stderr,"il file è vuoto\n");
		return EXIT_FAILURE;
	}
	int c,s=0;
	while((c=getc(lettura))!=EOF){
		s=s+c;
		c=getc(lettura);
	}
	printf("%d\n",s);
	fprintf(scrittura,"la somma è %dto\n",s);
	fclose(lettura), fclose(scrittura);
}
