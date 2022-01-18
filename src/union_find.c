#include <stdio.h>
#include <malloc.h> 
#include "union_find.h"


static void uf_init(UF uf_point, int n)
{
	int i ;

	uf_point->num = n;
	uf_point->ele_and_group = (int *)malloc(sizeof(int) * n);

	for(i = 0; i < n; i++){
		uf_point->ele_and_group[i] = i;
	}
	return;
}


static int find(UF uf_point, int p)
{
	return uf_point->ele_and_group[p];
}

static int is_connected(UF uf_point, int p, int q)
{
	return find(p) == find(q);
	
}

static void union_group(UF uf_point, int p, int q)
{
	int p_group, q_group;
	int i;
	if(is_connected(uf_point, p, q)){
		return ;
	}

	p_group = find(p);
	q_group = find(q);

	for(i = 0; i < uf_point->num; i++){
		if(uf_point->ele_and_group[i] == q_group){
			uf_point->ele_and_group[i] = p_group;
		}
		
	}

	uf_point->num --;
	return;
}

void union_find(void)
{
	UF uf_group;

	uf_init(&uf_group, 10);
	union_group(&uf_group, 1, 2);
	printf("%d\n", uf_group.num);
	union_group(&uf_group, 1, 2);
	printf("%d\n", uf_group.num);
	union_group(&uf_group, 1, 3);
	printf("%d\n", uf_group.num);
}

