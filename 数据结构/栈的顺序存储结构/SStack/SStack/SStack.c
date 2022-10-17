#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1024
typedef struct
{
	void* data[MAX];  //��Ϊ������û���洢ʲô���͵����ݣ�������void*�������Ļ����������Ͷ�����ֱ�Ӹ�ֵ��void*
	int size;         //ջ�ĵ�ǰ��С����ջ��Ԫ�ظ���
}SStack;

//��ʼ��ջ-------------------------------------------------------------------------------------------
SStack * Init()      
{
	SStack * stack = malloc(sizeof(SStack));       //Ϊջ���������ڴ�
	if (stack == NULL)  //��ջ
	{
		return NULL;
	}
	//�������
	memset(stack->data, 0, sizeof(void*)*MAX);     
	stack->size = 0;
	//���س�ʼ���õ�ջ����
	return stack;

}

//  ��ջ/ѹջ-----------------------------------------------------------------------------------------
void push(SStack*stack,void* data)
{
	if (stack == NULL) //��ջֱ�ӷ���
	{
		return; 
	}
	if (data = NULL)  //��������ݲ���Ҳֱ�ӷ���
	{
		return;
	}
	if (stack->size == MAX) //ջ���ˣ�ֱ�ӷ���
	{
		return;
	}
	//ѹջ�Ĺؼ������ ��  ����������ų��˾Ϳ�ʼѹջ 
	stack->data[stack->size] = data;//size��ʼΪ0�����ΪMAX,����stack->data[stack->size]����Ҫ�����λ��
	stack->size++;

}

// ��ջ----����ȳ�--------------------------------------------------------------------------------------
void pop(SStack*stack)
{
	if (stack == NULL)  //��ջ��ֱ�ӷ���
	{
		return;
	}
	if (stack->size <= 0)  //ջ�Ĵ�С����ֱ�ӷ���
	{
		return;
	}
	
	//��ջ�Ĺؼ�����
	stack->data[stack->size - 1] = NULL;  //��ջ��Ԫ��stack->data[stack->size - 1]�ÿ�
	stack->size--;

}

//����ջ -----------------------------------------------------------------------------------------
void Destory(SStack *stack)
{
	free(stack);
	stack = NULL;
}


//���ջ��Ԫ��-------------------------------------------------------------------------------------
void* topElem(SStack*stack)
{
	if (stack == NULL)  //��ջ��ֱ�ӷ���
	{
		return;
	}
	if (stack->size <= 0)  //ջ�Ĵ�С����ֱ�ӷ���
	{
		return;
	}
	//printf("������%s �����䣺%d ", stack->data[stack->size - 1]->name, stack->data[stack->size - 1]->age);
	return stack->data[stack->size-1 ];   //����ջ��Ԫ�� �� void * ���Խ��������������͵�����
	
}


//��ȡջ�Ĵ�С-------------------------------------------------------------------------------------
int Size(SStack*stack)
{
	return stack->size;
}



//------------------------------------------------------------------------------------------------
typedef struct
{
	char name[64];
	int age;
} Person;


//Person * InitPerson()
//{
//	Person  p1 = { "����",18 };
//	Person  p2 = { "����",20 };
//	
//
//}






int main()
{
	SStack *stack = Init();         //��ʼ�� ջ

	Person  p1 = { "����",18 };
	Person  p2 = { "����",20 };

	push(stack, &p1);    // ѹջ1
	push(stack, &p2);    // ѹջ2

	/*if (stack->data[stack->size - 1] == NULL)
	{
		printf("%s", "��ָ��");
	}
	printf("%d",Size(stack));*/

	//����ջ������Ԫ�أ����ⲻ�б�������Ϊ������֮��ջ�о�û��Ԫ����
	while (stack != NULL)     
	{
		Person * p = topElem(stack);      //��ȡջ��Ԫ��
		printf("������%s �����䣺%d ", p->name, p->age);
		
		pop(stack);   //��ջ
	}

	printf("ջ��ʣ��Ԫ�� %d", Size(stack));
	return 0;

}


























