#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct STACKNODE
{
	struct STACKNODE *next;
}StackNode;

typedef struct STACK_LINKLIST
{
	StackNode header;  //栈顶结点
	int size;
}LStack;



//初始化
void * Init()   //用void * 返回的原因是：不确定 栈 的类型
{
	//为栈申请一块内存
	LStack* stack = (LStack*)malloc(sizeof(LStack));

	stack->header.next = NULL;
	stack->size = 0;

	return stack;

}

//入栈
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

	LStack *stack = myStack;  //明确myStack的类型为 LStack
	StackNode* node = data;   //明确data的类型为 StackNode

	//插入结点
	node->next = stack->header.next;
	stack->header.next = node;

	stack->size++;
}

//出栈
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

	StackNode * pFirst = stack->header.next;  //pFirst指向第一个有元素的结点的位置
	stack->header.next = pFirst->next;

	//出栈后 ，更新链表长度
	stack->size--;

}

//栈顶元素
StackNode * TopElement(LStack*stack)
{
	if (stack == NULL)
	{
		return;
	}
	return stack->header.next;

}

//销毁 栈
void Free(LStack*stack)
{
	free(stack);
}

//测试---------------------------**********************-------------------------*************************---------------************************-------------

typedef struct MYCHAR
{
	StackNode node;
	char* pAddress;    //指向当前字符
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

int getPeriort(char c)  //比数字大小来表示运算符的优先级
{
	if (c == '*' || c == '/')   return 2;
	if (c == '+' || c == '-')   return 1;
	else              return 0;     //左括号优先级最低
	
}



int IsOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}



int main()
{
	LStack * stack = Init();  //初始化 栈容器

	char * str = "8+(3-1)*5";
	char * p = str;
	while (*p != '\0')
	{
		//判断是否是数字，如果是数字就输出
		if (isNum(*p))  
		{
			printf("%c", *p);
		}
		//判断是否为左括号,如果是左括号就进栈
		if (isLeft(*p))
		{
			MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));  //创建数据，让该类型的数据进栈
			mychar->pAddress = p;       //让指针pAddress指向左括号

			Push(stack, mychar);

		}
		//判断是否为右括号，如果是右括号，就检测栈顶元素，输出栈顶元素，直到匹配到左括号
		if (isRight(*p))
		{
			while (stack->size > 0)  //栈中有元素
			{
				MyChar * topChar = (MyChar*)TopElement(stack); //拿到栈顶元素
				if (isLeft(*(topChar->pAddress)))  //判断栈顶元素是否为左括号，如果是，就匹配成功，弹出即可
				{
					Pop(stack);
					break;
				}
				else  //栈顶元素不是左括号
				{
					printf("%c", *(topChar->pAddress));  //输出栈顶元素
					Pop(stack);
					free(topChar);
				}

			}
		}
		//其他运算符
		if(IsOperator(*p))
		{
			MyChar * topChar = (MyChar*)TopElement(stack);

			if (topChar == NULL)  //如果栈中没有元素，就直接进栈，不用比较
			{
				//进栈操作
				MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));  //创建数据，让该类型的数据进栈
				mychar->pAddress = p;       //让指针pAddress指向左括号
				Push(stack, mychar);
		
				return;
			}

			//栈顶符号优先级低于该符号，则此符号进栈
			if (getPeriort(*(topChar->pAddress)) < getPeriort(*p))
			{

				//进栈操作
				MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));  //创建数据，让该类型的数据进栈
				mychar->pAddress = p;       //让指针pAddress指向左括号
				Push(stack, mychar);
				return;
			}
			//如果栈顶符号优先级不低于该符号，则不断弹出并输出栈顶元素，直到栈顶符号优先级低于该符号
			else
			{
				while (stack->size > 0)
				{
					MyChar * topChar2 = (MyChar*)TopElement(stack);

					

					//栈顶符号优先级低于该符号，则此符号进栈
					if (getPeriort(*(topChar2->pAddress)) < getPeriort(*p))
					{
						//进栈操作
						MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));  //创建数据，让该类型的数据进栈
						mychar->pAddress = p;       //让指针pAddress指向左括号
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


	//遍历结束后，将栈中所有符号弹出
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

























