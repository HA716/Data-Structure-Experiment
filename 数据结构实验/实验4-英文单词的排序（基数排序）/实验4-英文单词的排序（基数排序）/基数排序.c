#include <stdio.h>
#include <malloc.h>
#include <string.h>
#pragma warning (disable:4996)
#define MAX_LEN 15                               //  单词的最大长度
#define RADIX 27                                //  基数rd为27,分别对应' ','a',...,'z'

typedef char String[MAX_LEN + 1];               //  定义String为字符数组类型
typedef struct node
{
	String word;
	struct node *next;
}link_node;                                     //  单链表结点类型

/*------------------输出单词------------------------*/
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

/*------------------对单词进行预处理,用空格填充尾部至MAX_LEN长------------------------*/
static void pre_process(String R[], int n)   //n是元素个数
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

/*---------------恢复处理,删除预处理时填充的尾部空格--------------------*/
static void end_process(String R[], int n)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = MAX_LEN - 1; R[i][j] == ' '; j--)
			R[i][j + 1] = '\0';
	}
}

/*--------------按关键字的第j个分量进行分配，进入此过程时各队列一定为空--------------*/
static void distribute(String R[], link_node *head[], link_node *tail[], int j, int n)
{
	int i;                                          //  循环变量
	int k;                                          //  队列编号
	link_node *p;

	for (i = 0; i < n; i++)                          //  依次扫描R[i],将其入队
	{
		if (R[i][j] == ' ')                          //  空格时放入0号队列中,'a'放入1号队列中,......
			k = 0;
		else
			k = R[i][j] - 'a' + 1;
		p = (link_node *)malloc(sizeof(link_node)); //  创建新结点
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

/*--------------依次将各非空队列中的结点收集起来，并释放各非空队列中的所有结点--------------*/
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

/*------------------对R[0...n-1]进行基数排序----------------*/
static void radix_sort(String R[], int n)
{
	int i, j;
	link_node *head[RADIX], *tail[RADIX];                    //定义各个链队的首尾指针

	for (i = MAX_LEN - 1; i >= 0; i--)                       //  从低位到高位做MAX_LEN趟基数排序
	{
		for (j = 0; j < RADIX; j++)                          //初始化每个链队
			head[j] = tail[j] = NULL;
		distribute(R, head, tail, i, n);                    //  第i趟分配
		collect(R, head);                                   //  第i趟收集
	}
}

int main(void)
{
	int n = 6;
	String R[] = { "we", "are", "family", "datastruct", "high score", "abcdef" };

	printf("排序前:\n");
	disp_word(R, n);
	pre_process(R, n);
	printf("预处理后:\n");
	disp_word(R, n);
	radix_sort(R, n);
	printf("排序结果:\n");
	disp_word(R, n);
	end_process(R, n);
	printf("最终结果:\n");
	disp_word(R, n);

	return 0;
}