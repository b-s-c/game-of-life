#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"

struct node *head=NULL;

void add_to_list(int n){
	struct node *new_node = malloc(sizeof(struct node));
		if (new_node==NULL)
			exit(1);
	new_node->data=n;
	new_node->next=head;
	head=new_node;
}

void print_list(){
	printf("Printing out\n");
	struct node *ptr=head;
	while(ptr!=NULL){
		printf("%d\n",ptr->data);
		ptr=ptr->next;
	};
}

