#include "ttree.h"

int n=14;
const int chiavi[]={1,1,1,1,1,1,1,7,-8,-4,-3,4,-10,-9,80,22,-56,15,15,15,13,14};

int main(void){
	nodo_t *root=NULL;
	n=sizeof(chiavi)/sizeof(int);
	for (int i=0;i<n;i++) inserisci(chiavi[i],&root);
	/*stampa_albero(root,stdout);
	int a;
	scanf("%d",&a);
	cancella(a,&root);
	stampa_albero(root,stdout);
	inserisci(a,&root);
	stampa_albero(root,stdout);
	scrivi_albero(stdout,root);
	printf("-------------------\n");
	ordine(root);
	*/
	//cerca1(root);
	free_albero(&root);
	scrivi_albero(stdout,root);
}
