#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <float.h>
//#include<string>
#pragma warning(disable:4996)
#define MAX 1000


typedef struct HUFFMANTREE
{
	char data[MAX];  //结点数据域
	double weight;
	int parent;
	int leftChild;
	int rightChild;
}HFtree;



void CreateTree(HFtree*tree,int n,double weight[], char**arr_str)
{
	//初始化n个叶子结点
	for (int i = 0; i < n; i++)
	{
		strcpy_s(tree[i].data, strlen(arr_str[i]) + 1, arr_str[i]);
		tree[i].weight = weight[i];
		tree[i].parent = -1;
		tree[i].leftChild = -1;
		tree[i].rightChild = -1;
	}
	//初始化n-1个非叶子结点
	for (int i = n; i < 2 * n - 1; i++)
	{
		tree[i].weight = -1;
		tree[i].parent = -1;
		tree[i].leftChild = -1;
		tree[i].rightChild = -1;
	}


	double min1, min2;
	int pos1, pos2;
	//for (int i = 0; i < 2 * n - 1; i++) {		//相关域全部置为-1
	//	tree[i].leftChild = tree[i].parent = tree[i].rightChild = -1;
	//}
	for (int i = n; i < 2 * n - 1; i++) {		//构造n0-1个分支结点
		min1 = DBL_MAX;   //DBL_MAX是double类型的最大值
		min2 = DBL_MAX;
		pos1 = pos2 = -1;
		//遍历全部结点，找权值最小且没有双亲结点的两个结点构造双亲结点
		for (int j = 0; j < i ; j++) 
		{//i是当前已有结点的个数	
			if (tree[j].parent == -1) 
			{					
				if (min1 > tree[j].weight) 
				{
					min2 = min1;
					pos2 = pos1;
					min1 = tree[j].weight;
					pos1 = j;
				}
				//这里一定要写成else if，写成if则结果不正确
	//			//因为若tree[j].weight < min1，则tree[j].weight < min2，所以两个if内的代码都会执行，引起结果错误
				else if (min2 > tree[j].weight) {
					min2 = tree[j].weight;
					pos2 = j;
				}
			}
		}

		tree[i].weight = tree[pos1].weight + tree[pos2].weight;
		tree[i].leftChild = pos1;			
		tree[i].rightChild = pos2;
		tree[pos1].parent = i;
		tree[pos2].parent = i;



	//ERROR***************************error******************************
	////构造n-1个非叶子结点
	//double min1;
	//double min2;
	//int pos1, pos2;
	//for (int i = n; i < 2 * n - 1; i++)
	//{
	//	 min1 = DBL_MAX;   //DBL_MAX使double类型的最大值
	//	 min2 = DBL_MAX;
	//	//int  min1 = INT_MAX;   //DBL_MAX使double类型的最大值
	//	//int  min2 = INT_MAX;
	//	 pos1 = -1;      //最小值在数组中的位置
	//	 pos2 = -1;      //次小值在数组中的位置

	//    //遍历全部结点，找权值最小且没有双亲结点的两个结点构造双亲结点
	//	for (int j = 0; j < i; j++)
	//	{//i是当前已有结点的个数
	//		if (tree[j].parent == -1)
	//		{
	//			if (tree[j].weight < min1)
	//			{
	//				//这几步的顺序不能错
	//				min2 = min1;
	//				pos2 = pos1;
	//				min1 = tree[j].weight;
	//				pos1 = j;
	//							
	//			}
	//			//这里一定要写成else if，写成if则结果不正确
	//			//因为若tree[j].weight < min1，则tree[j].weight < min2，所以两个if内的代码都会执行，引起结果错误
	//			else if (tree[j].weight < min2)
	//			{
	//				min2 = tree[j].weight;
	//				pos2 = j;
	//			}
	//		}
 //  
	//	}
	//	tree[i].weight = tree[pos1].weight + tree[pos2].weight;
	//	tree[i].leftChild = min1;
	//	tree[i].rightChild = min2;
	//	tree[pos1].parent = i;
	//	tree[pos2].parent = i;

		//打印哈夫曼树
		
	/*	printf("%.2f (%.2f , %.2f)\n",  tree[i].weight, tree[pos1].weight, tree[pos2].weight);*/
		printf("%.2f (%.2f , %.2f)\n", tree[i].weight, tree[pos1].weight, tree[pos2].weight);  ;
	}


}

//哈夫曼编码
void HuffManCode(HFtree*tree, int n, char** huffmanCode)
{

	int cur;
	int parent;
	char *curCode = (char *)malloc(sizeof(char)*n);
	int start;
	curCode[n - 1] = '\0';
	for (int i = 0; i < n; i++)
	{
		start = n - 1;
		for (cur = i, parent = tree[i].parent; parent != -1;cur = parent,parent = tree[parent].parent )
		{
			if (tree[parent].leftChild == cur)
			{
				curCode[--start] = '0';
			}
	/*		if(tree[parent].rightChild == cur)
			{
				curCode[--start] = '1';
			}*/
			else 
			{
				curCode[--start] = '1';
			}
		}


		//将当前叶子结点的哈夫曼编码复制到指针数组huffmanCode中
		huffmanCode[i] = (char*)malloc(sizeof(char)*(n - start));
		strcpy_s(huffmanCode[i],(n-start) ,&curCode[start]);
	
	}
	free(curCode);

	//打印哈夫曼编码序列
	for (int i = 0;i < n; i++)
	{
		printf("%s：%s\n", tree[i].data, huffmanCode[i]);
	}
}


//平均编码长度=码长×码字出现的概率
double AveLength(char**huffmanCode,double *weight,int n)
{
	double len = 0;
	double total=0;  //总权重 
	double *p = (double *)malloc(sizeof(double)*n);  //记录每个编码的概率

	for (int i = 0; i < n; i++)
	{
		total += (double)(weight[i]);

	}
	//每个编码出现的概率
	for (int i = 0; i < n; i++)
	{
		p[i] = ((double)weight[i]) / total;
	}
	for (int i = 0; i < n; i++)
	{
		len += ((double)strlen(huffmanCode[i]))*p[i];
	}

	return len;
}


void main()
{
	printf("请输入叶子结点的个数：");
	int n;
	scanf_s("%d", &n);
	double *Weight = (double *)malloc(sizeof(double)*(2 * n - 1));

	char**arr_str = (char**)malloc(sizeof(char*)*n);  //n个叶子结点
	for (int j = 0; j < n; j++)
	{
		arr_str[j] = (char*)malloc(sizeof(char)*MAX); //每个叶子结点数据域的大小
	}
	char**huffmanCode = (char**)malloc(sizeof(char*)*n);  //n个叶子结点的哈夫曼编码数组

	for (int i = 0; i < n; i++)
	{
		printf("第%d个叶子结点：\n", i+1);
		printf("data:");
		scanf_s("%s", arr_str[i],MAX);
		printf("weight:");
		scanf_s("%lf",&Weight[i]);
	}

	HFtree * tree = (HFtree*)malloc(sizeof(HFtree)*(2*n-1));
	//（1）.创建哈夫曼树
	printf("********************************\n");
	printf("哈夫曼树：\n");
	CreateTree(tree, n, Weight, arr_str);
	//（2）.打印哈夫曼编码
	printf("********************************\n");
	HuffManCode(tree, n, huffmanCode);
	//（3）.平均编码长度
	printf("********************************\n");
	double len = AveLength(huffmanCode, Weight, n);
	printf("平均编码长度：%f", len);
}









