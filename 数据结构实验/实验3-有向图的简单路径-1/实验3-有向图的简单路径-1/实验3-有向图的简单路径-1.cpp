#include <stdio.h>
#include <malloc.h>

#define INF     32767               //�����
#define MAX    100                 //��󶥵����

typedef char InfoType;
/*-------------------------���¶����ڽӾ�������---------------------------*/
typedef struct
{
	int no;                         //������
	InfoType info;                  //������Ϣ
}VertexType;                        //��������

typedef struct
{
	int edges[MAX][MAX];          //�ڽӾ�������(��һ����ά�����Ŷ�����ϵ(�߻�)������)
	int n;                          //������
	int e;                          //����
	VertexType vexs[MAX];          //��Ŷ�����Ϣ(��һ��һά������ͼ�����ж�������)
}MatGraph;                          //������ͼ�ڽӾ�������

//�ڽӱ��ʾ��-��ÿ��������ڽӵ㴮��һ��������
/*-----------���¶����ڽӱ�����--------------*/
typedef struct ArcNode
{
	int adjvex;                     //�ñߵ��ڽӵ���
	struct ArcNode *nextarc;        //ָ����һ���ߵ�ָ��
	int weight;                     //�ñߵ������Ϣ,��Ȩֵ(�����ͱ�ʾ)
}ArcNode;                           //�߽������

typedef struct VNode
{
	InfoType info;                  //����������Ϣ
	int cnt;                        //��Ŷ������,��������������
	ArcNode *firstarc;              //ָ���һ����
}VNode;                             //�ڽӱ�������

typedef struct
{
	VNode adjlist[MAX];            //�ڽӱ�ͷ�������
	int n;                          //ͼ�ж�����
	int e;                          //ͼ�б���
}AdjGraph;                          //������ͼ�ڽӱ�����

/*-------------------------�ڽӾ���Ļ��������㷨---------------------------*/
/*------------�ɱ�����A��������n�ͱ���e����ͼ���ڽӾ���g--------------------*/
void CreateMat(MatGraph &g, int A[MAX][MAX], int n, int e)
{
	int i, j;

	g.n = n;
	g.e = e;
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
			g.edges[i][j] = A[i][j];
}

/*------------����ڽӾ���g--------------------*/
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
				printf("%4s", "��");
		}
		printf("\n");
	}
}

/*-------------------------�ڽӱ�Ļ��������㷨---------------------------*/
/*-------------------�ɱ�����A��������n�ͱ���e����ͼ���ڽӱ�G--------------------*/
void CreateAdj(AdjGraph *&G, int A[MAX][MAX], int n, int e)
{
	int i, j;
	ArcNode *p;

	G = (AdjGraph *)malloc(sizeof(AdjGraph));
	for (i = 0; i < n; i++)                              //���ڽӱ�������ͷ����ָ�����ó�ֵNULL
	{
		G->adjlist[i].firstarc = NULL;
	}

	for (i = 0; i < n; i++)                              //����ڽӾ����е�ÿ��Ԫ��
	{
		for (j = n - 1; j >= 0; j--)
		{
			if (A[i][j] != 0 && A[i][j] != INF)          //����һ����
			{
				p = (ArcNode *)malloc(sizeof(ArcNode)); //����һ�����p
				p->adjvex = j;                          //�ڽӵ���
				p->weight = A[i][j];                    //�ߵ�Ȩ��
				p->nextarc = G->adjlist[i].firstarc;    //����ͷ�巨������p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = n;
	G->e = e;
}

/*-------------------����ڽӱ�G--------------------*/
void DispAdj(AdjGraph *G)
{
	ArcNode *p;

	for (int i = 0; i < G->n; i++)
	{
		p = G->adjlist[i].firstarc;
		printf("����%d: ", i);
		while (p != NULL)
		{
			printf("%3d[%d]->", p->adjvex, p->weight);  //�ڽӵ���[Ȩ��]
			p = p->nextarc;
		}
		printf("��\n");
	}
}

/*-------------------����ͼ���ڽӱ�G--------------------*/
void DestroyAdj(AdjGraph *&G)
{
	ArcNode *pre, *p;

	for (int i = 0; i < G->n; i++)
	{
		pre = G->adjlist[i].firstarc;                   //preָ���i����������׽��
		if (pre != NULL)
		{
			p = pre->nextarc;
			while (p != NULL)                            //�ͷŵ�i������������б߽��
			{
				free(pre);
				pre = p;
				p = p->nextarc;
			}
			free(pre);
		}
	}
	free(G);                                            //�ͷ�ͷ�������
}

int visited[MAX];              //ȫ������

/*----------���ͼG�дӶ���u��v�����м�·��------------*/
/**
*   ���ôӶ���u�����Ļ��������������������������������vʱ���·��path[0..d]��
*   Ȼ��������ݲ�������·����
*/
static void path_all1(AdjGraph *G, int u, int v, int path[], int d)
{
	ArcNode *p;                 //�߽������ָ��
	int i;
	int w;

	d++;                        //·��������1
	path[d] = u;                //��ǰ������ӵ�·����
	visited[u] = 1;             //���ѷ��ʱ��
	if (u == v && d > 0)         //�ҵ��յ�
	{
		for (i = 0; i <= d; i++)
			printf("%3d", path[i]);
		printf("\n");
	}
	p = G->adjlist[u].firstarc; //pָ�򶥵�u�ĵ�һ�����ڵ�
	while (p != NULL)
	{
		w = p->adjvex;          //wΪu�����ڵ���
		if (visited[w] == 0)     //���ö���δ��Ƿ��ʣ���ݹ����֮
			path_all1(G, w, v, path, d);
		p = p->nextarc;         //��u����һ�����ڵ�
	}
	visited[u] = 0;             //ȡ�����ʱ�ǣ���ʹ�ö��������ʹ��
}

/*-------------���ͼG�дӶ���u��v�ĳ���Ϊlen�����м�·����d�ǵ���ǰΪֹ���߹���·�����ȣ�����ʱ��ֵΪ-1----------------*/
/**
*   ���ôӶ���u�����Ļ��������������������ÿ����һ���¶��㣬·��������1��
*   ������������v��d����len�������·��path[0..d]��Ȼ��������ݲ�������·����
*
*/
static void path_all2(AdjGraph *G, int u, int v, int len, int path[], int d)
{
	int i;
	int w;
	ArcNode *p;                 //�߽������ָ��

	visited[u] = 1;             //���ѷ��ʱ��
	d++;                        //·��������1
	path[d] = u;                //����ǰ������ӵ�·����
	if (u == v && d == len)      //�������������һ��·��
	{
		for (i = 0; i <= d; i++)
			printf("%3d", path[i]);
		printf("\n");
	}
	p = G->adjlist[u].firstarc; //pָ�򶥵�u�ĵ�һ�����ڵ�
	while (p != NULL)
	{
		w = p->adjvex;          //wΪ����u�����ڵ���
		if (visited[w] == 0)     //���ö���δ��Ƿ��ʣ���ݹ����֮
			path_all2(G, w, v, len, path, d);
		p = p->nextarc;         //��u����һ�����ڵ�
	}
	visited[u] = 0;             //ȡ�����ʱ�ǣ���ʹ�ö��������ʹ��
}

/*-----------�󶥵�u������v(u != v)�����·��-----------------*/
/**
*   ���ôӶ���u���������������������������������vʱ���ڶ������ҳ���Ӧ��·����
*   �ɹ������������֪���ҵ���·��һ�������·����
*
*/
int short_path(AdjGraph *G, int u, int v, int path[])
{
	struct
	{
		int vno;                //��ǰ������
		int level;              //��ǰ����Ĳ��
		int parent;             //��ǰ�����˫�׽���ڶ����е��±�
	}qu[MAX];                  //����˳���ѭ������
	int qu_front = -1, qu_rear = -1, k, lev, i, j;
	ArcNode *p;

	visited[u] = 1;
	qu_rear++;                  //����u�ѷ��ʣ��������
	qu[qu_rear].vno = u;
	qu[qu_rear].level = 0;
	qu[qu_rear].parent = -1;
	while (qu_front < qu_rear)   //�ӷǿ�ѭ��
	{
		qu_front++;
		k = qu[qu_front].vno;   //���Ӷ���k
		lev = qu[qu_front].level;
		if (k == v)              //������kΪ�յ�
		{
			i = 0;
			j = qu_front;
			while (j != -1)
			{
				path[lev - i] = qu[j].vno;
				j = qu[j].parent;
				i++;
			}
			return lev;         //�ҵ�����v����������
		}
		p = G->adjlist[k].firstarc;//pָ�򶥵�k�ĵ�һ�����ڵ�
		while (p != NULL)           //��������k�����ڵ�
		{
			if (visited[p->adjvex] == 0)//��δ���ʹ�
			{
				visited[p->adjvex] = 1;
				qu_rear++;
				qu[qu_rear].vno = p->adjvex;//���ʹ������ڵ����
				qu[qu_rear].level = lev + 1;
				qu[qu_rear].parent = qu_front;
			}
			p = p->nextarc;                 //�ҵ�����k����һ�����ڵ�
		}
	}

	return -1;
}


//��ñߵ�Ȩ��
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

//�Ͻ�˹�����㷨
void Dijkstra(AdjGraph *G, int dist[], int path[], int v)
{
	int set[MAX];
	int i, j, u, min;
	float weight;
	//���������鸳��ֵ
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

//���·��
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
	int n = 6;  //������
	int e = 12; //����

	CreateAdj(G, A, n, e);
	printf("ͼG���ڽӱ�:\n");
	DispAdj(G);
	printf("(1)�Ӷ���%d��%d������·��:\n", u, v);
	for (i = 0; i < n; i++)
		visited[i] = 0;
	path_all1(G, u, v, path, -1);
	printf("(2)�Ӷ���%d��%d�����г���Ϊ%d·��:\n", u, v, len);
	path_all2(G, u, v, len, path, -1);
	printf("(3)�Ӷ���%d��%d�����·��:\n", u, v);
	for (i = 0; i < n; i++)
		visited[u] = 0;
	j = short_path(G, u, v, path);
	for (i = 0; i <= j; i++)
		printf("%3d", path[i]);
	printf("\n");


	DestroyAdj(G);


	return 0;
}