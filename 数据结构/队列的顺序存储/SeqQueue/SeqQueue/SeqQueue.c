#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable :4996)

#define MAX 1000

typedef struct  SEQQUEUE
{
	void* data[MAX];         //void * ��������ָ����Խ����κ�����,����data[]�����洢�����е���������
	int size;
}SeqQueue;


//���еĳ�ʼ��
SeqQueue * Init()  //ֻҪ�ṹ������������飬���г�ʼ����ʱ�����Ҫ������Ԫ��ȫ���ÿ�
{
	SeqQueue* queue = (SeqQueue*)malloc(sizeof(SeqQueue));     //Ϊ���������ڴ�
	for (int i = 0; i < MAX; i++ )                //�ÿն���
	{
		queue->data[i] = NULL;
	}
	queue->size = 0;

	return queue;
}

//���
void Push(SeqQueue *queue, void * data)      //Ҫ��������е����� data
{
	if (queue == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}
	if (queue->size == MAX)   //��������
	{
		return;
	}

	//���ݵ�ͷ��[0]��β��[size-1]����ͷ�����ԣ�Ϊ�˷��㣬����ѡ������ͷ��[0]����ͷ
	queue->data[queue->size] = data;
	queue->size++;

}


//����:��Ϊѡ������ͷ���Ƕ�ͷ�����Գ��о���ɾ������ͷ��[0]λ�õ�Ԫ�أ�ɾ��Ԫ�ؾ����ú����Ԫ�ظ���ǰ��Ԫ�ص�λ��
void Pop(SeqQueue * queue)
{
	if (queue == NULL)
	{
		return;
	}
	if (queue->size == 0)  
	{
		return;
	}

	//�ؼ�����
	for (int i = 0; i < queue->size - 1; i++)
	{
		queue->data[i] = queue->data[i + 1];      //��һ��Ԫ�� ���� ǰһ��Ԫ�� �������ɾ��
	}
	queue->size--;



}


//���ض�ͷԪ��Front
void * Front(SeqQueue*queue)
{
	if (queue == NULL)
	{
		return;
	}
	if (queue->size == 0)
	{
		return;
	}

	//�ؼ����룺���������ͷ��λ��Ԫ��
	return queue->data[0];

}

//���ض�βԪ��Back
void Back(SeqQueue*queue)
{
	if (queue == NULL)
	{
		return;
	}
	if (queue->size == 0)
	{
		return;
	}

	return queue->data[queue->size - 1];  //�����������һ��Ԫ��

}


//��ն���
void Clear(SeqQueue * queue)
{
	if (queue == NULL)
	{
		return;
	}
	if (queue->size == 0)
	{
		return;
	}


	//���鳤����0�����������޷�������
	queue->size = 0;
}


//���ٶ���
void Free(SeqQueue * queue)
{
	if (queue == NULL)
	{
		return;
	}

	free(queue);         //�ͷŶ��е��ڴ�ռ�

}

typedef struct PERSON     //˳��洢�����ݲ��ö���ṹ��ָ������
{
	char name[64];
	int age;

}Person;


int main()
{
	//��ʼ������
	SeqQueue * queue = Init();

	//��������
	Person p1 = { "����",10 };
	Person p2 = { "����",20 };
	Person p3 = { "����",30 };

	//���
	Push(queue, &p1);
	Push(queue, &p2);
	Push(queue, &p3);

	//����
	while (queue->size > 0)
	{              // ��������Ϊ�����е����ݱ�������Person���͵ģ����Բſ��Դ�void*ת��Person*
		Person * p = (Person*)Front(queue);            //��ȡ��ͷԪ��
		printf("������ %s     ���䣺 %d  \n", p->name, p->age);  
		Pop(queue);     //��ͷԪ�س���
	}










}










