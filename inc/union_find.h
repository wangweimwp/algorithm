#ifndef __UNION_FIND_H
#define __UNION_FIND_H

typedef struct union_find_struct{
	int *ele_and_group;
	int num;
}UF;


typedef struct union_find_tree_weight_struct{
	int *ele_and_group;
	int *size;
	int num;
}UF_tree_weight;


void union_find(void);
void uf_tw_test(void);


#endif


