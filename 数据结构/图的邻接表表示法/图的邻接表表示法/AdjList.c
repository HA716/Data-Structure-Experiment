#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxSize 100

typedef enum GEAPHKIND
{
	DG,
	UDG,
	DN,
	UDN
}GraphKind;



//构造边表：边表节点则是由存储边的终点在顶点表中的下标的数据域和指向下一个节点的指针域组成
typedef struct ARCNODE
{
	int AdjVex;                 //边表中结点的下标索引(也就是边的终点的位置)
	struct ARCNODE* nextArc;    //弧指针：指向当前结点的下一条弧
	int weight;                 //权重

	struct ARCNODE* nextOut;    //有向图的出边，用来构造 邻接表
	struct ARCNODE* nextIn;     //有向图的入边，用来构造 逆邻接表
	
}ArcNode;

//构造顶点表:顶点表节点由存储数据的数据域和存储边表头结点的指针域所组成
typedef struct VERLIST
{
	char * verTex;           //顶点名
	ArcNode * firstArc;      //边表的头指针

	ArcNode * firstOut;
	ArcNode * firstIn;

}VerList[maxSize];

//用邻接表实现图结构
typedef struct ADJGRAPH
{
	VerList ArrVerTex;   //顶点数组:元素是结点
	int vexNum;       //顶点数量
	int arcNum;       //边/弧的数量
	GraphKind graphKind;   //图的类型

}AdjGraph;


//寻找结点在邻接表中的位置
int Locate(AdjGraph * G, char * ver)
{
	int index =-1;
	if (ver == NULL)   return;
	if (G == NULL)     return;
	for (int i = 0; i < G->vexNum; i++)
	{		
		if (strcmp(ver, G->ArrVerTex[i].verTex) == 0)
		{
			index = i;
			break;
		}
	}
	return index;       //没找到就返回-1
}




//用邻接表创建无向图
int CreateUDG(AdjGraph * G)
{
	G->graphKind = UDG;   //设置图的类型为无向图
	printf("请输入顶点数量");
	scanf_s("%d", &G->vexNum);
	printf("请输入边的数量");
	scanf_s("%d", &G->arcNum);
	//初始化顶点信息
	for (int i = 0; i < G->vexNum; i++)
	{
		G->ArrVerTex[i].verTex = (char *) malloc(sizeof(char) * 10);
		printf("顶点%d:", i + 1);
		scanf_s("%s", G->ArrVerTex[i].verTex,10);
		//初始化邻接表：把边表置空
		G->ArrVerTex[i].firstArc = NULL;
	}

	//输入顶点和邻接点信息
	for (int i = 0; i < G->arcNum; i++)   //边的数量就代表结点和邻接点有多少对
	{
		char * ver1 = (char*)malloc(sizeof(char) * 10);
		char * ver2 = (char*)malloc(sizeof(char) * 10);
		printf("顶点：");
		scanf_s("%s", ver1,10);
		printf("邻接点：");
		scanf_s("%s", ver2,10);
		int x = Locate(G, ver1);             //寻找ver1在顶点表中的位置下标
		int y = Locate(G, ver2);
		while (x == -1 || y == -1)  //没找到，即创建失败
		{
			free(ver1);
			free(ver2);
			return -1;       
		}

		//构建图结构
		//这是由结点y指向结点x的边
		ArcNode*arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		arcNode->AdjVex = x;                                //边表结点下标赋值为x
		arcNode->nextArc = G->ArrVerTex[y].firstArc;        //G->ArrVerTex[y].firstArc被初始化为NULL
		G->ArrVerTex[y].firstArc = arcNode;    
 		arcNode->weight = 1;                                //有边的地方权重设为1

		//无向图是对称的
		//这是由结点x指向结点y的边
		arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		arcNode->AdjVex = y;                                //边表结点下标赋值为x
		arcNode->nextArc = G->ArrVerTex[x].firstArc;        //G->ArrVerTex[y].firstArc被初始化为NULL
		G->ArrVerTex[x].firstArc = arcNode;
		arcNode->weight = 1;

		free(ver1);
		free(ver2);
	}
	return 1;

}

//有向图
int CreateDG(AdjGraph * G)
{
	G->graphKind = DG;   //设置图的类型为无向图
	printf("请输入顶点数量");
	scanf_s("%d", &G->vexNum);
	printf("请输入边的数量");
	scanf_s("%d", &G->arcNum);
	//初始化顶点信息
	for (int i = 0; i < G->vexNum; i++)
	{
		G->ArrVerTex[i].verTex = (char *)malloc(sizeof(char) * 10);
		printf("顶点%d:", i + 1);
		scanf_s("%s", G->ArrVerTex[i].verTex, 10);
		//初始化邻接表：把边表置空
		G->ArrVerTex[i].firstArc = NULL;
	}

	//输入顶点和邻接点信息
	for (int i = 0; i < G->arcNum; i++)   //边的数量就代表结点和邻接点有多少对
	{
		char * ver1 = (char*)malloc(sizeof(char) * 10);
		char * ver2 = (char*)malloc(sizeof(char) * 10);
		printf("顶点：");
		scanf_s("%s", ver1, 10);
		printf("邻接点：");
		scanf_s("%s", ver2, 10);
		int x = Locate(G, ver1);             //寻找ver1在顶点表中的位置下标
		int y = Locate(G, ver2);
		while (x == -1 || y == -1)  //没找到，即创建失败
		{
			free(ver1);
			free(ver2);
			return -1;
		}

		//构建有向图结构
		//这是由结点x指向结点y的边,是 出边表
		ArcNode*arcNode1 = (ArcNode*)malloc(sizeof(ArcNode));
		arcNode1->AdjVex = y;                                //边表结点下标赋值为x
		arcNode1->nextOut = G->ArrVerTex[x].firstOut;        //G->ArrVerTex[y].firstArc被初始化为NULL
		G->ArrVerTex[x].firstOut = arcNode1;
		arcNode1->weight = 1;

		//这是由结点y指向结点x的边,是 入边表
		ArcNode*arcNode2 = (ArcNode*)malloc(sizeof(ArcNode));
		//arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		arcNode2->AdjVex = x;                                //边表结点下标赋值为x
		arcNode2->nextIn = G->ArrVerTex[y].firstIn;        //G->ArrVerTex[y].firstArc被初始化为NULL
		G->ArrVerTex[y].firstIn = arcNode2;
		arcNode2->weight = 1;

		free(ver1);
		free(ver2);
	}
	return 1;
}








void TestUDG()
{
	AdjGraph* G1 = (AdjGraph*)malloc(sizeof(AdjGraph));
	
	int ret = CreateUDG(G1);

	if (ret == -1)
	{
		printf("创建失败");
		return;
	}
	else
	{
		//输出样式
		for (int i = 0; i < G1->vexNum; i++)
		{
			printf("%s", G1->ArrVerTex[i].verTex);
			ArcNode * arcNode = G1->ArrVerTex[i].firstArc;      //顶点指针 指向 边表头节点
			while (arcNode != NULL)
			{
				printf(" -> %d", arcNode->AdjVex);
				arcNode = arcNode->nextArc;                   //边表结点的下一个结点
			}
			printf("\n");
		}
	}
}

void TestDG()
{
	AdjGraph* G2 = (AdjGraph*)malloc(sizeof(AdjGraph));
	int ret = CreateDG(G2);

	
	打印邻接表
	for (int i = 0; i < G2->vexNum; i++)
	{
		ArcNode* arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		//printf("%s", G2->ArrVerTex[i]);
	    arcNode = G2->ArrVerTex[i].firstOut;  //顶点表的头指针 指向 边表的头节点
	
		printf("顶点%s",G2->ArrVerTex[i].verTex);
		while (arcNode)
		{
			printf("->%d", arcNode->AdjVex);         // arcNode->AdjVex是边表节点的下标索引值
			arcNode = arcNode->nextOut;              //nextOut指针是 出边表的
		}
		printf("\n");

	}

	//打印逆邻接表
	for (int i = 0; i < G2->vexNum; i++)
	{
		ArcNode* arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		printf("顶点%s", G2->ArrVerTex[i].verTex);
	    arcNode = G2->ArrVerTex[i].firstIn;  //顶点表的头指针 指向 边表的头节点
		while (arcNode != NULL)
		{
			printf("%d<-", arcNode->AdjVex);         // arcNode->AdjVex是边表节点的下标索引值
			arcNode = arcNode->nextIn;              //nextOut指针是 出边表的
		}
		printf("\n");

	}
}



//有向网：有向图的基础上加上权值
int CreateDN()
{



}




int main()
{
	//TestUDG();
	  TestDG();
}





