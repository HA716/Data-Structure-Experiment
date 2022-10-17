#include<stdio.h>
#include<stdlib.h>

#define MAX 100
#define M 6   //行数
#define N 6     //列数
#define MaxSize    100     //栈最多元素个数

//边表结点
typedef struct ARCNODE
{
	int adjVex;
	int weight;
	struct ARCNODE*next;
}ArcNode;

//顶点
typedef struct NODE
{
	char data;
	ArcNode*firstArc;
}Node;

//邻接表
typedef struct ADJLIST
{
	Node vex[MAX];  //顶点数组
	int verNum;
	int arcNum;
}AdjList;


int mg[M + 2][N + 2] = 
{      //一个迷宫，其四周要加上均为1的外框
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 1, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 1, 1, 0, 1, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

int mg_AdjMatrix[MAX][MAX] =
{
	{0, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 1},
	{0, 0, 1, 0, 0, 1},
	{0, 0, 0, 1, 0, 0},
	{1, 1, 0, 1, 1, 0}
};

struct migong {
	int i;      //路径横坐标
	int j;      //路径纵坐标
	int di;     //方向
}Stack[MaxSize], Path[MaxSize];      //定义栈和存放最短路径的数组

int top = -1;     //栈顶指针
int count = 1;    //路径数计数
int minlen = MaxSize;     //最短路径长度

void DFS() {      //路径为:(1,1)->(M,N)
	int i, j, di, find, k;
	top++; Stack[top].i = 1; Stack[top].j = 1; Stack[top].di = -1;
	mg[1][1] = -1;        //初始结点进栈
	while (top > -1) {      //栈不空时循环
		i = Stack[top].i; j = Stack[top].j; di = Stack[top].di;
		if (i == M && j == N) {       //找到了出口，输出路径
			printf("M: %d ", count++);
			for (k = 0; k <= top; k++) {
				printf("(%d,%d)  ", Stack[k].i, Stack[k].j);
				if ((k + 1) % 5 == 0)      //输出时每5个结点换一行
					printf("\n\t");
			}
			printf("\n");
			if (top + 1 < minlen) {       //比较输出最短路径
				for (k = 0; k <= top; k++)
					Path[k] = Stack[k];
				minlen = top + 1;
			}
			mg[Stack[top].i][Stack[top].j] = 0;   //让该位置变为其他路径的可走结点
			top--;
			i = Stack[top].i; j = Stack[top].j; di = Stack[top].di;
		}
		find = 0;
		while (di < 4 && find == 0) {     //找下一个可走结点
			di++;
			switch (di) {
			case 0:i = Stack[top].i - 1; j = Stack[top].j; break;   //上面
			case 1:i = Stack[top].i; j = Stack[top].j + 1; break;   //右边
			case 2:i = Stack[top].i + 1; j = Stack[top].j; break;   //下面
			case 3:i = Stack[top].i; j = Stack[top].j - 1; break;   //左边
			}
			if (mg[i][j] == 0) //标记该点为可以走的点
				find = 1;
		}
		if (find == 1) {      //找到了下一个可走结点
			Stack[top].di = di;   //修改原栈顶元素的di值
			top++;      //下一个可走结点进栈
			Stack[top].i = i;
			Stack[top].j = j;
			Stack[top].di = -1;
			mg[i][j] = -1;        //避免重复走到该结点
		}
		else {
			mg[Stack[top].i][Stack[top].j] = 0;   //让该位置变为其他路径的可走结点
			top--;
		}
	}
	printf("最短路径如下:\n");
	printf("长度:  %d\n", minlen);
	printf("路径:  ");
	for (k = 0; k < minlen; k++) {
		printf("(%d,%d)  ", Path[k].i, Path[k].j);
		if ((k + 1) % 5 == 0)      //输出时每5个结点换一行
			printf("\n\t");
	}
	printf("\n");
}

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
		printf("%d  ", i);

		while (p != NULL)
		{
			printf("->%d", p->adjVex);
			p = p->next;
		}
		printf("->∧\n");

	}

}

int main() {
	AdjList*G = (AdjList*)malloc(sizeof(AdjList));

	Create_AdjList(G, mg_AdjMatrix, 6, 6);
	printf("邻接表：\n");
	Print_AdjList(G);
	printf("\n迷宫所有路径如下:\n");
	DFS();
	return 0;
}