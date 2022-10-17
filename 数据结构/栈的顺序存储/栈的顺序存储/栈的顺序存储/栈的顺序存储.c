#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996) // ���strcpy����ȫ����

#define MAX 100

typedef struct Sequence_Stack    //ջ��˳��洢������ʵ�֣�������������������
{
	void* data[MAX];   //���Խ��������������͵����� ������Ԫ��Ҳ��void * ����
	int size;
}SeqStack;

//ջ�ĳ�ʼ��-----------------------------------------------------------------------------------------------------------
SeqStack * Init()
{

	SeqStack *stack = (SeqStack*)malloc(sizeof(SeqStack));
	for (int i = 0; i < MAX; i++)
	{
		stack->data[i] = NULL;        //��ʼ������ ��NULL��Ӧ��ֵ�� 0
	}
	stack->size = 0;

}

//��ջ-----------------------------------------------------------------------------------------------------------
void Push(SeqStack* stack, void * myData)
{
	if (stack == NULL)
	{
		return;
	}
	if (myData == NULL)
	{
		return;
	}
	if (stack->size == MAX) //ջ ����
	{
		return; 
	}

	//��ջ�ؼ�����
	stack->data[stack->size] = myData;   //��Ϊdata[]��void*������void * ����myData�����������Ԫ��
	stack->size++;

}


//��ջ-----------------------------------------------------------------------------------------------------------
void Pop(SeqStack *stack)
{
	if (stack == NULL)
	{
		return NULL;
	}
	if (stack->size == 0)  //��ջ
	{
		return NULL;
	}

	//��ջ�ؼ�
	stack->data[stack->size - 1] = NULL;
	stack->size--;

}


//����ջ��Ԫ��-----------------------------------------------------------------------------------------------------------
void * TopElement(SeqStack*stack)
{
	if (stack == NULL)
	{
		return NULL;
	}
	if (stack->size == 0)  //��ջ
	{
		return NULL;
	}
	return stack->data[stack->size - 1];   //ջ��Ԫ��



}


//��� ջ-----------------------------------------------------------------------------------------------------------
void Clear(SeqStack*stack)
{
	if (stack == NULL)
	{
		return NULL;
	}
	if (stack->size == 0)  //��ջ
	{
		return NULL;
	}

	//�ؼ�����
	for (int i = 0; i < stack->size; i++)
	{
		stack->data[i] == NULL;
		
	}
	stack->size=0;
}

//���� ջ-----------------------------------------------------------------------------------------------------------
void Free(SeqStack *stack)
{
	free(stack);

}



typedef struct PERSON
{
	char name[64];
	int age;
}Person;


int main()
{
	//��ʼ��ջ
	SeqStack * stack = Init();

	//��������
	Person p1, p2, p3;
	strcpy(p1.name, "����");
	strcpy(p2.name, "����");
	strcpy(p3.name, "����");
	p1.age = 10;
	p2.age = 20;
	p3.age = 30;

	//����
	Push(stack, &p1);
	Push(stack, &p2);
	Push(stack, &p3);

	/*printf("%d ", stack->size);*/

	//��ӡ���ظ� ���ʡ����� ջ��Ԫ��
	while (stack->size > 0)
	{
		Person *p= (Person*)TopElement(stack);//����ջ��Ԫ��
		printf("������%s   ���䣺 %d  \n ",p->name,p->age );
		Pop(stack);//����ջ��Ԫ��

	}




}







