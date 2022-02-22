#ifndef __GRAPH_H
#define __GRAPH_H


typedef struct dfs_struct{
	int *marked;
	int *edgto;//查找路径时使用
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
	int *onstack; //有向图检测是否有环时使用
	int *order;//有向图顶点排序使用
	int stack_point;//有向图顶点排序使用
	struct dfs_struct dfs;
	struct bfs_struct bfs;
	
}graph;


typedef struct edge_struct{
	int v;
	int w;
	int weight;
}Edge;

typedef struct graph_weighted_struct{
	int points;
	int edges;
	struct edge_struct edge_queue[100][100];
}graph_weighted;


void graph_test(void);
void top_logic_test(void);
#endif
