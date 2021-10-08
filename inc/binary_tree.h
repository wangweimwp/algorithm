#ifndef __BINARY_TREE_H


typedef struct binary_tree_node
{
	unsigned int key;
	unsigned char *data;
	struct binary_tree_node *left, *right;
}bin_node;

void binary_tree_test(void);
#endif