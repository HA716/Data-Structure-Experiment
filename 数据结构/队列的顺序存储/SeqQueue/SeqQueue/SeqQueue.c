#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable :4996)

#define MAX 1000

typedef struct  SEQQUEUE
{
	void* data[MAX];         //void * 是无类型指针可以接收任何数据,数组data[]用来存储队列中的所有数据
	int size;
}SeqQueue;


//队列的初始化
SeqQueue * Init()  //只要结构体的属性有数组，进行初始化的时候就需要将数组元素全部置空
{
	SeqQueue* queue = (SeqQueue*)malloc(sizeof(SeqQueue));     //为队列申请内存
	for (int i = 0; i < MAX; i++ )                //置空队列
	{
		queue->data[i] = NULL;
	}
	queue->size = 0;

	return queue;
}

//入队
void Push(SeqQueue *queue, void * data)      //要插入队列中的数据 data
{
	if (queue == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}
	if (queue->size == MAX)   //队列已满
	{
		return;
	}

	//数据的头部[0]或尾部[size-1]做队头都可以，为了方便，下面选用数组头部[0]做队头
	queue->data[queue->size] = data;
	queue->size++;

}


//出队:因为选中数组头部是队头，所以出列就是删除数组头部[0]位置的元素，删除元素就是用后面的元素覆盖前面元素的位置
void Pop(SeqQueue * queue)
{
	if (queue == NULL)
	{
		return;
	}
	if (queue->size == 0)  
	{
		return;
	}

	//关键代码
	for (int i = 0; i < queue->size - 1; i++)
	{
		queue->data[i] = queue->data[i + 1];      //后一个元素 覆盖 前一个元素 ，这就是删除
	}
	queue->size--;



}


//返回队头元素Front
void * Front(SeqQueue*queue)
{
	if (queue == NULL)
	{
		return;
	}
	if (queue->size == 0)
	{
		return;
	}

	//关键代码：返回数组的头部位置元素
	return queue->data[0];

}

//返回队尾元素Back
void Back(SeqQueue*queue)
{
	if (queue == NULL)
	{
		return;
	}
	if (queue->size == 0)
	{
		return;
	}

	return queue->data[queue->size - 1];  //返回数组最后一个元素

}


//清空队列
void Clear(SeqQueue * queue)
{
	if (queue == NULL)
	{
		return;
	}
	if (queue->size == 0)
	{
		return;
	}


	//数组长度置0，这个数组就无法访问了
	queue->size = 0;
}


//销毁队列
void Free(SeqQueue * queue)
{
	if (queue == NULL)
	{
		return;
	}

	free(queue);         //释放队列的内存空间

}

typedef struct PERSON     //顺序存储的数据不用定义结构体指针属性
{
	char name[64];
	int age;

}Person;


int main()
{
	//初始化队列
	SeqQueue * queue = Init();

	//创建数据
	Person p1 = { "张三",10 };
	Person p2 = { "李四",20 };
	Person p3 = { "王五",30 };

	//入队
	Push(queue, &p1);
	Push(queue, &p2);
	Push(queue, &p3);

	//出队
	while (queue->size > 0)
	{              // ↓↓↓因为队列中的数据本来就是Person类型的，所以才可以从void*转回Person*
		Person * p = (Person*)Front(queue);            //获取队头元素
		printf("姓名： %s     年龄： %d  \n", p->name, p->age);  
		Pop(queue);     //队头元素出队
	}










}










