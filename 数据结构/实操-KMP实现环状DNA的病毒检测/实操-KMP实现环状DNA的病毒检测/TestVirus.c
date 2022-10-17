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


//串的堆式顺序存储
typedef struct HEAPSTRING
{
	char * ch;       //该字符串
	int len;         //串的当前长度
}HeapString;

//串的初始化
HeapString* Init()
{
	HeapString * str = (HeapString *)malloc(sizeof(HeapString));
	str->ch = NULL;   //初始化为空串
	str->len = 0;
	return str;
}

//串的复制
HeapString* Copy(HeapString * str, char * chars)
{
	int len = strlen(chars);
	if (len == 0)  //待复制的字符串长度为0,则无法复制
	{
		return;
	}
	else
	{
		str->ch = (char *)malloc(len * sizeof(char));  //要为指针分配内存空间
		//逐位复制 且 更新长度
		for (int i = 0; i < len; i++)
		{
			str->ch[i] = chars[i];
		}
		str->len = len;
		return str;
	}
}

//打印字符串
void Print(HeapString* str)
{
	//空串 555555

	if (str->len == 0)
	{
		printf("%s", "字符串为空");
		return;
	}
	for (int i = 0; i < str->len; i++)
	{
		printf("%c", str->ch[i]);
	}
}


//释放对内存
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
		if (j == -1 || child->ch[i] == child->ch[j])  //i遍历前缀，j遍历后缀
		{
			i++;
			j++;
			next[i] = j;  //i是子串字符下标，j是最长公共前后缀的长度
		}
		else
		{
			j = next[j];      //j下标指针回溯，移动的长度是j-next[j]，正好是j的前一段字符串的最长公共前后缀的长度
		}

	}

}


int  KMP(HeapString *parent, HeapString *child, int pos)
{
	int next[1024];    //存放各个字符对应的最长公共前后缀的位置
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
		return i - j;  //主串长度i+1 减去 子串长度j
	}

	return 0;

}

//创建样本信息
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


//病毒检测函数：要解开环状病毒
int VirusTest(HeapString * Person,HeapString * Virus)
{
	Virus = Init();
	Virus->len = 5;
	char temp[1024];  // ???
	for (int i = 0; i < Virus->len * 2; i++)
	{
		temp[i] = Virus->ch[i%Virus->len];     //解开环状DNA
	}
	temp[Virus->len * 2] = '\0';

	//从解开的DNA中每次取子串长度的串进行比较
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









