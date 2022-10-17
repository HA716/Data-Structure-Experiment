#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <float.h>
//#include<string>
#pragma warning(disable:4996)
#define MAX 1000


typedef struct HUFFMANTREE
{
	char data[MAX];  //���������
	double weight;
	int parent;
	int leftChild;
	int rightChild;
}HFtree;



void CreateTree(HFtree*tree,int n,double weight[], char**arr_str)
{
	//��ʼ��n��Ҷ�ӽ��
	for (int i = 0; i < n; i++)
	{
		strcpy_s(tree[i].data, strlen(arr_str[i]) + 1, arr_str[i]);
		tree[i].weight = weight[i];
		tree[i].parent = -1;
		tree[i].leftChild = -1;
		tree[i].rightChild = -1;
	}
	//��ʼ��n-1����Ҷ�ӽ��
	for (int i = n; i < 2 * n - 1; i++)
	{
		tree[i].weight = -1;
		tree[i].parent = -1;
		tree[i].leftChild = -1;
		tree[i].rightChild = -1;
	}


	double min1, min2;
	int pos1, pos2;
	//for (int i = 0; i < 2 * n - 1; i++) {		//�����ȫ����Ϊ-1
	//	tree[i].leftChild = tree[i].parent = tree[i].rightChild = -1;
	//}
	for (int i = n; i < 2 * n - 1; i++) {		//����n0-1����֧���
		min1 = DBL_MAX;   //DBL_MAX��double���͵����ֵ
		min2 = DBL_MAX;
		pos1 = pos2 = -1;
		//����ȫ����㣬��Ȩֵ��С��û��˫�׽���������㹹��˫�׽��
		for (int j = 0; j < i ; j++) 
		{//i�ǵ�ǰ���н��ĸ���	
			if (tree[j].parent == -1) 
			{					
				if (min1 > tree[j].weight) 
				{
					min2 = min1;
					pos2 = pos1;
					min1 = tree[j].weight;
					pos1 = j;
				}
				//����һ��Ҫд��else if��д��if��������ȷ
	//			//��Ϊ��tree[j].weight < min1����tree[j].weight < min2����������if�ڵĴ��붼��ִ�У�����������
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
	////����n-1����Ҷ�ӽ��
	//double min1;
	//double min2;
	//int pos1, pos2;
	//for (int i = n; i < 2 * n - 1; i++)
	//{
	//	 min1 = DBL_MAX;   //DBL_MAXʹdouble���͵����ֵ
	//	 min2 = DBL_MAX;
	//	//int  min1 = INT_MAX;   //DBL_MAXʹdouble���͵����ֵ
	//	//int  min2 = INT_MAX;
	//	 pos1 = -1;      //��Сֵ�������е�λ��
	//	 pos2 = -1;      //��Сֵ�������е�λ��

	//    //����ȫ����㣬��Ȩֵ��С��û��˫�׽���������㹹��˫�׽��
	//	for (int j = 0; j < i; j++)
	//	{//i�ǵ�ǰ���н��ĸ���
	//		if (tree[j].parent == -1)
	//		{
	//			if (tree[j].weight < min1)
	//			{
	//				//�⼸����˳���ܴ�
	//				min2 = min1;
	//				pos2 = pos1;
	//				min1 = tree[j].weight;
	//				pos1 = j;
	//							
	//			}
	//			//����һ��Ҫд��else if��д��if��������ȷ
	//			//��Ϊ��tree[j].weight < min1����tree[j].weight < min2����������if�ڵĴ��붼��ִ�У�����������
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

		//��ӡ��������
		
	/*	printf("%.2f (%.2f , %.2f)\n",  tree[i].weight, tree[pos1].weight, tree[pos2].weight);*/
		printf("%.2f (%.2f , %.2f)\n", tree[i].weight, tree[pos1].weight, tree[pos2].weight);  ;
	}


}

//����������
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


		//����ǰҶ�ӽ��Ĺ��������븴�Ƶ�ָ������huffmanCode��
		huffmanCode[i] = (char*)malloc(sizeof(char)*(n - start));
		strcpy_s(huffmanCode[i],(n-start) ,&curCode[start]);
	
	}
	free(curCode);

	//��ӡ��������������
	for (int i = 0;i < n; i++)
	{
		printf("%s��%s\n", tree[i].data, huffmanCode[i]);
	}
}


//ƽ�����볤��=�볤�����ֳ��ֵĸ���
double AveLength(char**huffmanCode,double *weight,int n)
{
	double len = 0;
	double total=0;  //��Ȩ�� 
	double *p = (double *)malloc(sizeof(double)*n);  //��¼ÿ������ĸ���

	for (int i = 0; i < n; i++)
	{
		total += (double)(weight[i]);

	}
	//ÿ��������ֵĸ���
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
	printf("������Ҷ�ӽ��ĸ�����");
	int n;
	scanf_s("%d", &n);
	double *Weight = (double *)malloc(sizeof(double)*(2 * n - 1));

	char**arr_str = (char**)malloc(sizeof(char*)*n);  //n��Ҷ�ӽ��
	for (int j = 0; j < n; j++)
	{
		arr_str[j] = (char*)malloc(sizeof(char)*MAX); //ÿ��Ҷ�ӽ��������Ĵ�С
	}
	char**huffmanCode = (char**)malloc(sizeof(char*)*n);  //n��Ҷ�ӽ��Ĺ�������������

	for (int i = 0; i < n; i++)
	{
		printf("��%d��Ҷ�ӽ�㣺\n", i+1);
		printf("data:");
		scanf_s("%s", arr_str[i],MAX);
		printf("weight:");
		scanf_s("%lf",&Weight[i]);
	}

	HFtree * tree = (HFtree*)malloc(sizeof(HFtree)*(2*n-1));
	//��1��.������������
	printf("********************************\n");
	printf("����������\n");
	CreateTree(tree, n, Weight, arr_str);
	//��2��.��ӡ����������
	printf("********************************\n");
	HuffManCode(tree, n, huffmanCode);
	//��3��.ƽ�����볤��
	printf("********************************\n");
	double len = AveLength(huffmanCode, Weight, n);
	printf("ƽ�����볤�ȣ�%f", len);
}









