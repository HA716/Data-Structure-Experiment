#include<stdio.h>
#include<stdlib.h>

#define MAXLEN  10 //最大元素个数
#define MAXD 100   //每个元素的最大关键字位数

typedef struct NODE
{
	char data[MAXD];
	struct NODE *next;
}Node;


//输出单词
void Print(char R[MAXLEN][MAXD], int n)
{

	int i;
	for (i = 0; i < n; i++)
	{
		printf("[%s]", R[i]);
	}
	printf("\n");
}


//预处理：用'  '将所有单词补齐
void PreProcess(char R[][MAXD],int n)
{
	int i;
	int j;
	for (i = 0; i < n; i++)
	{
		if (strlen(R[i]) < MAXLEN)
		{
			for (j = strlen(R[i]); j < MAXLEN; j++)
			{
				R[i][j] = ' ';
			}
			R[i][j] = '\0';
		}
	}

}


//恢复处理，删除原本填充的空格'  '
void end_process(char R[][MAXD], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = MAXLEN - 1; R[i][j] == ' '; j--)
		{
			R[i][j + 1] = '\0';
		}
	}


}



//对每个元素的第j个关键字进行分配           ↓一维指针数组，数组的元素是Node*
void Distribute(char R[MAXLEN][MAXD], Node *head[], Node *tail[], int n,int j)
{
	int i;  //元素标号
	int k;  //队列编号
	Node*p;

	for (i = 0; i < n; i++)
	{
		if (R[i][j] == ' ')
		{//放入0号队列
			k = 0;
		}
		else
		{
			k = R[i][j] - 'a' + 1;
		}

		p = (Node*)malloc(sizeof(Node));
		strcpy(p->data, R[i]);
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


//收集
void Collect(char R[][MAXD], Node*head[])
{
	int i;
	int k = 0;
	Node*pre, *p;
	
	for (i = 0; i < MAXD; i++)
	{
		if (head[i] != NULL)
		{//队列非空
			pre = head[i];
			p = pre->next;
			while (p != NULL)
			{
				strcpy(R[k++], pre->data);
				free(pre);
				pre = p;
				p = pre->next;
			}
			strcpy(R[k++], pre->data);
			free(pre);
		}
	}
}


//对R[0,...n-1]进行基数排序
void Radix_Sort(char R[MAXLEN][MAXD], int n)
{
	int i, j;
	Node*head[MAXD], *tail[MAXD];

	for (i = MAXLEN - 1; i >= 0; i--)
	{
		for (j = 0; j < MAXD; j++)
		{
			head[j] = tail[j] = NULL;
		}
		Distribute(R, head, tail, n, i);   //第i趟分配
		Collect(R, head);                  //第i趟收集

	}

}





int main()
{
	char R[MAXLEN][MAXD] = { "while", "if", "if else", "do while", "for", "case" };
	int n = 6;

	printf("排序前:\n");
	Print(R, n);

	PreProcess(R, n);
	printf("预处理后:\n");
	Print(R, n);

	Radix_Sort(R, n);
	printf("排序结果:\n");
	Print(R, n);

	end_process(R, n);
	printf("最终结果:\n");
	Print(R, n);
}




















