#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include"栈的链式存储.h"



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




typedef struct PERSON
{
	StackNode  node;     //栈顶结点
	char name[64];
	int age;
}Person;





//测试
void test()
{
	//初始化 栈
	LStack *stack = Init();

	//创建数据
	Person p1 = { NULL,"张三",10 };  //不能分成两步写： ①Person p1；
	                                 //                 ② p1 = { NULL,"张三",10 }; 
	Person p2 = { NULL,"李四",20 };
	Person p3 = { NULL,"王五",30 };

	//入栈
	Push(stack, &p1);
	Push(stack, &p2);
	Push(stack, &p3);

	printf("%d \n", stack->size);

	//访问栈顶元素并出栈  相当于 遍历
	while (stack->size > 0)
	{
		Person * p = (Person *)TopElement(stack);   //因为StackNode * 类型的栈顶元素 本就是由 Person类型 转过去的
		printf("姓名： %s   年龄：%d \n", p->name, p->age);
		Pop(stack);      //出栈

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










