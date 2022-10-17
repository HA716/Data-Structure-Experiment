#include<stdlib.h>
#include<stdio.h>
#include<string.h>


//���Ķ�ʽ˳��洢
typedef struct HEAPSTRING
{
	char * ch;       //���ַ���
	int len;         //���ĵ�ǰ����
}HeapString;

//���ĳ�ʼ��
HeapString* Init()
{
	HeapString * str = (HeapString *)malloc(sizeof(HeapString));
	str->ch = NULL;   //��ʼ��Ϊ�մ�
	str->len = 0;
	return str;
}

//���ĸ���
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

//�ַ���֮��ĸ���:��str2���Ƶ�str1��
HeapString* CopyString(HeapString * str1, HeapString * str2)
{
	if (str2->len == 0 || str2->ch == NULL)
	{
		printf("%s", "ԭ�ַ���Ϊ�մ�");
		return;
	}
	else
	{
		for (int i = 0; i < str2->len; i++)
		{
			str1->ch[i] = str2->ch[i];
		}
		str1->len = str2->len;
		return str1;
	}
}


//�ַ����ıȽ�:�����ǱȽ��ַ�ASCLL��Ĵ�С    ����ֵ�� ������0������
int CompareString(HeapString *str1, HeapString *str2)
{
	for (int i = 0; i < str1->len && i < str2->len; i++)
	{
		if (str1->ch[i] != str2->ch[i])
		{
			return (str1->ch[i] - str2->ch[i]);  //����ASCLL��Ĳ�ֵ
		}       //��str1>str2������������str1=str2����0����str1<str2���ظ���
	}
	//forѭ��ȫ��ִ����ͱ�ʾ�����ַ������

	//����Ӧ�����ַ������ �ͱȽ��ַ����ĳ���
	return str1->len - str2->len;  //����ֵ�� ������0������
}


//�ַ�����ƴ��:�����´�
HeapString * Concat(HeapString * str1, HeapString*str2)
{
	//��ʼ���´� 
	HeapString * newString = Init();
	newString->len = str1->len + str2->len;
	newString->ch  = (char*)malloc(sizeof(char)*newString->len);

	//ƴ��
	for (int i = 0; i < str1->len; i++)
	{
		newString->ch[i] = str1->ch[i];
	}
	for (int j = 0; j < str2->len; j++)
	{
		newString->ch[str1->len + j] = str2->ch[j];
	}

	return newString;
}


//��������λ�ý��н�ȡ�ַ�����pos�ǿ�ʼ��ȡ��λ�ã�len�Ǳ���ȡ�ĳ���
HeapString * SubString(HeapString*str2, int pos, int len) 
{
	HeapString * str1 = Init();  //����Ҫ�ȳ�ʼ��������srt1ΪNULL���޷���len��ch���в���
	str1->len = len;
	str1->ch = (char*)malloc(sizeof(char)*len);
	if (str2 == NULL) return;
	if (pos<1 || pos>str2->len || pos + len - 1 > str2->len ) return;
	for (int i = 0; i < len; i++)
	{
		str1->ch[i] = str2->ch[pos-1 + i];
	}
	str1->len = len;
	return str1;


}




//��ӡ�ַ���
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


//Ѱ�Ҵ�posλ�ÿ�ʼ���ִ�child�ڸ���parent�е�λ��
int  Index(HeapString * parent, HeapString * child, int pos)
{
	if (pos < 0)  return;
	HeapString * tempString = Init();    //�����洢��ȡ���ַ���
	tempString->ch = (char*)malloc(sizeof(char)*child->len);
	int i = pos;                         //��¼��ʼλ��
	while (i + child->len -1<= parent->len)
	{
		tempString = SubString(parent, i,child->len);   //�Ӹ���parent�н�ȡ
		/*Print(tempString);
		printf("\n");*/
		if (CompareString(child, tempString)==0)   //��ʾ��ȡ���ִ��봫����ִ����
		{
			printf("%s", "���");
			return i;
		}
		else   //�����ƫ�Ƶ���һλ��������ȡ
		{
			i++;
		}
	}
	//Free(tempString); 
	printf("%s", "û���ҵ���Ӧ���Ӵ�");
	
}











//�ͷŶ��ڴ�
void Free(HeapString *str)
{
	free(str);
}


int main()
{
	////���ĸ���
	//HeapString *str = Init();
	//Copy(str,"abcdef");
	//Print(str);
	//Free(str);

	////�ַ���֮��ĸ���
	//HeapString *str1 = Init();
	//HeapString *str2 = Init();
	//Copy(str1, "abcdef");
	//Copy(str2, "123456");
	//CopyString(str1, str2);
	//Print(str1);
	//Free(str1);
	//Free(str2);

	//HeapString *str3 = Init();
	//HeapString *str4 = Init();
	//Copy(str3, "abcmef");
	//Copy(str4, "abcmefa");
	//int num = CompareString(str3, str4);
	//printf("%d", num);

	////�ַ�����ƴ��
	//HeapString *str5 = Init();
	//HeapString *str6 = Init();
	//Copy(str5, "abc");
	//Copy(str6, "def");
	//HeapString * newString= Concat(str5, str6);
	//Print(newString);

	////�ַ����Ľ�ȡ
	//HeapString *str7 = Init();
	//Copy(str7, "abcdefghijkl");
	//HeapString *str8 = SubString(str7, 3, 6);
	//Print(str8);

	//Ѱ���Ӵ��ڸ����е�λ��
	HeapString *str9 = Init();
	HeapString *str10 = Init();
	Copy(str9, "abcdef");
	Copy(str10,"def");
	int pos = Index(str9, str10, 1);
	printf("�Ӵ���λ����%d", pos);











}
















