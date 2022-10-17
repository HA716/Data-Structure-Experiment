#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 50//表达式最大字符数
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
{//当字符串中不存在+和-时，构造二叉树
	//temp_left左子树，存储数字；temp_head双亲结点，存储*或/
	BTNode* temp_left, *temp_head;
	InitBTree(&temp_left);
	InitBTree(&temp_head);
	
	if (flag + 2 == n)
	{//根结点后只有一个数字
		temp_head->data = str[flag + 1];
	}
	else
	{//根结点后还有*或/算术运算
		temp_left->data = str[flag + 1];   //str[flag + 1]一定是数字
		temp_head->lchild = temp_left;
		//索引i对应位置都是*或/运算符
		for (int i = flag + 2; i < n; i = i + 2) 
		{//连续构建右子树
			temp_head->data = str[i];
			//temp_right右子树，存储数字
			BTNode* temp_right;
			InitBTree(&temp_right);
			//str[i + 1]一定是数字
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
{//根据表达式递归构造二叉树
	int flag = n;
	BTNode* b;
	BTNode* right_tree, *right_tree_lchild;
	InitBTree(&b);
	for (int i = 0; i < n; i++)
	{//遍历表达式字符串找到最后的+或-，从而将字符串分为左右子树进行构建
		if (str[i] == '+' || str[i] == '-')
			//字符串中的最后一个"+or-"作为根结点
			flag = i;           
	}
	if (flag != n)
	{//存在+或-
		b->data = str[flag];//根结点
		b->lchild = CreateBTree(str, flag);
		b->rchild = CreateBTree_Special(str, flag, n);
		/*经历了上面的for循环，此时根结点后无+或-，构造右子树*/
		
	}
	else
	{//不存在+或-
		b = CreateBTree_Special(str, -1, n);
	}
	return b;
}

void DisplayBTree(BTNode* b)
{//输出二叉树
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
{//计算算术表达式的值
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

	printf("请输入算术表达式(只包含+、-、*、/和一位正整数且格式正确)：");
	scanf_s("%s", str,MaxSize);

	b = CreateBTree(str, strlen(str));
	printf("对应二叉树为：");
	DisplayBTree(b);
	ans = Caculate(b);
	printf("\n算术表达式的值为：%f\n", ans);
	return 0;
}