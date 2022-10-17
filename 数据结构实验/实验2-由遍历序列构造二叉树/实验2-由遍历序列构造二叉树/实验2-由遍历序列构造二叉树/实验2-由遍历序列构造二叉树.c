#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)
#define MAX 100

typedef struct NODE
{
	char data;
	struct NODE* leftNode;
	struct NODE* rightNode;
}Node;


//*********************************************************************************** 
//                               ↓先序序列    ↓中序序列  ↓先序或中序序列的长度  
Node* CreateTree_PreMid(char* preTree, char* midTree, int len)
{
	Node* tree = (Node*)malloc(sizeof(Node));
	if (!tree)
		return;
	tree->data = preTree[0];   //先序序列的第一个就是树的根结点
	tree->leftNode = NULL;
	tree->rightNode = NULL;
	if (len == 1)      //若只剩一个结点，就直接返回这个结点
		return tree;

	//leftLen是左子树的结点树，rightLen是右子树的结点树，midPos是先序遍历的根结点在中序遍历中的位置
	int  leftLen, rightLen;
	int midPos = 0;
	while (midTree[++midPos] != preTree[0]) {}    //找出中序遍历中根节点的位置

	//画图分析
	leftLen = midPos;                   //左子树结点数
	rightLen = len - leftLen - 1;       //右子树结点数,再-1是因为要减去根结点的长度
									  //  ↓ 新的先序序列要去掉原先的根结点  
	tree->leftNode = CreateTree_PreMid(&preTree[1], midTree, leftLen);                           //当前根结点的 左子树
	tree->rightNode = CreateTree_PreMid(&preTree[leftLen + 1], &midTree[leftLen + 1], rightLen); //当前根结点的 右子树
	return tree;
}


//************************************************************************************************************************
//                               ↓中序序列    ↓后序序列  ↓后序或中序序列的长度
Node* CreateTree_MidPost(char* midTree, char* postTree, int len)
{

	Node*tree = (Node*)malloc(sizeof(Node));
	tree->data = postTree[len - 1];             //根结点是后序序列的最后一个结点
	tree->leftNode = NULL;
	tree->rightNode = NULL;

	if (tree == NULL) return;
	if (len == 1) return;         //说明只有一个结点了，直接返回

	int  leftLen, rightLen;
	int midPos = 0;

	while (midTree[midPos] != postTree[len - 1])
	{
		midPos++;
	}

	//画图分析
	leftLen = midPos;
	rightLen = len - midPos - 1;

	tree->leftNode = CreateTree_MidPost(midTree, postTree, midPos);
	tree->rightNode = CreateTree_MidPost(&midTree[leftLen + 1], &postTree[leftLen], rightLen);
	//    ↑  &midTree[leftLen + 1] 等价于 midTree + leftLen + 1
	return  tree;

}




//括号表示法输出二叉树*******************************************************************************************
void Print_KUOHAO(Node* tree)  //打印后序遍历结果
{
	if (!tree)	return;

	printf("%c", tree->data);
	if (tree->leftNode != NULL || tree->rightNode != NULL)
	{
		printf("(");
		Print_KUOHAO(tree->leftNode);
		if (tree->rightNode != NULL)
		{
			printf(",");
		}
		Print_KUOHAO(tree->rightNode);
		printf(")");
	}


}


//凹入法输出二叉树*******************************************************************************************
//                         ↓     ↓ （n、k都是用来控制凹入表示法格式的参数）
void Print_AORU(Node *b, int n, int k)
{
	if (b != NULL)
	{

		for (int j = 0; j < k; j++)
		{
			printf("   ");
		}
		printf("%c ", b->data);
		for (int j = 0; j < n; j++)
		{
			printf("-");
		}
		printf("\n");
		Print_AORU(b->leftNode, n - 1, k + 1);
		Print_AORU(b->rightNode, n - 1, k + 1);
	}
}


int main()
{

	//char pre[MAX], mid[MAX];
	//要对char*输入就要malloc分配空间,否则要使用char[]
	char * pre = (char*)malloc(sizeof(char)*MAX);
	char * mid = (char*)malloc(sizeof(char)*MAX);
	char * post = (char*)malloc(sizeof(char)*MAX);

	//scanf输入的时候，不用对char*类型加'&',但其他类型都要
	printf("请输入先序遍历结果：");
	scanf_s("%s", pre, MAX);
	printf("请输入中序遍历结果：");
	scanf("%s", mid, MAX);
	printf("请输入后序遍历结果：");
	scanf("%s", post, MAX);


	int len = strlen(pre);
	int len2 = strlen(mid);

	//由先序、中序创建二叉树
	Node* tree_pre_mid = CreateTree_PreMid(pre, mid, len);
	Node* tree_mid_post = CreateTree_MidPost(mid, post, len2);

	//括号表示法输出（先序+中序）二叉树
	printf("\n由（先序+中序）创建的二叉树:\n");
	Print_KUOHAO(tree_pre_mid);

	//凹入表示法输出（中序+后序）二叉树
	printf("\n由（中序+后序）创建的二叉树:\n");
	Print_AORU(tree_mid_post, 14, 1);
	return 0;
}





















