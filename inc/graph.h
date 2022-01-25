#ifndef __GRAPH_H
#define __GRAPH_H


typedef struct dfs_struct{
	int *marked;
	int searched;
};

typedef struct bfs_struct{
	int *marked;
	int *queue_tmp;
	int q_p1, q_p2;
	int searched;
};

typedef struct graph_struct{
	int point;
	int edge;
	int queue[100][100];
	struct dfs_struct dfs;
	struct bfs_struct bfs;
}graph;


void graph_test(void);
#endif