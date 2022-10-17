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


//����---------------**********-----------------------***********-----------------------------***********-------------------------------***********--------
typedef struct MYCHAR
{
	StackNode node;
	char * pAddress;       //��ǰ�ַ���λ��
	int index;             //�ַ����еĵ�index���ַ�

}MyChar;


void showError( int index,char * str)
{
	printf("%s \n", str);
	for (int i = 0; i < index; i++)
	{
		printf("%s"," ");
	}

	printf("%s\n", "��");
	
}




int main()
{

	LStack * stack = Init();      //��ʼ��ջ����

	char * str = "(66)+()+(((66))";     //str���ַ������׵�ַ
	char * p = str;           //���޸�ԭָ���ָ�򣬸���ȫ

	int index=0;  //���� ��Ǵ���λ��
	
	while (*p != '\0')    //���ַ���ָ������õõ����� �����ַ�
	{
		
	     //�ж��Ƿ�Ϊ�����ţ����������žͽ�ջ,��������ֱ���������Ž�ջ��������MyChar���͵ı�����ջ����Ϊջ�����Ĵ�ŵ�����������MyChar
		if (*p == '(')
		{
		
			//����ṹ���������ŵ�ǰָ��ָ��
			MyChar * mychar = (MyChar *)malloc(sizeof(MyChar));
			mychar->pAddress = p;
			mychar->index = index;

			//��ջ
			Push(stack, mychar);
		}

		//�ж��Ƿ�Ϊ�����ţ����������ţ��Ϳ�ջ��Ԫ���Ƿ�Ϊ�����ţ���ջ��Ϊ�����ž͵��������򲻵���
		if (*p == ')')
		{
		
			if (stack->size > 0)   //ջ����Ԫ��
			{
				MyChar *topChar = (MyChar *)TopElement(stack);   //�õ�ջ��Ԫ��
				if ((*topChar->pAddress) == '(')          //��ջ��Ԫ��Ϊ�����ţ��͵���
				{
					
					Pop(stack);
					free(topChar);
				}
			}

			else   //ջ��û��Ԫ��
			{
	
				printf("%s\n", "û����������ƥ���������");
				//���������Ϊ���γ�һ���Ӿ�Ч��
			
				showError( index ,str);
				break;
			}

		}

		p++;         //ָ����һ���ַ�
		index++;     //pָ��ָ���˵ڣ�index-1�����ַ�

	}


	//ִ��������Ĵ�������õ��Ĳ��ǿ�ջ��˵����ջ��������û�е�����Ҳ����û������ƥ���������
	while (stack->size > 0)
	{
	
		MyChar * mychar = (MyChar*)TopElement(stack);
		printf("%s\n", "û����������ƥ���������");
		showError(mychar->index, str);
		Pop(stack);
		free(mychar);      //��Ϊmychar��MyChar����1��������malloc�õ��ģ����Ե�������ͷ��ڴ�
	}


}





















































