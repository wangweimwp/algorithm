#ifndef __RED_BLACK_H
#define __RED_BLACK_H



#define BLACK	0
#define RED		1

typedef struct red_black_node
{
	int key;
	unsigned char *data;
	struct red_black_node *left, *right;
	int color;
}rb_node;

void red_black_tree_test(void);
#endif