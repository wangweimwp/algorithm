#ifndef __GRAPH_H
#define __GRAPH_H


typedef struct dfs_struct{
	int *marked;
	int searched;
};
typedef struct graph_struct{
	int point;
	int edge;
	int queue[100][100];
	struct dfs_struct dfs;
}graph;


void graph_test(void);
#endif