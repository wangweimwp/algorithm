#include <stdio.h>
#include "list.h"

#define list_reverse(node)		__list_reverse(node, node->next)

void __list_reverse(node *hand, node *curr)
{
	
	if(curr->next == NULL){
		hand->next = curr;
		return;
	}else{
		__list_reverse(hand, curr->next);
		curr->next->next = curr;
		curr->next = NULL;
	}
		
}


void list_reverse_test(void)
{
	node nodes[10] = { 0 };
	node list_hand;
	node *temp ;
	temp = &list_hand;
	unsigned int data;

	nodes[0].data = 1;
	list_hand.next  = &nodes[0];

	nodes[1].data = 2;
	nodes[0].next = &nodes[1];

	nodes[2].data = 3;
	nodes[1].next = &nodes[2];

	nodes[3].data = 4;
	nodes[2].next = &nodes[3];

	
	while(temp->next){
		temp = temp->next;
		printf("%d ", temp->data);
	}
	printf("\n");
	
	temp = &list_hand;
	list_reverse(temp);

	temp = &list_hand;
	while(temp->next){
		temp = temp->next;
		printf("%d ", temp->data);
	}
	printf("\n");
	return ;
}


