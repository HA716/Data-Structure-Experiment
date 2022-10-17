#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int BF(char *a, char *b)
{
	int i, j;  //i指向主串，j指向模式串
	i = 0;
	j = 0;
	int len_a = strlen(a);
	int len_b = strlen(b);

	while (i < len_a&&j < len_b)
	{
		if (a[i] == b[j])
		{
			i++;
			j++;
		}
		else
		{//不匹配时,i和j都要发生回溯，下面是他们回溯的位置
			i = i - j + 1;
			j = 0;
		}
	}


	if (j == len_b)
	{//代表模式串在主串中能找到
		return i - j;
	}
	else
		return -1;
}

int main()
{
	char a[] = "abcdef";
	char b[] = "cde";
	int pos = BF(a, b);
	if (pos != -1)
	{
		printf("%s在%s的第%d个位置", b, a, pos + 1);
	}
	else
	{
		printf("匹配失败");
	}


}












