#include <stdlib.h>
#include <stdio.h>

typedef struct list{
	int num;
	struct list *next;
}list_t;

list_t* list_of_numbers=NULL;
int numbers[8]={7,4,9,12,4,6,8,2};

list_t * put_num_in_list (int n,list_t* l){	
	static int a=0;
	int b=0,c=0;
	if(a==0) b++,a++;

	if(l==NULL) c=1;
	else{
		if(n>l->num) c=1;
		if(n<l->num) c=-1;
	}

  if(c==0) return l;
  if(c==-1) put_num_in_list(n,l->next);

  if(c==1){
    list_t *temp=(list_t *)malloc(sizeof(list_t));
    if(temp==NULL){
      fprintf(stderr, "error\n");
      return EXIT_FAILURE;
    }   
    if(l!=NULL){   
      temp->num=n;
      temp->next=l;  
      l=temp;
    }
    if(l==NULL){//se si trova alla fine
      l=temp;
      l->next=NULL;
      l->num=n;
    }
  }
  if(b==1){
    a=0,b=0;return l;
  }
}

void print_list(list_t* l){
	if(l==NULL) return;
	printf("%d\n",l->num);
	print_list(l->next);
}

int main(void){
	for(int i=0;i<8;i++){
		put_num_in_list(numbers[i],list_of_numbers);
	}
	print_list(list_of_numbers);
}



