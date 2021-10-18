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

struct binary_tree_node *binary_tree_dele(struct binary_tree_node *root, unsigned int key)
{
	struct binary_tree_node *tmp_node1, *tmp_node2;

	if(root == NULL)
		return NULL;
#if 1
	if(key < root->key){
		root->left = binary_tree_dele(root->left, key);
	}else if(key > root->key){
		root->right = binary_tree_dele(root->right, key);
	}else if(key == root->key){
		if(root->right == NULL){
			return root->left;
		}else if(root->left == NULL){
			return root->right;
		}else{
			tmp_node1 = root->right;
			tmp_node2 = root->right;
			while(tmp_node1->left != NULL){
				tmp_node1 = tmp_node1->left;
			}
			while(tmp_node2->left != NULL){
				if(tmp_node2->left->left == NULL){
					tmp_node2->left = NULL;
				}else{
					tmp_node2 = tmp_node2->left;
				}
			}
			tmp_node1->left = root->left;
			tmp_node1->right = root->right;
			root = tmp_node1;
			
		}
	}
#endif

	return root;

}

void binary_tree_test(void)
{
	struct binary_tree_node node[10] = {0};

	struct binary_tree_node *del_node;

	root.key = 20;
	root.data = "wangwei";

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

	binary_tree_put(&root, &node[0]);
	binary_tree_put(&root, &node[1]);
	binary_tree_put(&root, &node[2]);
	binary_tree_put(&root, &node[3]);
	binary_tree_put(&root, &node[4]);
	binary_tree_put(&root, &node[5]);

	printf("%s \n", root.left->data);
	printf("%s \n", root.right->data);
	printf("%s \n", root.right->right->data);
	printf("%s \n", root.right->left->data);
	printf("%s \n", root.right->right->left->data);
	printf("%s \n", root.right->right->right->data);
	del_node = binary_tree_dele(&root, 22);
	printf("after dele %s \n", del_node->right->data);

	printf("%s \n", binary_tree_get(&root, 25));
}



