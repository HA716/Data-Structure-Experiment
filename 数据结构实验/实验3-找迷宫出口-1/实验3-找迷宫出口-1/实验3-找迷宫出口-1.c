#include<stdio.h>
#include<stdlib.h>

#define MAX 100
#define M 6   //����
#define N 6     //����
#define MaxSize    100     //ջ���Ԫ�ظ���

//�߱���
typedef struct ARCNODE
{
	int adjVex;
	int weight;
	struct ARCNODE*next;
}ArcNode;

//����
typedef struct NODE
{
	char data;
	ArcNode*firstArc;
}Node;

//�ڽӱ�
typedef struct ADJLIST
{
	Node vex[MAX];  //��������
	int verNum;
	int arcNum;
}AdjList;


int mg[M + 2][N + 2] = 
{      //һ���Թ���������Ҫ���Ͼ�Ϊ1�����
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
	int i;      //·��������
	int j;      //·��������
	int di;     //����
}Stack[MaxSize], Path[MaxSize];      //����ջ�ʹ�����·��������

int top = -1;     //ջ��ָ��
int count = 1;    //·��������
int minlen = MaxSize;     //���·������

void DFS() {      //·��Ϊ:(1,1)->(M,N)
	int i, j, di, find, k;
	top++; Stack[top].i = 1; Stack[top].j = 1; Stack[top].di = -1;
	mg[1][1] = -1;        //��ʼ����ջ
	while (top > -1) {      //ջ����ʱѭ��
		i = Stack[top].i; j = Stack[top].j; di = Stack[top].di;
		if (i == M && j == N) {       //�ҵ��˳��ڣ����·��
			printf("M: %d ", count++);
			for (k = 0; k <= top; k++) {
				printf("(%d,%d)  ", Stack[k].i, Stack[k].j);
				if ((k + 1) % 5 == 0)      //���ʱÿ5����㻻һ��
					printf("\n\t");
			}
			printf("\n");
			if (top + 1 < minlen) {       //�Ƚ�������·��
				for (k = 0; k <= top; k++)
					Path[k] = Stack[k];
				minlen = top + 1;
			}
			mg[Stack[top].i][Stack[top].j] = 0;   //�ø�λ�ñ�Ϊ����·���Ŀ��߽��
			top--;
			i = Stack[top].i; j = Stack[top].j; di = Stack[top].di;
		}
		find = 0;
		while (di < 4 && find == 0) {     //����һ�����߽��
			di++;
			switch (di) {
			case 0:i = Stack[top].i - 1; j = Stack[top].j; break;   //����
			case 1:i = Stack[top].i; j = Stack[top].j + 1; break;   //�ұ�
			case 2:i = Stack[top].i + 1; j = Stack[top].j; break;   //����
			case 3:i = Stack[top].i; j = Stack[top].j - 1; break;   //���
			}
			if (mg[i][j] == 0) //��Ǹõ�Ϊ�����ߵĵ�
				find = 1;
		}
		if (find == 1) {      //�ҵ�����һ�����߽��
			Stack[top].di = di;   //�޸�ԭջ��Ԫ�ص�diֵ
			top++;      //��һ�����߽���ջ
			Stack[top].i = i;
			Stack[top].j = j;
			Stack[top].di = -1;
			mg[i][j] = -1;        //�����ظ��ߵ��ý��
		}
		else {
			mg[Stack[top].i][Stack[top].j] = 0;   //�ø�λ�ñ�Ϊ����·���Ŀ��߽��
			top--;
		}
	}
	printf("���·������:\n");
	printf("����:  %d\n", minlen);
	printf("·��:  ");
	for (k = 0; k < minlen; k++) {
		printf("(%d,%d)  ", Path[k].i, Path[k].j);
		if ((k + 1) % 5 == 0)      //���ʱÿ5����㻻һ��
			printf("\n\t");
	}
	printf("\n");
}

//�����ڽӱ�
void Create_AdjList(AdjList *G, int AdjMatrix[MAX][MAX], int verNum, int arcNum)
{
	ArcNode*p;
	G->verNum = verNum;
	G->arcNum = arcNum;
	//printf("�����붥����:");
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
			//���ڱ�
			if (AdjMatrix[i][j] != 0)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->adjVex = j;
				p->weight = AdjMatrix[i][j];
				p->next = G->vex[i].firstArc;  //ͷ��
				G->vex[i].firstArc = p;
			}
		}
	}
}


//����ڽӱ�
void Print_AdjList(AdjList*G)
{
	ArcNode*p;
	for (int i = 0; i < G->verNum; i++)
	{
		p = G->vex[i].firstArc;
		//printf("���� %c�� %d", G->vex[i].data,i);
		printf("%d  ", i);

		while (p != NULL)
		{
			printf("->%d", p->adjVex);
			p = p->next;
		}
		printf("->��\n");

	}

}

int main() {
	AdjList*G = (AdjList*)malloc(sizeof(AdjList));

	Create_AdjList(G, mg_AdjMatrix, 6, 6);
	printf("�ڽӱ�\n");
	Print_AdjList(G);
	printf("\n�Թ�����·������:\n");
	DFS();
	return 0;
}