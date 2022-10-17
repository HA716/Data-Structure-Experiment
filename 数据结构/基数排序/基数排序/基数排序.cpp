#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAX_Node 20			//链表结点个数
#define MAX_Radix 10		//基数的最大取值
#define MAX_Bit 8			//关键字位数的最大取值
typedef struct node
{
	char data[MAX_Bit];	//关键字
	struct node *next;
} NodeType;

void CreateLink(NodeType *&p, char a[MAX_Node][MAX_Bit], int n);  //创建单链表
void DispLink(NodeType *p);                                       //打印
void RadixSort(NodeType *&p, int r, int d);                       //基数排序


/*基数排序：指针p是单链表指针，radix是基数，bit是关键字的位数*/
void RadixSort(NodeType *&p, int radix, int bit) 
{
	NodeType *head[MAX_Radix], *tail[MAX_Radix];  //定义各链队的首尾指针
	NodeType *t=NULL;   //链表尾指针
	int i, j, k;

	//从低位向高位遍历关键字的每一位
	for (i = 0; i < bit; i++)
	{
		//初始化各链队
		for (j = 0; j < radix; j++) 				
			head[j] = tail[j] = NULL;

		//分配：遍历链表中的每个结点
		while (p != NULL)          		
		{
			//找到编号为k的链队
			k = p->data[i] - '0';     //字符转数字
			if (head[k] == NULL)   		//进行分配
			{
				head[k] = p;
				tail[k] = p;
			}
			else
			{
				tail[k]->next = p;
				tail[k] = p;
			}
			p = p->next;             		//取下一个待排序的元素
		}

		/* 收集 */
		p = NULL;				//重新用p来收集所有结点
		//遍历每个链队
		for (j = 0; j < radix; j++)        		
			if (head[j] != NULL)         	//进行收集
			{
				if (p == NULL)
				{
					p = head[j];
					t = tail[j];
				}
				else
				{
					t->next = head[j];
					t = tail[j];
				}
			}
		t->next = NULL;					//最后一个结点的next域置NULL

		printf("  按%s位排序\t", (i == 0 ? "个" : "十"));
		DispLink(p);
	}
}

void CreateLink(NodeType *&p, char a[MAX_Node][MAX_Bit], int n)	//采用后插法产生链表
{
	int i;
	NodeType *s, *t=NULL;
	for (i = 0; i < n; i++)
	{
		s = (NodeType *)malloc(sizeof(NodeType));
		strcpy(s->data, a[i]);
		if (i == 0)
		{
			p = s; t = s;
		}
		else
		{
			t->next = s; t = s;
		}
	}
	t->next = NULL;
}


void DispLink(NodeType *p)	//输出链表
{
	while (p != NULL)
	{
		printf("%c%c ", p->data[1], p->data[0]);
		p = p->next;
	}
	printf("\n");
}



void main()
{
	int n = 10, r = 10, d = 2;
	int i, j, k;
	NodeType *p;
	char a[MAX_Node][MAX_Bit];
	int b[] = { 75,23,98,44,57,12,29,64,38,82 };
	for (i = 0; i < n; i++)		//将b[i]转换成字符串
	{
		k = b[i];
		for (j = 0; j < d; j++)	//例如b[0]=75,转换后a[0][0]='7',a[0][1]='5'
		{
			a[i][j] = k % 10 + '0';
			k = k / 10;
		}
		a[i][j] = '\0';
	}
	CreateLink(p, a, n);
	printf("\n");
	printf("  初始关键字\t");		//输出初始关键字序列
	DispLink(p);
	RadixSort(p, 10, 2);
	printf("  最终结果\t");			//输出最终结果
	DispLink(p);
	printf("\n");
}
