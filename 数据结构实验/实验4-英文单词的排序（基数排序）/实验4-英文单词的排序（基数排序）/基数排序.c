#include <stdio.h>
#include <malloc.h>
#include <string.h>
#pragma warning (disable:4996)
#define MAX_LEN 15                               //  ���ʵ���󳤶�
#define RADIX 27                                //  ����rdΪ27,�ֱ��Ӧ' ','a',...,'z'

typedef char String[MAX_LEN + 1];               //  ����StringΪ�ַ���������
typedef struct node
{
	String word;
	struct node *next;
}link_node;                                     //  ������������

/*------------------�������------------------------*/
static void disp_word(String R[], int n)
{
	int i;

	printf("  ");
	for (i = 0; i < n; i++)
	{
		printf("[%s] ", R[i]);
	}
	printf("\n");
}

/*------------------�Ե��ʽ���Ԥ����,�ÿո����β����MAX_LEN��------------------------*/
static void pre_process(String R[], int n)   //n��Ԫ�ظ���
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		if (strlen(R[i]) < MAX_LEN)
		{
			for (j = strlen(R[i]); j < MAX_LEN; j++)
			{
				R[i][j] = ' ';
			}
			R[i][j] = '\0';
		}
	}
}

/*---------------�ָ�����,ɾ��Ԥ����ʱ����β���ո�--------------------*/
static void end_process(String R[], int n)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = MAX_LEN - 1; R[i][j] == ' '; j--)
			R[i][j + 1] = '\0';
	}
}

/*--------------���ؼ��ֵĵ�j���������з��䣬����˹���ʱ������һ��Ϊ��--------------*/
static void distribute(String R[], link_node *head[], link_node *tail[], int j, int n)
{
	int i;                                          //  ѭ������
	int k;                                          //  ���б��
	link_node *p;

	for (i = 0; i < n; i++)                          //  ����ɨ��R[i],�������
	{
		if (R[i][j] == ' ')                          //  �ո�ʱ����0�Ŷ�����,'a'����1�Ŷ�����,......
			k = 0;
		else
			k = R[i][j] - 'a' + 1;
		p = (link_node *)malloc(sizeof(link_node)); //  �����½��
		strcpy(p->word, R[i]);
		p->next = NULL;
		if (head[k] == NULL)
		{
			head[k] = p;
			tail[k] = p;
		}
		else
		{
			tail[k]->next = p;
			tail[k] = p;
		}
	}
}

/*--------------���ν����ǿն����еĽ���ռ����������ͷŸ��ǿն����е����н��--------------*/
static void collect(String R[], link_node *head[])
{
	int i;
	int k = 0;
	link_node *pre, *p;

	for (i = 0; i < RADIX; i++)
	{
		if (head[i] != NULL)
		{
			pre = head[i];
			p = pre->next;
			while (p != NULL)
			{
				strcpy(R[k++], pre->word);
				free(pre);
				pre = p;
				p = p->next;
			}
			strcpy(R[k++], pre->word);
			free(pre);
		}
	}
}

/*------------------��R[0...n-1]���л�������----------------*/
static void radix_sort(String R[], int n)
{
	int i, j;
	link_node *head[RADIX], *tail[RADIX];                    //����������ӵ���βָ��

	for (i = MAX_LEN - 1; i >= 0; i--)                       //  �ӵ�λ����λ��MAX_LEN�˻�������
	{
		for (j = 0; j < RADIX; j++)                          //��ʼ��ÿ������
			head[j] = tail[j] = NULL;
		distribute(R, head, tail, i, n);                    //  ��i�˷���
		collect(R, head);                                   //  ��i���ռ�
	}
}

int main(void)
{
	int n = 6;
	String R[] = { "we", "are", "family", "datastruct", "high score", "abcdef" };

	printf("����ǰ:\n");
	disp_word(R, n);
	pre_process(R, n);
	printf("Ԥ�����:\n");
	disp_word(R, n);
	radix_sort(R, n);
	printf("������:\n");
	disp_word(R, n);
	end_process(R, n);
	printf("���ս��:\n");
	disp_word(R, n);

	return 0;
}