#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void GetNext(char*child, int *next)  //���Ӵ�child��next����
{
	int Clen = strlen(child);
	next[0] = -1;              //next[0]Ĭ��Ϊ-1�ȽϺ���
	next[1] = 0;               //����ֵΪ1���±����ڶ����ַ���ǰ��ֻ��һ���ַ�������û������ǰ��׺
	int i = 2;  //��ǰi�±�Ϊ2����Ϊ����ֵΪ0��1��λ���Ѿ��趨Ĭ��ֵ��
	int k = 0;  //����next[i-1]������ǰ��׺�ĳ���
	while (i < Clen)
	{
		if (k==-1||child[i - 1] == child[k])       //���ۣ���p[i]==p[k]ʱ������next[i+1] = next[i] + 1 = k + 1 
		{  
			next[i] = k + 1;      //��next����ĸ�ֵ��next[i+1]=k+1������ʱ�����е�i�൱����i+1��
			i++;
			k++;
		}
		else
		{
			k= next[k];
		}
	}


	//int k = -1;   //�Ӵ�ǰ׺������ֵ��ʼΪ-1
	//int j = 0;    //�Ӵ���׺������ֵ��ʼΪ0
	//while (j < Clen-1)  //�������Ӵ�����
	//{
	//	if (k = -1 || child[k] == child[j])  //��һ�������Լ����ֻ�ͼ֤����D A B C D A B D E
	//	{                                                             //  -1 0 0 0 0 1 2 3 3
	//		k++;
	//		j++;
	//		next[j] = k;
	//	}
	//	else
	//	{
	//		k = next[k];    //��С��Χ��Ѱ��ǰ��׺�ĳ���
	//	}
	//}

}

//next���飺next[i]=k��ʾ ����i���ַ���ƥ��ʱ����¼���ַ�ǰ���ַ����������ǰ��׺����k
int KMP(char *parent, char*child, int pos)
{
	int Plen = strlen(parent);     //��������
	int Clen = strlen(child);      //�Ӵ�����
	if (Plen == 0 || Clen == 0) return;
	if (pos<0 || pos>Plen)      return;

	int * next = (int *)malloc(sizeof(int)*Clen);      //next�����С���Ӵ�����һ��

	GetNext(child, next);  //�ú�����������Ӵ���Ӧ��next����

	int i = pos;  //��������
	int j = 0;    //�����Ӵ�
	while (i < Plen&&j < Clen)
	{
		//j==-1�ᷢ������Խ�磬������j++��ͬʱi++�������ܱ�֤j���ַ�����i+1���Ƚϣ���Ϊ��ǰ��i���ı��Ѿ��������
		if (j==-1||parent[i] == child[j])  //��parent[i] == child[j]��������Ƚ�parent[i+1] == child[j+1]�Ƿ����
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];     //ָ����ݣ�������ǰ׺�ƶ������Ⱥ�׺��λ�ã��ƶ���j-next[j]�ĳ���
		}
	}
	if (j >= Clen)   //j���������Ӵ���Clen���Ӵ����ȣ���ʱ��j����ƥ���ַ�������һ��λ�ã���j==Clenʱ���Ѿ���ʾģʽ����ȫƥ�䣬��ͼ��֪����λ���±�i-j����
	{
		return i - j;
	}
	else
		return -1;

}


int main()
{
	char*parent = "abcabeabcabcmn";
	char*child = "abcabcmn";
	printf("%d",KMP("abcabeabcabcmn", "abcabcmn", 0));
}






















