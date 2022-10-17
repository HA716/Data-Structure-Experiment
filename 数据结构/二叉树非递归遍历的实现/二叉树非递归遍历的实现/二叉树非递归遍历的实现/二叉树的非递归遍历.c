#include "栈的链式存储.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//创建二叉树
typedef struct BINARYNODE
{
	char ch;
	struct BINARYNODE * leftNode;
	struct BINARYNODE * rightNode;
}BinaryNode;

//为了二叉树的节点添加标志量falg，所以要重新封装上面这种节点
typedef struct BITREENODE
{
	StackNode node;       //联系二叉树的节点
	BinaryNode * root;    //二叉树根节点
	int flag;             //标记节点的能否输出，若flag==1就输出，0则不输出
}BiTreeNode;

//创建栈里面的节点
BiTreeNode * CreatNode(BinaryNode * node, int flag)
{
	BiTreeNode * newNode = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	newNode->root = node;
	newNode->flag = flag;

	return newNode;
}

//非递归遍历
void NonRecursion(BinaryNode * root)
{
	//先创建栈
	LStack *stack = Init();
	//创建二叉树节点
	BiTreeNode* newNode = CreatNode(root, 0);  //0意味着默认不可见

	//让节点入栈
	Push(stack, (StackNode*)newNode);

	while (stack->size > 0)
	{
		//拿到栈顶元素
		BiTreeNode * topNode = (BiTreeNode*)TopElement(stack);
		//弹出栈顶元素
		Pop(stack);
		 //判断栈顶元素是否为空
		if (topNode->root == NULL)
		{
			continue;   //跳过此次循环
		}
		//判断栈顶元素能否输出
		if (topNode->flag == 1)
		{
			printf("%c", topNode->root->ch);
		}
		//
		else  //即topNode->flag == 0  -->不能输出，那么就根据遍历的需要，进行压栈
			  //比如先序遍历是 根、左、右 ， 那么压栈顺序就是 右、左、根
		{
			Push(stack, (StackNode*)topNode->root->rightNode);  //将右节点压入栈
			Push(stack, (StackNode*)topNode->root->leftNode);   //将左节点压入栈
			topNode->flag = 1;           //第一次是置0，弹出后再压栈就置1
			Push(stack, (StackNode*)topNode->root);             //将根节点压入栈
		}

	}




}






//遍历二叉树
void Print(BinaryNode * root)
{
	if (root == NULL)
	{
		return NULL;
	}

	//先序遍历
	printf("%c", root->ch);
	Print(root->leftNode);     //认真思考 递归的过程
	Print(root->rightNode);

}


/*二叉树如图
              A
         B          F
            C          G
          D  E        H
 */


//初始化二叉树
BinaryNode  CreatBinaryTree()
{
	//创建节点
	BinaryNode nodeA = { 'A',NULL,NULL };
	BinaryNode nodeB = { 'B',NULL,NULL };
	BinaryNode nodeC = { 'C',NULL,NULL };
	BinaryNode nodeD = { 'D',NULL,NULL };
	BinaryNode nodeE = { 'E',NULL,NULL };
	BinaryNode nodeF = { 'F',NULL,NULL };
	BinaryNode nodeG = { 'G',NULL,NULL };
	BinaryNode nodeH = { 'H',NULL,NULL };

	//建立二叉树节点间的联系
	nodeA.leftNode = &nodeB;
	nodeA.rightNode = &nodeF;

	nodeB.rightNode = &nodeC;

	nodeC.leftNode = &nodeD;
	nodeC.rightNode = &nodeE;

	nodeF.rightNode = &nodeG;
	nodeG.leftNode = &nodeH;

	//遍历二叉树
	//Print(&nodeA);

   NonRecursion(&nodeA);
	//return nodeA;

}









int main()
{
	CreatBinaryTree();
}












