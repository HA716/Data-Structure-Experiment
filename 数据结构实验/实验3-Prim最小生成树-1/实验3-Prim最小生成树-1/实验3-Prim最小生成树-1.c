#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10
#define NAME_SIZE 100

//n个顶点的图，最小生成树有n-1条边，而low[]数组就是用来记录这n-1条边的权值
int low[MAX];  //记录每2个点间的最小权值
int visited[MAX]; //标记顶点是否被访问


typedef struct ADJMATRIX
{
	char * vertex[MAX];  //顶点数组
	int * arc[MAX][MAX]; //邻接矩阵
	int verNum;
	int arcNum;
}AdjMatrix;

typedef struct//辅助数组结构体(候选最短边) 
{
	char adjvex[NAME_SIZE];//候选最短边的邻接点 
	int lowcost;//候选最短边的权值 
}ShortEdge;


int Located(AdjMatrix*G, char * ver)
{
	int index = -1;
	if (G == NULL || ver == NULL) return index;
	else
	{
	
		for (int i = 0; i < G->verNum; i++)
		{
			if (strcmp(G->vertex[i],ver) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

}


//无向网
void Create_UDN(AdjMatrix*G)
{
	printf("请输入顶点数：");
	scanf_s("%d", &G->verNum);
	getchar();
	printf("请输入边的数量：");
	scanf_s("%d", &G->arcNum);
	getchar();

	//初始化顶点
	for (int i = 0; i < G->verNum; i++)
	{
		G->vertex[i] = (char *)malloc(sizeof(char)*NAME_SIZE);
		printf("%d：", i + 1);
		scanf_s("%s", G->vertex[i],NAME_SIZE);
		getchar();
	}

	//初始化邻接矩阵
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			G->arc[i][j] = INT_MAX;   //网的权值初始化为∞
		}
	}

	//创建无向网 
	int weight = 0;
	for (int k = 0; k < G->arcNum; k++)
	{
		char* ver1 = (char*)malloc(sizeof(char)*NAME_SIZE);
		char* ver2 = (char*)malloc(sizeof(char)*NAME_SIZE);
		printf("顶点：");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("邻接点：");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();
		printf("权值：");
		scanf_s("%d", &weight);
		getchar();

		int i = Located(G, ver1);
		int j = Located(G, ver2);

		if (i == -1 || j == -1) return;
		else
		{
			//无向网
			G->arc[i][j] = weight;
			G->arc[j][i] = weight;
		}

	}

}

void Print_UDN(AdjMatrix*G)
{
	printf("\nUDN：\n");
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			if (G->arc[i][j] == INT_MAX)
			{
				printf("∞ ");
			}
			else
			{
				//左对齐
				printf("%-3d", G->arc[i][j]);
			}
		}
		printf("\n");
	}
}



int  Prim(AdjMatrix*G)
{
	int pos = 0;  //
	int MST = 0;  //最小生成树
	int min;

	//printf("起始点：");
	//scanf_s("%d", &pos);
	//getchar();
	//visited[pos] = 1;
	visited[1] = 1; 
	pos = 1;

	//第一次给low[]数组赋值：记录当前点pos到其他各点i的路径长度
	for (int i = 1; i <= G->verNum; i++)
	{
		if (i != pos)
		{
			low[i] = G->arc[pos][i];
		}
		
	}

	/*遍历n-1次，找出最小生成树的n-1条边，每次遍历都会找到最小生成树的一条边
	  并将它记录到low数组中 */
	for (int i = 1; i < G->verNum; i++)
	{
		//找出最小权值的位置
		min = INT_MAX;
		for (int j = 1; j < G->verNum; j++)
		{
			if (visited[j] == 0 && min > low[j])
			{
				min = low[j];
				pos = j;
			}
		}
		//printf("%d->%d: %d",)
		MST += min;
		
		//标记该点，即访问该点
		visited[pos] = 1;

		//更新low[]数组
		for (int k = 1; k <= G->verNum; k++)
		{
			if (visited[k] == 0 && low[k] > G->arc[pos][k])
			{
				low[k] = G->arc[pos][k];
		   }

		}

	}
	return MST;
}




//⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇ERROR⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇
//void MiniSpanTree_Prim(AdjMatrix *G )
//{
//	int i, j, k;
//	int min = INT_MAX;
//	int pos = 0;
//	int MST = 0;
//	char start[NAME_SIZE];
//	ShortEdge shortedge[MAX];
//
//	//1.处理起始点start 
//	printf("请输入最小生成树的起点：");
//	scanf_s("%s", start,NAME_SIZE);
//	k = Located(G, start);
//	int kk = k;
//	//第一次给lowcost数组赋值
//	for (i = 0; i < G->verNum; i++)
//	{
//		strcpy_s(shortedge[i].adjvex, NAME_SIZE, start);
//		if (i != k)
//		{			
//			shortedge[i].lowcost = G->arc[k][i];   //将起点k到图中其他顶点i的路径长度记录下来
//		}
//	}
//    //lowcost为0表示该顶点属于U集合 
//	shortedge[k].lowcost = 0;// 可以理解为"第start个顶点到它自身的距离为0，
//
//	//2.处理后续结点 
//	for (i = 0; i < G->verNum ; i++)//对集合U，去找最短路径的顶点 
//	{
//		// 由于从start开始的，因此不需要再对第start个顶点进行处理
//		if (i == k)
//		{
//			continue;
//		}
//
//
//		//k = minimal(G, shortedge);//找最短路径的顶点 
//		min = INT_MAX;
//		for (j = 0; j < G->verNum; j++)
//		{
//			//在未被加入到最小生成树的顶点中，找出权值最小的顶点
//			if (shortedge[j].lowcost != 0 && min > shortedge[j].lowcost )
//			{
//				min = shortedge[j].lowcost;
//				pos = j;
//			}
//		}
//	/*	if (i == 0)
//		{
//			
//		}*/
//
//			
//		//printf("%s->%s,%d\n", shortedge[k].adjvex,/*G->vertex[k],*/ G->vertex[pos], shortedge[pos].lowcost);//输出找到的最短路径顶，及路径权值 
//		printf("%s->%s,%d\n",/* shortedge[k].adjvex,*/G->vertex[k], G->vertex[pos], shortedge[pos].lowcost);//输出找到的最短路径顶，及路径权值 
//		MST += shortedge[pos].lowcost;	
//		shortedge[pos].lowcost = 0;//将找到的最短路径顶点加入集合U中 
//
//
//		for (j = 0; j < G->verNum; j++)//U中加入了新节点，可能出现新的最短路径，故更新shortedge数组 
//		{
//			//当第j个节点没有被处理，并且出现了更短路径时才被更新
//			if (shortedge[j].lowcost!=0 && G->arc[pos][j] < shortedge[j].lowcost)//有更短路径出现时，将其替换进shortedge数组 
//			{
//				shortedge[j].lowcost = G->arc[pos][j]; 
//				strcpy_s(shortedge[i].adjvex, NAME_SIZE, G->vertex[pos]);
//				k = pos;
//
//			}
//	
//		}
//
//	}
//	printf("MST:%d", MST);
//}

//⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆ERROR⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆⬆

int minimal(AdjMatrix *G, ShortEdge *shortedge)
{
	int i, j;
	int min, loc;

	min = INT_MAX;
	for (i = 1; i < G->verNum; i++)
	{
		if (min > shortedge[i].lowcost&&shortedge[i].lowcost != 0)
		{
			min = shortedge[i].lowcost;
			loc = i;
		}
	}
	return loc;
}

void MiniSpanTree_Prim(AdjMatrix *G)
{
	int i, j, k;
	int MST = 0;
	char* start[NAME_SIZE];
	ShortEdge shortedge[MAX];

	//1.处理起始点start 
	printf("请输入起点：");
	scanf_s("%s", start,NAME_SIZE);
	k = Located(G, start);
	for (i = 0; i < G->verNum; i++)
	{
		//shortedge[i].adjvex = start;
		strcpy_s(shortedge[i].adjvex, NAME_SIZE, start);
		shortedge[i].lowcost = G->arc[k][i];
	}
	shortedge[k].lowcost = 0;//lowcost为0表示该顶点属于U集合 

	//2.处理后续结点 
	for (i = 0; i < G->verNum - 1; i++)//对集合U，去找最短路径的顶点 
	{
		k = minimal(G, shortedge);//找最短路径的顶点 

		printf("%s->%s,%d\n", shortedge[k].adjvex, G->vertex[k], shortedge[k].lowcost);//输出找到的最短路径顶，及路径权值 
		MST += shortedge[k].lowcost;
		shortedge[k].lowcost = 0;//将找到的最短路径顶点加入集合U中 

		for (j = 0; j < G->verNum; j++)//U中加入了新节点，可能出现新的最短路径，故更新shortedge数组 
		{
			if (G->arc[k][j] < shortedge[j].lowcost)//有更短路径出现时，将其替换进shortedge数组 
			{
				shortedge[j].lowcost = G->arc[k][j];
				strcpy_s(shortedge[j].adjvex, NAME_SIZE, G->vertex[k]);
			}
		}

	}
	printf("MST：%d", MST);
}



int main()
{
	AdjMatrix* UDN = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	Create_UDN(UDN);
	Print_UDN(UDN);
	//int MST = Prim(UDN);
	//printf("\nMST:%d", MST);

	printf("\n");
	MiniSpanTree_Prim(UDN);

}























