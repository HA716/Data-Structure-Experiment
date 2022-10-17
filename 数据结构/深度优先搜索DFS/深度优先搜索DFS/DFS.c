#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MaxSize 100

//该数组保存图中每个结点的访问状态，未访问的给0，已访问的给1
int visited[MaxSize];


typedef enum  //枚举图的类型
{
	DG,  //有向图  Direct Graph
	UDG, //无向图
	DN,  //有向网  Direct Network
	UDN  //无向网
}GraphKind;



//图的顺序存储：邻接矩阵表示法
typedef struct MATRIXGRAPH
{
	char * verTex[MaxSize];      //一维数组存放顶点，且数量最多为MaxSize
	int arcs[MaxSize][MaxSize];  //邻接矩阵存放点和边的关系，有邻接边就存入1，没有邻接边就存入0（可以认为是权值）
	int verTexNum;               //记录顶点的数量
	int arcsNum;                 //记录边的数量（邻接边）
	GraphKind graphKind;         //图的类型
}MatrixGraph;

//寻找邻接点ver在图G中的位置（从0开始找）
int Locate(MatrixGraph*G, char * ver)
{
	int index = 0;
	while (index < G->verTexNum)
	{
		if (strcmp(G->verTex[index], ver) == 0) //若找到，则返回位置下标
		{
			break;
		}
		index++;
	}

	//index == G->verTexNum的情况就代表没有找到，则返回-1
	return index == G->verTexNum ? -1 : index;

}




//创建无向图：1、邻接矩阵对称  2、第i个顶点的度数=第i行中1的个数
int CreateUDG(MatrixGraph * G)
{
	G->graphKind = UDG;                                    //设置图的类型为无向图  
	printf("%s", "请输入顶点数");
	scanf_s("%d", &G->verTexNum);
	printf("%s", "请输入边数");
	scanf_s("%d", &G->arcsNum);
	//初始化顶点
	for (int i = 0; i < G->verTexNum; i++)
	{
		G->verTex[i] = (char*)malloc(sizeof(char) * 10);    //因为是指针，所以要为每个顶点都分配空间
		printf("初始化顶点，请输入各个顶点名");
		scanf_s("%s", G->verTex[i], 10);

	}

	//初始化邻接矩阵(方阵的行列数都是等于顶点数)：所有边的权值置为0
	for (int i = 0; i < G->verTexNum; i++)
	{
		for (int j = 0; j < G->verTexNum; j++)
		{
			G->arcs[i][j] = 0;
		}
	}


	//构建邻接矩阵
	for (int k = 0; k < G->arcsNum; k++)  //边的数量就是邻接点的对数
	{
		//ver1、ver2是临时变量，互为邻接点，为邻接点申请内存空间
		char * ver1 = (char*)malloc(sizeof(char) * 10);
		char * ver2 = (char*)malloc(sizeof(char) * 10);
		//构建邻接点的关系
		printf("顶点名：");
		scanf_s("%s", ver1, 10);

		printf("邻接点名：");
		scanf_s("%s", ver2, 10);

		//寻找邻接点ver1、ver2在图中的位置
		int x = Locate(G, ver1);
		int y = Locate(G, ver2);

		if (x == -1 || y == -1) //构建失败
		{
			return -1;
		}
		else
		{
			//无向图的邻接矩阵对称
			G->arcs[x][y] = 1;     //代表x、y处的两个顶点是邻接点，故有邻接边
			G->arcs[y][x] = 1;

		}

		free(ver1);
		free(ver2);
	}
	return 1;    //构建成功
}




//在邻接矩阵中，返回顶点ver所在行的第一个邻接点下标
int FirstAdjVer(MatrixGraph*G, char* ver)
{
	//因为在邻接矩阵中，邻接点和它所邻接的顶点一定在同一行在，所以i就是邻接点所在行的位置
	int i = Locate(G, ver);      //顶点ver的下标为i
	if (i == -1)
	{
		return -1;       //代表没有找到这个顶点
	}
	else
	{
		int defaultWright;     //默认权重：图为0，网为∞
		defaultWright = G->graphKind <= 1 ? 0 : INT_MAX;

		//搜索顶点的第一个邻接点的下标
		for (int j = 0; j < G->verTexNum; j++)
		{
			//在顶点所在的第i行中，若j列的元素的权值不等于默认值，那么这个点就是邻接点
			if (G->verTex[i][j] != defaultWright) 
			{
				return j;    //返回邻接点的位置
			}

		}

		return 0;   //没找到邻接点就返回0

	}


}


//寻找第二个邻接点：在图G的顶点ver1，除第一个邻接点ver2外的另一个邻接点
int  SecondAdjVer(MatrixGraph*G, char*ver1, char*ver2)
{
	int index1 = Locate(G, ver1);  //顶点的索引值
	int index2 = Locate(G, ver2);  //第一个邻接点的索引值
	if (index1 == -1 || index2 == -1)
	{
		return 0;    
	}

	//设置邻接矩阵的默认权重
	int defaultWeight;
	defaultWeight = G->graphKind <= 1 ? 0 : INT_MAX;

	//寻找第二个邻接点
	for (int i = index2 + 1; i < G->verTexNum; i++)  //int i = index2 + 1; 因为要从第一个邻接点的下一个位置去寻找第二个邻接点
	{
		if (G->verTex[index1][i] != defaultWeight)   //邻接点的标志就是 不等于默认权重
		{
			return i;
		}
	}

	return 0;     //没找到第二个邻接点就返回0

}



//深度优先搜索的核心算法：DFS_Core
void DFS_Core(MatrixGraph *G,int index)   //可替换index为char*
{
	printf("-> %s", G->verTex[index]);          //访问下标为index的顶点
	visited[index] = 1;                         //标记下标为index的顶点为已访问
	

	//回溯：当没有找到第二个邻接点时，返回i=0,跳出循环
	for (int i = FirstAdjVer(G, G->verTex[index]); i;i=SecondAdjVer(G,G->verTex[index],G->verTex[i]))
	{                                                               //            ⬆              ⬆
		if (visited[i] == 0)                                        //         顶点索引     第一个邻接点的索引
		{
			DFS_Core(G, i);  //如果没有访问过，就继续递归遍历去访问
		}
 
	}


}


//邻接矩阵的深度优先搜索DFS
void DFS(MatrixGraph*G)
{
	//初始化状态数组
	for (int i = 0; i < G->verTexNum; i++)
	{
		visited[i] = 0;
	}

	//DFS遍历
	for (int i = 0; i < G->verTexNum; i++)
	{
		if (visited[i] == 0)   //存在未被访问到的顶点
		{
			//调用遍历函数
			DFS_Core(G, i);
		}
	}
}


//创建有向网：1、邻接矩阵不对称  2、权重默认为无穷大，用INT_MAX表示，邻接边的权重要认为输入
int CreateDN(MatrixGraph * G)
{
	G->graphKind = DN;                                    //设置图的类型为有向图  
	printf("%s", "请输入顶点数");
	scanf_s("%d", &G->verTexNum);
	printf("%s", "请输入边数");
	scanf_s("%d", &G->arcsNum);

	for (int i = 0; i < G->verTexNum; i++)
	{
		G->verTex[i] = (char*)malloc(sizeof(char) * 10);
		printf("初始化顶点，请输入各个顶点名");
		scanf_s("%s", G->verTex[i], 10);

	}

	for (int i = 0; i < G->verTexNum; i++)
	{
		for (int j = 0; j < G->verTexNum; j++)
		{
			G->arcs[i][j] = 0;
		}
	}

	for (int k = 0; k < G->arcsNum; k++)
	{
		char * ver1 = (char*)malloc(sizeof(char) * 10);
		char * ver2 = (char*)malloc(sizeof(char) * 10);

		printf("顶点名：");
		scanf_s("%s", ver1, 10);

		printf("邻接点名：");
		scanf_s("%s", ver2, 10);

		int x = Locate(G, ver1);
		int y = Locate(G, ver2);

		if (x == -1 || y == -1)
		{
			return -1;
		}
		else
		{
			int value;
			printf("请输入权重");
			scanf_s("%d", &value);
			//有向网的邻接矩阵不对称，且邻接边的权重靠人为输入
			G->arcs[x][y] = value;     //区别在于此：要用手动输入的value进行赋值
		//	G->arcs[y][x] = 1;     //注释掉这一行就是有向图，否则就是无向图，这是有向图与无向图代码的唯一区别

		}
		free(ver1);
		free(ver2);
	}
	return 1;    //构建成功
}


int main()
{
	MatrixGraph * G = (MatrixGraph *)malloc(sizeof(MatrixGraph));
	int ret = CreateDN(G);     //ret接收无向图构建的结果（成功或失败）
	if (ret == -1)
	{
		printf("无向图构建失败");
	}
	else
	{
		for (int i = 0; i < G->verTexNum; i++)
		{
			printf("\t%s", G->verTex[i]);
		}

		for (int i = 0; i < G->verTexNum; i++)
		{
			printf("\n%s", G->verTex[i]);
			for (int j = 0; j < G->verTexNum; j++)
			{
				if (G->arcs[i][j] == INT_MAX)      //打印网的邻接矩阵时，把INT_MAX这个数打印成∞便于观察
				{
					printf("\t%∞");
				}
				printf("\t%d", G->arcs[i][j]);
			}

		}

	}

	printf("\n");
	DFS(G);




}























