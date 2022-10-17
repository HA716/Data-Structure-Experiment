#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

//创建一棵树，0代表NULL,非0代表节点： 1 2 0 0 3 0 0

typedef struct BITREENODE
{
	char ch;
	struct BITREENODE * leftNode;
	struct BITREENODE * rightNode;
}BiTreeNode;

BiTreeNode * CreateTree()
{
	int ch;
	scanf("%d", &ch);
	BiTreeNode * node;
	if (ch ==0)    
	{
		node = NULL;
	}
	else
	{
		node = (BiTreeNode*)malloc(sizeof(BiTreeNode));  //否则节点不为空，所以要为节点开辟空间
		node->ch = ch;
		node->leftNode = CreateTree();           //创建左子树，因为CreateTree()的返回值是node
		node->rightNode= CreateTree();           //创建右子树，因为CreateTree()的返回值是node
	}
	return node;
}


//递归遍历
void R(BiTreeNode * root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%d", root->ch);
	R(root->leftNode);
	R(root->rightNode);
 }


void main()
{

	BiTreeNode * node;
	node = CreateTree();
	R(node);
}










