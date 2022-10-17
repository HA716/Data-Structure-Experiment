#include<iostream>
using namespace std;

const int MAX = 100; //��󶥵���
const int MAX_NAME = 50;  //�����Ϣ��󳤶�
bool flag_1 = false;  //�����ж��Ƿ�·��C����·��C��˵���ܱ��
bool flag_2 = false;  //�����ж������Ƿ��׳ɹ���������·��C�ҵ����յ�B
//bool flag_3 = false;  //�����ж���cΪ��㣬�ڲ��������c��ǰ����������£��ܷ��ҵ����b��
int visited[MAX];    //��Ƕ����Ƿ��Ѿ�������--��aΪ���
int visited_2[MAX];  //��Ƕ����Ƿ��Ѿ�������--��cΪ���

//�߱�
typedef struct EDGE
{
	int adjvex;
	struct EDGE * next;
}Edge;

//����
typedef struct NODE
{
	char data[MAX_NAME];  //�����Ϣ
	Edge*firstEdge;
}Node;

//�ڽӱ�
typedef struct ADJLIST
{
	Node vertex[MAX]; //��������
	int verNum;       //��ǰ������
	int arcNum;       //��ǰ�ߵ�����
}AdjList;

//����ԭ��
int Located(AdjList*list, char*str);                   //��λ���ver�ڶ�����е�λ��
void CreateGraph(AdjList**list);                       //����ͼ
void PrintGraph(AdjList*list);                         //��ӡ�ڽӱ�
bool DFS_1(AdjList*list, char*a, char*b, char*c);           //��aΪ���,bΪ�յ㣬cΪab·���ϵĵ�
bool DFS_2(AdjList*list, char*c, char*b, int index);   /*�ж��Ƿ�����cΪ��㣬���ܾ���b�������ܾ���index����·����
														 ��Ϊ��index��������c��ͬʱindex��c���ڽӵ㣬����һ������index����ζ�Ż�ȥc��������֧����ķ�֧Ѱ�ң����Ǵ����*/
														 /*����ͼ*/
void CreateGraph(AdjList**list)
{
	int i; //ѭ������
	char* str;

	cout << "������С��(����)������";
	cin >> (*list)->verNum;
	cout << "������С��֮��·��(��)��������";
	cin >> (*list)->arcNum;
	getchar();


	//���������
	cout << "������С��(����)��Ϣ��" << endl;
	for (i = 0; i < (*list)->verNum; i++)
	{
		cout << i + 1 << ":";
		gets_s((*list)->vertex[i].data);
		(*list)->vertex[i].firstEdge = NULL;
	}

	//�����ڽӱ�
	cout << "�����ڽӱ�" << endl;
	for (i = 0; i < (*list)->arcNum; i++)
	{

		char strVer1[MAX_NAME];
		char strVer2[MAX_NAME];
		cout << "���㣺";
		cin >> strVer1;
		cout << "�ڽӵ㣺";
		cin >> strVer2;
		int ver1, ver2;
		ver1 = Located((*list), strVer1);
		ver2 = Located((*list), strVer2);

		//����ͼ

		Edge*adjNode_1 = (Edge*)malloc(sizeof(Edge));  //�ڽӵ�(�߱���)
		adjNode_1->adjvex = ver2;
		//ͷ�巨�����ڽӵ���뵽�߱���
		adjNode_1->next = (*list)->vertex[ver1].firstEdge;
		(*list)->vertex[ver1].firstEdge = adjNode_1;

		Edge*adjNode_2 = (Edge*)malloc(sizeof(Edge));  //�ڽӵ�(�߱���)
		adjNode_2->adjvex = ver1;
		//ͷ�巨�����ڽӵ���뵽�߱���
		adjNode_2->next = (*list)->vertex[ver2].firstEdge;
		(*list)->vertex[ver2].firstEdge = adjNode_2;

	}

}


/*��ӡ�ڽӱ�*/
void PrintGraph(AdjList*list)
{
	if (list == NULL) return;

	cout << "�ڽӱ�" << endl;
	for (int i = 0; i < list->verNum; i++)
	{
		cout << i << "  " << list->vertex[i].data;
		Edge *p = (list->vertex[i].firstEdge);  //pָ���һ���߱���
		while (p)
		{
			cout << "->" << list->vertex[p->adjvex].data;
			p = p->next;
		}
		if (p == NULL)
		{
			cout << "-> NULL";
		}
		cout << endl;
	}
}


/*��λ���ver�ڶ�����е�λ��*/
int Located(AdjList*list, char*str)
{
	int index = -1;
	bool flag = false;
	for (int i = 0; i < list->verNum; i++)
	{
		if (strcmp(list->vertex[i].data, str) == 0)
		{
			index = i;
			flag = true;
			break;
		}
	}
	if (flag == false)
	{
		cout << "�����������������룡" << endl;
	}
	return index;
}


/*�ж��Ƿ�����cΪ��㣬���ܾ���b�������ܾ���index����·��(��ֹ������)*/
bool DFS_2(AdjList*list, char*c, char*b, int index)
{

	int Stack[MAX];  //ջ�е�Ԫ���ǽ���ڶ�����е��±�
	int topNode = 0; //ջ��Ԫ��
	Edge*p;
	int top = -1;  //ջ��ָ��
	int i, j, k;
	int size = 0;  //ջ�Ĵ�С
	int pos_c, pos_b;
	bool flag_3 = false;  //�����ж���cΪ��㣬�ڲ��������c��ǰ����������£��ܷ��ҵ����b��

	pos_c = Located(list, c); //��λ c�ڶ�����е�����
	pos_b = Located(list, b);


	for (i = 0; i < list->verNum; i++)
	{//��ʼ��visited����
		visited_2[i] = 0;
	}

	//�����pos_c��ʼ����
	i = pos_c;
	if (visited_2[i] == 0)
	{//���ö���δ�������������������ջ
		visited_2[i] = 1;
		Stack[++top] = i;
		size++;
	}

	/*��ջ��Ϊ�գ�����ջ��Ԫ�ز������Ȼ����������ڽӵ�*/
	while (size > 0)
	{
		//��ȡջ��Ԫ�� �����䵯��
		topNode = Stack[top--];
		size--;

		if (topNode == index)
		{//���ջ��Ԫ����index,���������������ܱ����ܵ�������֧��ȥ����
			continue;
		}

		if (topNode == pos_b)
		{//�����cΪ�����б����ܵ���b,���ñ�־flag_3=true
			flag_3 = true;
			break;
		}

		//pָ��ջ��Ԫ�صĵ�һ���߱���
		p = list->vertex[topNode].firstEdge;
		while (p)
		{
			if (visited_2[p->adjvex] == 0)
			{//�����ڽӵ㣬�Ҹ��ڽӵ�δ�����ʣ��������������ջ
				visited_2[p->adjvex] = 1;
				Stack[++top] = p->adjvex;
				size++;
			}
			p = p->next;
		}
	}
	return flag_3;
}



//�ǵݹ飨ջ����a����㣬b���յ㣬c��ab·���ϵĵ�
bool DFS_1(AdjList*list, char*a, char*b, char*c)
{
	int Stack[MAX];  //ջ�е�Ԫ���ǽ���ڶ�����е��±�
	int topNode = 0; //ջ��Ԫ��
	Edge*p;
	int top = -1;  //ջ��ָ��
	int i, j, k;
	int size = 0;  //ջ�Ĵ�С
	int pos_a, pos_b, pos_c;
	int index = -1;
	bool flag_3 = false; //�����ж���cΪ��㣬�ڲ��������c��ǰ����������£��ܷ��ҵ����b��



	pos_a = Located(list, a); //��λ a�ڶ�����е�����
	pos_b = Located(list, b);
	pos_c = Located(list, c);

	for (i = 0; i < list->verNum; i++)
	{//��ʼ��visited����
		visited[i] = 0;
	}

	//�����pos_a��ʼ����
	i = pos_a;

	if (visited[i] == 0)
	{//���ö���δ�������������������ջ
		visited[i] = 1;
		Stack[++top] = i;
		size++;
	}

	/*��ջ��Ϊ�գ�����ջ��Ԫ�ز������Ȼ����������ڽӵ�*/
	while (size > 0)
	{
		//��ȡջ��Ԫ�� �����䵯��
		topNode = Stack[top--];
		size--;


		if (topNode == pos_c)
		{//���·������c����ô���Ϊ flag_1=true
			flag_1 = true; //˵�������ߵ�·�߻ᾭ��C�壬��������˵���ܱ�ף���Ϊ����·��Ҫ��ȥ��b���·����
		}


		//pָ��ջ��Ԫ�صĵ�һ���߱���
		p = list->vertex[topNode].firstEdge;

		if (p->adjvex == pos_c)
		{//��¼c��˫�׽��
			if (flag_3 == false)
			{ //һ��flase_3��Ϊtrue�Ͳ��ٽ���DFS����
				index = topNode;
				flag_3 = DFS_2(list, c, b, index);
			}
		}



		while (p)
		{
			if (visited[p->adjvex] == 0)
			{//�����ڽӵ㣬�Ҹ��ڽӵ�δ�����ʣ��������������ջ
				visited[p->adjvex] = 1;
				Stack[++top] = p->adjvex;
				size++;
			}

			if (p->next != NULL)
			{//��¼c��˫�׽��
				if (p->next->adjvex == pos_c)
				{//p�ǿ� �� p���ڽӵ���c�����¼p��λ�ã���ʱp����c��ǰ���ڵ�
					if (flag_3 == false)
					{//һ��flase_3��Ϊtrue�Ͳ��ٽ���DFS����
						index = p->adjvex;  //��¼c��˫�׽��
						flag_3 = DFS_2(list, c, b, index);
					}

				}
			}

			//����Ҫ��������ͬʱ���������flag_2Ϊtrue����ʾ�ܱ�׳ɹ�
			if (flag_3 == true && flag_1 == true && topNode == pos_b)
			{
				flag_2 = true;
				break;
			}
			p = p->next;
		}
	}

	return flag_2;
}


void Test(AdjList*list)
{
	char a[MAX_NAME];
	char b[MAX_NAME];
	char c[MAX_NAME];
	int M;
	cout << "������������M��";
	cin >> M;
	cout << "��ֱ�����A,B,C���ӵı�ţ��ÿո����" << endl;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b >> c;
		bool flag = DFS_1(list, a, b, c);
		if (flag == true) cout << "Yes!" << endl;
		else cout << "No" << endl;
		cout << endl;
		for (int j = 0; j < list->verNum; j++)
		{
			visited[j] = 0;
		}
		flag_2 = false;   //����flag_2
	}

}


int main()
{
	AdjList*list = (AdjList*)malloc(sizeof(AdjList));
	CreateGraph(&list);
	cout << endl;
	PrintGraph(list);
	cout << endl;
	Test(list);   //������������

}

















