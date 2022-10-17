#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100
#define NAME_SIZE 10

//采用邻接矩阵法存储有向图


typedef struct ADJMAXTRIX
{

	char* Vertex[MAX];  //顶点数组
	int arc[MAX][MAX];  //邻接矩阵
	int verNum;
	int arcNum;
}AdjMatrix;

int Located(AdjMatrix*G, char*ver)
{
	int index = -1;
	if (G == NULL) return;
	else
	{
		for (int i = 0; i < G->verNum; i++)
		{
			if (strcmp(G->Vertex[i], ver) == 0)
			{
				index = i;
			}
		}//end for

	}
	return index;   // -1代表没找到

}


void Print_DG(AdjMatrix*G)
{
	if (G == NULL) return;
	else
	{
		for (int i = 0; i < G->verNum; i++)
		{
			for (int j = 0; j < G->verNum; j++)
			{
				printf("%d ", G->arc[i][j]);
			}
			printf("\n");
		}


	}

}


void Create_DG(AdjMatrix*G)
{
	//输入图的顶点数和边数
	printf("请输入顶点个数：");
	scanf_s("%d", &G->verNum);
	getchar();
	printf("请输入边的数量：");
	scanf_s("%d", &G->arcNum);
	getchar();

	//初始化邻接矩阵：根据顶点
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			G->arc[i][j] = 0;
		}
	}

	//Print_DG(G);
	//printf("\n%d", G->arcNum);
	//printf("\n%d", G->verNum);
	//初始化顶点数组
	for (int i = 0; i < G->verNum; i++)
	{
		G->Vertex[i] = (char*)malloc(sizeof(char)*NAME_SIZE);
		printf("%d：", i + 1);
		scanf_s("%s", G->Vertex[i], NAME_SIZE);
		getchar();
	}
	//for (int i = 0; i < G->verNum; i++)
	//{
	//	printf("%s   ", G->Vertex[i]);
	//}

	//创建邻接矩阵:根据边
	for (int k = 0; k < G->arcNum; k++)
	{
		char *ver1 = (char*)malloc(sizeof(char)*NAME_SIZE);
		char *ver2 = (char*)malloc(sizeof(char)*NAME_SIZE);
		//int weight;
		printf("顶点：");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("邻接点：");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();
	/*	printf("权值：");
		scanf_s("%d", &weight);
		getchar();*/

		int i = Located(G, ver1);
		int j = Located(G, ver2);
		//printf("\ni:%d", i);
		//printf("\nj:%d", j);


		if (i == -1 || j == -1)
		{//创建失败
			return;
		}
		else
		{
			G->arc[i][j] = 1;
		}
		free(ver1);
		free(ver2);
	}
}


//DFS深度优先搜索**********************************************
//初始化顶点标记为0,代表未被访问
void Init_Visited(AdjMatrix*G,int *visited)
{
	for (int i = 0; i < G->verNum; i++)
	{
		visited[i] = 0;
	}
}

//找索引为v的结点的第一个邻接点
int FirstAdjVex(AdjMatrix*G, int v)
{
	int index = -1;
	if (G == NULL || v<0 || v>G->verNum-1) return;
	for (int i = 0; i < G->verNum; i++)
	{
		//i是v的邻接点
		if (G->arc[v][i] != 0)
		{
			index = i;
		}
		
	}
	return index;   // -1代表没找到

}

//寻找结点v的邻接点，且这个邻接点要排在w后面
int NextAdjVex(AdjMatrix*G, int v, int w)
{
	int index = -1;
	if (G == NULL || v<0 || v>G->verNum-1) return;
	for (int i = w+1; i < G->verNum; i++)
	{
		if (G->arc[v][i] != 0)
		{
			index = i;
		}

	}
	return index;

}

//深度优先搜索
void DFS(AdjMatrix*G, int v,int *visited)
{
	visited[v] = 1;   //标记当前顶点v为 已访问
	printf("%s ", G->Vertex[v]);

	//w是邻接点
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
	{
		//邻接点w未被访问，则对其进行DFS遍历
		if (visited[w] == 0)
		{
			DFS(G, w, visited);
		}
	}
}


void DFS_Travel(AdjMatrix*G, int *visited)
{
	//初始化visited数组
	Init_Visited(G, visited);

	//遍历每个顶点，寻找每个顶点的所有邻接点
	for (int i = 0; i < G->verNum; i++)
	{
		if (visited[i] == 0)
		{
			DFS(G,i,visited);
		}

	}
}



//DFS非递归（栈）***************************************************************
void DFS_Stack(AdjMatrix*G, int *visited)
{
	int top = -1;  //栈顶指针，指向栈顶元素
	int Stack[MAX];
	int size=0;   //栈中元素个数
	int index=0;
	//初始化顶点标记
	Init_Visited(G, visited); 

	//遍历图中所有顶点，若当前顶点未被访问，则访问且让它入栈
	for (int i = 0; i < G->verNum; i++)
	{
		if (visited[i] == 0)
		{
			visited[i] = 1;
			Stack[++top] = i;   //入栈
			size++;
		}

		/*非空栈，则访问栈顶元素，然后弹出该栈顶元素，遍历查找栈顶元素的邻接点，
		  若栈顶元素的邻接点未被访问，则访问且让它入栈           */
		while (size>0)
		{
			index = Stack[top];
			//printf("index:%d", index);
			printf("%s ", G->Vertex[(Stack[top])]);   //访问栈顶元素
			
			top--;  //栈顶元素出栈，因为后面还要将未被访问的邻接点压栈
			size--;
			//搜索栈顶元素的邻接点
			for (int j = 0; j < G->verNum; j++)
			{
				//存在邻接点，且该邻接点未被访问，则访问且让它入栈
				if (G->arc[index][j] == 1 && visited[j] == 0)
				{
					visited[j] = 1;
					Stack[++top] = j;
					size++;
					//break;  //没必要break
				}
			}
		}//end while
	}//end for
}





//BFS广度优先搜索*******************************************************************
void BFS_Travel(AdjMatrix*G, int *visited)
{
	//采用顺序队列
	int head = 0;
	int rear = 0;
	int Queue[MAX];  //辅助队列
	//int  j, k;

	//初始化顶点标记，全部置为未被访问
	Init_Visited(G, visited);


	//开始遍历图中的每个顶点
	for (int i = 0; i < G->verNum; i++)
	{
		//当前顶点未被访问，则访问它，且让它入队
		if (visited[i] == 0)
		{
			visited[i] = 1;
			printf("%s ", G->Vertex[i]);
			Queue[rear++] = i;  //入队
		}
		//如队列非空，则遍历队列中所有结点，找它们的邻接点
		while (head != rear)
		{
			//cur是当前的队头结点
			int cur = Queue[head++];   //出队

			for (int w = FirstAdjVex(G, cur); w >= 0; w = NextAdjVex(G, cur, w))
			{
				//邻接点w未被访问，则访问它，且让它入队
				if (visited[w] == 0)
				{
					visited[w] = 1;  //访问
					printf("%s ", G->Vertex[w]);
					Queue[rear++] = w;  //入队

				}
			}
		}// end while
	}//end for

}





int main()
{
	//创建有向图
	AdjMatrix* DG = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	Create_DG(DG);
	Print_DG(DG);
	printf("\n");

	//DFS（递归）
	int *visited1 = (int *)malloc(sizeof(int)*MAX);   //标记结点是否被访问过
	printf("DFS递归：");
	DFS_Travel(DG, visited1);
	printf("\n");


	//DFS（非递归-栈）
	int *visited2 = (int *)malloc(sizeof(int)*MAX);
	printf("DFS非递归（栈）：");
	DFS_Stack(DG, visited2);
	printf("\n");


	////BFS
	int *visited3 = (int *)malloc(sizeof(int)*MAX);
	printf("BFS：");
	BFS_Travel(DG, visited3);
	printf("\n");

	free(visited1);
	free(visited2);
	free(visited3);

}
















