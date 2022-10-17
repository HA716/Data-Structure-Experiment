#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996) // 解决strcpy不安全问题

#define MAX 100

typedef struct Sequence_Stack    //栈的顺序存储用数组实现，所以属性里面有数组
{
	void* data[MAX];   //可以接受任意数据类型的数组 ，数组元素也是void * 类型
	int size;
}SeqStack;

//栈的初始化-----------------------------------------------------------------------------------------------------------
SeqStack * Init()
{

	SeqStack *stack = (SeqStack*)malloc(sizeof(SeqStack));
	for (int i = 0; i < MAX; i++)
	{
		stack->data[i] = NULL;        //初始化数组 ，NULL对应的值是 0
	}
	stack->size = 0;

}

//入栈-----------------------------------------------------------------------------------------------------------
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
	if (stack->size == MAX) //栈 满了
	{
		return; 
	}

	//入栈关键步骤
	stack->data[stack->size] = myData;   //因为data[]是void*，所以void * 类型myData可以做数组的元素
	stack->size++;

}


//出栈-----------------------------------------------------------------------------------------------------------
void Pop(SeqStack *stack)
{
	if (stack == NULL)
	{
		return NULL;
	}
	if (stack->size == 0)  //空栈
	{
		return NULL;
	}

	//出栈关键
	stack->data[stack->size - 1] = NULL;
	stack->size--;

}


//返回栈顶元素-----------------------------------------------------------------------------------------------------------
void * TopElement(SeqStack*stack)
{
	if (stack == NULL)
	{
		return NULL;
	}
	if (stack->size == 0)  //空栈
	{
		return NULL;
	}
	return stack->data[stack->size - 1];   //栈顶元素



}


//清空 栈-----------------------------------------------------------------------------------------------------------
void Clear(SeqStack*stack)
{
	if (stack == NULL)
	{
		return NULL;
	}
	if (stack->size == 0)  //空栈
	{
		return NULL;
	}

	//关键代码
	for (int i = 0; i < stack->size; i++)
	{
		stack->data[i] == NULL;
		
	}
	stack->size=0;
}

//销毁 栈-----------------------------------------------------------------------------------------------------------
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
	//初始化栈
	SeqStack * stack = Init();

	//创建数据
	Person p1, p2, p3;
	strcpy(p1.name, "张三");
	strcpy(p2.name, "李四");
	strcpy(p3.name, "王五");
	p1.age = 10;
	p2.age = 20;
	p3.age = 30;

	//插入
	Push(stack, &p1);
	Push(stack, &p2);
	Push(stack, &p3);

	/*printf("%d ", stack->size);*/

	//打印：重复 访问、弹出 栈顶元素
	while (stack->size > 0)
	{
		Person *p= (Person*)TopElement(stack);//访问栈顶元素
		printf("姓名：%s   年龄： %d  \n ",p->name,p->age );
		Pop(stack);//弹出栈顶元素

	}




}







