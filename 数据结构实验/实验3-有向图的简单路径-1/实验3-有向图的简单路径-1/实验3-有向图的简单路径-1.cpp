#include <stdio.h>
#include <malloc.h>

#define INF     32767               //定义∞
#define MAX    100                 //最大顶点个数

typedef char InfoType;
/*-------------------------以下定义邻接矩阵类型---------------------------*/
typedef struct
{
	int no;                         //顶点编号
	InfoType info;                  //顶点信息
}VertexType;                        //顶点类型

typedef struct
{
	int edges[MAX][MAX];          //邻接矩阵数组(用一个二维数组存放顶点间关系(边或弧)的数据)
	int n;                          //顶点数
	int e;                          //边数
	VertexType vexs[MAX];          //存放顶点信息(用一个一维数组存放图中所有顶点数据)
}MatGraph;                          //完整的图邻接矩阵类型

//邻接表表示法-将每个顶点的邻接点串成一个单链表
/*-----------以下定义邻接表类型--------------*/
typedef struct ArcNode
{
	int adjvex;                     //该边的邻接点编号
	struct ArcNode *nextarc;        //指向下一条边的指针
	int weight;                     //该边的相关信息,如权值(用整型表示)
}ArcNode;                           //边结点类型

typedef struct VNode
{
	InfoType info;                  //顶点其他信息
	int cnt;                        //存放顶点入度,仅用于拓扑排序
	ArcNode *firstarc;              //指向第一条边
}VNode;                             //邻接表结点类型

typedef struct
{
	VNode adjlist[MAX];            //邻接表头结点数组
	int n;                          //图中顶点数
	int e;                          //图中边数
}AdjGraph;                          //完整的图邻接表类型

/*-------------------------邻接矩阵的基本运算算法---------------------------*/
/*------------由边数组A、顶点数n和边数e创建图的邻接矩阵g--------------------*/
void CreateMat(MatGraph &g, int A[MAX][MAX], int n, int e)
{
	int i, j;

	g.n = n;
	g.e = e;
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
			g.edges[i][j] = A[i][j];
}

/*------------输出邻接矩阵g--------------------*/
void DispMat(MatGraph g)
{
	int i, j;

	for (i = 0; i < g.n; i++)
	{
		for (j = 0; j < g.n; j++)
		{
			if (g.edges[i][j] != INF)
				printf("%4d", g.edges[i][j]);
			else
				printf("%4s", "∞");
		}
		printf("\n");
	}
}

/*-------------------------邻接表的基本运算算法---------------------------*/
/*-------------------由边数组A、顶点数n和边数e创建图的邻接表G--------------------*/
void CreateAdj(AdjGraph *&G, int A[MAX][MAX], int n, int e)
{
	int i, j;
	ArcNode *p;

	G = (AdjGraph *)malloc(sizeof(AdjGraph));
	for (i = 0; i < n; i++)                              //给邻接表中所有头结点的指针域置初值NULL
	{
		G->adjlist[i].firstarc = NULL;
	}

	for (i = 0; i < n; i++)                              //检查邻接矩阵中的每个元素
	{
		for (j = n - 1; j >= 0; j--)
		{
			if (A[i][j] != 0 && A[i][j] != INF)          //存在一条边
			{
				p = (ArcNode *)malloc(sizeof(ArcNode)); //创建一个结点p
				p->adjvex = j;                          //邻接点编号
				p->weight = A[i][j];                    //边的权重
				p->nextarc = G->adjlist[i].firstarc;    //采用头插法插入结点p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = n;
	G->e = e;
}

/*-------------------输出邻接表G--------------------*/
void DispAdj(AdjGraph *G)
{
	ArcNode *p;

	for (int i = 0; i < G->n; i++)
	{
		p = G->adjlist[i].firstarc;
		printf("顶点%d: ", i);
		while (p != NULL)
		{
			printf("%3d[%d]->", p->adjvex, p->weight);  //邻接点编号[权重]
			p = p->nextarc;
		}
		printf("∧\n");
	}
}

/*-------------------销毁图的邻接表G--------------------*/
void DestroyAdj(AdjGraph *&G)
{
	ArcNode *pre, *p;

	for (int i = 0; i < G->n; i++)
	{
		pre = G->adjlist[i].firstarc;                   //pre指向第i个单链表的首结点
		if (pre != NULL)
		{
			p = pre->nextarc;
			while (p != NULL)                            //释放第i个单链表的所有边结点
			{
				free(pre);
				pre = p;
				p = p->nextarc;
			}
			free(pre);
		}
	}
	free(G);                                            //释放头结点数组
}

int visited[MAX];              //全局数组

/*----------输出图G中从顶点u到v的所有简单路径------------*/
/**
*   采用从顶点u出发的回溯深度优先搜索方法，当搜索到顶点v时输出路径path[0..d]，
*   然后继续回溯查找其他路径。
*/
static void path_all1(AdjGraph *G, int u, int v, int path[], int d)
{
	ArcNode *p;                 //边结点类型指针
	int i;
	int w;

	d++;                        //路径长度增1
	path[d] = u;                //当前顶点添加到路径中
	visited[u] = 1;             //置已访问标记
	if (u == v && d > 0)         //找到终点
	{
		for (i = 0; i <= d; i++)
			printf("%3d", path[i]);
		printf("\n");
	}
	p = G->adjlist[u].firstarc; //p指向顶点u的第一个相邻点
	while (p != NULL)
	{
		w = p->adjvex;          //w为u的相邻点编号
		if (visited[w] == 0)     //若该顶点未标记访问，则递归访问之
			path_all1(G, w, v, path, d);
		p = p->nextarc;         //找u的下一个相邻点
	}
	visited[u] = 0;             //取消访问标记，以使该顶点可重新使用
}

/*-------------输出图G中从顶点u到v的长度为len的所有简单路径，d是到当前为止已走过的路径长度，调用时初值为-1----------------*/
/**
*   采用从顶点u出发的回溯深度优先搜索方法，每搜索一个新顶点，路径长度增1，
*   若搜索到顶点v且d等于len，则输出路径path[0..d]，然后继续回溯查找其他路径。
*
*/
static void path_all2(AdjGraph *G, int u, int v, int len, int path[], int d)
{
	int i;
	int w;
	ArcNode *p;                 //边结点类型指针

	visited[u] = 1;             //置已访问标记
	d++;                        //路径长度增1
	path[d] = u;                //将当前顶点添加到路径中
	if (u == v && d == len)      //满足条件，输出一条路径
	{
		for (i = 0; i <= d; i++)
			printf("%3d", path[i]);
		printf("\n");
	}
	p = G->adjlist[u].firstarc; //p指向顶点u的第一个相邻点
	while (p != NULL)
	{
		w = p->adjvex;          //w为顶点u的相邻点编号
		if (visited[w] == 0)     //若该顶点未标记访问，则递归访问之
			path_all2(G, w, v, len, path, d);
		p = p->nextarc;         //找u的下一个相邻点
	}
	visited[u] = 0;             //取消访问标记，以使该顶点可重新使用
}

/*-----------求顶点u到顶点v(u != v)的最短路径-----------------*/
/**
*   采用从顶点u出发广度优先搜索方法，当搜索到顶点v时，在队列中找出对应的路径。
*   由广度优先搜索可知，找到的路径一定是最短路径。
*
*/
int short_path(AdjGraph *G, int u, int v, int path[])
{
	struct
	{
		int vno;                //当前顶点编号
		int level;              //当前顶点的层次
		int parent;             //当前顶点的双亲结点在队列中的下标
	}qu[MAX];                  //定义顺序非循环队列
	int qu_front = -1, qu_rear = -1, k, lev, i, j;
	ArcNode *p;

	visited[u] = 1;
	qu_rear++;                  //顶点u已访问，将其入队
	qu[qu_rear].vno = u;
	qu[qu_rear].level = 0;
	qu[qu_rear].parent = -1;
	while (qu_front < qu_rear)   //队非空循环
	{
		qu_front++;
		k = qu[qu_front].vno;   //出队顶点k
		lev = qu[qu_front].level;
		if (k == v)              //若顶点k为终点
		{
			i = 0;
			j = qu_front;
			while (j != -1)
			{
				path[lev - i] = qu[j].vno;
				j = qu[j].parent;
				i++;
			}
			return lev;         //找到顶点v，返回其层次
		}
		p = G->adjlist[k].firstarc;//p指向顶点k的第一个相邻点
		while (p != NULL)           //依次搜索k的相邻点
		{
			if (visited[p->adjvex] == 0)//若未访问过
			{
				visited[p->adjvex] = 1;
				qu_rear++;
				qu[qu_rear].vno = p->adjvex;//访问过的相邻点进队
				qu[qu_rear].level = lev + 1;
				qu[qu_rear].parent = qu_front;
			}
			p = p->nextarc;                 //找到顶点k的下一个相邻点
		}
	}

	return -1;
}


//获得边的权重
float getWeight(AdjGraph *G, int u, int j)
{
	ArcNode *p = G->adjlist[u].firstarc;
	while (p != NULL)
	{
		if (p->adjvex == j)
			return p->weight;
		p = p->nextarc;
	}
	return INF;
}

//迪杰斯特拉算法
void Dijkstra(AdjGraph *G, int dist[], int path[], int v)
{
	int set[MAX];
	int i, j, u, min;
	float weight;
	//给三个数组赋初值
	for (i = 0; i < G->n; i++)
	{
		set[i] = 0;
		path[i] = -1;
		dist[i] = INF;
	}

	/*for (i = 0; i < G->n; i++)
	{
		printf("%d\n", path[i]);
	}*/

	ArcNode *p = G->adjlist[v].firstarc;
	while (p != NULL)
	{
		dist[p->adjvex] = p->weight;
		path[p->adjvex] = v;
		p = p->nextarc;
	}
	path[v] = -1;
	set[v] = 1;
	dist[v] = 0;

	for (i = 0; i < G->n - 1; i++)
	{
		min = INF;

		for (j = 0; j < G->n; j++)
		{
			if (set[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				u = j;
			}
		}
		set[u] = 1;

		for (j = 0; j < G->n; j++)
		{
			float weight = getWeight(G, u, j);
			if (set[j] == 0 && dist[u] + weight < dist[j])
			{
				dist[j] = dist[u] + weight;
				path[j] = u;
			}
		}
	}
	//for (i = 0; i < G->n; i++)
	//{
	//	printf("%d\n", path[i]);
	//}
}

//输出路径
void print_path(int path[], int v1)
{
	if (path[v1] == -1)
		printf("%d ", v1);
	else
	{
		print_path(path, path[v1]);
		printf("%d ", v1);
	}
}
int main(void)
{
	int i, j;
	int u = 5, v = 2, len = 3;
	int path[MAX];
	AdjGraph *G;
	int A[MAX][MAX] = {
		{0, 1, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{1, 0, 0, 0, 0, 1},
		{0, 0, 1, 0, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{1, 1, 0, 1, 1, 0}
	};
	int n = 6;  //顶点数
	int e = 12; //边数

	CreateAdj(G, A, n, e);
	printf("图G的邻接表:\n");
	DispAdj(G);
	printf("(1)从顶点%d到%d的所有路径:\n", u, v);
	for (i = 0; i < n; i++)
		visited[i] = 0;
	path_all1(G, u, v, path, -1);
	printf("(2)从顶点%d到%d的所有长度为%d路径:\n", u, v, len);
	path_all2(G, u, v, len, path, -1);
	printf("(3)从顶点%d到%d的最短路径:\n", u, v);
	for (i = 0; i < n; i++)
		visited[u] = 0;
	j = short_path(G, u, v, path);
	for (i = 0; i <= j; i++)
		printf("%3d", path[i]);
	printf("\n");


	DestroyAdj(G);


	return 0;
}