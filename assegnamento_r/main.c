#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "myrand.h"
#include "drop.h"
#include "file.h"

int n_iter;
char* adiacenza;
FILE* infile;
unsigned N;
unsigned M;
FILE* ostacoli;
FILE* outfile;


int main(int argc, char* argv[]){git
	for(int i=0;i<argc && argv[i][0]=='-';i++){
		unsigned n=atoi(argv[i]);
		if(n!=0 && (argv[i-1]!="-n"||argv[i-1]|="-m")) {
			n_iter=n;
			printf("%s\n",n_iter);
		}
	}
	printf("%d\n",n_iter);
}