#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

//ǰ׺��:��¼ģʽ��pattern��ÿ���Ӵ��������ǰ��׺����
void Get_Next(char * pattern, int* next, int n)
{
	next[0] = 0;     //��1���ַ��������ǰ��׺����Ϊ0
	int len = 0;     //��ʼ�������ǰ��׺����
	int i = 1;       //�ӵڶ����ַ���ʼ

	//����ģʽ����ÿ��λ��
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
				next[i] = len;   //��ʱlen==0
				i++;
			}
		}
	}
}


//����next���飬ʹ֮��������ƶ�һλ��������ĵ�һ��λ�ò���Ԫ��-1,����kmp�㷨�Ĳ���
void Move_Next(int *next, int n)
{

	for (int i = n - 1; i > 0; i--)
	{
		next[i] = next[i - 1];
	}
	next[0] = -1;
}


//KMP�㷨:str��������pattern���Ӵ�
void KMP(char *str, char *pattern)
{
	int n = strlen(pattern);
	int m = strlen(str);
	int *next = (int *)malloc(sizeof(int)*n);
	Get_Next(pattern, next, n);
	Move_Next(next, n);

	//��i����str����j����pattern
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
		{//��ƥ�������
			j = next[j];
			if (j == -1)
			{
				i++;
				j++;
			}
		}

		//��ʾ�ҵ�
		if (j == n - 1 && str[i] == pattern[j])
		{
			printf("λ�ã�%d\n", i - j);
			j = next[j];   //����Ѱ��ģʽ���������г��ֵ�����λ��
		}
	}
}


int main()
{
	char pattern[] = "bc";
	char str[] = "1bc456bc9bc";
	KMP(str, pattern);

}
















