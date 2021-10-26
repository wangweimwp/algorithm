#include <stdio.h>
#include "binary_tree.h"
#include "list.h"
#include <malloc.h> 



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
void binary_perergodic(struct binary_tree_node *root)
{
	if(root == NULL)
		return;
	printf("key = %d, data = %s\n", root->key, root->data);

	if(root->left != NULL){
		binary_perergodic(root->left);
	}
	if(root->right != NULL){
		binary_perergodic(root->right);
	}
	return;
}

void binary_midergodic(struct binary_tree_node *root)
{
	if(root == NULL)
		return;

	if(root->left != NULL){
		binary_midergodic(root->left);
	}

	printf("key = %d, data = %s\n", root->key, root->data);
	
	if(root->right != NULL){
		binary_midergodic(root->right);
	}
	return;
}

void binary_bakergodic(struct binary_tree_node *root)
{
	if(root == NULL)
		return;

	if(root->left != NULL){
		binary_bakergodic(root->left);
	}
	
	if(root->right != NULL){
		binary_bakergodic(root->right);
	}

	printf("key = %d, data = %s\n", root->key, root->data);
	return;
}

void binary_layer_ergodic(struct binary_tree_node *root)
{
	struct binary_tree_node *node_p[20] = { 0 };
	int index1, index2;
	index1 = 0;
	index2 = 0;
	node_p[index1++] = root;

	while(index2 < index1){
		/*如果有左子节点，则把左子节点放入队列*/
		if(node_p[index2]->left != NULL){
			node_p[index1++] = node_p[index2]->left;
		}
		/*如果有右子节点，则把右子节点放入队列*/
		if(node_p[index2]->right != NULL){
			node_p[index1++] = node_p[index2]->right;
		}
		/*弹出一个节点*/
		printf("key = %d, data = %s\n", node_p[index2]->key, node_p[index2]->data);
		index2++;
	}
}

static void binary_paper_fold(unsigned int N)
{
	struct binary_tree_node root = {0};
	struct binary_tree_node *tmp_node;
	struct binary_tree_node *node_p[20] = { 0 };
	int i;
	int index1, index2;
	index1 = 0;
	index2 = 0;

	for(i = 0; i < N; i++){
		/*第一次对折*/
		if(i == 0){
			root.data = "down";
			continue;
		}
		/*不是第一次对折*/
		node_p[index1++] = &root;
		while(index2 < index1){
			if(node_p[index2]->left != NULL){
				node_p[index1++] = node_p[index2]->left;
			}
			if(node_p[index2]->right != NULL){
				node_p[index1++] = node_p[index2]->right;
			}
			if((node_p[index2]->left == NULL) || (node_p[index2]->right == NULL)){
				tmp_node =(struct binary_tree_node *) malloc(sizeof(struct binary_tree_node));
				tmp_node->data = "down";
				tmp_node->left = NULL;
				tmp_node->right = NULL;
				node_p[index2]->left = tmp_node;
				tmp_node =(struct binary_tree_node *) malloc(sizeof(struct binary_tree_node));
				tmp_node->data = "up";
				tmp_node->left = NULL;
				tmp_node->right = NULL;
				node_p[index2]->right = tmp_node;
			}
			index2++;
		}
		
	}
	printf("fold %s\n", root.left->right->data);

	binary_midergodic(&root);

	/*释放内存*/
/*
	for(i = 1; i < 20; i++){
		if(node_p[i] != 0){
			free((void *)node_p[i]);
			printf("addr = %x\n", node_p[i]);
		}
	}
*/	
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

	node[6].key = 18;
	node[6].data = "hikvision";
	binary_tree_put(&root, &node[0]);
	binary_tree_put(&root, &node[1]);
	binary_tree_put(&root, &node[2]);
	binary_tree_put(&root, &node[3]);
	binary_tree_put(&root, &node[4]);
	binary_tree_put(&root, &node[5]);
	binary_tree_put(&root, &node[6]);
	binary_perergodic(&root);
	printf("\n");
	binary_midergodic(&root);
	printf("\n");
	binary_bakergodic(&root);

	printf("binary_layer_ergodic\n");
	binary_layer_ergodic(&root);

	printf("%s \n", root.left->data);
	printf("%s \n", root.right->data);
	printf("%s \n", root.right->right->data);
	printf("%s \n", root.right->left->data);
	printf("%s \n", root.right->right->left->data);
	printf("%s \n", root.right->right->right->data);
	del_node = binary_tree_dele(&root, 22);
	printf("after dele %s \n", del_node->right->data);
	binary_perergodic(del_node);
	printf("%s \n", binary_tree_get(&root, 25));
	printf("binary_layer_ergodic\n");
	binary_layer_ergodic(&root);


	printf("binary_paper_fold\n");
	binary_paper_fold(3);
}



