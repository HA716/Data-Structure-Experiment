#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef char ElemType;
typedef struct node
{
	ElemType data; // 数据元素
	struct node *lchild; // 指向左孩子结点
	struct node *rchild; // 指向右孩子结点
}BTNode; // 声明二叉链结点类型

/*--------------------------以括号表示法输出二叉树b----------------------*/
static void disp_btree(BTNode *b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("("); // 有孩子结点时才输出(
			disp_btree(b->lchild); // 递归处理左子树
			if (b->rchild != NULL) // 有右孩子结点时才输出,
				printf(",");
			disp_btree(b->rchild); // 递归处理右子树
			printf(")"); // 有孩子结点时才输出)
		}
	}
}

/*--------------------------释放二叉树b的所有结点----------------------*/
//static void destroy_btree(BTNode *&b) // 销毁二叉树(形参b:指针的引用)
//{
//	if (b != NULL)
//	{
//		destroy_btree(b->lchild);
//		destroy_btree(b->rchild);
//		free(b);
//	}
//}

/*--------------------------建立简单算术表达式s[i...j]对应的二叉树----------------------*/
/**
*   @功能:用于生成简单算术表达式对应的二叉树，递归函数。
*   @param s:存放简单算术表达式字符串
*   @i:该字符串或其子串的起始位置
*   @j:该字符串或其子串的终止位置
*   如果i=j，说明子串只有一个字符，即为叶子结点，则创建只有一个根结点的二叉树并返回。
*   如果i≠j，根据运算规则，在串中找"+"或"-"号，以最后的"+"或"-"为根(体现从左到右的原则)；
*   当没有"+"或"-"号时，则进一步找"*"或"/"(体现先乘除后加减的原则)，同样以最后的运算符
*   为根，将串分为两部分，即左子树和右子树。创建一个根结点，将找到的运算符放入，递归
*   调用自身进入左子树的建树工作，之后递归调用自身进入右子树的建树工作。
*/
static BTNode *cr_tree(char s[], int i, int j)
{
	int oper_num = 0; // 记录运算符的个数
	BTNode *p;
	int k;
	int pos;

	if (i == j) // 处理i=j的情况,说明只有一个字符
	{
		p = (BTNode *)malloc(sizeof(BTNode));
		p->data = s[i];
		p->lchild = p->rchild = NULL;
		return p;
	}

	/*---------------------以下为i≠j的情况-----------------------*/
	for (k = i; k <= j; k++) // 首先查找+和-运算符
	{
		if (s[k] == '+' || s[k] == '-')
		{
			oper_num++; // oper_num记录+或者-的个数
			pos = k; // pos记录最后一个+或者-的位置
		}
	}
	if (oper_num == 0) // 没有+或者-的情况
	{
		for (k = i; k <= j; k++)
		{
			if (s[k] == '*' || s[k] == '/')
			{
				oper_num++; // oper_num记录*或者/的个数
				pos = k; // pos记录最后一个*或者/的位置
			}
		}
	}
	if (oper_num != 0) // 有运算符的情况,创建一个存放它的结点
	{
		p = (BTNode *)malloc(sizeof(BTNode));
		p->data = s[pos];
		p->lchild = cr_tree(s, i, pos - 1); // 递归处理s[i...pos - 1]构造左子树
		p->rchild = cr_tree(s, pos + 1, j); // 递归处理s[pos + 1, j]构造右子树
	}
	else // 没有任何运算符,返回NULL
		return NULL;
}

/*--------------------------计算二叉树对应表达式的值----------------------*/
/**
*   @功能:计算二叉树对应表达式的值，递归函数。
*   若为空树，则返回0，否则若b所指结点为叶子结点，则返回其data值，否则求出
*   左子树的值v1，再求出右子树的值v2，根据b所指结点的运算符对v1和v2进行相应
*   的计算并返回计算后的结果。
*/
static double compute(BTNode *b)
{
	double v1, v2;

	if (b == NULL)
		return 0;
	if (b->lchild == NULL && b->rchild == NULL) // 叶子结点直接返回结点值
		return b->data - '0';

	v1 = compute(b->lchild); // 递归求出左子树的值v1
	v2 = compute(b->rchild); // 递归求出右子树的值v2
	switch (b->data) // 根据b结点做相应运算
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
			abort(); // 除0异常退出
	}
}

int main(int argc, char *argv[])
{
	BTNode *b;
	char s[MAX_SIZE] = "1+2*3-4/2";

	printf("算术表达式%s\n", s);
	b = cr_tree(s, 0, strlen(s) - 1);
	printf("对应二叉树:");           //!!!这个位置输出有问题
	disp_btree(b);
	printf("\n算术表达式的值:%g\n", compute(b));

	//destroy_btree(b);

	return 0;
}