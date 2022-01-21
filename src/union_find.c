#include <stdio.h>
#include <malloc.h> 
#include "union_find.h"


static void uf_init(UF *uf_point, int n)
{
	int i ;

	uf_point->num = n;
	uf_point->ele_and_group = (int *)malloc(sizeof(int) * n);

	for(i = 0; i < n; i++){
		uf_point->ele_and_group[i] = i;
	}
	return;
}


static int find(UF *uf_point, int p)
{
	return uf_point->ele_and_group[p];
}

static int is_connected(UF *uf_point, int p, int q)
{
	return find(uf_point, p) == find(uf_point, q);
	
}

static void union_group(UF *uf_point, int p, int q)
{
	int p_group, q_group;
	int i;
	if(is_connected(uf_point, p, q)){
		return ;
	}

	p_group = find(uf_point, p);
	q_group = find(uf_point, q);

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

/*************************************************************************************************/

static void uf_tw_init(UF_tree_weight *uf_tw_point, int n)
{
	int i;
	if(uf_tw_point == NULL)
		return;
	
	uf_tw_point->num = n;
	uf_tw_point->ele_and_group =(int *) malloc(sizeof(int) * n);
	uf_tw_point->size =(int *) malloc(sizeof(int) * n);

	for(i = 0; i < n; i++){
		uf_tw_point->ele_and_group[i] = i;
		uf_tw_point->size[i] = 1;
	}

	return ;
}

static int uf_tw_find(UF_tree_weight *uf_tw_point, int p)
{
	int tmp_p = p;
	while(tmp_p != uf_tw_point->ele_and_group[tmp_p]){
		tmp_p = uf_tw_point->ele_and_group[tmp_p];
	}
		
	return tmp_p;
}

static int uf_tw_is_connected(UF_tree_weight *uf_tw_point, int p, int q)
{
	return uf_tw_find(uf_tw_point, p) == uf_tw_find(uf_tw_point, q);
	
}

static void uf_tw_union_group(UF_tree_weight *uf_tw_point, int p, int q)
{
	int p_root, q_root;
	int i;
	if(uf_tw_is_connected(uf_tw_point, p, q)){
		return ;
	}

	p_root = uf_tw_find(uf_tw_point, p);
	q_root = uf_tw_find(uf_tw_point, q);

	if(uf_tw_point->size[p_root] > uf_tw_point->size[q_root]){
		uf_tw_point->ele_and_group[q_root] = p_root;
		uf_tw_point->size[p_root] += uf_tw_point->size[q_root];
	}else{
		uf_tw_point->ele_and_group[p_root] = q_root;
		uf_tw_point->size[q_root] += uf_tw_point->size[p_root];
	}
	uf_tw_point->num --;
	return;
}

void uf_tw_test(void)
{
	UF_tree_weight uf_tw_group;

	uf_tw_init(&uf_tw_group, 10);
	uf_tw_union_group(&uf_tw_group, 1, 2);
	printf("%d\n", uf_tw_group.num);
	printf("%d, %d\n", uf_tw_is_connected(&uf_tw_group, 1, 2),
						uf_tw_is_connected(&uf_tw_group, 1, 3));
	uf_tw_union_group(&uf_tw_group, 1, 2);
	printf("%d\n", uf_tw_group.num);
	printf("%d, %d\n", uf_tw_is_connected(&uf_tw_group, 1, 2), 
						uf_tw_is_connected(&uf_tw_group, 1, 3));
	uf_tw_union_group(&uf_tw_group, 2, 3);
	printf("%d\n", uf_tw_group.num);
	printf("%d, %d\n", uf_tw_is_connected(&uf_tw_group, 1, 2), 
						uf_tw_is_connected(&uf_tw_group, 1, 3));
}



