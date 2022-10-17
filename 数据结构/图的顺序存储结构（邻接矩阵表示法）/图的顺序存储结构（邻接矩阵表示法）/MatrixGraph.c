#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxSize 100



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
	char * verTex [MaxSize];     //一维数组存放顶点，且数量最多为MaxSize
	int arcs[MaxSize][MaxSize];  //邻接矩阵存放点和边的关系，由邻接边就存入1，没有邻接边就存入0（可以认为是权值）
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
		if (strcmp(G->verTex[index] , ver)==0) //若找到，则返回位置下标
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
		scanf_s("%s", G->verTex[i],10);

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
		scanf_s("%s", ver1,10);

		printf("邻接点名：");
		scanf_s("%s", ver2,10);
		
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



//创建有向图：1、邻接矩阵不对称  2、第i个顶点的入度=第i列中1的个数
int CreateDG(MatrixGraph * G)
{
	G->graphKind = DG;                                    //设置图的类型为有向图  
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

	//邻接矩阵初始化为无穷大∞，用INT_MAX表示
	for (int i = 0; i < G->verTexNum; i++)
	{
		for (int j = 0; j < G->verTexNum; j++)
		{
			G->arcs[i][j] = INT_MAX;    //INT_MAX是整形的最大值，可认为是无穷大
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
			//有向图的邻接矩阵不对称
			G->arcs[x][y] = 1;     //代表x、y处的两个顶点是邻接点，故有邻接边
		//	G->arcs[y][x] = 1;     //区别在于此：注释掉这一行就是有向图，否则就是无向图，这是有向图与无向图代码的唯一区别

		}
		free(ver1);
		free(ver2);
	}
	return 1;    //构建成功
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
	MatrixGraph * G=(MatrixGraph *)malloc(sizeof(MatrixGraph ));
	int ret = CreateUDG(G);     //ret接收无向图构建的结果（成功或失败）
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
	
		for (int i = 0; i < G->verTexNum;i++)
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

}




