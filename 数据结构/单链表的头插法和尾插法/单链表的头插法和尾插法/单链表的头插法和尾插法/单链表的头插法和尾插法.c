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
	LinkNode node;   //链表结点
}LinkList;

LinkList * Init()
{
	LinkList * list;
	list = (LinkList*)malloc(sizeof(LinkList));
	list->node.next = NULL;          //首元结点为NULL
	list->size = 0;

	return list;
}

//尾插法
//list就是头结点node的头指针
LinkList*Rear_Insert(LinkList * list)
{
	LinkNode * Rear;      //尾指针
	Rear = &(list->node);    //初始化尾指针：指向头结点
	LinkNode * newNode;
	int index = 1;
	int x;
	printf("第%d次输入", index);
	scanf("%d", &x);
	while (x != -1)         //输入-1代表停止插入
	{

		//创建新结点
		newNode = (LinkNode*)malloc(sizeof(LinkNode));
		newNode->data = x;
		newNode->next = NULL;
		Rear->next = newNode;   //连接最后一个结点和新结点
		Rear = newNode;         //尾指针始终指向链表的最后一个结点
		list->size++;           //更新链表长度
		index++;
		printf("第%d次输入", index);
		scanf("%d", &x);
	}
	Rear->next = NULL;          //最后一个结点一定要指向NULL才算结束

	return list;
}

//头插法
LinkList * Head_Insert(LinkList*list)
{
	LinkNode * newNode;
	int index = 1;
	int x;
	printf("第%d次输入", index);
	scanf("%d", &x);
	while (x != -1)
	{
		newNode = (LinkNode*)malloc(sizeof(LinkNode));
		newNode->data = x;
		//插入新结点
		newNode->next = list->node.next;       //插入的第一个新结点的next=list->node.next，此时等效与next=NULL
		list->node.next = newNode;

		list->size++;           //更新链表长度
		index++;
		printf("第%d次输入", index);
		scanf("%d", &x);
	}

	return list;
}

void Print(LinkList*list)
{
	LinkNode * first = list->node.next;     //头结点没有数据，要首元结点才有数据
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
	list = Rear_Insert(list);     //尾插法：结果会顺序输出
	Print(list);
	list = Head_Insert(list);     //头插法：结果会逆序输出
	Print(list);
	int len = GetLength(list);
	printf("\n链表长度为：%d", GetLength(list));
}



