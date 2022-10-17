#include "dynamic_Array.h"

Dynamic_Array* Init()
{
	//Ϊ�ṹ��ָ������ڴ�
	Dynamic_Array * p = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
	//��ʼ��
	p->len = 0;  //��ʼ����Ϊ0
	p->maxsize = 20;  //�������Ϊ20
	p->address = (int *)malloc(sizeof(int)*p->maxsize); //װ���ݵ��ڴ�ռ�Ĵ�С

	return p;  //���س�ʼ���õ�����ṹ��ָ��

}

//����---------------------------------------------------------------------------------------------------------------------
void Insert(Dynamic_Array*arr, int value)
{
	if (arr->len == arr->maxsize)  //�ռ䲻��
	{
		//1.�����ԭ����������¿ռ�
		int * newspace = (int*)malloc(sizeof(int)*arr->maxsize * 2);
		//2.�������ݵ��¿ռ�
		memcpy(newspace, arr->address, sizeof(int)*arr->maxsize); //���ֽڿ���
		//3.�ͷžɿռ�
		free(arr->address);
		//4.�����¿ռ��ַ����������
		arr->address = newspace;
		arr->maxsize = arr->maxsize * 2;
		
	}
	arr->address[arr->len] = value;   //��������
	arr->len++;

}

//����λ�ý���ɾ��----------------------------------------------------------------------------------------------------------
void Delete_pos(Dynamic_Array*arr, int pos)  //�ø��ǵķ�ʽʵ��ɾ������
{
	for (int i = pos; i < arr->maxsize-1; i++)  
	{
		arr->address[i] = arr->address[i + 1];
	}
}

//ɾ��Ԫ��---------------------------------------------------------------------------------------------------------------
void Delete_value(Dynamic_Array*arr, int value)
{
	int pos;
	for (int i = 0; i < arr->len; i++)
	{
		if (arr->address[i] == value)  //�ҵ���ӦԪ��ֵ���±�
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

//��ӡ----------------------------------------------------------------------------------------------------------------------
void Print(Dynamic_Array*arr)
{
	for (int i = 0; i < arr->len; i++)
	{
		printf("%d", arr->address[i]);    //arrֻ�ǽṹ��ָ�룬�����������ַ����address���Ǵ�����ݵĵ�ַ
	}
	printf("\n");
}

//�ͷ�-----------------------------------------------------------------------------------------------------------------------
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
	free(arr);  //�ṹ��ָ������Ҳ��Ҫ�ͷ�
}

//-----------------------------------------------------------------------------------------------------------------------------
int main()
{
	Dynamic_Array *Darr = Init();  //��������ʼ���ṹ��ָ��
	for (int i = 0; i < 10; i++)
	{
		Insert(Darr, i);
	}
	Print(Darr);
	
}




















