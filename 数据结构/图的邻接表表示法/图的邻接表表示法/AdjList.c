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



//����߱��߱�ڵ������ɴ洢�ߵ��յ��ڶ�����е��±���������ָ����һ���ڵ��ָ�������
typedef struct ARCNODE
{
	int AdjVex;                 //�߱��н����±�����(Ҳ���Ǳߵ��յ��λ��)
	struct ARCNODE* nextArc;    //��ָ�룺ָ��ǰ������һ����
	int weight;                 //Ȩ��

	struct ARCNODE* nextOut;    //����ͼ�ĳ��ߣ��������� �ڽӱ�
	struct ARCNODE* nextIn;     //����ͼ����ߣ��������� ���ڽӱ�
	
}ArcNode;

//���춥���:�����ڵ��ɴ洢���ݵ�������ʹ洢�߱�ͷ����ָ���������
typedef struct VERLIST
{
	char * verTex;           //������
	ArcNode * firstArc;      //�߱��ͷָ��

	ArcNode * firstOut;
	ArcNode * firstIn;

}VerList[maxSize];

//���ڽӱ�ʵ��ͼ�ṹ
typedef struct ADJGRAPH
{
	VerList ArrVerTex;   //��������:Ԫ���ǽ��
	int vexNum;       //��������
	int arcNum;       //��/��������
	GraphKind graphKind;   //ͼ������

}AdjGraph;


//Ѱ�ҽ�����ڽӱ��е�λ��
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
	return index;       //û�ҵ��ͷ���-1
}




//���ڽӱ�������ͼ
int CreateUDG(AdjGraph * G)
{
	G->graphKind = UDG;   //����ͼ������Ϊ����ͼ
	printf("�����붥������");
	scanf_s("%d", &G->vexNum);
	printf("������ߵ�����");
	scanf_s("%d", &G->arcNum);
	//��ʼ��������Ϣ
	for (int i = 0; i < G->vexNum; i++)
	{
		G->ArrVerTex[i].verTex = (char *) malloc(sizeof(char) * 10);
		printf("����%d:", i + 1);
		scanf_s("%s", G->ArrVerTex[i].verTex,10);
		//��ʼ���ڽӱ��ѱ߱��ÿ�
		G->ArrVerTex[i].firstArc = NULL;
	}

	//���붥����ڽӵ���Ϣ
	for (int i = 0; i < G->arcNum; i++)   //�ߵ������ʹ�������ڽӵ��ж��ٶ�
	{
		char * ver1 = (char*)malloc(sizeof(char) * 10);
		char * ver2 = (char*)malloc(sizeof(char) * 10);
		printf("���㣺");
		scanf_s("%s", ver1,10);
		printf("�ڽӵ㣺");
		scanf_s("%s", ver2,10);
		int x = Locate(G, ver1);             //Ѱ��ver1�ڶ�����е�λ���±�
		int y = Locate(G, ver2);
		while (x == -1 || y == -1)  //û�ҵ���������ʧ��
		{
			free(ver1);
			free(ver2);
			return -1;       
		}

		//����ͼ�ṹ
		//�����ɽ��yָ����x�ı�
		ArcNode*arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		arcNode->AdjVex = x;                                //�߱����±긳ֵΪx
		arcNode->nextArc = G->ArrVerTex[y].firstArc;        //G->ArrVerTex[y].firstArc����ʼ��ΪNULL
		G->ArrVerTex[y].firstArc = arcNode;    
 		arcNode->weight = 1;                                //�бߵĵط�Ȩ����Ϊ1

		//����ͼ�ǶԳƵ�
		//�����ɽ��xָ����y�ı�
		arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		arcNode->AdjVex = y;                                //�߱����±긳ֵΪx
		arcNode->nextArc = G->ArrVerTex[x].firstArc;        //G->ArrVerTex[y].firstArc����ʼ��ΪNULL
		G->ArrVerTex[x].firstArc = arcNode;
		arcNode->weight = 1;

		free(ver1);
		free(ver2);
	}
	return 1;

}

//����ͼ
int CreateDG(AdjGraph * G)
{
	G->graphKind = DG;   //����ͼ������Ϊ����ͼ
	printf("�����붥������");
	scanf_s("%d", &G->vexNum);
	printf("������ߵ�����");
	scanf_s("%d", &G->arcNum);
	//��ʼ��������Ϣ
	for (int i = 0; i < G->vexNum; i++)
	{
		G->ArrVerTex[i].verTex = (char *)malloc(sizeof(char) * 10);
		printf("����%d:", i + 1);
		scanf_s("%s", G->ArrVerTex[i].verTex, 10);
		//��ʼ���ڽӱ��ѱ߱��ÿ�
		G->ArrVerTex[i].firstArc = NULL;
	}

	//���붥����ڽӵ���Ϣ
	for (int i = 0; i < G->arcNum; i++)   //�ߵ������ʹ�������ڽӵ��ж��ٶ�
	{
		char * ver1 = (char*)malloc(sizeof(char) * 10);
		char * ver2 = (char*)malloc(sizeof(char) * 10);
		printf("���㣺");
		scanf_s("%s", ver1, 10);
		printf("�ڽӵ㣺");
		scanf_s("%s", ver2, 10);
		int x = Locate(G, ver1);             //Ѱ��ver1�ڶ�����е�λ���±�
		int y = Locate(G, ver2);
		while (x == -1 || y == -1)  //û�ҵ���������ʧ��
		{
			free(ver1);
			free(ver2);
			return -1;
		}

		//��������ͼ�ṹ
		//�����ɽ��xָ����y�ı�,�� ���߱�
		ArcNode*arcNode1 = (ArcNode*)malloc(sizeof(ArcNode));
		arcNode1->AdjVex = y;                                //�߱����±긳ֵΪx
		arcNode1->nextOut = G->ArrVerTex[x].firstOut;        //G->ArrVerTex[y].firstArc����ʼ��ΪNULL
		G->ArrVerTex[x].firstOut = arcNode1;
		arcNode1->weight = 1;

		//�����ɽ��yָ����x�ı�,�� ��߱�
		ArcNode*arcNode2 = (ArcNode*)malloc(sizeof(ArcNode));
		//arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		arcNode2->AdjVex = x;                                //�߱����±긳ֵΪx
		arcNode2->nextIn = G->ArrVerTex[y].firstIn;        //G->ArrVerTex[y].firstArc����ʼ��ΪNULL
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
		printf("����ʧ��");
		return;
	}
	else
	{
		//�����ʽ
		for (int i = 0; i < G1->vexNum; i++)
		{
			printf("%s", G1->ArrVerTex[i].verTex);
			ArcNode * arcNode = G1->ArrVerTex[i].firstArc;      //����ָ�� ָ�� �߱�ͷ�ڵ�
			while (arcNode != NULL)
			{
				printf(" -> %d", arcNode->AdjVex);
				arcNode = arcNode->nextArc;                   //�߱������һ�����
			}
			printf("\n");
		}
	}
}

void TestDG()
{
	AdjGraph* G2 = (AdjGraph*)malloc(sizeof(AdjGraph));
	int ret = CreateDG(G2);

	
	��ӡ�ڽӱ�
	for (int i = 0; i < G2->vexNum; i++)
	{
		ArcNode* arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		//printf("%s", G2->ArrVerTex[i]);
	    arcNode = G2->ArrVerTex[i].firstOut;  //������ͷָ�� ָ�� �߱��ͷ�ڵ�
	
		printf("����%s",G2->ArrVerTex[i].verTex);
		while (arcNode)
		{
			printf("->%d", arcNode->AdjVex);         // arcNode->AdjVex�Ǳ߱�ڵ���±�����ֵ
			arcNode = arcNode->nextOut;              //nextOutָ���� ���߱��
		}
		printf("\n");

	}

	//��ӡ���ڽӱ�
	for (int i = 0; i < G2->vexNum; i++)
	{
		ArcNode* arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		printf("����%s", G2->ArrVerTex[i].verTex);
	    arcNode = G2->ArrVerTex[i].firstIn;  //������ͷָ�� ָ�� �߱��ͷ�ڵ�
		while (arcNode != NULL)
		{
			printf("%d<-", arcNode->AdjVex);         // arcNode->AdjVex�Ǳ߱�ڵ���±�����ֵ
			arcNode = arcNode->nextIn;              //nextOutָ���� ���߱��
		}
		printf("\n");

	}
}



//������������ͼ�Ļ����ϼ���Ȩֵ
int CreateDN()
{



}




int main()
{
	//TestUDG();
	  TestDG();
}





