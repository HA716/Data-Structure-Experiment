#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1024
typedef struct
{
	void* data[MAX];  //因为不清楚用户会存储什么类型的数据，所以用void*，这样的话，所有类型都可以直接赋值给void*
	int size;         //栈的当前大小，即栈中元素个数
}SStack;

//初始化栈-------------------------------------------------------------------------------------------
SStack * Init()      
{
	SStack * stack = malloc(sizeof(SStack));       //为栈容器开辟内存
	if (stack == NULL)  //空栈
	{
		return NULL;
	}
	//清空数组
	memset(stack->data, 0, sizeof(void*)*MAX);     
	stack->size = 0;
	//返回初始化好的栈容器
	return stack;

}

//  入栈/压栈-----------------------------------------------------------------------------------------
void push(SStack*stack,void* data)
{
	if (stack == NULL) //空栈直接返回
	{
		return; 
	}
	if (data = NULL)  //传入的数据不行也直接返回
	{
		return;
	}
	if (stack->size == MAX) //栈满了，直接返回
	{
		return;
	}
	//压栈的关键代码↓ ，  以上情况都排除了就开始压栈 
	stack->data[stack->size] = data;//size起始为0，最大为MAX,所以stack->data[stack->size]就是要插入的位置
	stack->size++;

}

// 出栈----后进先出--------------------------------------------------------------------------------------
void pop(SStack*stack)
{
	if (stack == NULL)  //空栈，直接返回
	{
		return;
	}
	if (stack->size <= 0)  //栈的大小有误，直接返回
	{
		return;
	}
	
	//出栈的关键代码
	stack->data[stack->size - 1] = NULL;  //将栈顶元素stack->data[stack->size - 1]置空
	stack->size--;

}

//销毁栈 -----------------------------------------------------------------------------------------
void Destory(SStack *stack)
{
	free(stack);
	stack = NULL;
}


//获得栈顶元素-------------------------------------------------------------------------------------
void* topElem(SStack*stack)
{
	if (stack == NULL)  //空栈，直接返回
	{
		return;
	}
	if (stack->size <= 0)  //栈的大小有误，直接返回
	{
		return;
	}
	//printf("姓名：%s ，年龄：%d ", stack->data[stack->size - 1]->name, stack->data[stack->size - 1]->age);
	return stack->data[stack->size-1 ];   //返回栈顶元素 ， void * 可以接收任意数据类型的数据
	
}


//获取栈的大小-------------------------------------------------------------------------------------
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
//	Person  p1 = { "张三",18 };
//	Person  p2 = { "李四",20 };
//	
//
//}






int main()
{
	SStack *stack = Init();         //初始化 栈

	Person  p1 = { "张三",18 };
	Person  p2 = { "李四",20 };

	push(stack, &p1);    // 压栈1
	push(stack, &p2);    // 压栈2

	/*if (stack->data[stack->size - 1] == NULL)
	{
		printf("%s", "空指针");
	}
	printf("%d",Size(stack));*/

	//访问栈中所以元素，但这不叫遍历，因为访问完之后，栈中就没有元素了
	while (stack != NULL)     
	{
		Person * p = topElem(stack);      //获取栈顶元素
		printf("姓名：%s ，年龄：%d ", p->name, p->age);
		
		pop(stack);   //出栈
	}

	printf("栈中剩余元素 %d", Size(stack));
	return 0;

}


























