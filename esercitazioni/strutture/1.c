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

/*int scambia(studente_t *a, studente_t *b){

}*/

int main(void){
	//creo un file sistemato
	studente_t alunno[numero_righe("./elenco_nomi")];
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
	for(int i=0;i<numero_righe("./elenco_nomi");i++){	
		fgets(alunno[i].nome,50,elenco);
		fgets(alunno[i].cognome,50,elenco);
		char temp[50];
		fgets(temp,50,elenco);
		alunno[i].matricola=atoi(temp);
		
	}
	fclose(elenco);

	//ordino gli studenti in ordine alfabetico
	
}
