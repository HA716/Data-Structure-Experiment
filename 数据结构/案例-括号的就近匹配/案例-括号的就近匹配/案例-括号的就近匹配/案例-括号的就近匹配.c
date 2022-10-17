#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct STACKNODE
{
	struct STACKNODE *next;
}StackNode;

typedef struct STACK_LINKLIST
{
	StackNode header;  //ջ�����
	int size;
}LStack;



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
void Push(void*myStack, void *data)
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct MYCHAR
{
	StackNode node;
	char * pAddress;    //pAddressָ���ַ�����ĳ���ַ��ĵ�ַ
	int index;         //��¼��ǰ�ַ���λ��
}MyChar;


MyChar * CreatChar(char * p)
{
	MyChar * mychar = (MyChar *)malloc(sizeof(MyChar));
	mychar->pAddress = p;

	return mychar;
}

void showError(char* str,int pos)   //pos���� ���Ų�ƥ���λ��
{
	printf("%s \n", str);
	for (int i = 0; i < pos; i++ )   //���forѭ��������ʾ����ƥ������ŵ�λ��
	{
		print("%s", " ");  
	}
	printf("%s", "��");





}

int main()
{
	//��ʼ�� ջ
	LStack * stack = (LStack*)malloc(sizeof(stack));
	int index = 0;
	char * str = "666+12+(6+4)+((aaa)";
	char * p = str;    //Ŀ���ǲ��޸�ԭָ�룬����str��ָ��
	while (*p = '\0')  //�ַ��������ı�־
	{
		//����������žͽ�ջ
		if (*p == '(')  
		{
			Push(stack,CreatChar(p));
		}

		//����������ţ��͵���ջ��Ԫ�أ����жϸ�Ԫ���ǲ���������
		if (*p == ')')
		{
			MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));
			if(stack->size>0)  //ջ����Ԫ��
			{
				if (mychar->pAddress == '(')   //���ջ��Ԫ���������ž͵���������
				{
					Pop(stack);
				}
			}
			else
			{
				printf("%s", "������û��ƥ���������");
				showError(str, index);
			}

		}

		else  //�Ȳ����������ֲ���������
		{
			p++;   //ָ���ַ������ַ���ָ���������
			index++;
		}
	}


}























