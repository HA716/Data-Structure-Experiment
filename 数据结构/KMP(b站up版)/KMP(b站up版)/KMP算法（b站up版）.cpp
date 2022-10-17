#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

//前缀表:记录模式串pattern的每个子串的最长公共前后缀长度
void Get_Next(char * pattern, int* next, int n)
{
	next[0] = 0;     //第1个字符的最长公共前后缀长度为0
	int len = 0;     //初始化最长公共前后缀长度
	int i = 1;       //从第二个字符开始

	//遍历模式串的每个位置
	while (i < n)
	{
		if (pattern[i] == pattern[len])
		{
			len++;
			next[i] = len;
			i++;
		}
		else
		{
			if (len > 0)
			{
				len = next[len - 1];
			}
			else
			{
				next[i] = len;   //此时len==0
				i++;
			}
		}
	}
}


//调整next数组，使之整体向后移动一位，在数组的第一个位置插入元素-1,方便kmp算法的操作
void Move_Next(int *next, int n)
{

	for (int i = n - 1; i > 0; i--)
	{
		next[i] = next[i - 1];
	}
	next[0] = -1;
}


//KMP算法:str是主串，pattern是子串
void KMP(char *str, char *pattern)
{
	int n = strlen(pattern);
	int m = strlen(str);
	int *next = (int *)malloc(sizeof(int)*n);
	Get_Next(pattern, next, n);
	Move_Next(next, n);

	//用i遍历str，用j遍历pattern
	int i = 0;
	int j = 0;
	while (i < m)
	{
		if (str[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
		{//不匹配则回溯
			j = next[j];
			if (j == -1)
			{
				i++;
				j++;
			}
		}

		//表示找到
		if (j == n - 1 && str[i] == pattern[j])
		{
			printf("位置：%d\n", i - j);
			j = next[j];   //继续寻找模式串在主串中出现的其他位置
		}
	}
}


int main()
{
	char pattern[] = "bc";
	char str[] = "1bc456bc9bc";
	KMP(str, pattern);

}
















