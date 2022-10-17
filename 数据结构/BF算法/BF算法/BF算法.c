#include<stdlib.h>
#include<stdio.h>
#include<string.h>


//串的堆式顺序存储----------------------------------------------------------------------------
typedef struct HEAPSTRING
{
	char * ch;       //该字符串
	int len;         //串的当前长度
}HeapString;

//串的初始化---------------------------------------------------------------------------------
HeapString* Init()
{
	HeapString * str = (HeapString *)malloc(sizeof(HeapString));
	str->ch = NULL;   //初始化为空串
	str->len = 0;
	return str;
}

//串的复制------------------------------------------------------------------------------
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


//打印字符串------------------------------------------------------------------------------
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


//释放对内存---------------------------------------------------------------------------------
void Free(HeapString *str)
{
	free(str);
}


//BF算法:parent是父串，child是待查找的子串，pos是开始查找的位置-----------------------------------------
int BFcompare(HeapString * parent, HeapString * child, int pos)
{
	int i = pos; //开始查找的位置
	int j = 0;   //子串中第一个字符字符的索引值
	while (i < parent->len&&j < child->len)   // 下标不超过串长
	{
		//当ch中第i个字符与T中第j个字符相等时，i向后移一个，j向后移一个,继续比较下一个位置
		if (parent->ch[i] == child->ch[j])
		{
			i++;
			j++;
		}
		else    //若父串和子串对应位置的字符不相等，就要 指针回溯(也就是更新指针的位置)
		{       //当parent中第i个字符与child中第i个字符不相等时，i回到前一个位置的下一个位置，j回到0号位置
			i = (i - j) + 1;   //i一开始大于等于0，j一开始等于0，故i-j始终大于等于0， 【(i - j) + 1】就是下一个位置
			j = 0;
		}
	}
	//能跳出while循环，代表i >= parent->len 或 j >= child->len
	if (j >= child->len)  //当j走完child的长度时，也就说明子串child在父串parent中匹配成功
	{
		return i - j;     //画图易知，返回的是 子串位置
	}
	else
	{
		return -1;   //匹配失败，则返回-1，因为-1下标不存在
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
















