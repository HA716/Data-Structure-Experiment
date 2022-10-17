#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable :4996)


//  问题出在： 输入的 # 无法被识别  --> 改成单引号后解决了 ，但是仍无法结束输出

typedef struct  BINARYNODE
{
	char ch;
	struct BINARYNODE * leftNode;
	struct BINARYNODE * rightNode;
}BinaryNode;


BinaryNode * CreateNode()
{
	char ch;
	BinaryNode * node;//创建树的节点
	scanf("%c", &ch);

	
	      //只能用单引号‘’，只有单引号代表字符，且用ASCLL码表示，如果是双引号""就变成字符串了,不能作条件表达式
	if (ch == '#')    //输入井号#就代表为左子树或右子树为NULL
	{
		node = NULL;
	}
	else
	{
	    node=(BinaryNode *)malloc(sizeof(BinaryNode));  

		//实现树的节点：这一步主要是根据先序遍历的原则进行操作的
		node->ch = ch;                  //节点的名字
		node->leftNode=CreateNode();  //递归，继续创建左子树
		node->rightNode= CreateNode(); //递归，创建右子树

	}

	return node;

}


//递归遍历树
void Recursion(BinaryNode * root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%c", root->ch);
	Recursion(root->leftNode);
	Recursion(root->rightNode);

}

int main()
{
	BinaryNode * root = CreateNode();
	Recursion(root);
	return 0;
}



// 2.

//#include <iostream>
//#include <malloc.h>
//
//using namespace std;
//
/*
 * 二叉树的二叉链表结构的创建与相关操作
 * 1.先序法创建二叉树
 * 2.先序遍历
 * 3.中序遍历
 * 4.后序遍历
 * 说明：如果结点为叶子结点，只需将左右孩子的值置为'#',(即紧邻之后的两个输入为'#');
 * 例如：输入：a b # # c # # ,得到以a为根结点，b为左孩子，c为右孩子的二叉树。
 */

// //二叉树结点结构体
//typedef struct BTNode
//{
//	char data;
//	struct BTNode *pLchild, *pRchild;
//}BTNode, *BinTree;
//
////声明函数
//void CreatBTree(BinTree&);       //创建二叉树
//void PreTraverseTree(BinTree);   //先序遍历
//void InTraverseTree(BinTree);    //中序遍历
//void PostTraverseTree(BinTree);  //后序遍历
//
////main函数
//int main()
//{
//	BTNode* pBintree = NULL;
//	CreatBTree(pBintree);
//	cout << "先序遍历：";
//	PreTraverseTree(pBintree);
//	cout << "\n中序遍历：";
//	InTraverseTree(pBintree);
//	cout << "\n后序遍历：";
//	PostTraverseTree(pBintree);
//	return 0;
//}
//
////先序建立二叉树
//void CreatBTree(BinTree& bt)
//{
//	char val;
//	cout << "请输入结点值：";
//	cin >> val;
//	if (val == '#')
//	{
//		return;
//	}
//	if (bt == NULL)
//	{
//		bt = (BTNode*)malloc(sizeof(BTNode));
//		bt->data = val;
//		bt->pLchild = NULL;
//		bt->pRchild = NULL;
//	}
//	CreatBTree(bt->pLchild);
//	CreatBTree(bt->pRchild);
//}
//
////先序遍历
//void PreTraverseTree(BinTree bt)
//{
//	if (bt != NULL)
//	{
//		cout << bt->data << "->";
//		PreTraverseTree(bt->pLchild);
//		PreTraverseTree(bt->pRchild);
//	}
//	else
//		return;
//}
//
////中序遍历
//void InTraverseTree(BinTree bt)
//{
//	if (bt != NULL)
//	{
//		InTraverseTree(bt->pLchild);
//		cout << bt->data << "->";
//		InTraverseTree(bt->pRchild);
//	}
//	else
//		return;
//}
//
////后序遍历
//void PostTraverseTree(BinTree bt)
//{
//	if (bt != NULL)
//	{
//		PostTraverseTree(bt->pLchild);
//		PostTraverseTree(bt->pRchild);
//		cout << bt->data << "->";
//	}
//	else
//		return;
//}
//



// 3. 

///************************
// *
// *
// * 包含头文件
// *
// * *********************/
//#include<stdio.h>
//#include<stdlib.h>
//
// /************************
//  *
//  *
//  * 结构体定义
//  *
//  * **********************/
//typedef struct BTNode
//{
//	char data;
//	struct BTNode* left;
//	struct BTNode* right;
//}BinTree;
//
///************************
// *
// *
// * 构造一个二叉树
// *
// * **********************/
//BinTree* CreateBiTree()
//{
//	int a;
//	BinTree *T;
//	scanf("%d", &a);
//	if (a == 0)
//	{
//		T = NULL;
//
//	}
//	else
//	{
//		T = (BinTree*)malloc(sizeof(BinTree));
//		T->data = a;
//		T->left = CreateBiTree();
//		T->right = CreateBiTree();
//	}
//	return T;//返回根节点
//}
//
///************************
// *
// *
// * 中序遍历
// *
// * **********************/
//void InorderTraversal(BinTree *BT)
//{
//
//	if (BT) {
//		InorderTraversal(BT->left);
//		printf("%d ", BT->data); /* 假设数据为整型 */
//		InorderTraversal(BT->right);
//	}
//}
//
///************************
//*
//*
//* 先序遍历
//*
//* **********************/
//void PreorderTraversal(BinTree *BT)
//{
//
//	if (BT) {
//		printf("%d ", BT->data);
//		PreorderTraversal(BT->left);
//		PreorderTraversal(BT->right);
//	}
//
//}
//
///************************
//*
//*
//* 后序遍历
//*
//* **********************/
//void PostorderTraversal(BinTree *BT)
//{
//	if (BT) {
//		PostorderTraversal(BT->left);
//		PostorderTraversal(BT->right);
//		printf("%d ", BT->data);
//	}
//}
//
//
//
//
///************************
//*
//*
//* 主函数
//*
//* **********************/
//
//void main()
//{
//	BinTree *bt;
//	bt = CreateBiTree();
//	printf("------------先序遍历------------");
//	PreorderTraversal(bt);
//	printf("\n\n\n------------中序遍历------------");
//	InorderTraversal(bt);
//	printf("\n\n\n------------后序遍历------------");
//	PostorderTraversal(bt);
//	printf("\n\n\n");
//}