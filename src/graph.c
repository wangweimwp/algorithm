#include <stdio.h>
#include <malloc.h> 
#include "graph.h"


static void graph_init(graph *graph_p, int point)
{
	int i, j;
	graph_p->point = point;
	graph_p->edge = 0;
	//graph_p->queue = (int **)malloc(point * point * sizeof(int));
	graph_p->dfs.marked = (int *)malloc(point * sizeof(int));
	graph_p->bfs.marked = (int *)malloc(point * sizeof(int));
	graph_p->bfs.queue_tmp = (int *)malloc(point * sizeof(int));
	for(i = 0; i < point; i++){
		for(j = 0; j < point; j++){
			graph_p->queue[i][j] = -1;
		}
		graph_p->dfs.marked[i] = -1;
		graph_p->bfs.marked[i] = -1;
		graph_p->bfs.queue_tmp[i] = -1;
	}
	graph_p->dfs.searched = 0;
	graph_p->bfs.searched = 0;
	graph_p->bfs.q_p1 = 0;
	graph_p->bfs.q_p2 = 0;
	return;
}

static void add_edge(graph *graph_p, int point1, int point2)
{
	int i;
	for(i = 0; graph_p->queue[point1][i] != -1; i++){}
	graph_p->queue[point1][i] = point2;
	for(i = 0; graph_p->queue[point2][i] != -1; i++){}
	graph_p->queue[point2][i] = point1;
	graph_p->edge ++;
	return;
	
}

static void print_queue(graph *graph_p, int point)
{
	int i;
	for(i = 0; graph_p->queue[point][i] != -1; i++){
		printf("point %d = %d\n", i, graph_p->queue[point][i]);
	}
	return;
}

static void dfs(graph *graph_p, int point)
{
	int i;
	graph_p->dfs.marked[point] = 1;
	for(i = 0; graph_p->queue[point][i] != -1; i++){
		if(graph_p->dfs.marked[graph_p->queue[point][i]] != 1){
			dfs(graph_p, graph_p->queue[point][i]);
		}
	}
	graph_p->dfs.searched ++;

	return;
}

static void bfs(graph *graph_p, int point)
{
/*感觉有问题，和深度优先搜索逻辑一样*/
	int tmp = 0;
	int i;
	graph_p->bfs.marked[point] = 1;
	graph_p->bfs.queue_tmp[graph_p->bfs.q_p1] = point;
	graph_p->bfs.q_p1 ++;

	while(graph_p->bfs.queue_tmp[graph_p->bfs.q_p2] != -1){
		tmp = graph_p->bfs.queue_tmp[graph_p->bfs.q_p2];
		graph_p->bfs.q_p2 ++;
		for(i = 0; graph_p->queue[tmp][i] != -1; i++){
			if(graph_p->bfs.marked[graph_p->queue[tmp][i]] == -1){
				
				bfs(graph_p, graph_p->queue[tmp][i]);
			}
		}
	}
	graph_p->bfs.searched++;
}

static int is_connected(graph *graph_p, int point1, int point2)
{
	dfs(graph_p, point1);
	return graph_p->dfs.marked[point2] == 1;
}

static int edge_count(graph *graph_p, int point)
{
	dfs(graph_p, point);
	return graph_p->dfs.searched;
}

void graph_test(void)
{
	graph gra;
	int ret;
	graph_init(&gra, 13);
	add_edge(&gra, 0, 5);
	add_edge(&gra, 0, 1);
	add_edge(&gra, 0, 2);
	add_edge(&gra, 0, 6);
	add_edge(&gra, 5, 3);
	add_edge(&gra, 5, 4);
	add_edge(&gra, 3, 4);
	add_edge(&gra, 4, 6);

	add_edge(&gra, 7, 8);

	add_edge(&gra, 9, 10);
	add_edge(&gra, 9, 11);
	add_edge(&gra, 9, 12);
	add_edge(&gra, 11, 12);
	
	print_queue(&gra, 6);

	ret = edge_count(&gra, 0);
	printf("ret = %d\n", ret);
	ret = is_connected(&gra, 5, 6);
	printf("ret = %d\n", ret);

	bfs(&gra, 0);
	printf("searched = %d\n", gra.bfs.searched);
}


