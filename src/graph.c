#include <stdio.h>
#include <malloc.h> 
#include "graph.h"
#include "union_find.h"



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
/*????????????0->1  	0->2	1->2*/
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

/***********************???????????????****************************************/

static inline int either(Edge *edge)
{
	return edge->v;
}
static inline int other(Edge *edge, int point)
{
	return edge->v == point? edge->w : edge->v;
}
/*????????????*/
static int compare_to(Edge *edge1, Edge *edge2)
{
	if(edge1->weight > edge2->weight){
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

	for(i = 0; graph->edge_queue[v][i].v != -1; i ++){}
	printf("v = %d w = %d weight = %d i = %d\n", v, w, edge->weight, i);
	graph->edge_queue[v][i].v = v;
	graph->edge_queue[v][i].w = w;
	graph->edge_queue[v][i].weight = edge->weight;

	for(i = 0; graph->edge_queue[w][i].v != -1; i ++){}
	graph->edge_queue[w][i].v = v;	
	graph->edge_queue[w][i].w = w;
	graph->edge_queue[w][i].weight = edge->weight;

	graph->edges++;
	return;
}


//??????1  ???????????????
static int queue_is_empty(int *queue, int size)
{
	int i;
	for(i = 0; i < size; i++){
		if(queue[i] != -1)
			return 0;
	}
	return 1;
}

//????????????????????????????????????????????????????????????
static int del_return_nim_index(int *queue, int size)
{
	int i;
	int min = 1000, index_min = 0;
	for(i = 0; i < size; i ++){
		if((queue[i] < min) && (queue[i] > 0)){
			min = queue[i];
			index_min = i;
		}
	}
	queue[index_min] = -1;
	return index_min;
}


void pri_MST(graph_weighted *graph)
{
	int v, w;

	/*???????????????????????????????????????????????????????????????????????????*/
	Edge edges[100];
	/*??????????????????????????????????????????????????????*/
	int mark[100];
	/*????????????????????????????????????????????????????????????*/
	int index_pri_queue[100];

	int i;
	for(i = 0; i < 100; i++){
		edges[i].v = -1;
		edges[i].w = -1;
		edges[i].weight = -1;
		mark[i] = -1;
		index_pri_queue[i] = -1;
	}

	//??????0?????????????????????
	index_pri_queue[0] = 0;

	while(!queue_is_empty(index_pri_queue, graph->points)){
		v = del_return_nim_index(index_pri_queue, graph->points);
		printf("v = %d\n", v);
		//????????????????????????????????????????????????????????????
		mark[v] = 1;
		//????????????v????????????
		for(i =0; graph->edge_queue[v][i].v != -1; i++){
			w = other(&graph->edge_queue[v][i], v); //????????????????????????
			printf("w = %d\n", w);

			if(mark[w] == 1){//??????w???????????????????????????
				continue;
			}
			//??????????????????w????????????w???????????????????????????????????????????????????????????????
			if((index_pri_queue[w] > graph->edge_queue[v][i].weight) || 
				(index_pri_queue[w] < 0)){//?????????w??????????????????????????????????????????
				edges[w].v = graph->edge_queue[v][i].v;
				edges[w].w = graph->edge_queue[v][i].w;
				edges[w].weight = graph->edge_queue[v][i].weight;

				index_pri_queue[w] = graph->edge_queue[v][i].weight;
				printf("index_pri_queue[%d] = %d\n", w, index_pri_queue[w]);
				
			}
		}
	}

	for(i = 0; i < 100; i++){
		if(edges[i].v != -1){
			printf(" %d : edge 	v = %d 	w = %d 	weight = %d\n", 
				i, edges[i].v, edges[i].w, edges[i].weight);
		}
	}
	
}


void pri_MST_test(void)
{
	Edge edges[16] = {0};
	graph_weighted graph;
	int i;

	graph_weighted_init(&graph, 8);
	edges[0].v = 4; edges[0].w = 5; edges[0].weight = 35;
	edges[1].v = 4; edges[1].w = 7; edges[1].weight = 37;
	edges[2].v = 5; edges[2].w = 7; edges[2].weight = 28;
	edges[3].v = 0; edges[3].w = 7; edges[3].weight = 16;
	edges[4].v = 1; edges[4].w = 5; edges[4].weight = 32;
	edges[5].v = 0; edges[5].w = 4; edges[5].weight = 38;
	edges[6].v = 2; edges[6].w = 3; edges[6].weight = 17;
	edges[7].v = 1; edges[7].w = 7; edges[7].weight = 19;
	edges[8].v = 0; edges[8].w = 2; edges[8].weight = 26;
	edges[9].v = 1; edges[9].w = 2; edges[9].weight = 36;
	edges[10].v = 1; edges[10].w = 3; edges[10].weight = 29;
	edges[11].v = 2; edges[11].w = 7; edges[11].weight = 34;
	edges[12].v = 6; edges[12].w = 2; edges[12].weight = 40;
	edges[13].v = 3; edges[13].w = 6; edges[13].weight = 52;
	edges[14].v = 6; edges[14].w = 0; edges[14].weight = 58;
	edges[15].v = 6; edges[15].w = 4; edges[15].weight = 93;


	for(i = 0; i < 16; i++){
		add_edge_gra_weighted(&graph, &edges[i]);
	}

	printf("edges in graph is %d \n", graph.edges);

	pri_MST(&graph);

}



/*****************************kruskal ??????**********************************************/

static int is_edge_empty(Edge *edges)
{
	int i;
	for(i = 0; i < 100; i++){
		if(edges[i].weight != -1){
			return 0;
		}
	}
	return 1;
}

static int find_min_edg(Edge *edges)
{
	int i;
	int min_index, min_weight;
	min_weight = 1000;
	min_index = -1;
	for(i = 0; i < 100; i++){
		if((edges[i].weight < min_weight) && (edges[i].weight > 0)){
			min_weight = edges[i].weight;
			min_index = i;
		}
	}
	return min_index;
}



void kruskal_MST_test(void)
{
	graph_weighted graph;
	
	/*???????????????????????????????????????????????????????????????????????????*/
	Edge edges_mst[100];
	/*??????????????????*/
	Edge edges[100];
	/*???????????????????????????????????????????????????????????????????????????????????????*/
	UF uf_group;

	int i, j;
	int index;

	printf("kruskal_MST_test\n");

	for(i = 0 ; i < 100; i++){
		edges_mst[i].v = -1;
		edges_mst[i].w = -1;
		edges_mst[i].weight = -1;
		edges[i].v = -1;
		edges[i].w = -1;
		edges[i].weight = -1;
	}
	uf_init(&uf_group, graph.points);
	
	edges[0].v = 4; edges[0].w = 5; edges[0].weight = 35;
	edges[1].v = 4; edges[1].w = 7; edges[1].weight = 37;
	edges[2].v = 5; edges[2].w = 7; edges[2].weight = 28;
	edges[3].v = 0; edges[3].w = 7; edges[3].weight = 16;
	edges[4].v = 1; edges[4].w = 5; edges[4].weight = 32;
	edges[5].v = 0; edges[5].w = 4; edges[5].weight = 38;
	edges[6].v = 2; edges[6].w = 3; edges[6].weight = 17;
	edges[7].v = 1; edges[7].w = 7; edges[7].weight = 19;
	edges[8].v = 0; edges[8].w = 2; edges[8].weight = 26;
	edges[9].v = 1; edges[9].w = 2; edges[9].weight = 36;
	edges[10].v = 1; edges[10].w = 3; edges[10].weight = 29;
	edges[11].v = 2; edges[11].w = 7; edges[11].weight = 34;
	edges[12].v = 6; edges[12].w = 2; edges[12].weight = 40;
	edges[13].v = 3; edges[13].w = 6; edges[13].weight = 52;
	edges[14].v = 6; edges[14].w = 0; edges[14].weight = 58;
	edges[15].v = 6; edges[15].w = 4; edges[15].weight = 93;

	graph_weighted_init(&graph, 8);
	for(i = 0; i < 16; i++){
		add_edge_gra_weighted(&graph, &edges[i]);
	}

	while(!is_edge_empty(edges)){
		index = find_min_edg(edges);
		if(!is_connected_uf(&uf_group, edges[index].v, edges[index].w)){
			union_group(&uf_group, edges[index].v, edges[index].w);
			printf(" edge 	v = %d 	w = %d 	weight = %d\n", 
			edges[index].v, edges[index].w, edges[index].weight);
		}
		edges[index].v = -1; edges[index].w = -1; edges[index].weight = -1;
	
	}
	

}


/********************************???????????????????????????***************************************************/

static void graph_weighted_dic_init(graph_weighted_dic *graph_dic, int point)
{
	int i, j;
	graph_dic->points = point;
	graph_dic->edges = 0;
	for(i = 0; i < 100; i++){
		for(j = 0; j < 100; j++){
			graph_dic->edge_queue[i][j].from = -1;
			graph_dic->edge_queue[i][j].to = -1;
			graph_dic->edge_queue[i][j].weight = -1;
		}
	}

	return;
}


void add_edge_gra_weighted_dic(graph_weighted_dic *graph_dic, Edge_dic *edge)
{
	int from, to;
	int i;
	from = edge->from;
	to = edge->to;

	for(i = 0; graph_dic->edge_queue[from][i].from != -1; i ++){}
	printf("from = %d to = %d weight = %d i = %d\n", from, to, edge->weight, i);
	graph_dic->edge_queue[from][i].from = from;
	graph_dic->edge_queue[from][i].to = to;
	graph_dic->edge_queue[from][i].weight = edge->weight;

	graph_dic->edges++;
	return;
}



void pri_dijkstra(graph_weighted_dic *graph_dic, int start)
{
	int from, to;

	/*????????????????????????????????????????????????????????????????????????*/
	Edge_dic edges_dic[100];
	/*????????????????????????????????????????????????????????????*/
	int index_pri_queue[100];
	/*??????????????????????????????????????????*/
	int dist_to[100];

	int i;

	for(i = 0; i < 100; i++){
		edges_dic[i].from = -1;
		edges_dic[i].to = -1;
		edges_dic[i].weight = -1;
		dist_to[i] = -1;
		index_pri_queue[i] = -1;
	}

	/*???????????????????????????*/
	index_pri_queue[start] = 0;
	dist_to[start] = 0;

	while(!queue_is_empty(index_pri_queue, graph_dic->points)){
		from = del_return_nim_index(index_pri_queue, graph_dic->points);
		printf("del %d\n", from);

		for(i =0; graph_dic->edge_queue[from][i].from != -1; i++){
			to = graph_dic->edge_queue[from][i].to; //????????????????????????
			printf("from = %d, to = %d\n", from, to);

			//???????????????to???????????????????????????from + from???to?????????
			if((dist_to[to] > dist_to[from] + graph_dic->edge_queue[from][i].weight) || 
				(dist_to[to] < 0)){//?????????to??????????????????????????????????????????
				edges_dic[to].from = graph_dic->edge_queue[from][i].from;
				edges_dic[to].to = graph_dic->edge_queue[from][i].to;
				edges_dic[to].weight = graph_dic->edge_queue[from][i].weight;

				if(index_pri_queue[to] == -1)
					index_pri_queue[to] = 0;
				if(dist_to[to] == -1)
					dist_to[to] = 0;

				dist_to[to] = dist_to[from] + graph_dic->edge_queue[from][i].weight;
				index_pri_queue[to] = dist_to[from] + graph_dic->edge_queue[from][i].weight;
				printf("index_pri_queue[%d] = %d\n", to, index_pri_queue[to]);
				
			}
		}

		for(i = 0; i < 8; i++){
			printf("%d ", index_pri_queue[i]);
		}
		printf("\n");
	}

	for(i = 0; i < 100; i++){
		if(edges_dic[i].from != -1){
			printf(" %d : edge 	from = %d 	to = %d 	weight = %d\n", 
				i, edges_dic[i].from, edges_dic[i].to, edges_dic[i].weight);
		}
	}
	
}

void pri_dijkstra_test(void)
{
	Edge_dic edges_dic[15] = {0};
	graph_weighted_dic graph_dic;
	int i;

	graph_weighted_dic_init(&graph_dic, 8);
	edges_dic[0].from = 4; edges_dic[0].to = 5; edges_dic[0].weight = 35;
	edges_dic[1].from = 5; edges_dic[1].to = 4; edges_dic[1].weight = 35;
	edges_dic[2].from = 4; edges_dic[2].to = 7; edges_dic[2].weight = 37;
	edges_dic[3].from = 5; edges_dic[3].to = 7; edges_dic[3].weight = 28;
	edges_dic[4].from = 7; edges_dic[4].to = 5; edges_dic[4].weight = 28;
	edges_dic[5].from = 5; edges_dic[5].to = 1; edges_dic[5].weight = 32;
	edges_dic[6].from = 0; edges_dic[6].to = 4; edges_dic[6].weight = 38;
	edges_dic[7].from = 0; edges_dic[7].to = 2; edges_dic[7].weight = 26;
	edges_dic[8].from = 7; edges_dic[8].to = 3; edges_dic[8].weight = 39;
	edges_dic[9].from = 1; edges_dic[9].to = 3; edges_dic[9].weight = 29;
	edges_dic[10].from = 2; edges_dic[10].to = 7; edges_dic[10].weight = 34;
	edges_dic[11].from = 6; edges_dic[11].to = 2; edges_dic[11].weight = 40;
	edges_dic[12].from = 3; edges_dic[12].to = 6; edges_dic[12].weight = 52;
	edges_dic[13].from = 6; edges_dic[13].to = 0; edges_dic[13].weight = 58;
	edges_dic[14].from = 6; edges_dic[14].to = 4; edges_dic[14].weight = 93;


	for(i = 0; i < 15; i++){
		add_edge_gra_weighted_dic(&graph_dic, &edges_dic[i]);
	}

	printf("edges in graph is %d \n", graph_dic.edges);

	pri_dijkstra(&graph_dic, 0);

}

