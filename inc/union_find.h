#ifndef __UNION_FIND_H
#define __UNION_FIND_H

typedef struct union_find_struct{
	int *ele_and_group;
	int num;
}UF;

void union_find(void);

#endif


