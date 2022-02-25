#ifndef __UNION_FIND_H
#define __UNION_FIND_H

typedef struct union_find_struct{
	int *ele_and_group;
	int point;
	int num;
}UF;


typedef struct union_find_tree_weight_struct{
	int *ele_and_group;
	int *size;
	int num;
}UF_tree_weight;


void union_find(void);
void uf_tw_test(void);
int is_connected_uf(UF *uf_point, int p, int q);
void uf_init(UF *uf_point, int n);

void union_group(UF *uf_point, int p, int q);


#endif


