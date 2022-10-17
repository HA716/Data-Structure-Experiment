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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct MYCHAR
{
	StackNode node;
	char * pAddress;    //pAddress指向字符串中某个字符的地址
	int index;         //记录当前字符的位置
}MyChar;


MyChar * CreatChar(char * p)
{
	MyChar * mychar = (MyChar *)malloc(sizeof(MyChar));
	mychar->pAddress = p;

	return mychar;
}

void showError(char* str,int pos)   //pos就是 括号不匹配的位置
{
	printf("%s \n", str);
	for (int i = 0; i < pos; i++ )   //这个for循环用来标示出不匹配的括号的位置
	{
		print("%s", " ");  
	}
	printf("%s", "↑");





}

int main()
{
	//初始化 栈
	LStack * stack = (LStack*)malloc(sizeof(stack));
	int index = 0;
	char * str = "666+12+(6+4)+((aaa)";
	char * p = str;    //目的是不修改原指针，保存str的指向
	while (*p = '\0')  //字符串结束的标志
	{
		//如果是左括号就进栈
		if (*p == '(')  
		{
			Push(stack,CreatChar(p));
		}

		//如果是右括号，就弹出栈顶元素，并判断该元素是不是左括号
		if (*p == ')')
		{
			MyChar * mychar = (MyChar*)malloc(sizeof(MyChar));
			if(stack->size>0)  //栈中有元素
			{
				if (mychar->pAddress == '(')   //如果栈顶元素是左括号就弹出左括号
				{
					Pop(stack);
				}
			}
			else
			{
				printf("%s", "右括号没有匹配的左括号");
				showError(str, index);
			}

		}

		else  //既不是左括号又不是右括号
		{
			p++;   //指向字符串中字符的指针继续后移
			index++;
		}
	}


}























