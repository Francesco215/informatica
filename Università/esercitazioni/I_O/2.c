#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double number;

int main(void){
	FILE *output;
	output=fopen("./random","w");
	srand(time(NULL));
	for(int i=0;i<150;i++){
		double a=random();
		double b=RAND_MAX;
		fprintf(output, "%f\n",number);
	}
	fclose(output);
	
}
