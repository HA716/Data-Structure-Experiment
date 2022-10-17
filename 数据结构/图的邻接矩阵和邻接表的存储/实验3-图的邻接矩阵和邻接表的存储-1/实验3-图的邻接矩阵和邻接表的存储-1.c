#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#pragma warning (disable:4996)

#define MAX 100
#define NAME_SIZE 10

//ö��ͼ������
typedef enum GRAPHKIND
{
	DG,   //����ͼ 0
	UDG,  //����ͼ 1
	DN,   //������ 2
	UDN   //������ 3
}GraphKind;


//����ͼ ��Ȩ �ڽӾ��� �ڽӱ�

//�ڽӾ���********************************************************
typedef struct ADJMATRIX
{
	char *verTex[MAX]; //�������� 
	int arc[MAX][MAX]; //�ڽӾ���
	int verNum; //��¼���������
	int arcNum; //��¼�ߵ�����
	GraphKind kind; //ͼ������
}AdjMatrix;

//*******************************************************************
//�߱�
typedef struct ARCLIST
{
	int adjvex;               //�ڽӵ�����
	struct ARCLIST * next;    //���ӱ߱��ָ��
	int weight;               //�ߵ�Ȩ��:�Ӷ��㵽�ñ߱���ıߵ�Ȩ��
}ArcNode; //����Node�ڵ�����ڽڵ���Ϣ

//�����
typedef struct VEXLIST
{
	char data[NAME_SIZE];   //������
	ArcNode * firstArc;     //�ɶ���ָ���һ���ڽӵ�ı�
}VexNode;  //���涥����Ϣ

//�ڽӱ�
typedef struct ADJLIST
{
	VexNode verTex[MAX];  //��������
	int verNum;           //��ǰ������� 
	int arcNum;           //��ǰ�ߵ�����
	GraphKind kind;       //ͼ������
}AdjList;

//*********************************************************************



//��λ ������ڽӵ� �ڶ��������е������±�
int Located(AdjMatrix*G,char * ver)
{
	if (G == NULL) return;
	int index = -1;
	
	for (int i = 0; i < G->verNum; i++)
	{
		//��Ȳŷ���0
		if (strcmp(G->verTex[i], ver) == 0)
		{
			index = i;
			break;
		}
	}
	return index; //�ҵ��ͷ�����ʵ�±�index���Ҳ����ͷ���-1
}


//�ڽӱ��Located
int Located_List(AdjList*G, char *ver)
{
	if (G == NULL) return;
	int index = -1;
	for (int i = 0; i < G->verNum; i++)
	{
		             //          ������
		if (strcmp(G->verTex[i].data, ver) == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}





//����ͼ���ڽӱ�*************************************************************
void Create_UDG_list(AdjList* G)
{
	G->kind = UDG;
	printf("�����붥������");
	scanf_s("%d", &G->verNum);
	getchar();
	printf("������ߵ�������");
	scanf_s("%d", &G->arcNum);
	getchar();
	
	//��ʼ�������
	printf("��ʼ������������������������\n");
	for (int i = 0; i < G->verNum; i++)
	{
		printf("%d��", i + 1);
		scanf_s("%s", G->verTex[i].data, NAME_SIZE);
		getchar();
		G->verTex[i].firstArc = NULL;  //��
	}


	printf("�����ڽӱ�\n");
	for(int k=0;k<G->arcNum;k++)
	{
		char * ver1 = (char *)malloc(sizeof(char)*NAME_SIZE);
		char * ver2 = (char *)malloc(sizeof(char)*NAME_SIZE);
		printf("���㣺");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("�ڽӵ㣺");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();

		int i = Located_List(G, ver1);
		int j = Located_List(G, ver2);
		if (i == -1 || j == -1) return;

		else
		{
			//��������ͼ�ı߱��㣨����ͼ�ǶԳƵģ�
		    //i�����㣬j���ڽӵ�
			ArcNode*arcNode1 = (ArcNode*)malloc(sizeof(ArcNode));
			arcNode1->adjvex = j;
			arcNode1->next = G->verTex[i].firstArc;
			G->verTex[i].firstArc = arcNode1;

			//j�����㣬i���ڽӵ�
			ArcNode*arcNode2 = (ArcNode*)malloc(sizeof(ArcNode));
			arcNode2->adjvex = i;
			arcNode2->next = G->verTex[j].firstArc;
			G->verTex[j].firstArc = arcNode2;

		}//end else
		
		free(ver1);
		free(ver2);
		
	}//end for

}


//���������ڽӱ�*******************************************************
void Create_DN_list(AdjList* G)
{
	G->kind = DN;
	printf("�����붥������");
	scanf_s("%d", &G->verNum);
	getchar();
	printf("������ߵ�������");
	scanf_s("%d", &G->arcNum);
	getchar();

	//��ʼ�������
	printf("��ʼ������������������������\n");
	for (int i = 0; i < G->verNum; i++)
	{
		printf("%d��", i + 1);
		scanf_s("%s", G->verTex[i].data, NAME_SIZE);
		getchar();
		G->verTex[i].firstArc = NULL;  //��
	}


	//�����ڽӱ�
	int weight;
	printf("�����ڽӱ�\n");
	for (int k = 0; k < G->arcNum; k++)
	{
		char * ver1 = (char *)malloc(sizeof(char)*NAME_SIZE);
		char * ver2 = (char *)malloc(sizeof(char)*NAME_SIZE);
		printf("���㣺");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("�ڽӵ㣺");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();
		printf("ȨֵΪ��");
		scanf_s("%d", &weight);
		getchar();

		int i = Located_List(G, ver1);  //����
		int j = Located_List(G, ver2);  //�ڽӵ�
		if (i == -1 || j == -1) return;

		else
		{
			//�����������ı߱���
			//i�����㣬j���ڽӵ�
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






//��ӡ�ڽӱ�
void Print_List(AdjList*G)
{
	if (G == NULL) return;

	for (int i = 0; i < G->verNum; i++)
	{
		printf("%s �� %d", G->verTex[i].data, i);
		//�߱�Ϊ��
		if (G->verTex[i].firstArc != NULL)
		{
			//temp�Ǳ߱���
			ArcNode*temp = G->verTex[i].firstArc;
			while (temp != NULL)
			{
				//��������������������Ҫ��ӡ Ȩֵ������
				if (G->kind == DN || G->kind == UDN)
				{
					printf("-> %d(%d) ", temp->adjvex, temp->weight);
					temp = temp->next;
				}
				//����ͼ��������ͼֻ��Ҫ��ӡ�����������ӡȨֵ
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


//�����ڽӱ�
void Destory_list(ArcNode*arcNode)
{
	if (arcNode == NULL)
	{
		return;
	}
	Destory_list(arcNode->next);
	free(arcNode);
}





//����ͼ���ڽӾ���************************************************************************
void Create_UDG(AdjMatrix*G)
{
	G->kind = UDG;      //����ͼ������ΪUDG
	int verNum, arcNum;
	printf("�����붥������");
	scanf_s("%d", &verNum);
	printf("������ߵ�������");
	scanf_s("%d", &arcNum);
	G->verNum = verNum;
	G->arcNum = arcNum;
	//��ʼ��������Ϣ
	printf("��ʼ�����㣬�����������������\n");
	for (int i = 0; i < G->verNum; i++)
	{
		G->verTex[i] = (char*)malloc(sizeof(char) * NAME_SIZE);
		printf("%d:", i + 1);
		scanf_s("%s", G->verTex[i], NAME_SIZE);
	}
	
	//printf("�㣺%d", verNum);
	//printf("\n��%d\n", arcNum);
	//for (int i = 0; i < UDG->verNum; i++)
	//{
	//	printf("%s ", UDG->verTex[i]);
	//}

	//��ʼ���ڽӾ���
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			G->arc[i][j] = 0;
		}
	}

	//��������ͼ
	printf("�����ڽӾ���\n");
	for (int k = 0; k < G->arcNum; k++)
	{
		char *ver1 = (char*)malloc(sizeof(char) * NAME_SIZE); //����
		char *ver2 = (char*)malloc(sizeof(char) * NAME_SIZE); //�ڽӵ�
		printf("���㣺");
		scanf_s("%s", ver1, NAME_SIZE);
		getchar();
		printf("�ڽӵ㣺");
		scanf_s("%s", ver2, NAME_SIZE);
		getchar();
		//��λ ������ڽӵ� �ڶ��������е������±�
		int i = Located(G, ver1);
		int j = Located(G, ver2);
		//printf("i:%d", i);
		//printf("j:%d", j);
		if (i == -1 || j == -1)
		{//����ʧ��
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


//���������ڽӾ���*************************************************************************
void Create_DN(AdjMatrix*G)
{
	G->kind = DN;  //������
	int verNum;
	int arcNum;
	printf("�����붥������");
	scanf_s("%d", &verNum);\
	getchar();
	printf("�����뻡��������");
	scanf_s("%d", &arcNum);
	getchar();
	G->verNum = verNum;
	G->arcNum = arcNum;

	//��ʼ��������
	printf("��ʼ�����㣬�����������������\n");
	for (int i = 0; i < G->verNum; i++)
	{
		printf("%d��", i + 1);
		G->verTex[i] = (char*)malloc(sizeof(char)*NAME_SIZE);
		scanf_s("%s", G->verTex[i], NAME_SIZE);
	}

	//��ʼ�����������ڽӾ���Ϊ��
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			G->arc[i][j] = INT_MAX;   // ��
		}
	}

	//�����ڽӾ���
	printf("�����ڽӾ���\n");
	for (int k = 0; k < G->arcNum; k++)
	{
		int weight;
		char*ver1 = (char*)malloc(sizeof(char)*NAME_SIZE);
		char*ver2 = (char*)malloc(sizeof(char)*NAME_SIZE);
		printf("���㣺");
		scanf_s("%s", ver1, NAME_SIZE);
		printf("�ڽӵ㣺");
		scanf_s("%s", ver2, NAME_SIZE);

		//��λ������ڽӵ��ڶ��������е�λ��
		int i = Located(G, ver1);
		int j = Located(G, ver2);

		if (i == -1 || j == -1)  return;
		else
		{
			printf("�����뻡��Ȩֵ��");
			scanf_s("%d", &weight);
			getchar();
			G->arc[i][j] = weight;
		}

		free(ver1);
		free(ver2);
	}

}

//��ӡ������
void Print_DG(AdjMatrix*G)
{
	if (G == NULL) return;
	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			if (G->arc[i][j] == INT_MAX)
			{
				printf("�� ");
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
	//����ͼ���ڽӾ���
	printf("��������ͼ���ڽӾ���\n");
	AdjMatrix*UDG = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	Create_UDG(UDG);
	printf("UDG�ڽӾ���Ϊ��\n");
	Print_UDG(UDG);
	printf("\n***************************************\n");

	//���������ڽӾ���
	printf("�������������ڽӾ���\n");
	AdjMatrix*DN = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	Create_DN(DN);
	printf("DN�ڽӾ���Ϊ��\n");
	Print_DG(DN);
	printf("\n***************************************\n");

	//����ͼ���ڽӱ�
	printf("��������ͼ���ڽӱ�\n");
	AdjList*UDG_list = (AdjList*)malloc(sizeof(AdjList));
	Create_UDG_list(UDG_list);
	printf("UDG���ڽӱ�\n");
	Print_List(UDG_list);
	printf("\n***************************************\n");

	//���������ڽӱ�
	printf("�������������ڽӱ�\n");
	AdjList*DN_list = (AdjList*)malloc(sizeof(AdjList));
	Create_DN_list(DN_list);
	printf("DN���ڽӱ�\n");
	Print_List(DN_list);
	printf("\n***************************************\n");

	//��������ͼ���ڽӱ�
	for (int i = 0; i < UDG_list->verNum; i++)
	{
		ArcNode*p = UDG_list->verTex[i].firstArc;
		Destory_list(p);
	}
	printf("\n�ɹ�����UDG\n");

	//�������������ڽӱ�
	for (int i = 0; i < DN_list->verNum; i++)
	{
		ArcNode*p = DN_list->verTex[i].firstArc;
		Destory_list(p);
	}
	printf("\n�ɹ�����DN\n");

}




















