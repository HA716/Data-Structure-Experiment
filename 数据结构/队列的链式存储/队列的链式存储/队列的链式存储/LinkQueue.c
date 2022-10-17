#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

//��ʽ�洢�Ķ��� �� ���
typedef struct QUEUENODE
{
	struct QUEUENODE * next;
}QueueNode;

typedef struct LINKQUEUE
{
	QueueNode header;      //ͷ���
	int size;
	QueueNode * pTail;       //βָ�룺��¼��β��λ�ã��������ݵĲ���

}LinkQueue;

//��ʼ������
LinkQueue* Init()
{
	LinkQueue * queue = (LinkQueue*)malloc(sizeof(LinkQueue));  //Ϊ���п����ڴ�
	
	queue->header.next = NULL;     //ͷ����nextָ��NULL
	queue->size = 0;
	queue->pTail = &(queue->header);  //��Ϊ��ʼֻ��ͷ��㣬���� βָ��pTailָ��ͷ���
}


//���
void Push(LinkQueue*queue,void * data)
{
	if (queue == NULL)
	{
		return;
	}

	//��ת�����ݵ�����
	QueueNode* node = (QueueNode*)data;  //��Ϊ�����е��������;���QueueNode

	//�����½��
	queue->pTail->next = node;
	node->next = NULL;         //β���ʼ��ָ��NULL

	//����βָ���λ�ã���βָ��ָ�����һ�����
	queue->pTail = node;

	//���¶��г���
	queue->size++;

}


//����
void Pop(LinkQueue*queue)
{
	if (queue == NULL)
	{
		return;
	}

	QueueNode * FirstValid = queue->header.next;  //��Ԫ���FirstValid

	//���У���ͷ���ָ����Ԫ������һ����㣬����������Ԫ���(��һ�������ݵĽ��)
	queue->header.next = FirstValid->next;

	//���¶��г���
	queue->size--;
}

//���� ��ͷԪ��
void * Front(LinkQueue*queue)
{
	return queue->header.next;
}

//���� ��βԪ��
void * Back(LinkQueue*queue)
{
	return queue->pTail;
}


//���ٶ���
void Free(LinkQueue * queue)
{
	free(queue);
}



//����
typedef struct PERSON
{
	QueueNode * node;
	char name[64];
	int age;
}Person;

int main()
{
	//��ʼ������
	LinkQueue * queue = Init();

	//��������
	Person p1 = { NULL,"����",10 };
	Person p2 = { NULL,"����",20 };
	Person p3 = { NULL,"����",30 };

	//���
	Push(queue, &p1);
	Push(queue, &p2);
	Push(queue, &p3);

	printf("%d  \n", queue->size);

	//����
	while (queue->size > 0)
	{
		Person* p = (Person*)Front(queue);         //��ͷԪ��
		printf("������ %s   ���䣺 %d \n", p->name, p->age);
		Pop(queue);
	}
	printf("%d  \n", queue->size);

	free(queue);
}







