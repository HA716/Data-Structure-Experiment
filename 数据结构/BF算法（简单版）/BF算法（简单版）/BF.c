#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int BF(char *a, char *b)
{
	int i, j;  //iָ��������jָ��ģʽ��
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
		{//��ƥ��ʱ,i��j��Ҫ�������ݣ����������ǻ��ݵ�λ��
			i = i - j + 1;
			j = 0;
		}
	}


	if (j == len_b)
	{//����ģʽ�������������ҵ�
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
		printf("%s��%s�ĵ�%d��λ��", b, a, pos + 1);
	}
	else
	{
		printf("ƥ��ʧ��");
	}


}












