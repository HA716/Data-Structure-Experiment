#ifndef DYNAMIC_ARRAY_H    //防止头文件重复定义
#define DYNAMIC_ARRAY_H 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct 
{
	int * address; //存放数据的地址
	int len;       //当前长度
	int maxsize;   //最大容量
}Dynamic_Array;

Dynamic_Array * Init();
void Insert(Dynamic_Array*arr, int value);
void Delete_pos(Dynamic_Array*arr, int pos);
void Delete_value(Dynamic_Array*arr, int value);
void Print(Dynamic_Array*arr);
void FreeArray(Dynamic_Array*arr);



#endif // !DYNAMIC_ARRAY_H











