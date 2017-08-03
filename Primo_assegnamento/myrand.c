/* 
\file
  \authors informatica (CDS Fisica) 2016/17
  \brief intestazione delle funzioni da implementare
 */

// protezione inclusioni multiple 
#ifndef __MYRAND__H
#define __MYRAND__H
#include <math.h>
#include <stdlib.h>


unsigned int lastnumber;

void my_srand(int seed){
	//lastnumber=seed;
	strand(seed);
}

int my_rand(void){
	/*
	int M=2147483647;
	int a=16807;
	int max=10000;
	lastnumber=(lastnumber*a)%M;
	return lastnumber%max;
	*/
	rand(NULL);
}
#endif


