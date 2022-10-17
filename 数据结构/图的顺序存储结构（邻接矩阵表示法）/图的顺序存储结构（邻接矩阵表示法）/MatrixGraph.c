#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxSize 100



typedef enum  //ö��ͼ������
{
	DG,  //����ͼ  Direct Graph
	UDG, //����ͼ
	DN,  //������  Direct Network
	UDN  //������
}GraphKind;



//ͼ��˳��洢���ڽӾ����ʾ��
typedef struct MATRIXGRAPH
{
	char * verTex [MaxSize];     //һά�����Ŷ��㣬���������ΪMaxSize
	int arcs[MaxSize][MaxSize];  //�ڽӾ����ŵ�ͱߵĹ�ϵ�����ڽӱ߾ʹ���1��û���ڽӱ߾ʹ���0��������Ϊ��Ȩֵ��
	int verTexNum;               //��¼���������
	int arcsNum;                 //��¼�ߵ��������ڽӱߣ�
	GraphKind graphKind;         //ͼ������
}MatrixGraph;

//Ѱ���ڽӵ�ver��ͼG�е�λ�ã���0��ʼ�ң�
int Locate(MatrixGraph*G, char * ver)
{
	int index = 0;
	while (index < G->verTexNum)
	{
		if (strcmp(G->verTex[index] , ver)==0) //���ҵ����򷵻�λ���±�
		{
			break;
		}
		index++;
	}

	//index == G->verTexNum������ʹ���û���ҵ����򷵻�-1
	return index == G->verTexNum ? -1 : index;

}




//��������ͼ��1���ڽӾ���Գ�  2����i������Ķ���=��i����1�ĸ���
int CreateUDG(MatrixGraph * G)
{
	G->graphKind = UDG;                                    //����ͼ������Ϊ����ͼ  
	printf("%s", "�����붥����");
	scanf_s("%d", &G->verTexNum);
	printf("%s", "���������");
	scanf_s("%d", &G->arcsNum);
	//��ʼ������
	for (int i = 0; i < G->verTexNum; i++)
	{
		G->verTex[i] = (char*)malloc(sizeof(char) * 10);    //��Ϊ��ָ�룬����ҪΪÿ�����㶼����ռ�
		printf("��ʼ�����㣬���������������");
		scanf_s("%s", G->verTex[i],10);

	}

	//��ʼ���ڽӾ���(��������������ǵ��ڶ�����)�����бߵ�Ȩֵ��Ϊ0
	for (int i = 0; i < G->verTexNum; i++)
	{
		for (int j = 0; j < G->verTexNum; j++)
		{
			G->arcs[i][j] = 0;
		}
	}


	//�����ڽӾ���
	for (int k = 0; k < G->arcsNum; k++)  //�ߵ����������ڽӵ�Ķ���
	{
		//ver1��ver2����ʱ��������Ϊ�ڽӵ㣬Ϊ�ڽӵ������ڴ�ռ�
		char * ver1 = (char*)malloc(sizeof(char) * 10);
		char * ver2 = (char*)malloc(sizeof(char) * 10);
		//�����ڽӵ�Ĺ�ϵ
		printf("��������");
		scanf_s("%s", ver1,10);

		printf("�ڽӵ�����");
		scanf_s("%s", ver2,10);
		
		//Ѱ���ڽӵ�ver1��ver2��ͼ�е�λ��
		int x = Locate(G, ver1);
		int y = Locate(G, ver2);

		if (x == -1 || y == -1) //����ʧ��
		{
			return -1;  
		}
		else
		{
			//����ͼ���ڽӾ���Գ�
			G->arcs[x][y] = 1;     //����x��y���������������ڽӵ㣬�����ڽӱ�
			G->arcs[y][x] = 1;

		}

		free(ver1);
		free(ver2);
	}
	return 1;    //�����ɹ�
}



//��������ͼ��1���ڽӾ��󲻶Գ�  2����i����������=��i����1�ĸ���
int CreateDG(MatrixGraph * G)
{
	G->graphKind = DG;                                    //����ͼ������Ϊ����ͼ  
	printf("%s", "�����붥����");
	scanf_s("%d", &G->verTexNum);
	printf("%s", "���������");
	scanf_s("%d", &G->arcsNum);

	for (int i = 0; i < G->verTexNum; i++)
	{
		G->verTex[i] = (char*)malloc(sizeof(char) * 10);    
		printf("��ʼ�����㣬���������������");
		scanf_s("%s", G->verTex[i], 10);

	}

	//�ڽӾ����ʼ��Ϊ�����ޣ���INT_MAX��ʾ
	for (int i = 0; i < G->verTexNum; i++)
	{
		for (int j = 0; j < G->verTexNum; j++)
		{
			G->arcs[i][j] = INT_MAX;    //INT_MAX�����ε����ֵ������Ϊ�������
		}
	}

	for (int k = 0; k < G->arcsNum; k++)  
	{
		char * ver1 = (char*)malloc(sizeof(char) * 10);
		char * ver2 = (char*)malloc(sizeof(char) * 10);
	
		printf("��������");
		scanf_s("%s", ver1, 10);

		printf("�ڽӵ�����");
		scanf_s("%s", ver2, 10);

		int x = Locate(G, ver1);
		int y = Locate(G, ver2);

		if (x == -1 || y == -1)
		{
			return -1;
		}
		else
		{
			//����ͼ���ڽӾ��󲻶Գ�
			G->arcs[x][y] = 1;     //����x��y���������������ڽӵ㣬�����ڽӱ�
		//	G->arcs[y][x] = 1;     //�������ڴˣ�ע�͵���һ�о�������ͼ�������������ͼ����������ͼ������ͼ�����Ψһ����

		}
		free(ver1);
		free(ver2);
	}
	return 1;    //�����ɹ�
}


//������������1���ڽӾ��󲻶Գ�  2��Ȩ��Ĭ��Ϊ�������INT_MAX��ʾ���ڽӱߵ�Ȩ��Ҫ��Ϊ����
int CreateDN(MatrixGraph * G)
{
	G->graphKind = DN;                                    //����ͼ������Ϊ����ͼ  
	printf("%s", "�����붥����");
	scanf_s("%d", &G->verTexNum);
	printf("%s", "���������");
	scanf_s("%d", &G->arcsNum);

	for (int i = 0; i < G->verTexNum; i++)
	{
		G->verTex[i] = (char*)malloc(sizeof(char) * 10);
		printf("��ʼ�����㣬���������������");
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

		printf("��������");
		scanf_s("%s", ver1, 10);

		printf("�ڽӵ�����");
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
			printf("������Ȩ��");
			scanf_s("%d", &value);
			//���������ڽӾ��󲻶Գƣ����ڽӱߵ�Ȩ�ؿ���Ϊ����
			G->arcs[x][y] = value;     //�������ڴˣ�Ҫ���ֶ������value���и�ֵ
		//	G->arcs[y][x] = 1;     //ע�͵���һ�о�������ͼ�������������ͼ����������ͼ������ͼ�����Ψһ����

		}
		free(ver1);
		free(ver2);
	}
	return 1;    //�����ɹ�
}

int main()
{
	MatrixGraph * G=(MatrixGraph *)malloc(sizeof(MatrixGraph ));
	int ret = CreateUDG(G);     //ret��������ͼ�����Ľ�����ɹ���ʧ�ܣ�
	if (ret == -1)
	{
		printf("����ͼ����ʧ��");
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
				if (G->arcs[i][j] == INT_MAX)      //��ӡ�����ڽӾ���ʱ����INT_MAX�������ӡ�ɡޱ��ڹ۲�
				{
					printf("\t%��");
				}
				printf("\t%d", G->arcs[i][j]);
			}
			
		}

	}

}




