#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int visited[MAX];
//�ڽӱ�
typedef struct ARCNODE
{
	int adjVex;  //�ڽӵ�
	int weight;
	struct ARCNODE *next;
}ArcNode;

//�����
typedef struct NODE
{
	char data;
	ArcNode*firstArc;  
}Node;

//�ڽӱ�
typedef struct ADJLIST
{
	Node vex[MAX];   //��������
	int verNum;
	int arcNum;
}AdjList;


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
		printf("%d  ",i);

		while (p != NULL)
		{
			printf("->%d", p->adjVex);
			p = p->next;
		}
		printf("->��\n");

	}

}


//�������м�·��:��Ϊ�ݹ麯����if�����жϣ����Բ���Ҫ����return����������if��ʱ��ͻ�ִ�������������壬Ȼ��һ��㷵��
void Allpath_1(AdjList*G, int start, int end, int path[],int curLen)
{
	ArcNode*p;
	int adjvex;
	curLen++;
	path[curLen] = start;  //�����start��ӵ�·��path��
	visited[start] = 1;   //���Ϊ�ѷ���
	//�ҵ��յ�
	if (start == end) 
	{
		for (int i = 0; i <= curLen; i++)
		{
			printf("%d ", path[i]);
		}
		printf("\n");
	}
	
	p = G->vex[start].firstArc; //start�ĵ�һ���ڽӵ�
	while (p != NULL)
	{
		adjvex = p->adjVex;
		if (visited[adjvex] == 0)
		{//������ڽӵ�δ�����ʣ�������Ϊ�������ݹ飬ֱ������ڽӵ����յ�
			Allpath_1(G, adjvex, end, path, curLen);
		}

		p = p->next;

	}
	visited[start] = 0;     //��ΪҪ��������·�������Բ�����һ��·��֮���ں����ع��ʱ���Ҫ������Щ���㣬������һ�β���·��
}



//����ָ�����ȵ�·��
void AllPath_2(AdjList*G, int start, int end, int len, int path[], int curLen)
{
	ArcNode*p;
	int adjVex;
	visited[start] = 1;
	path[++curLen] = start;
	
	//���ж�������ͬ
	if (start == end && (curLen+1) == len)  //curLenʵ�������±�����������Ҫ��1���ǳ���
	{
		for (int i = 0; i <= curLen; i++)
		{
			printf("%d ", path[i]);
		}
		printf("\n");
	}

	p = G->vex[start].firstArc;
	while (p != NULL)
	{
		adjVex = p->adjVex;
		if (visited[adjVex] == 0)
		{
			AllPath_2(G, adjVex, end, len, path, curLen);
		}
		p = p->next;
	}

	visited[start] = 0;
}


//��ȡͼG�б�<start,end>��Ȩ�أ�����start��end������ͨ�ģ��򷵻������
int GetWeight(AdjList*G, int start, int end)
{
	ArcNode*p = G->vex[start].firstArc;
	while(p != NULL)
	{
		if (p->adjVex == end)
		{
			return p->weight;
	   }
		p = p->next;  //��������start�ı߱�(���������ڽӵ�)��ֱ���ҵ������ڽӵ�end
	}
	return INT_MAX;
}



/*Dijkstra�㷨��ȡ���·����
  ����S����������·�����յ㼯�ϣ���ʼֻ�����v0��
  ����V-S����δ������·���Ķ��㼯��
  dist[i]:��¼�Ӷ���start������i�ĵ�ǰ���·������
  path[i]:��¼"���start"��"�յ�i"�����·����������ȫ�������У�λ��"�յ�i"֮ǰ���Ǹ����㡣
  s[i]:��Ƕ���i�Ƿ��ڼ���S�У���s[i]=1���������������뵽����S��
*/
void Dijkstra(AdjList*G, int dist[], int path[], int start)
{
	int S[MAX];
	float weight;    //һ��Ҫ��float��
	int min;
	int pos;
	//��ʼ������
	for (int i = 0; i < G->verNum; i++)
	{
		S[i] = 0;  //��ʼ�� ����S��û��Ԫ�أ�������i�����·����û��ȡ��
		path[i] = -1;  //��ʼ��ͼ�����ж���û��ǰ�����
		dist[i] = INT_MAX;  //��ʼ��start��ͼ������һ��û�б�
	}

	ArcNode*p = G->vex[start].firstArc;
	while (p != NULL)
	{
		dist[p->adjVex] = p->weight;
		path[p->adjVex] = start;
		p = p->next;  //��������start�ı߱�(���������ڽӵ�)
	}
	path[start] = -1;  
	S[start] = 1;      //�����start���뵽����S��
	dist[start] = 0;   //start���������·������Ϊ0

	for (int i = 0; i < G->verNum - 1; i++)
	{
		min = INT_MAX;
		for (int j = 0; j < G->verNum; j++)
		{
			//�ҵ���start������V-S�еĵ�����·��
			if (S[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				pos = j;
			}
		}
		S[pos] = 1;

		//�����ڼ���S�м������¶���pos,������Ҫ������ǰ���·����ǰ������
		for (int k = 0; k < G->verNum; k++)
		{
			//pos�Ǽ���S���¼���ĵ㣬��ȡ��pos��V-S�����ж����·�����ȣ�ͨ���Ƚ��ж��Ƿ���Ҫ����
			weight = GetWeight(G, pos, k);
			//����int weight, ��weight = INT_MAXʱ��dist[pos] + weight���ܻ����,����Ҫfloat�͵�weight
			if (S[k] == 0 && dist[pos] + weight < dist[k])
			{//<start,pos> + <pos,k> < <start,k>
				dist[k] = dist[pos] + weight;
				path[k] = pos;
			}
		}
	}
}




//������·��
void Print_ShortPath(int path[], int end)
{
	if (path[end] == -1)
	{
		printf("%d ", end);
	}
	else
	{
		Print_ShortPath(path, path[end]);
		printf("%d ", end);
	}
}


//�����ڽӱ�
void Destroy(AdjList *G)
{
	ArcNode *pre, *p;

	for (int i = 0; i < G->verNum; i++)
	{
		pre = G->vex[i].firstArc;                   //preָ���i����������׽��
		if (pre != NULL)
		{
			p = pre->next;
			while (p != NULL)                            //�ͷŵ�i������������б߽��
			{
				free(pre);
				pre = p;
				p = p->next;
			}
			free(pre);
		}
	}
	free(G);                                            //�ͷ�ͷ�������
}


void main()
{
	//ͼ���ڽӾ���
	int AdjMatrix[MAX][MAX] = {
	{0, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 1},
	{0, 0, 1, 0, 0, 1},
	{0, 0, 0, 1, 0, 0},
	{1, 1, 0, 1, 1, 0}
	};
	int verNum = 6;  //������
	int arcNum = 12; //����
	int start;
	int end;
	int len;

	AdjList*G = (AdjList*)malloc(sizeof(AdjList));
	Create_AdjList(G, AdjMatrix, verNum, arcNum);
	printf("ͼG���ڽӱ�:\n");
	Print_AdjList(G);

	//��1��	�������ͼG�Ӷ���5������2�����м�·����
	int path[MAX];    //��¼��㵽�յ��·��
	printf("\n�������·������㣺");
	scanf_s("%d", &start);
	getchar();
	printf("�������·�����յ㣺");
	scanf_s("%d",&end);
	getchar();
	Allpath_1(G, start, end, path, -1);

	//��2��	�������ͼG�Ӷ���5������2�����г���Ϊ3�ļ�·����
	printf("\n�������·������㣺");
	scanf_s("%d", &start);
	getchar();
	printf("�������·�����յ㣺");
	scanf_s("%d", &end);
	getchar();
	printf("�������·���ĳ��ȣ�");
	scanf_s("%d", &len);
	getchar();
	AllPath_2(G, start, end, len, path, -1);

	//��3��	�������ͼG�Ӷ���5������2�����·��
	char dist[MAX];
	printf("\n���������·������㣺");
	scanf_s("%d", &start);
	getchar();
	printf("���������·�����յ㣺");
	scanf_s("%d", &end);
	getchar();
	Dijkstra(G, dist, path, start);
	printf("���·��Ϊ��");
	Print_ShortPath(path, end);
	printf("\n");

	Destroy(G);
	printf("�ɹ�����");
}








