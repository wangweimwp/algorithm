#include <stdio.h>
#include <malloc.h> 
#include "heap.h"


static void heap_swim(struct heap_struct *heap)
{
	int k;
	unsigned int tmp;
	k = heap->num;

	while(k > 1){
		if(heap->heap_p[k / 2] < heap->heap_p[k]){
			tmp = heap->heap_p[k] ;
			heap->heap_p[k] = heap->heap_p[k / 2];
			heap->heap_p[k / 2] = tmp;
		}
		k = k / 2;
	}
}

static void heap_insert(struct heap_struct *heap, unsigned int n)
{
	heap->heap_p[++(heap->num)] = n;
	heap_swim(heap);
}




void heap_test(void)
{
	struct heap_struct heap;
	int arry[1000] = { 0 };
	int i;

	heap.heap_p = arry;
	heap.num = 0;

	arry[1] = 20;
	arry[2] = 17;
	arry[3] = 16;
	arry[4] = 14;
	arry[5] = 15;
	arry[6] = 15;
	arry[7] = 12;
	arry[8] = 10;
	heap.num = 8;
	heap_insert(&heap, 18);

	for(i = 1; i < 20; i ++){
		printf("%d %d\n", i, heap.heap_p[i]);
	}
}


