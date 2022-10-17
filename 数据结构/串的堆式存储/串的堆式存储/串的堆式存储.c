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

//字符串之间的复制:把str2复制到str1中
HeapString* CopyString(HeapString * str1, HeapString * str2)
{
	if (str2->len == 0 || str2->ch == NULL)
	{
		printf("%s", "原字符串为空串");
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


//字符串的比较:本质是比较字符ASCLL码的大小    返回值是 正数、0、负数
int CompareString(HeapString *str1, HeapString *str2)
{
	for (int i = 0; i < str1->len && i < str2->len; i++)
	{
		if (str1->ch[i] != str2->ch[i])
		{
			return (str1->ch[i] - str2->ch[i]);  //返回ASCLL码的差值
		}       //若str1>str2返回正数，若str1=str2返回0，若str1<str2返回负数
	}
	//for循环全部执行完就表示各个字符都相等

	//若对应各个字符都相等 就比较字符串的长度
	return str1->len - str2->len;  //返回值是 正数、0、负数
}


//字符串的拼接:返回新串
HeapString * Concat(HeapString * str1, HeapString*str2)
{
	//初始化新串 
	HeapString * newString = Init();
	newString->len = str1->len + str2->len;
	newString->ch  = (char*)malloc(sizeof(char)*newString->len);

	//拼接
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


//根据所给位置进行截取字符串：pos是开始截取的位置，len是被截取的长度
HeapString * SubString(HeapString*str2, int pos, int len) 
{
	HeapString * str1 = Init();  //必须要先初始化，否则srt1为NULL，无法对len、ch进行操作
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


//寻找从pos位置开始的字串child在父串parent中的位置
int  Index(HeapString * parent, HeapString * child, int pos)
{
	if (pos < 0)  return;
	HeapString * tempString = Init();    //用来存储截取的字符串
	tempString->ch = (char*)malloc(sizeof(char)*child->len);
	int i = pos;                         //记录起始位置
	while (i + child->len -1<= parent->len)
	{
		tempString = SubString(parent, i,child->len);   //从父串parent中截取
		/*Print(tempString);
		printf("\n");*/
		if (CompareString(child, tempString)==0)   //表示截取的字串与传入的字串相等
		{
			printf("%s", "相等");
			return i;
		}
		else   //否则就偏移到下一位，继续截取
		{
			i++;
		}
	}
	//Free(tempString); 
	printf("%s", "没有找到对应的子串");
	
}











//释放对内存
void Free(HeapString *str)
{
	free(str);
}


int main()
{
	////串的复制
	//HeapString *str = Init();
	//Copy(str,"abcdef");
	//Print(str);
	//Free(str);

	////字符串之间的复制
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

	////字符串的拼接
	//HeapString *str5 = Init();
	//HeapString *str6 = Init();
	//Copy(str5, "abc");
	//Copy(str6, "def");
	//HeapString * newString= Concat(str5, str6);
	//Print(newString);

	////字符串的截取
	//HeapString *str7 = Init();
	//Copy(str7, "abcdefghijkl");
	//HeapString *str8 = SubString(str7, 3, 6);
	//Print(str8);

	//寻找子串在父串中的位置
	HeapString *str9 = Init();
	HeapString *str10 = Init();
	Copy(str9, "abcdef");
	Copy(str10,"def");
	int pos = Index(str9, str10, 1);
	printf("子串的位置是%d", pos);











}
















