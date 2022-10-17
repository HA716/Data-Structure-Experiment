#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100
#define NAME_SIZE 10

//�����ڽӾ��󷨴洢����ͼ


typedef struct ADJMAXTRIX
{

	char* Vertex[MAX];  //��������
	int arc[MAX][MAX];  //�ڽӾ���
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
	return index;   // -1����û�ҵ�

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
	//����ͼ�Ķ������ͱ���
	printf("�����붥�������");
	scanf_s("%d", &G->verNum);
	getchar();
	printf("������ߵ�������");
	scanf_s("%d", &G->arcNum);
	getchar();

	//��ʼ���ڽӾ��󣺸��ݶ���
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
	//��ʼ����������
	for (int i = 0; i < G->verNum; i++)
	{
		G->Vertex[i] = (char*)malloc(sizeof(char)*NAME_SIZE);
		printf("%d��", i + 1);
		scanf_s("%s", G->Vertex[i], NAME_SIZE);
		getchar();
	}
	//for (int i = 0; i < G->verNum; i++)
	//{
	//	printf("%s   ", G->Vertex[i]);
	//}

	//�����ڽӾ���:���ݱ�
	for (int k = 0; k < G->arcNum; k++)
	{
		char *ver1 = (char*)malloc(sizeof(char)*NAME_SIZE);
		char *ver2 = (char*)malloc(sizeof(char)*NAME_SIZE);
		//int weight;
		printf("���㣺");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("�ڽӵ㣺");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();
	/*	printf("Ȩֵ��");
		scanf_s("%d", &weight);
		getchar();*/

		int i = Located(G, ver1);
		int j = Located(G, ver2);
		//printf("\ni:%d", i);
		//printf("\nj:%d", j);


		if (i == -1 || j == -1)
		{//����ʧ��
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


//DFS�����������**********************************************
//��ʼ��������Ϊ0,����δ������
void Init_Visited(AdjMatrix*G,int *visited)
{
	for (int i = 0; i < G->verNum; i++)
	{
		visited[i] = 0;
	}
}

//������Ϊv�Ľ��ĵ�һ���ڽӵ�
int FirstAdjVex(AdjMatrix*G, int v)
{
	int index = -1;
	if (G == NULL || v<0 || v>G->verNum-1) return;
	for (int i = 0; i < G->verNum; i++)
	{
		//i��v���ڽӵ�
		if (G->arc[v][i] != 0)
		{
			index = i;
		}
		
	}
	return index;   // -1����û�ҵ�

}

//Ѱ�ҽ��v���ڽӵ㣬������ڽӵ�Ҫ����w����
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

//�����������
void DFS(AdjMatrix*G, int v,int *visited)
{
	visited[v] = 1;   //��ǵ�ǰ����vΪ �ѷ���
	printf("%s ", G->Vertex[v]);

	//w���ڽӵ�
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
	{
		//�ڽӵ�wδ�����ʣ���������DFS����
		if (visited[w] == 0)
		{
			DFS(G, w, visited);
		}
	}
}


void DFS_Travel(AdjMatrix*G, int *visited)
{
	//��ʼ��visited����
	Init_Visited(G, visited);

	//����ÿ�����㣬Ѱ��ÿ������������ڽӵ�
	for (int i = 0; i < G->verNum; i++)
	{
		if (visited[i] == 0)
		{
			DFS(G,i,visited);
		}

	}
}



//DFS�ǵݹ飨ջ��***************************************************************
void DFS_Stack(AdjMatrix*G, int *visited)
{
	int top = -1;  //ջ��ָ�룬ָ��ջ��Ԫ��
	int Stack[MAX];
	int size=0;   //ջ��Ԫ�ظ���
	int index=0;
	//��ʼ��������
	Init_Visited(G, visited); 

	//����ͼ�����ж��㣬����ǰ����δ�����ʣ��������������ջ
	for (int i = 0; i < G->verNum; i++)
	{
		if (visited[i] == 0)
		{
			visited[i] = 1;
			Stack[++top] = i;   //��ջ
			size++;
		}

		/*�ǿ�ջ�������ջ��Ԫ�أ�Ȼ�󵯳���ջ��Ԫ�أ���������ջ��Ԫ�ص��ڽӵ㣬
		  ��ջ��Ԫ�ص��ڽӵ�δ�����ʣ��������������ջ           */
		while (size>0)
		{
			index = Stack[top];
			//printf("index:%d", index);
			printf("%s ", G->Vertex[(Stack[top])]);   //����ջ��Ԫ��
			
			top--;  //ջ��Ԫ�س�ջ����Ϊ���滹Ҫ��δ�����ʵ��ڽӵ�ѹջ
			size--;
			//����ջ��Ԫ�ص��ڽӵ�
			for (int j = 0; j < G->verNum; j++)
			{
				//�����ڽӵ㣬�Ҹ��ڽӵ�δ�����ʣ��������������ջ
				if (G->arc[index][j] == 1 && visited[j] == 0)
				{
					visited[j] = 1;
					Stack[++top] = j;
					size++;
					//break;  //û��Ҫbreak
				}
			}
		}//end while
	}//end for
}





//BFS�����������*******************************************************************
void BFS_Travel(AdjMatrix*G, int *visited)
{
	//����˳�����
	int head = 0;
	int rear = 0;
	int Queue[MAX];  //��������
	//int  j, k;

	//��ʼ�������ǣ�ȫ����Ϊδ������
	Init_Visited(G, visited);


	//��ʼ����ͼ�е�ÿ������
	for (int i = 0; i < G->verNum; i++)
	{
		//��ǰ����δ�����ʣ�������������������
		if (visited[i] == 0)
		{
			visited[i] = 1;
			printf("%s ", G->Vertex[i]);
			Queue[rear++] = i;  //���
		}
		//����зǿգ���������������н�㣬�����ǵ��ڽӵ�
		while (head != rear)
		{
			//cur�ǵ�ǰ�Ķ�ͷ���
			int cur = Queue[head++];   //����

			for (int w = FirstAdjVex(G, cur); w >= 0; w = NextAdjVex(G, cur, w))
			{
				//�ڽӵ�wδ�����ʣ�������������������
				if (visited[w] == 0)
				{
					visited[w] = 1;  //����
					printf("%s ", G->Vertex[w]);
					Queue[rear++] = w;  //���

				}
			}
		}// end while
	}//end for

}





int main()
{
	//��������ͼ
	AdjMatrix* DG = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	Create_DG(DG);
	Print_DG(DG);
	printf("\n");

	//DFS���ݹ飩
	int *visited1 = (int *)malloc(sizeof(int)*MAX);   //��ǽ���Ƿ񱻷��ʹ�
	printf("DFS�ݹ飺");
	DFS_Travel(DG, visited1);
	printf("\n");


	//DFS���ǵݹ�-ջ��
	int *visited2 = (int *)malloc(sizeof(int)*MAX);
	printf("DFS�ǵݹ飨ջ����");
	DFS_Stack(DG, visited2);
	printf("\n");


	////BFS
	int *visited3 = (int *)malloc(sizeof(int)*MAX);
	printf("BFS��");
	BFS_Travel(DG, visited3);
	printf("\n");

	free(visited1);
	free(visited2);
	free(visited3);

}
















