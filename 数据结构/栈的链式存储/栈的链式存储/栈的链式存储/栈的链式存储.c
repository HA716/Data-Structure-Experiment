#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include"ջ����ʽ�洢.h"



//��ʼ��
void * Init()   //��void * ���ص�ԭ���ǣ���ȷ�� ջ ������
{
	//Ϊջ����һ���ڴ�
	LStack* stack = (LStack*)malloc(sizeof(LStack));

	stack->header.next = NULL;
	stack->size = 0;

	return stack;
	
}

//��ջ
void Push(void*myStack,void *data)
{
	if (myStack == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	LStack *stack = myStack;  //��ȷmyStack������Ϊ LStack
	StackNode* node = data;   //��ȷdata������Ϊ StackNode

	//������
	node->next = stack->header.next;
	stack->header.next = node;

	stack->size++;
}

//��ջ
void Pop(LStack * stack)
{
	if (stack == NULL)
	{
		return;
	}
	if (stack->size < 0)
	{
		return;
	}

	StackNode * pFirst = stack->header.next;  //pFirstָ���һ����Ԫ�صĽ���λ��
	stack->header.next = pFirst->next;

	//��ջ�� ������������
	stack->size--;

}

//ջ��Ԫ��
StackNode * TopElement(LStack*stack)  
{
	if (stack == NULL)
	{
		return;
	}
	return stack->header.next;

}

//���� ջ
void Free(LStack*stack)
{
	free(stack);
}




typedef struct PERSON
{
	StackNode  node;     //ջ�����
	char name[64];
	int age;
}Person;





//����
void test()
{
	//��ʼ�� ջ
	LStack *stack = Init();

	//��������
	Person p1 = { NULL,"����",10 };  //���ֳܷ�����д�� ��Person p1��
	                                 //                 �� p1 = { NULL,"����",10 }; 
	Person p2 = { NULL,"����",20 };
	Person p3 = { NULL,"����",30 };

	//��ջ
	Push(stack, &p1);
	Push(stack, &p2);
	Push(stack, &p3);

	printf("%d \n", stack->size);

	//����ջ��Ԫ�ز���ջ  �൱�� ����
	while (stack->size > 0)
	{
		Person * p = (Person *)TopElement(stack);   //��ΪStackNode * ���͵�ջ��Ԫ�� �������� Person���� ת��ȥ��
		printf("������ %s   ���䣺%d \n", p->name, p->age);
		Pop(stack);      //��ջ

	}

	printf("%d \n", stack->size);





}














//
//
//
//int main()
//{
//	test();
//}
//
//
//










