//#include<stdlib.h>
//#include<stdio.h>
//#include<string.h>

//typedef struct HEADER
//{
//	struct Header * node;
//	int len;
//}Header;
//
//typedef struct HSTRING
//{
//	char * data;
//	struct HString* next;
//}HString;
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


//�ͷŶ��ڴ�
void Free(HeapString *str)
{
	free(str);
}


int GetNext(HeapString *child, int*next)
{
	int i = 0;
	int j = -1;
	next[0] = -1;
	while (i < child->len)
	{
		if (j == -1 || child->ch[i] == child->ch[j])  //i����ǰ׺��j������׺
		{
			i++;
			j++;
			next[i] = j;  //i���Ӵ��ַ��±꣬j�������ǰ��׺�ĳ���
		}
		else
		{
			j = next[j];      //j�±�ָ����ݣ��ƶ��ĳ�����j-next[j]��������j��ǰһ���ַ����������ǰ��׺�ĳ���
		}

	}

}


int  KMP(HeapString *parent, HeapString *child, int pos)
{
	int next[1024];    //��Ÿ����ַ���Ӧ�������ǰ��׺��λ��
	GetNext(child, next);  
	int i = pos;
	int j = 0;
	while (i < parent->len-1&&j < child->len)
	{
		if (j == -1 || parent->ch[i] == child->ch[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	if (j == child->len)
	{
		return i - j;  //��������i+1 ��ȥ �Ӵ�����j
	}

	return 0;

}

//����������Ϣ
void PersonAndVirus()
{
	char*person[3] = { "aaabbb","cccddd","eeefff" };
	char*virus[3] = { "ab","cd","emmm" };
	HeapString * Person[3];
	HeapString * Virus[3];
	for (int i = 0; i < 3; i++)
	{
		Person[i] = Init();
		Virus[i] = Init();
		Copy(Person[i], person[i]);
		Copy(Virus[i], virus[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		Print(Person[i]);
	}
	printf("\n");
	for (int i = 0; i < 3; i++)
	{
		Print(Virus[i]);
	}
}


//������⺯����Ҫ�⿪��״����
int VirusTest(HeapString * Person,HeapString * Virus)
{
	Virus = Init();
	Virus->len = 5;
	char temp[1024];  // ???
	for (int i = 0; i < Virus->len * 2; i++)
	{
		temp[i] = Virus->ch[i%Virus->len];     //�⿪��״DNA
	}
	temp[Virus->len * 2] = '\0';

	//�ӽ⿪��DNA��ÿ��ȡ�Ӵ����ȵĴ����бȽ�
	for (int i = 0; i < Virus->len; i++)
	{
		char* vir[12];  //
		for (int j = i; j < i + Virus->len; j++)
		{
			vir[j - i] = temp[j];
		}
		vir[Virus->len] = '\0';
		HeapString * Virus_h;
		Virus_h = Init();
		Copy(Virus_h, vir);





	}
	





}



int main()
{
	PersonAndVirus();




}









