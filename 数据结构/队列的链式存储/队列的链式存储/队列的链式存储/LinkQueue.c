#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

//链式存储的队列 的 结点
typedef struct QUEUENODE
{
	struct QUEUENODE * next;
}QueueNode;

typedef struct LINKQUEUE
{
	QueueNode header;      //头结点
	int size;
	QueueNode * pTail;       //尾指针：记录队尾的位置，便于数据的插入

}LinkQueue;

//初始化队列
LinkQueue* Init()
{
	LinkQueue * queue = (LinkQueue*)malloc(sizeof(LinkQueue));  //为队列开辟内存
	
	queue->header.next = NULL;     //头结点的next指向NULL
	queue->size = 0;
	queue->pTail = &(queue->header);  //因为初始只有头结点，所以 尾指针pTail指向头结点
}


//入队
void Push(LinkQueue*queue,void * data)
{
	if (queue == NULL)
	{
		return;
	}

	//先转换数据的类型
	QueueNode* node = (QueueNode*)data;  //因为队列中的属性类型就是QueueNode

	//插入新结点
	queue->pTail->next = node;
	node->next = NULL;         //尾结点始终指向NULL

	//更新尾指针的位置，让尾指针指向最后一个结点
	queue->pTail = node;

	//更新队列长度
	queue->size++;

}


//出队
void Pop(LinkQueue*queue)
{
	if (queue == NULL)
	{
		return;
	}

	QueueNode * FirstValid = queue->header.next;  //首元结点FirstValid

	//出列：让头结点指向首元结点的下一个结点，即跳过了首元结点(第一个有数据的结点)
	queue->header.next = FirstValid->next;

	//更新队列长度
	queue->size--;
}

//返回 队头元素
void * Front(LinkQueue*queue)
{
	return queue->header.next;
}

//返回 队尾元素
void * Back(LinkQueue*queue)
{
	return queue->pTail;
}


//销毁队列
void Free(LinkQueue * queue)
{
	free(queue);
}



//测试
typedef struct PERSON
{
	QueueNode * node;
	char name[64];
	int age;
}Person;

int main()
{
	//初始化队列
	LinkQueue * queue = Init();

	//创建数据
	Person p1 = { NULL,"张三",10 };
	Person p2 = { NULL,"李四",20 };
	Person p3 = { NULL,"王五",30 };

	//入队
	Push(queue, &p1);
	Push(queue, &p2);
	Push(queue, &p3);

	printf("%d  \n", queue->size);

	//出队
	while (queue->size > 0)
	{
		Person* p = (Person*)Front(queue);         //队头元素
		printf("姓名： %s   年龄： %d \n", p->name, p->age);
		Pop(queue);
	}
	printf("%d  \n", queue->size);

	free(queue);
}







