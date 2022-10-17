#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

//����һ������0����NULL,��0����ڵ㣺 1 2 0 0 3 0 0

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
		node = (BiTreeNode*)malloc(sizeof(BiTreeNode));  //����ڵ㲻Ϊ�գ�����ҪΪ�ڵ㿪�ٿռ�
		node->ch = ch;
		node->leftNode = CreateTree();           //��������������ΪCreateTree()�ķ���ֵ��node
		node->rightNode= CreateTree();           //��������������ΪCreateTree()�ķ���ֵ��node
	}
	return node;
}


//�ݹ����
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










