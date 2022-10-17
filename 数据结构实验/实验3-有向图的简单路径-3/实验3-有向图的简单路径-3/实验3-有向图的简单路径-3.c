#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int visited[MAX];
//邻接表
typedef struct ARCNODE
{
	int adjVex;  //邻接点
	int weight;
	struct ARCNODE *next;
}ArcNode;

//顶点表
typedef struct NODE
{
	char data;
	ArcNode*firstArc;  
}Node;

//邻接表
typedef struct ADJLIST
{
	Node vex[MAX];   //顶点数组
	int verNum;
	int arcNum;
}AdjList;


//创建邻接表
void Create_AdjList(AdjList *G, int AdjMatrix[MAX][MAX], int verNum, int arcNum)
{
	ArcNode*p;
	G->verNum = verNum;
	G->arcNum = arcNum;
	//printf("请输入顶点名:");
	for (int i = 0; i < G->verNum; i++)
	{
		//scanf_s("%c", &G->vex[i].data,1);
		//getchar();
		G->vex[i].firstArc = NULL;
	}
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			//存在边
			if (AdjMatrix[i][j] != 0)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->adjVex = j;
				p->weight = AdjMatrix[i][j];
				p->next = G->vex[i].firstArc;  //头插
				G->vex[i].firstArc = p;
			}
		}
	}
}


//输出邻接表
void Print_AdjList(AdjList*G)
{
	ArcNode*p;
	for (int i = 0; i < G->verNum; i++)
	{
		p = G->vex[i].firstArc;
		//printf("顶点 %c： %d", G->vex[i].data,i);
		printf("%d  ",i);

		while (p != NULL)
		{
			printf("->%d", p->adjVex);
			p = p->next;
		}
		printf("->∧\n");

	}

}


//查找所有简单路径:因为递归函数有if条件判断，所以不需要设置return，当不满足if的时候就会执行完整个函数体，然后一层层返回
void Allpath_1(AdjList*G, int start, int end, int path[],int curLen)
{
	ArcNode*p;
	int adjvex;
	curLen++;
	path[curLen] = start;  //将结点start添加到路径path中
	visited[start] = 1;   //标记为已访问
	//找到终点
	if (start == end) 
	{
		for (int i = 0; i <= curLen; i++)
		{
			printf("%d ", path[i]);
		}
		printf("\n");
	}
	
	p = G->vex[start].firstArc; //start的第一个邻接点
	while (p != NULL)
	{
		adjvex = p->adjVex;
		if (visited[adjvex] == 0)
		{//如果该邻接点未被访问，就以它为起点继续递归，直到这个邻接点是终点
			Allpath_1(G, adjvex, end, path, curLen);
		}

		p = p->next;

	}
	visited[start] = 0;     //因为要查找所有路径，所以查找完一条路径之后，在函数回归的时候就要重置这些顶点，方便下一次查找路径
}



//查找指定长度的路径
void AllPath_2(AdjList*G, int start, int end, int len, int path[], int curLen)
{
	ArcNode*p;
	int adjVex;
	visited[start] = 1;
	path[++curLen] = start;
	
	//仅判断条件不同
	if (start == end && (curLen+1) == len)  //curLen实际上是下标索引，还需要加1才是长度
	{
		for (int i = 0; i <= curLen; i++)
		{
			printf("%d ", path[i]);
		}
		printf("\n");
	}

	p = G->vex[start].firstArc;
	while (p != NULL)
	{
		adjVex = p->adjVex;
		if (visited[adjVex] == 0)
		{
			AllPath_2(G, adjVex, end, len, path, curLen);
		}
		p = p->next;
	}

	visited[start] = 0;
}


//获取图G中边<start,end>的权重，若若start和end不是连通的，则返回无穷大
int GetWeight(AdjList*G, int start, int end)
{
	ArcNode*p = G->vex[start].firstArc;
	while(p != NULL)
	{
		if (p->adjVex == end)
		{
			return p->weight;
	   }
		p = p->next;  //遍历顶点start的边表(遍历所有邻接点)，直到找到它的邻接点end
	}
	return INT_MAX;
}



/*Dijkstra算法获取最短路径：
  集合S：已求出最短路径的终点集合（初始只有起点v0）
  集合V-S：尚未求出最短路径的顶点集合
  dist[i]:记录从顶点start到顶点i的当前最短路径长度
  path[i]:记录"起点start"到"终点i"的最短路径所经历的全部顶点中，位于"终点i"之前的那个顶点。
  s[i]:标记顶点i是否在集合S中，若s[i]=1则代表把这个顶点加入到集合S中
*/
void Dijkstra(AdjList*G, int dist[], int path[], int start)
{
	int S[MAX];
	float weight;    //一定要是float型
	int min;
	int pos;
	//初始化数组
	for (int i = 0; i < G->verNum; i++)
	{
		S[i] = 0;  //初始化 集合S中没有元素，即顶点i的最短路径还没获取到
		path[i] = -1;  //初始化图中所有顶点没有前驱结点
		dist[i] = INT_MAX;  //初始化start到图中任意一点没有边
	}

	ArcNode*p = G->vex[start].firstArc;
	while (p != NULL)
	{
		dist[p->adjVex] = p->weight;
		path[p->adjVex] = start;
		p = p->next;  //遍历顶点start的边表(遍历所有邻接点)
	}
	path[start] = -1;  
	S[start] = 1;      //将起点start加入到集合S中
	dist[start] = 0;   //start到它自身的路径长度为0

	for (int i = 0; i < G->verNum - 1; i++)
	{
		min = INT_MAX;
		for (int j = 0; j < G->verNum; j++)
		{
			//找到从start到集合V-S中的点的最短路径
			if (S[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				pos = j;
			}
		}
		S[pos] = 1;

		//由于在集合S中加入了新顶点pos,所以需要修正当前最短路径和前驱顶点
		for (int k = 0; k < G->verNum; k++)
		{
			//pos是集合S中新加入的点，获取从pos到V-S中所有顶点的路径长度，通过比较判断是否需要修正
			weight = GetWeight(G, pos, k);
			//若是int weight, 则当weight = INT_MAX时，dist[pos] + weight可能会溢出,所以要float型的weight
			if (S[k] == 0 && dist[pos] + weight < dist[k])
			{//<start,pos> + <pos,k> < <start,k>
				dist[k] = dist[pos] + weight;
				path[k] = pos;
			}
		}
	}
}




//输出最短路径
void Print_ShortPath(int path[], int end)
{
	if (path[end] == -1)
	{
		printf("%d ", end);
	}
	else
	{
		Print_ShortPath(path, path[end]);
		printf("%d ", end);
	}
}


//销毁邻接表
void Destroy(AdjList *G)
{
	ArcNode *pre, *p;

	for (int i = 0; i < G->verNum; i++)
	{
		pre = G->vex[i].firstArc;                   //pre指向第i个单链表的首结点
		if (pre != NULL)
		{
			p = pre->next;
			while (p != NULL)                            //释放第i个单链表的所有边结点
			{
				free(pre);
				pre = p;
				p = p->next;
			}
			free(pre);
		}
	}
	free(G);                                            //释放头结点数组
}


void main()
{
	//图的邻接矩阵
	int AdjMatrix[MAX][MAX] = {
	{0, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 1},
	{0, 0, 1, 0, 0, 1},
	{0, 0, 0, 1, 0, 0},
	{1, 1, 0, 1, 1, 0}
	};
	int verNum = 6;  //顶点数
	int arcNum = 12; //边数
	int start;
	int end;
	int len;

	AdjList*G = (AdjList*)malloc(sizeof(AdjList));
	Create_AdjList(G, AdjMatrix, verNum, arcNum);
	printf("图G的邻接表:\n");
	Print_AdjList(G);

	//（1）	输出有向图G从顶点5到顶点2的所有简单路径。
	int path[MAX];    //记录起点到终点的路径
	printf("\n请输入简单路径的起点：");
	scanf_s("%d", &start);
	getchar();
	printf("请输入简单路径的终点：");
	scanf_s("%d",&end);
	getchar();
	Allpath_1(G, start, end, path, -1);

	//（2）	输出有向图G从顶点5到顶点2的所有长度为3的简单路径。
	printf("\n请输入简单路径的起点：");
	scanf_s("%d", &start);
	getchar();
	printf("请输入简单路径的终点：");
	scanf_s("%d", &end);
	getchar();
	printf("请输入简单路径的长度：");
	scanf_s("%d", &len);
	getchar();
	AllPath_2(G, start, end, len, path, -1);

	//（3）	输出有向图G从顶点5到顶点2的最短路径
	char dist[MAX];
	printf("\n请输入最短路径的起点：");
	scanf_s("%d", &start);
	getchar();
	printf("请输入最短路径的终点：");
	scanf_s("%d", &end);
	getchar();
	Dijkstra(G, dist, path, start);
	printf("最短路径为：");
	Print_ShortPath(path, end);
	printf("\n");

	Destroy(G);
	printf("成功销毁");
}








