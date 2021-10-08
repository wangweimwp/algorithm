#include <stdio.h>
#include "binary_tree.h"


struct binary_tree_node root = {0};

void binary_tree_put(struct binary_tree_node *root, struct binary_tree_node *node)
{
	if(root == NULL)
		return;
	if(node->key < root->key){
		if(root->left == NULL){
			root->left = node;
			return;
		}else{
		binary_tree_put(root->left, node);
		return;
		}
		
	}else if(node->key > root->key){
		if(root->right == NULL){
			root->right = node;
			return;
		}else{
		binary_tree_put(root->right, node);
		return;
		}
		
	}else{
		root->data = node->data;
		return;
	}

}


unsigned char *binary_tree_get(struct binary_tree_node *root, unsigned int key)
{
	if(root == NULL)
		return NULL;
	if(key < root->key){
		return binary_tree_get(root->left, key);
	}else if(key > root->key){
		return binary_tree_get(root->right, key);
	}else if(key == root->key){
		return root->data;
	}else{
		return NULL;
	}
}

void binary_tree_test(void)
{
	struct binary_tree_node node[10] = {0};

	root.key = 20;
	root.data = "wangwei";

	node[0].key = 21;
	node[0].data = "xialaoban";

	node[1].key = 19;
	node[1].data = "binge";

	node[2].key = 25;
	node[2].data = "wanggong";

	binary_tree_put(&root, &node[0]);
	binary_tree_put(&root, &node[1]);
	binary_tree_put(&root, &node[2]);

	printf("%s \n", root.left->data);
	printf("%s \n", root.right->data);
	printf("%s \n", root.right->right->data);

	printf("%s \n", binary_tree_get(&root, 25));
}



