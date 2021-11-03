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

static void heap_sink(struct heap_struct *heap, unsigned int k, unsigned int rang)
{
	unsigned max;
	int tmp;

	while(2 * k <= rang){
		if(2 * k + 1 <= rang){
			if(heap->heap_p[2 * k] < heap->heap_p[2 * k + 1]){
				max = 2 * k + 1;
			}else{
				max = 2 * k;
			}
		}else{
			max = 2 * k;
		}

		if(heap->heap_p[k] >= heap->heap_p[max]){
			break;
		}else{
			tmp = heap->heap_p[k];
			heap->heap_p[k] = heap->heap_p[max];
			heap->heap_p[max] = tmp;
			k = max;
		}

	}
}

static void heap_insert(struct heap_struct *heap, unsigned int n)
{
	heap->heap_p[++(heap->num)] = n;
	heap_swim(heap);
}

static void heap_delmax(struct heap_struct *heap)
{
	unsigned int max;
	max = 1;

	heap->heap_p[1] = heap->heap_p[heap->num];
	heap->heap_p[heap->num] = 0;

	heap->num--;

	heap_sink(heap, 1, heap->num);

	return;
}


static void heap_creat(struct heap_struct *heap)
{
	int i;
	int tmp;
	tmp = heap->num / 2;

	for(i = tmp; i > 0; i--){
		heap_sink(heap, i, heap->num);
	}

	return;
}

static void heap_sort(struct heap_struct *heap)
{
	int i;
	int tmp;
	i = heap->num;

	while(i > 1){
		tmp = heap->heap_p[i];
		heap->heap_p[i] = heap->heap_p[1];
		heap->heap_p[1] = tmp;
		heap_sink(heap, 1, --i);
	}
}


void heap_test(void)
{
	struct heap_struct heap;
	int arry[1000] = { 0 };
	int i;

	heap.heap_p = arry;
	heap.num = 0;

	arry[1] = 35;
	arry[2] = 2;
	arry[3] = 14;
	arry[4] = 23;
	arry[5] = 43;
	arry[6] = 22;
	arry[7] = 7;
	arry[8] = 26;
	heap.num = 8;

	heap_creat(&heap);
	heap_insert(&heap, 27);
	//heap_delmax(&heap);
	heap_sort(&heap);

	for(i = 1; i < 20; i ++){
		printf("%d %d\n", i, heap.heap_p[i]);
	}
}


