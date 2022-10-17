
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)


//定义二叉树结点的结构体：
typedef struct BINARYNODE
{
	char ch;      //结点的数据域
	struct BINARYNODE * leftNode;       //指向 左节点 的指针
	struct BINARYNODE * rightNode;      //指向 右节点 的指针

}BinaryNode;



//二叉树的递归遍历
void recursion(BinaryNode *root)  //传入根节点
{
	//递归结束的条件
	if (root == NULL)
	{
		return;
	}
	//先序遍历
	printf("%c", root->ch);
	recursion(root->leftNode);      //遍历左子树
	recursion(root->rightNode);     //遍历右子树

	////中序遍历
	//recursion(root->leftNode);
	//printf("%c", root->ch);
	//recursion(root->rightNode);

	////后序遍历
	//recursion(root->leftNode);
	//recursion(root->rightNode);
	//printf("%c", root->ch);
}


//计算 叶子数目
void calculateLeaf(BinaryNode *root, int * num)
{
	if (root == NULL)
	{
		return;
	}
	if (root->leftNode == NULL && root->rightNode == NULL)    //判断是否为 叶子
	{
		(*num)++;
	}
	calculateLeaf(root->leftNode, num);   //递归，先计算左节点的叶子
	calculateLeaf(root->rightNode, num);  //递归，再计算右节点的叶子

}

//计算树的高度
int Height(BinaryNode *root)   //传入根节点
{
	if (root == NULL)
	{
		return 0;
	}
	int leftHeight = Height(root->leftNode);     //左子树高度
	int rightHeight = Height(root->rightNode);   //右子树高度

	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1; //取兄弟节点中，高度更高的那个+1 ，就是树的深度

}


//对二叉树的拷贝：先拷贝左子树，再拷贝右子树，再创建新节点，最后返回新节点
BinaryNode * CopyTree(BinaryNode* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	 
	BinaryNode * LeftTree = CopyTree(root->leftNode);      //对左叉树的拷贝
	BinaryNode * RightTree = CopyTree(root->rightNode);    //对右叉树的拷贝
	//上面这两行代码，递推到最底层，也就是叶子的位置时，再执行就会出现root=NULL的情况，于是return,不再递推，变成执行下面代码

	//创建新结点
	BinaryNode *newNode = (BinaryNode*)malloc(sizeof(BinaryNode));
	newNode->ch = root->ch;
	newNode->leftNode = LeftTree;
	newNode->rightNode = RightTree;

	//返回新结点
	return newNode;

}

//释放内存
void Free(BinaryNode* root)
{
	if (root == NULL)
	{
		return;
	}
	//先释放左子树
	free(root->leftNode);
	//在释放右子树
	free(root->rightNode);
	//最后释放根节点
	free(root);

}



//创建并树的数据
void test()
{
	BinaryNode nodeA = { 'A',NULL,NULL };
	BinaryNode nodeB = { 'B',NULL,NULL };
	BinaryNode nodeC = { 'C',NULL,NULL };
	BinaryNode nodeD = { 'D',NULL,NULL };
	BinaryNode nodeE = { 'E',NULL,NULL };
	BinaryNode nodeF = { 'F',NULL,NULL };
	BinaryNode nodeG = { 'G',NULL,NULL };
	BinaryNode nodeH = { 'H',NULL,NULL };

	//根据已知信息，建立节点间的关系
	nodeA.leftNode = &nodeB;
	nodeA.rightNode = &nodeF;

	nodeB.rightNode = &nodeC;

	nodeC.leftNode = &nodeD;
	nodeC.rightNode = &nodeE;

	nodeF.rightNode = &nodeG;

	nodeG.leftNode = &nodeH;

	//1.遍历二叉树
/*	recursion(&nodeA);*/ 


	////2.记录叶子数量
	//int num = 0;   
	//calculateLeaf(&nodeA, &num);
	//printf("\n叶子数目为 ：%d", num);

	////3.记录树的高度
	//int height= Height(&nodeA);
	//printf("\n树的深度为 ：%d", height);

	//4.对二叉树的拷贝
	BinaryNode * newNode = CopyTree(&nodeA);
	recursion(newNode);

    //释放二叉树
	Free(newNode);

	return;
}

int main()
{
	 test();
	


}
















