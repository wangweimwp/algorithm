#include <stdio.h>
#include <malloc.h> 
#include "red_black_tree.h"


rb_node *rotate_left(rb_node *h)
{

	rb_node x = h->right;

	h->right = x->left;
	x->left = h;
	x.color = h.color;
	h.color = RED;
	return x;
}

rb_node *rotate_right(rb_node *h)
{

	rb_node x = h->left;

	h->left = x->right;
	x->right = h;
	x.color = h.color;
	h.color = RED;
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

	if((root->left->color == BLACK) && (root->right->color == RED)){
		root = rotate_left(root);
	}
	if((root->left == RED) && (root->left->left->color == RED)){
		root = rotate_right(root);
	}
	if(root->left->color == RED) && (root->right->color == RED){
		root = flip_color(root);
	}

	return root;
}
























