#ifndef DYNAMIC_ARRAY_H    //��ֹͷ�ļ��ظ�����
#define DYNAMIC_ARRAY_H 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct 
{
	int * address; //������ݵĵ�ַ
	int len;       //��ǰ����
	int maxsize;   //�������
}Dynamic_Array;

Dynamic_Array * Init();
void Insert(Dynamic_Array*arr, int value);
void Delete_pos(Dynamic_Array*arr, int pos);
void Delete_value(Dynamic_Array*arr, int value);
void Print(Dynamic_Array*arr);
void FreeArray(Dynamic_Array*arr);



#endif // !DYNAMIC_ARRAY_H











