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

//����---------------------------**********************-------------------------*************************---------------************************-------------

typedef struct MYCHAR
{
	StackNode node;
	char* pAddress;    //ָ��ǰ�ַ�
}MyChar;

int isNum(char  c)
{
	if (c >= '0' && c <= '9') return 1;
	else return 0;
	
}

int isLeft(char c)
{
	return c == '(';
}

int isRight(char c)
{
	return c == ')';
}

int getPeriort(char c)  //�����ִ�С����ʾ����������ȼ�
{
	if (c == '*' || c == '/')   return 2;
	if (c == '+' || c == '-')   return 1;
	else              return 0;     //���������ȼ����
	
}



int IsOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}



int main()
{
	LStack * stack = Init();  //��ʼ�� ջ����

	char * str = "8+(3-1)*5";
	char * p = str;
	while (*p != '\0')
	{
		//�ж��Ƿ������֣���������־����
		if (isNum(*p))  
		{
			printf("%c", *p);
		}
		//�ж��Ƿ�Ϊ������,����������žͽ�ջ
		if (isLeft(*p))
		{
			MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));  //�������ݣ��ø����͵����ݽ�ջ
			mychar->pAddress = p;       //��ָ��pAddressָ��������

			Push(stack, mychar);

		}
		//�ж��Ƿ�Ϊ�����ţ�����������ţ��ͼ��ջ��Ԫ�أ����ջ��Ԫ�أ�ֱ��ƥ�䵽������
		if (isRight(*p))
		{
			while (stack->size > 0)  //ջ����Ԫ��
			{
				MyChar * topChar = (MyChar*)TopElement(stack); //�õ�ջ��Ԫ��
				if (isLeft(*(topChar->pAddress)))  //�ж�ջ��Ԫ���Ƿ�Ϊ�����ţ�����ǣ���ƥ��ɹ�����������
				{
					Pop(stack);
					break;
				}
				else  //ջ��Ԫ�ز���������
				{
					printf("%c", *(topChar->pAddress));  //���ջ��Ԫ��
					Pop(stack);
					free(topChar);
				}

			}
		}
		//���������
		if(IsOperator(*p))
		{
			MyChar * topChar = (MyChar*)TopElement(stack);

			if (topChar == NULL)  //���ջ��û��Ԫ�أ���ֱ�ӽ�ջ�����ñȽ�
			{
				//��ջ����
				MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));  //�������ݣ��ø����͵����ݽ�ջ
				mychar->pAddress = p;       //��ָ��pAddressָ��������
				Push(stack, mychar);
		
				return;
			}

			//ջ���������ȼ����ڸ÷��ţ���˷��Ž�ջ
			if (getPeriort(*(topChar->pAddress)) < getPeriort(*p))
			{

				//��ջ����
				MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));  //�������ݣ��ø����͵����ݽ�ջ
				mychar->pAddress = p;       //��ָ��pAddressָ��������
				Push(stack, mychar);
				return;
			}
			//���ջ���������ȼ������ڸ÷��ţ��򲻶ϵ��������ջ��Ԫ�أ�ֱ��ջ���������ȼ����ڸ÷���
			else
			{
				while (stack->size > 0)
				{
					MyChar * topChar2 = (MyChar*)TopElement(stack);

					

					//ջ���������ȼ����ڸ÷��ţ���˷��Ž�ջ
					if (getPeriort(*(topChar2->pAddress)) < getPeriort(*p))
					{
						//��ջ����
						MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));  //�������ݣ��ø����͵����ݽ�ջ
						mychar->pAddress = p;       //��ָ��pAddressָ��������
						Push(stack, mychar);
						break;
					}
					else
					{
						printf("%c", *(topChar2->pAddress));
						Pop(stack);
						free(topChar2);
					}

				}
			}

		}

		p++;


	}


	//���������󣬽�ջ�����з��ŵ���
	while (stack->size > 0)
	{
		MyChar* topChar = (MyChar*)TopElement(stack);
		printf("%c", *(topChar->pAddress));
		Pop(stack);
		free(topChar);
	}

	printf("\n");
	return 0;


}

























