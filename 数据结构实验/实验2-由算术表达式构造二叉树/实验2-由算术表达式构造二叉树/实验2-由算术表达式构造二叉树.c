#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 50//���ʽ����ַ���
typedef struct node
{
	struct node* lchild;
	struct node* rchild;
	char data;
}BTNode;



void InitBTree(BTNode** b)
{
	(*b)= (BTNode*)malloc(sizeof(BTNode));
	(*b)->lchild = NULL;
	(*b)->rchild = NULL;
}

BTNode* CreateBTree_Special(char str[MaxSize], int flag, int n)
{//���ַ����в�����+��-ʱ�����������
	//temp_left���������洢���֣�temp_head˫�׽�㣬�洢*��/
	BTNode* temp_left, *temp_head;
	InitBTree(&temp_left);
	InitBTree(&temp_head);
	
	if (flag + 2 == n)
	{//������ֻ��һ������
		temp_head->data = str[flag + 1];
	}
	else
	{//��������*��/��������
		temp_left->data = str[flag + 1];   //str[flag + 1]һ��������
		temp_head->lchild = temp_left;
		//����i��Ӧλ�ö���*��/�����
		for (int i = flag + 2; i < n; i = i + 2) 
		{//��������������
			temp_head->data = str[i];
			//temp_right���������洢����
			BTNode* temp_right;
			InitBTree(&temp_right);
			//str[i + 1]һ��������
			temp_right->data = str[i + 1];
			temp_head->rchild = temp_right;
			if (i + 2 >= n)
				break;

			BTNode* new_temp_head;
			InitBTree(&new_temp_head);
	       
			new_temp_head->lchild = temp_head;
			temp_head = new_temp_head;
		}
	}
	return temp_head;
}

BTNode* CreateBTree(char* str, int n)
{//���ݱ��ʽ�ݹ鹹�������
	int flag = n;
	BTNode* b;
	BTNode* right_tree, *right_tree_lchild;
	InitBTree(&b);
	for (int i = 0; i < n; i++)
	{//�������ʽ�ַ����ҵ�����+��-���Ӷ����ַ�����Ϊ�����������й���
		if (str[i] == '+' || str[i] == '-')
			//�ַ����е����һ��"+or-"��Ϊ�����
			flag = i;           
	}
	if (flag != n)
	{//����+��-
		b->data = str[flag];//�����
		b->lchild = CreateBTree(str, flag);
		b->rchild = CreateBTree_Special(str, flag, n);
		/*�����������forѭ������ʱ��������+��-������������*/
		
	}
	else
	{//������+��-
		b = CreateBTree_Special(str, -1, n);
	}
	return b;
}

void DisplayBTree(BTNode* b)
{//���������
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DisplayBTree(b->lchild);
			if (b->rchild != NULL)
			{
				printf(",");
				DisplayBTree(b->rchild);
			}
			printf(")");
		}
	}
}

double Caculate(BTNode* b)
{//�����������ʽ��ֵ
	if (b == NULL)
		return 0;
	if (b->data >= '0' && b->data <= '9')
		return b->data - '0';
	switch (b->data)
	{
	case '+':return Caculate(b->lchild) + Caculate(b->rchild); break;
	case '-':return Caculate(b->lchild) - Caculate(b->rchild); break;
	case '*':return Caculate(b->lchild) * Caculate(b->rchild); break;
	case '/':return Caculate(b->lchild) / Caculate(b->rchild); break;
	}
}

int main(void)
{
	char str[MaxSize] = { 0 };
	BTNode* b;
	double ans;

	printf("�������������ʽ(ֻ����+��-��*��/��һλ�������Ҹ�ʽ��ȷ)��");
	scanf_s("%s", str,MaxSize);

	b = CreateBTree(str, strlen(str));
	printf("��Ӧ������Ϊ��");
	DisplayBTree(b);
	ans = Caculate(b);
	printf("\n�������ʽ��ֵΪ��%f\n", ans);
	return 0;
}