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
	graph_p->onstack = (int *)malloc(point * sizeof(int));
	graph_p->order = (int *)malloc(point * sizeof(int));
	graph_p->bfs.marked = (int *)malloc(point * sizeof(int));
	graph_p->dfs.edgto = (int *)malloc(point * sizeof(int));
	graph_p->bfs.queue_tmp = (int *)malloc(point * sizeof(int));
	for(i = 0; i < point; i++){
		for(j = 0; j < point; j++){
			graph_p->queue[i][j] = -1;
		}
		graph_p->dfs.marked[i] = -1;
		graph_p->order[i] = -1;
		graph_p->onstack[i] = -1;
		graph_p->bfs.marked[i] = -1;
		graph_p->bfs.queue_tmp[i] = -1;
	}
	graph_p->dfs.searched = 0;
	graph_p->bfs.searched = 0;
	graph_p->bfs.q_p1 = 0;
	graph_p->bfs.q_p2 = 0;
	graph_p->stack_point = point - 1;
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
			graph_p->dfs.edgto[graph_p->queue[point][i]] = point;
			dfs(graph_p, graph_p->queue[point][i]);
		}
	}
	graph_p->dfs.searched ++;

	return;
}

static void bfs(graph *graph_p, int point)
{
	int tmp = 0;
	int i;
	graph_p->bfs.marked[point] = 1;
	graph_p->bfs.queue_tmp[graph_p->bfs.q_p1] = point;
	graph_p->bfs.q_p1 ++;
	graph_p->bfs.searched++;

	while(graph_p->bfs.queue_tmp[graph_p->bfs.q_p2] != -1){
		tmp = graph_p->bfs.queue_tmp[graph_p->bfs.q_p2];
		graph_p->bfs.q_p2 ++;
		for(i = 0; graph_p->queue[tmp][i] != -1; i++){
			if(graph_p->bfs.marked[graph_p->queue[tmp][i]] == -1){
				graph_p->bfs.marked[graph_p->queue[tmp][i]] = 1;
				graph_p->bfs.queue_tmp[graph_p->bfs.q_p1] = graph_p->queue[tmp][i];
				graph_p->bfs.q_p1 ++;
				graph_p->bfs.searched++;
			}
		}
	}

	
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

static void depth_first_paths(graph *graph_p, int start, int end)
{
	int tmp;
	if(!is_connected(graph_p, start, end))
		return;

	tmp = end;
	printf("%d ", end);
	while(tmp != start){
		tmp = graph_p->dfs.edgto[tmp];
		printf("%d ", tmp);
	}
	printf("\n");
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

	depth_first_paths(&gra, 3, 6);
	
	print_queue(&gra, 6);

	ret = edge_count(&gra, 0);
	printf("ret = %d\n", ret);
	ret = is_connected(&gra, 5, 6);
	printf("ret = %d\n", ret);

	bfs(&gra, 0);
	printf("searched = %d\n", gra.bfs.searched);
}


/**********************************************************************************************/


static void dic_add_edge(graph *graph_p, int point1, int point2)
{
	int i;
	for(i = 0; graph_p->queue[point1][i] != -1; i++){}
	graph_p->queue[point1][i] = point2;
	graph_p->edge ++;
	return;
}

static void revert_dic_graph(graph *graph_p, graph *res)
{
	int i, j;
	graph_init(res, graph_p->point);
	for(i = 0; i < graph_p->point; i++){
		for(j = 0; graph_p->queue[i][j] != -1; j++)
		dic_add_edge(res, graph_p->queue[i][j], i);
	}
	return;
}
static int dic_dfs(graph *graph_p, int point)
{
	int i;
	printf("point = %d \n", point);
	graph_p->dfs.marked[point] = 1;
	graph_p->onstack[point] = 1;
	for(i = 0; graph_p->queue[point][i] != -1; i++){
		if(graph_p->dfs.marked[graph_p->queue[point][i]] != 1){
			graph_p->dfs.edgto[graph_p->queue[point][i]] = point;
			dic_dfs(graph_p, graph_p->queue[point][i]);
		}
		if(graph_p->onstack[graph_p->queue[point][i]] != -1)
			return 1;
	}
	graph_p->onstack[point] = -1;
	graph_p->order[graph_p->stack_point--] = point;
	graph_p->dfs.searched ++;
	return 0;
}


static int dic_is_cycle(graph *graph_p)
{
	int i;

	for(i = 0; i < graph_p->point; i++){
		if(graph_p->dfs.marked[i] == -1){
			if(dic_dfs(graph_p, i) == 1){
				return 1;
			}
		}
	}
	return 0;
}
/*特殊例子0->1  	0->2	1->2*/
void top_logic_test(void)
{
	graph gra;
	int i;
	int res;
	
	graph_init(&gra, 6);
	dic_add_edge(&gra, 0, 2);
	dic_add_edge(&gra, 0, 3);
	dic_add_edge(&gra, 2, 4);
	dic_add_edge(&gra, 3, 4);
	dic_add_edge(&gra, 4, 5);
	dic_add_edge(&gra, 1, 3);

	res = dic_is_cycle(&gra);
	printf("res = %d\n", res);
	for(i = 0; i < 6; i++){
		printf("%d-> ", gra.order[i]);
	}
	printf("\n");
}

/***********************加权无向图****************************************/

static inline int either(Edge *edge)
{
	return edge->v;
}
static inline int other(Edge *edge, int point)
{
	return edge->v == point? edge->w : edge->v;
}
/*比较规则*/
static int compare_to(Edge *edge1, Edge *edge2)
{
	if(edge1->wright > edge2->wright){
		return 1;
	}else if(edge1->weight > edge2->weight){
		return -1;
	}else{
		return 0;
	}
}


void graph_weighted_init(graph_weighted *graph, int point)
{
	int i, j;
	graph->points = point;
	graph->edges = 0;
	for(i = 0; i < 100; i++){
		for(j = 0; j < 100; j++){
			graph->edge_queue[i][j].v = -1;
			graph->edge_queue[i][j].w = -1;
			graph->edge_queue[i][j].weight = -1;
		}
	}

	return;
}

void add_edge_gra_weighted(graph_weighted *graph, Edge *edge)
{
	int v, w;
	int i;
	v = either(edge);
	w = other(edge, v);

	for(i = 0; i < graph.points; i ++){
		if(graph->edge_queue[v][i].v == -1)
			break;
	}
	graph->edge_queue[v][i].v = v;	
	graph->edge_queue[v][i].w = w;
	graph->edge_queue[v][i].weight = edge.wright;

	for(i = 0; i < graph.points; i ++){
		if(graph->edge_queue[w][i].v == -1)
			break;
	}
	graph->edge_queue[w][i].v = v;	
	graph->edge_queue[w][i].w = w;
	graph->edge_queue[w][i].weight = edge.wright;

	graph->edges++;
	return;
}

void pri_MST(graph_weighted *graph)
{
	/*索引代表顶点，存储当前顶点到最小生成树之间的最短边*/
	Edge edges[100];
	/*索引代表顶点，存储当前顶点到最小生成树之间的最短边*/
	int weights[100];
	/*索引代表顶点，存储当前顶点是否在树中*/
	int mark[100];
	/*存放树中顶点与非树中顶点之间的有效横切边*/
	int index_pri_queue[100];

	int i;
	for(i = 0; i < 100; i++){
		edges[i].v = -1;
		edges[i].w = -1;
		edges[i].weight = -1;
		weights[i] = -1;
		mark[i] = -1;
		index_pri_queue[i] = -1;
	}

	
	
}


