#include <stdio.h>
#include <malloc.h> 
#include "red_black_tree.h"


rb_node *rotate_left(rb_node *h)
{

	rb_node *x = h->right;

	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}

rb_node *rotate_right(rb_node *h)
{

	rb_node *x = h->left;

	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}

void flip_color(rb_node *h)
{
	h->color = RED;
	h->left->color = BLACK;
	h->right->color = BLACK;
	return;
}

rb_node * put(rb_node *root, rb_node *node)
{
	if(root == NULL){
		node->color = RED;
		return node;
	}

	if(node->key < root->key){
		root->left = put(root->left, node);
	}else if(node->key > root->key){
		root->right = put(root->right, node);
	}else{
		root->data = node->data;
	}

	if((root->left != NULL) && (root->right != NULL)){
		if((root->left->color == BLACK) && (root->right->color == RED)){
			root = rotate_left(root);
		}
		if(root->left->left != NULL){
			if((root->left ->color == RED) && (root->left->left->color == RED)){
				root = rotate_right(root);
			}
		}
		if((root->left->color == RED) && (root->right->color == RED)){
			flip_color(root);
		}
	}

	return root;
}



rb_node * get(rb_node *root, int key)
{
	if(root == NULL){
		return NULL;
	}

	if(root->key < key){
		return get(root->right, key);
	}else if(root->key > key){
		return get(root->left, key);
	}else{
		return root;
	}
}


void red_black_tree_test(void)
{

	rb_node node[10] = { 0 };
	rb_node *root = NULL;
	rb_node *out_node = NULL;

	node[0].key = 22;
	node[0].data = "xialaoban";

	node[1].key = 19;
	node[1].data = "binge";
	
	node[2].key = 25;
	node[2].data = "wanggong";

	node[3].key = 21;
	node[3].data = "yuqi";

	node[4].key = 23;
	node[4].data = "yanglei";

	node[5].key = 26;
	node[5].data = "xuhuaqin";

	node[6].key = 18;
	node[6].data = "hikvision";

	root = put(root, &node[0]);
	printf("%s\n", root->data);

	root = put(root, &node[1]);
	root = put(root, &node[2]);
	root = put(root, &node[3]);
	root = put(root, &node[4]);
	root = put(root, &node[5]);
	root = put(root, &node[6]);

	out_node = get(root, 23);

	printf("%s\n", out_node->data);


	
	
}


















