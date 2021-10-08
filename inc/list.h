#ifndef __LIST_H
#define __LIST_H

typedef struct list_node
{
	struct list_node *prev;
	struct list_node *next;
	unsigned int data;	
}node;

void list_reverse_test(void);




#endif
