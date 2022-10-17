#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAX_Node 20			//���������
#define MAX_Radix 10		//���������ȡֵ
#define MAX_Bit 8			//�ؼ���λ�������ȡֵ
typedef struct node
{
	char data[MAX_Bit];	//�ؼ���
	struct node *next;
} NodeType;

void CreateLink(NodeType *&p, char a[MAX_Node][MAX_Bit], int n);  //����������
void DispLink(NodeType *p);                                       //��ӡ
void RadixSort(NodeType *&p, int r, int d);                       //��������


/*��������ָ��p�ǵ�����ָ�룬radix�ǻ�����bit�ǹؼ��ֵ�λ��*/
void RadixSort(NodeType *&p, int radix, int bit) 
{
	NodeType *head[MAX_Radix], *tail[MAX_Radix];  //��������ӵ���βָ��
	NodeType *t=NULL;   //����βָ��
	int i, j, k;

	//�ӵ�λ���λ�����ؼ��ֵ�ÿһλ
	for (i = 0; i < bit; i++)
	{
		//��ʼ��������
		for (j = 0; j < radix; j++) 				
			head[j] = tail[j] = NULL;

		//���䣺���������е�ÿ�����
		while (p != NULL)          		
		{
			//�ҵ����Ϊk������
			k = p->data[i] - '0';     //�ַ�ת����
			if (head[k] == NULL)   		//���з���
			{
				head[k] = p;
				tail[k] = p;
			}
			else
			{
				tail[k]->next = p;
				tail[k] = p;
			}
			p = p->next;             		//ȡ��һ���������Ԫ��
		}

		/* �ռ� */
		p = NULL;				//������p���ռ����н��
		//����ÿ������
		for (j = 0; j < radix; j++)        		
			if (head[j] != NULL)         	//�����ռ�
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
		t->next = NULL;					//���һ������next����NULL

		printf("  ��%sλ����\t", (i == 0 ? "��" : "ʮ"));
		DispLink(p);
	}
}

void CreateLink(NodeType *&p, char a[MAX_Node][MAX_Bit], int n)	//���ú�巨��������
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


void DispLink(NodeType *p)	//�������
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
	for (i = 0; i < n; i++)		//��b[i]ת�����ַ���
	{
		k = b[i];
		for (j = 0; j < d; j++)	//����b[0]=75,ת����a[0][0]='7',a[0][1]='5'
		{
			a[i][j] = k % 10 + '0';
			k = k / 10;
		}
		a[i][j] = '\0';
	}
	CreateLink(p, a, n);
	printf("\n");
	printf("  ��ʼ�ؼ���\t");		//�����ʼ�ؼ�������
	DispLink(p);
	RadixSort(p, 10, 2);
	printf("  ���ս��\t");			//������ս��
	DispLink(p);
	printf("\n");
}
