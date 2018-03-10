#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studente {
	char nome[50];
	char cognome[50];
	unsigned matricola;	
}studente_t;

int numero_righe(char* nome_file){
	FILE *file;
	file=fopen(nome_file,"r");
	int nummero=1;
	char l;
	while((l=getc(file))!=EOF){
		if (l=='\n') nummero++;
	}
	fclose(file);
	return nummero;
}

void scambia(studente_t *a, studente_t *b){
	studente_t asd;
	asd=*a;
	*a=*b;
	*b=asd;
}

int main(void){
	//creo un file sistemato
	int nr=numero_righe("./elenco_nomi");
	studente_t alunno[nr];
	FILE *elenco,*input;
	input=fopen("./elenco_nomi","r");
	elenco=fopen("./elenco_sistemato","w");
	char l;
	while((l=getc(input))!=EOF){
		if(l==':') fprintf(elenco,"\n");
		else fprintf(elenco,"%c",l);
	}
	fclose(input);
	fclose(elenco);
	elenco=fopen("./elenco_sistemato","r");

	//leggo il file sistemato e assegno le robe a un vettore di studenti_t
	for(int i=0;i<nr;i++){	
		fgets(alunno[i].nome,50,elenco);
		fgets(alunno[i].cognome,50,elenco);
		char temp[50];
		fgets(temp,50,elenco);
		alunno[i].matricola=atoi(temp);
		
	}
	fclose(elenco);

	//ordino gli studenti in ordine alfabetico
	for(int i=0;i<nr;i++){
		studente_t max=alunno[i];
		int m;
		for(int j=i;j<nr;j++){
			if(alunno[j].nome[0]>max.nome[0]){
				max=alunno[j];
				m=j;
			}
		}
		scambia(&alunno[i],&alunno[m]);
		printf("%s\n",alunno[i].nome);
	}
}
