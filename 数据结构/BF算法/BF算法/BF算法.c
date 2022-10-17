#include<stdlib.h>
#include<stdio.h>
#include<string.h>


//���Ķ�ʽ˳��洢----------------------------------------------------------------------------
typedef struct HEAPSTRING
{
	char * ch;       //���ַ���
	int len;         //���ĵ�ǰ����
}HeapString;

//���ĳ�ʼ��---------------------------------------------------------------------------------
HeapString* Init()
{
	HeapString * str = (HeapString *)malloc(sizeof(HeapString));
	str->ch = NULL;   //��ʼ��Ϊ�մ�
	str->len = 0;
	return str;
}

//���ĸ���------------------------------------------------------------------------------
HeapString* Copy(HeapString * str, char * chars)
{
	int len = strlen(chars);
	if (len == 0)  //�����Ƶ��ַ�������Ϊ0,���޷�����
	{
		return;
	}
	else
	{
		str->ch = (char *)malloc(len * sizeof(char));  //ҪΪָ������ڴ�ռ�
		//��λ���� �� ���³���
		for (int i = 0; i < len; i++)
		{
			str->ch[i] = chars[i];
		}
		str->len = len;
		return str;
	}
}


//��ӡ�ַ���------------------------------------------------------------------------------
void Print(HeapString* str)
{
	//�մ� 555555

	if (str->len == 0)
	{
		printf("%s", "�ַ���Ϊ��");
		return;
	}
	for (int i = 0; i < str->len; i++)
	{
		printf("%c", str->ch[i]);
	}
}


//�ͷŶ��ڴ�---------------------------------------------------------------------------------
void Free(HeapString *str)
{
	free(str);
}


//BF�㷨:parent�Ǹ�����child�Ǵ����ҵ��Ӵ���pos�ǿ�ʼ���ҵ�λ��-----------------------------------------
int BFcompare(HeapString * parent, HeapString * child, int pos)
{
	int i = pos; //��ʼ���ҵ�λ��
	int j = 0;   //�Ӵ��е�һ���ַ��ַ�������ֵ
	while (i < parent->len&&j < child->len)   // �±겻��������
	{
		//��ch�е�i���ַ���T�е�j���ַ����ʱ��i�����һ����j�����һ��,�����Ƚ���һ��λ��
		if (parent->ch[i] == child->ch[j])
		{
			i++;
			j++;
		}
		else    //���������Ӵ���Ӧλ�õ��ַ�����ȣ���Ҫ ָ�����(Ҳ���Ǹ���ָ���λ��)
		{       //��parent�е�i���ַ���child�е�i���ַ������ʱ��i�ص�ǰһ��λ�õ���һ��λ�ã�j�ص�0��λ��
			i = (i - j) + 1;   //iһ��ʼ���ڵ���0��jһ��ʼ����0����i-jʼ�մ��ڵ���0�� ��(i - j) + 1��������һ��λ��
			j = 0;
		}
	}
	//������whileѭ��������i >= parent->len �� j >= child->len
	if (j >= child->len)  //��j����child�ĳ���ʱ��Ҳ��˵���Ӵ�child�ڸ���parent��ƥ��ɹ�
	{
		return i - j;     //��ͼ��֪�����ص��� �Ӵ�λ��
	}
	else
	{
		return -1;   //ƥ��ʧ�ܣ��򷵻�-1����Ϊ-1�±겻����
	}
}



int main()
{
	HeapString* parent = Init();
	HeapString* child  = Init();
	Copy(parent, "abcdefg");
	Copy(child, "cde");
	int index = BFcompare(parent, child, 0);
	printf("%d", index);



}
















