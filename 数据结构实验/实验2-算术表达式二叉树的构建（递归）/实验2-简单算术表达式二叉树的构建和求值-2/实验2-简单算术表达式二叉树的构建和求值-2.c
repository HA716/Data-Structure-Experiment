#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef char ElemType;
typedef struct node
{
	ElemType data; // ����Ԫ��
	struct node *lchild; // ָ�����ӽ��
	struct node *rchild; // ָ���Һ��ӽ��
}BTNode; // �����������������

/*--------------------------�����ű�ʾ�����������b----------------------*/
static void disp_btree(BTNode *b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("("); // �к��ӽ��ʱ�����(
			disp_btree(b->lchild); // �ݹ鴦��������
			if (b->rchild != NULL) // ���Һ��ӽ��ʱ�����,
				printf(",");
			disp_btree(b->rchild); // �ݹ鴦��������
			printf(")"); // �к��ӽ��ʱ�����)
		}
	}
}

/*--------------------------�ͷŶ�����b�����н��----------------------*/
//static void destroy_btree(BTNode *&b) // ���ٶ�����(�β�b:ָ�������)
//{
//	if (b != NULL)
//	{
//		destroy_btree(b->lchild);
//		destroy_btree(b->rchild);
//		free(b);
//	}
//}

/*--------------------------�������������ʽs[i...j]��Ӧ�Ķ�����----------------------*/
/**
*   @����:�������ɼ��������ʽ��Ӧ�Ķ��������ݹ麯����
*   @param s:��ż��������ʽ�ַ���
*   @i:���ַ��������Ӵ�����ʼλ��
*   @j:���ַ��������Ӵ�����ֹλ��
*   ���i=j��˵���Ӵ�ֻ��һ���ַ�����ΪҶ�ӽ�㣬�򴴽�ֻ��һ�������Ķ����������ء�
*   ���i��j��������������ڴ�����"+"��"-"�ţ�������"+"��"-"Ϊ��(���ִ����ҵ�ԭ��)��
*   ��û��"+"��"-"��ʱ�����һ����"*"��"/"(�����ȳ˳���Ӽ���ԭ��)��ͬ�������������
*   Ϊ����������Ϊ�����֣�����������������������һ������㣬���ҵ�����������룬�ݹ�
*   ������������������Ľ���������֮��ݹ������������������Ľ���������
*/
static BTNode *cr_tree(char s[], int i, int j)
{
	int oper_num = 0; // ��¼������ĸ���
	BTNode *p;
	int k;
	int pos;

	if (i == j) // ����i=j�����,˵��ֻ��һ���ַ�
	{
		p = (BTNode *)malloc(sizeof(BTNode));
		p->data = s[i];
		p->lchild = p->rchild = NULL;
		return p;
	}

	/*---------------------����Ϊi��j�����-----------------------*/
	for (k = i; k <= j; k++) // ���Ȳ���+��-�����
	{
		if (s[k] == '+' || s[k] == '-')
		{
			oper_num++; // oper_num��¼+����-�ĸ���
			pos = k; // pos��¼���һ��+����-��λ��
		}
	}
	if (oper_num == 0) // û��+����-�����
	{
		for (k = i; k <= j; k++)
		{
			if (s[k] == '*' || s[k] == '/')
			{
				oper_num++; // oper_num��¼*����/�ĸ���
				pos = k; // pos��¼���һ��*����/��λ��
			}
		}
	}
	if (oper_num != 0) // ������������,����һ��������Ľ��
	{
		p = (BTNode *)malloc(sizeof(BTNode));
		p->data = s[pos];
		p->lchild = cr_tree(s, i, pos - 1); // �ݹ鴦��s[i...pos - 1]����������
		p->rchild = cr_tree(s, pos + 1, j); // �ݹ鴦��s[pos + 1, j]����������
	}
	else // û���κ������,����NULL
		return NULL;
}

/*--------------------------�����������Ӧ���ʽ��ֵ----------------------*/
/**
*   @����:�����������Ӧ���ʽ��ֵ���ݹ麯����
*   ��Ϊ�������򷵻�0��������b��ָ���ΪҶ�ӽ�㣬�򷵻���dataֵ���������
*   ��������ֵv1���������������ֵv2������b��ָ�����������v1��v2������Ӧ
*   �ļ��㲢���ؼ����Ľ����
*/
static double compute(BTNode *b)
{
	double v1, v2;

	if (b == NULL)
		return 0;
	if (b->lchild == NULL && b->rchild == NULL) // Ҷ�ӽ��ֱ�ӷ��ؽ��ֵ
		return b->data - '0';

	v1 = compute(b->lchild); // �ݹ������������ֵv1
	v2 = compute(b->rchild); // �ݹ������������ֵv2
	switch (b->data) // ����b�������Ӧ����
	{
	case '+':
		return v1 + v2;
	case '-':
		return v1 - v2;
	case '*':
		return v1 * v2;
	case '/':
		if (v2 != 0)
			return v1 / v2;
		else
			abort(); // ��0�쳣�˳�
	}
}

int main(int argc, char *argv[])
{
	BTNode *b;
	char s[MAX_SIZE] = "1+2*3-4/2";

	printf("�������ʽ%s\n", s);
	b = cr_tree(s, 0, strlen(s) - 1);
	printf("��Ӧ������:");           //!!!���λ�����������
	disp_btree(b);
	printf("\n�������ʽ��ֵ:%g\n", compute(b));

	//destroy_btree(b);

	return 0;
}