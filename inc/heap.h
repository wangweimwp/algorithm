#ifndef __HEAP_H
#define __HEAP_H


typedef struct heap_struct
{
	int *heap_p;
	unsigned int num;
}heap;


void heap_test(void);
#endif