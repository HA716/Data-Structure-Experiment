#include "dynamic_Array.h"

Dynamic_Array* Init()
{
	//为结构体指针分配内存
	Dynamic_Array * p = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
	//初始化
	p->len = 0;  //初始长度为0
	p->maxsize = 20;  //最大容量为20
	p->address = (int *)malloc(sizeof(int)*p->maxsize); //装数据的内存空间的大小

	return p;  //返回初始化好的这个结构体指针

}

//插入---------------------------------------------------------------------------------------------------------------------
void Insert(Dynamic_Array*arr, int value)
{
	if (arr->len == arr->maxsize)  //空间不足
	{
		//1.申请比原来两倍大的新空间
		int * newspace = (int*)malloc(sizeof(int)*arr->maxsize * 2);
		//2.拷贝数据到新空间
		memcpy(newspace, arr->address, sizeof(int)*arr->maxsize); //逐字节拷贝
		//3.释放旧空间
		free(arr->address);
		//4.更新新空间地址、更新容量
		arr->address = newspace;
		arr->maxsize = arr->maxsize * 2;
		
	}
	arr->address[arr->len] = value;   //插入数据
	arr->len++;

}

//根据位置进行删除----------------------------------------------------------------------------------------------------------
void Delete_pos(Dynamic_Array*arr, int pos)  //用覆盖的方式实现删除操作
{
	for (int i = pos; i < arr->maxsize-1; i++)  
	{
		arr->address[i] = arr->address[i + 1];
	}
}

//删除元素---------------------------------------------------------------------------------------------------------------
void Delete_value(Dynamic_Array*arr, int value)
{
	int pos;
	for (int i = 0; i < arr->len; i++)
	{
		if (arr->address[i] == value)  //找到相应元素值的下标
		{
			pos = i;
		}
		break;
	}
	for (int i = pos; i < arr->maxsize - 1; i++)
	{
		arr->address[i] = arr->address[i + 1];
	}
}

//打印----------------------------------------------------------------------------------------------------------------------
void Print(Dynamic_Array*arr)
{
	for (int i = 0; i < arr->len; i++)
	{
		printf("%d", arr->address[i]);    //arr只是结构体指针，并不是数组地址，而address才是存放数据的地址
	}
	printf("\n");
}

//释放-----------------------------------------------------------------------------------------------------------------------
void FreeArray(Dynamic_Array*arr)
{
	if (arr == NULL)
	{
		return 0;
	}
	if (arr->address != NULL)
	{
		free(arr->address);
	}
	free(arr);  //结构体指针自身也需要释放
}

//-----------------------------------------------------------------------------------------------------------------------------
int main()
{
	Dynamic_Array *Darr = Init();  //创建并初始化结构体指针
	for (int i = 0; i < 10; i++)
	{
		Insert(Darr, i);
	}
	Print(Darr);
	
}




















