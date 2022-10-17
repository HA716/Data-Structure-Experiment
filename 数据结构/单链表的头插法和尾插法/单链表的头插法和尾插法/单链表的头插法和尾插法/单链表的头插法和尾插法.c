#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
typedef struct LINKNODE
{
	int data;
	struct LINKNODE*next;
}LinkNode;

typedef struct LINKLIST
{
	int size;
	LinkNode node;   //������
}LinkList;

LinkList * Init()
{
	LinkList * list;
	list = (LinkList*)malloc(sizeof(LinkList));
	list->node.next = NULL;          //��Ԫ���ΪNULL
	list->size = 0;

	return list;
}

//β�巨
//list����ͷ���node��ͷָ��
LinkList*Rear_Insert(LinkList * list)
{
	LinkNode * Rear;      //βָ��
	Rear = &(list->node);    //��ʼ��βָ�룺ָ��ͷ���
	LinkNode * newNode;
	int index = 1;
	int x;
	printf("��%d������", index);
	scanf("%d", &x);
	while (x != -1)         //����-1����ֹͣ����
	{

		//�����½��
		newNode = (LinkNode*)malloc(sizeof(LinkNode));
		newNode->data = x;
		newNode->next = NULL;
		Rear->next = newNode;   //�������һ�������½��
		Rear = newNode;         //βָ��ʼ��ָ����������һ�����
		list->size++;           //����������
		index++;
		printf("��%d������", index);
		scanf("%d", &x);
	}
	Rear->next = NULL;          //���һ�����һ��Ҫָ��NULL�������

	return list;
}

//ͷ�巨
LinkList * Head_Insert(LinkList*list)
{
	LinkNode * newNode;
	int index = 1;
	int x;
	printf("��%d������", index);
	scanf("%d", &x);
	while (x != -1)
	{
		newNode = (LinkNode*)malloc(sizeof(LinkNode));
		newNode->data = x;
		//�����½��
		newNode->next = list->node.next;       //����ĵ�һ���½���next=list->node.next����ʱ��Ч��next=NULL
		list->node.next = newNode;

		list->size++;           //����������
		index++;
		printf("��%d������", index);
		scanf("%d", &x);
	}

	return list;
}

void Print(LinkList*list)
{
	LinkNode * first = list->node.next;     //ͷ���û�����ݣ�Ҫ��Ԫ����������
	for (int i = 0; i < list->size; i++)
	{
		printf("%d  ", first->data);
		first = first->next;
	}
}

int GetLength(LinkList*list)
{
	return list->size;
}

int main()
{
	LinkList*list = Init();
	list = Rear_Insert(list);     //β�巨�������˳�����
	Print(list);
	list = Head_Insert(list);     //ͷ�巨��������������
	Print(list);
	int len = GetLength(list);
	printf("\n������Ϊ��%d", GetLength(list));
}



