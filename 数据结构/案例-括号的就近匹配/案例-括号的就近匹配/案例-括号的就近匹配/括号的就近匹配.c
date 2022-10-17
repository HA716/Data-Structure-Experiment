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


//测试---------------**********-----------------------***********-----------------------------***********-------------------------------***********--------
typedef struct MYCHAR
{
	StackNode node;
	char * pAddress;       //当前字符的位置
	int index;             //字符串中的第index个字符

}MyChar;


void showError( int index,char * str)
{
	printf("%s \n", str);
	for (int i = 0; i < index; i++)
	{
		printf("%s"," ");
	}

	printf("%s\n", "↑");
	
}




int main()
{

	LStack * stack = Init();      //初始化栈容器

	char * str = "(66)+()+(((66))";     //str是字符串的首地址
	char * p = str;           //不修改原指针的指向，更安全

	int index=0;  //用于 标记错误位置
	
	while (*p != '\0')    //对字符串指针解引用得到的是 单个字符
	{
		
	     //判断是否为左括号，若是左括号就进栈,但并不是直接让左括号进栈，而是让MyChar类型的变量进栈，因为栈容器的存放的数据类型是MyChar
		if (*p == '(')
		{
		
			//定义结构体变量，存放当前指针指向
			MyChar * mychar = (MyChar *)malloc(sizeof(MyChar));
			mychar->pAddress = p;
			mychar->index = index;

			//进栈
			Push(stack, mychar);
		}

		//判断是否为右括号，若是右括号，就看栈顶元素是否为左括号，若栈顶为左括号就弹出，否则不弹出
		if (*p == ')')
		{
		
			if (stack->size > 0)   //栈中有元素
			{
				MyChar *topChar = (MyChar *)TopElement(stack);   //拿到栈顶元素
				if ((*topChar->pAddress) == '(')          //若栈顶元素为左括号，就弹出
				{
					
					Pop(stack);
					free(topChar);
				}
			}

			else   //栈中没有元素
			{
	
				printf("%s\n", "没有与右括号匹配的左括号");
				//下面代码是为了形成一种视觉效果
			
				showError( index ,str);
				break;
			}

		}

		p++;         //指向下一个字符
		index++;     //p指针指向了第（index-1）个字符

	}


	//执行完上面的代码后，若得到的不是空栈，说明进栈的左括号没有弹出，也就是没有遇到匹配的右括号
	while (stack->size > 0)
	{
	
		MyChar * mychar = (MyChar*)TopElement(stack);
		printf("%s\n", "没有与左括号匹配的右括号");
		showError(mychar->index, str);
		Pop(stack);
		free(mychar);      //因为mychar是MyChar类型1变量，是malloc得到的，所以弹出后就释放内存
	}


}





















































