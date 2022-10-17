#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#pragma warning (disable:4996)

#define MAX 100
#define NAME_SIZE 10

//枚举图的类型
typedef enum GRAPHKIND
{
	DG,   //有向图 0
	UDG,  //无向图 1
	DN,   //有向网 2
	UDN   //无向网 3
}GraphKind;


//有向图 带权 邻接矩阵 邻接表

//邻接矩阵********************************************************
typedef struct ADJMATRIX
{
	char *verTex[MAX]; //顶点数组 
	int arc[MAX][MAX]; //邻接矩阵
	int verNum; //记录顶点的数量
	int arcNum; //记录边的数量
	GraphKind kind; //图的类型
}AdjMatrix;

//*******************************************************************
//边表
typedef struct ARCLIST
{
	int adjvex;               //邻接点索引
	struct ARCLIST * next;    //链接边表的指针
	int weight;               //边的权重:从顶点到该边表结点的边的权重
}ArcNode; //保存Node节点的相邻节点信息

//顶点表
typedef struct VEXLIST
{
	char data[NAME_SIZE];   //顶点名
	ArcNode * firstArc;     //由顶点指向第一个邻接点的边
}VexNode;  //保存顶点信息

//邻接表
typedef struct ADJLIST
{
	VexNode verTex[MAX];  //顶点数组
	int verNum;           //当前点的数量 
	int arcNum;           //当前边的数量
	GraphKind kind;       //图的类型
}AdjList;

//*********************************************************************



//定位 顶点和邻接点 在顶点数组中的索引下标
int Located(AdjMatrix*G,char * ver)
{
	if (G == NULL) return;
	int index = -1;
	
	for (int i = 0; i < G->verNum; i++)
	{
		//相等才返回0
		if (strcmp(G->verTex[i], ver) == 0)
		{
			index = i;
			break;
		}
	}
	return index; //找到就返回真实下标index，找不到就返回-1
}


//邻接表的Located
int Located_List(AdjList*G, char *ver)
{
	if (G == NULL) return;
	int index = -1;
	for (int i = 0; i < G->verNum; i++)
	{
		             //          ↓区别
		if (strcmp(G->verTex[i].data, ver) == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}





//无向图的邻接表*************************************************************
void Create_UDG_list(AdjList* G)
{
	G->kind = UDG;
	printf("请输入顶点数：");
	scanf_s("%d", &G->verNum);
	getchar();
	printf("请输入边的数量：");
	scanf_s("%d", &G->arcNum);
	getchar();
	
	//初始化顶点表
	printf("初始化顶点表，请输入各个顶点名：\n");
	for (int i = 0; i < G->verNum; i++)
	{
		printf("%d：", i + 1);
		scanf_s("%s", G->verTex[i].data, NAME_SIZE);
		getchar();
		G->verTex[i].firstArc = NULL;  //！
	}


	printf("创建邻接表：\n");
	for(int k=0;k<G->arcNum;k++)
	{
		char * ver1 = (char *)malloc(sizeof(char)*NAME_SIZE);
		char * ver2 = (char *)malloc(sizeof(char)*NAME_SIZE);
		printf("顶点：");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("邻接点：");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();

		int i = Located_List(G, ver1);
		int j = Located_List(G, ver2);
		if (i == -1 || j == -1) return;

		else
		{
			//创建无向图的边表结点（无向图是对称的）
		    //i做顶点，j做邻接点
			ArcNode*arcNode1 = (ArcNode*)malloc(sizeof(ArcNode));
			arcNode1->adjvex = j;
			arcNode1->next = G->verTex[i].firstArc;
			G->verTex[i].firstArc = arcNode1;

			//j做顶点，i做邻接点
			ArcNode*arcNode2 = (ArcNode*)malloc(sizeof(ArcNode));
			arcNode2->adjvex = i;
			arcNode2->next = G->verTex[j].firstArc;
			G->verTex[j].firstArc = arcNode2;

		}//end else
		
		free(ver1);
		free(ver2);
		
	}//end for

}


//有向网的邻接表*******************************************************
void Create_DN_list(AdjList* G)
{
	G->kind = DN;
	printf("请输入顶点数：");
	scanf_s("%d", &G->verNum);
	getchar();
	printf("请输入边的数量：");
	scanf_s("%d", &G->arcNum);
	getchar();

	//初始化顶点表
	printf("初始化顶点表，请输入各个顶点名：\n");
	for (int i = 0; i < G->verNum; i++)
	{
		printf("%d：", i + 1);
		scanf_s("%s", G->verTex[i].data, NAME_SIZE);
		getchar();
		G->verTex[i].firstArc = NULL;  //！
	}


	//创建邻接表
	int weight;
	printf("创建邻接表：\n");
	for (int k = 0; k < G->arcNum; k++)
	{
		char * ver1 = (char *)malloc(sizeof(char)*NAME_SIZE);
		char * ver2 = (char *)malloc(sizeof(char)*NAME_SIZE);
		printf("顶点：");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("邻接点：");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();
		printf("权值为：");
		scanf_s("%d", &weight);
		getchar();

		int i = Located_List(G, ver1);  //顶点
		int j = Located_List(G, ver2);  //邻接点
		if (i == -1 || j == -1) return;

		else
		{
			//创建有向网的边表结点
			//i做顶点，j做邻接点
			ArcNode*arcNode = (ArcNode*)malloc(sizeof(ArcNode));
			arcNode->adjvex = j;
			arcNode->next = G->verTex[i].firstArc;
			G->verTex[i].firstArc = arcNode;
			arcNode->weight = weight;

		}//end else

		free(ver1);
		free(ver2);

	}//end for

}






//打印邻接表
void Print_List(AdjList*G)
{
	if (G == NULL) return;

	for (int i = 0; i < G->verNum; i++)
	{
		printf("%s ： %d", G->verTex[i].data, i);
		//边表不为空
		if (G->verTex[i].firstArc != NULL)
		{
			//temp是边表结点
			ArcNode*temp = G->verTex[i].firstArc;
			while (temp != NULL)
			{
				//有向网或者无向网才需要打印 权值和索引
				if (G->kind == DN || G->kind == UDN)
				{
					printf("-> %d(%d) ", temp->adjvex, temp->weight);
					temp = temp->next;
				}
				//有向图或者无向图只需要打印索引，无需打印权值
				else
				{
					printf("-> %d ", temp->adjvex);
					temp = temp->next;
				}
		
			}
		}

		else
		{
			printf("-> NULL");
		}
		printf("\n");
	}
}


//销毁邻接表
void Destory_list(ArcNode*arcNode)
{
	if (arcNode == NULL)
	{
		return;
	}
	Destory_list(arcNode->next);
	free(arcNode);
}





//无向图的邻接矩阵************************************************************************
void Create_UDG(AdjMatrix*G)
{
	G->kind = UDG;      //设置图的类型为UDG
	int verNum, arcNum;
	printf("请输入顶点数：");
	scanf_s("%d", &verNum);
	printf("请输入边的数量：");
	scanf_s("%d", &arcNum);
	G->verNum = verNum;
	G->arcNum = arcNum;
	//初始化顶点信息
	printf("初始化顶点，请输入各个顶点名：\n");
	for (int i = 0; i < G->verNum; i++)
	{
		G->verTex[i] = (char*)malloc(sizeof(char) * NAME_SIZE);
		printf("%d:", i + 1);
		scanf_s("%s", G->verTex[i], NAME_SIZE);
	}
	
	//printf("点：%d", verNum);
	//printf("\n边%d\n", arcNum);
	//for (int i = 0; i < UDG->verNum; i++)
	//{
	//	printf("%s ", UDG->verTex[i]);
	//}

	//初始化邻接矩阵
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			G->arc[i][j] = 0;
		}
	}

	//创建无向图
	printf("创建邻接矩阵：\n");
	for (int k = 0; k < G->arcNum; k++)
	{
		char *ver1 = (char*)malloc(sizeof(char) * NAME_SIZE); //顶点
		char *ver2 = (char*)malloc(sizeof(char) * NAME_SIZE); //邻接点
		printf("顶点：");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("邻接点：");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();
		//定位 顶点和邻接点 在顶点数组中的索引下标
		int i = Located(G, ver1);
		int j = Located(G, ver2);
		//printf("i:%d", i);
		//printf("j:%d", j);
		if (i == -1 || j == -1)
		{//创建失败
			return;
		}
		G->arc[i][j] = 1;
		G->arc[j][i] = 1;

		free(ver1);
		free(ver2);
	}

}

void Print_UDG(AdjMatrix*G)
{
	if (G == NULL) return;
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			printf("%d ", G->arc[i][j]);
		}
		printf("\n");
	}
}


//有向网的邻接矩阵*************************************************************************
void Create_DN(AdjMatrix*G)
{
	G->kind = DN;  //有向网
	int verNum;
	int arcNum;
	printf("请输入顶点数：");
	scanf_s("%d", &verNum);\
	getchar();
	printf("请输入弧的数量：");
	scanf_s("%d", &arcNum);
	getchar();
	G->verNum = verNum;
	G->arcNum = arcNum;

	//初始化有向网
	printf("初始化顶点，请输入各个顶点名：\n");
	for (int i = 0; i < G->verNum; i++)
	{
		printf("%d：", i + 1);
		G->verTex[i] = (char*)malloc(sizeof(char)*NAME_SIZE);
		scanf_s("%s", G->verTex[i], NAME_SIZE);
	}

	//初始化有向网的邻接矩阵为∞
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			G->arc[i][j] = INT_MAX;   // ∞
		}
	}

	//创建邻接矩阵
	printf("创建邻接矩阵：\n");
	for (int k = 0; k < G->arcNum; k++)
	{
		int weight;
		char*ver1 = (char*)malloc(sizeof(char)*NAME_SIZE);
		char*ver2 = (char*)malloc(sizeof(char)*NAME_SIZE);
		printf("顶点：");
		scanf_s("%s", ver1, NAME_SIZE);
		printf("邻接点：");
		scanf_s("%s", ver2, NAME_SIZE);

		//定位顶点和邻接点在顶点数组中的位置
		int i = Located(G, ver1);
		int j = Located(G, ver2);

		if (i == -1 || j == -1)  return;
		else
		{
			printf("请输入弧的权值：");
			scanf_s("%d", &weight);
			getchar();
			G->arc[i][j] = weight;
		}

		free(ver1);
		free(ver2);
	}

}

//打印有向网
void Print_DG(AdjMatrix*G)
{
	if (G == NULL) return;
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
				printf("%d ", G->arc[i][j]);
			}
		}// end for j
		printf("\n");
	}//end for i
}



int main()
{
	//无向图的邻接矩阵
	printf("创建无向图的邻接矩阵：\n");
	AdjMatrix*UDG = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	Create_UDG(UDG);
	printf("UDG邻接矩阵为：\n");
	Print_UDG(UDG);
	printf("\n***************************************\n");

	//有向网的邻接矩阵
	printf("创建有向网的邻接矩阵：\n");
	AdjMatrix*DN = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	Create_DN(DN);
	printf("DN邻接矩阵为：\n");
	Print_DG(DN);
	printf("\n***************************************\n");

	//无向图的邻接表
	printf("创建无向图的邻接表：\n");
	AdjList*UDG_list = (AdjList*)malloc(sizeof(AdjList));
	Create_UDG_list(UDG_list);
	printf("UDG的邻接表：\n");
	Print_List(UDG_list);
	printf("\n***************************************\n");

	//有向网的邻接表
	printf("创建有向网的邻接表：\n");
	AdjList*DN_list = (AdjList*)malloc(sizeof(AdjList));
	Create_DN_list(DN_list);
	printf("DN的邻接表：\n");
	Print_List(DN_list);
	printf("\n***************************************\n");

	//销毁无向图的邻接表
	for (int i = 0; i < UDG_list->verNum; i++)
	{
		ArcNode*p = UDG_list->verTex[i].firstArc;
		Destory_list(p);
	}
	printf("\n成功销毁UDG\n");

	//销毁有向网的邻接表
	for (int i = 0; i < DN_list->verNum; i++)
	{
		ArcNode*p = DN_list->verTex[i].firstArc;
		Destory_list(p);
	}
	printf("\n成功销毁DN\n");

}




















