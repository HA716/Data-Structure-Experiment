#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable :4996)


//  ������ڣ� ����� # �޷���ʶ��  --> �ĳɵ����ź����� ���������޷��������

typedef struct  BINARYNODE
{
	char ch;
	struct BINARYNODE * leftNode;
	struct BINARYNODE * rightNode;
}BinaryNode;


BinaryNode * CreateNode()
{
	char ch;
	BinaryNode * node;//�������Ľڵ�
	scanf("%c", &ch);

	
	      //ֻ���õ����š�����ֻ�е����Ŵ����ַ�������ASCLL���ʾ�������˫����""�ͱ���ַ�����,�������������ʽ
	if (ch == '#')    //���뾮��#�ʹ���Ϊ��������������ΪNULL
	{
		node = NULL;
	}
	else
	{
	    node=(BinaryNode *)malloc(sizeof(BinaryNode));  

		//ʵ�����Ľڵ㣺��һ����Ҫ�Ǹ������������ԭ����в�����
		node->ch = ch;                  //�ڵ������
		node->leftNode=CreateNode();  //�ݹ飬��������������
		node->rightNode= CreateNode(); //�ݹ飬����������

	}

	return node;

}


//�ݹ������
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
 * �������Ķ�������ṹ�Ĵ�������ز���
 * 1.���򷨴���������
 * 2.�������
 * 3.�������
 * 4.�������
 * ˵����������ΪҶ�ӽ�㣬ֻ�轫���Һ��ӵ�ֵ��Ϊ'#',(������֮�����������Ϊ'#');
 * ���磺���룺a b # # c # # ,�õ���aΪ����㣬bΪ���ӣ�cΪ�Һ��ӵĶ�������
 */

// //���������ṹ��
//typedef struct BTNode
//{
//	char data;
//	struct BTNode *pLchild, *pRchild;
//}BTNode, *BinTree;
//
////��������
//void CreatBTree(BinTree&);       //����������
//void PreTraverseTree(BinTree);   //�������
//void InTraverseTree(BinTree);    //�������
//void PostTraverseTree(BinTree);  //�������
//
////main����
//int main()
//{
//	BTNode* pBintree = NULL;
//	CreatBTree(pBintree);
//	cout << "���������";
//	PreTraverseTree(pBintree);
//	cout << "\n���������";
//	InTraverseTree(pBintree);
//	cout << "\n���������";
//	PostTraverseTree(pBintree);
//	return 0;
//}
//
////������������
//void CreatBTree(BinTree& bt)
//{
//	char val;
//	cout << "��������ֵ��";
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
////�������
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
////�������
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
////�������
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
// * ����ͷ�ļ�
// *
// * *********************/
//#include<stdio.h>
//#include<stdlib.h>
//
// /************************
//  *
//  *
//  * �ṹ�嶨��
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
// * ����һ��������
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
//	return T;//���ظ��ڵ�
//}
//
///************************
// *
// *
// * �������
// *
// * **********************/
//void InorderTraversal(BinTree *BT)
//{
//
//	if (BT) {
//		InorderTraversal(BT->left);
//		printf("%d ", BT->data); /* ��������Ϊ���� */
//		InorderTraversal(BT->right);
//	}
//}
//
///************************
//*
//*
//* �������
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
//* �������
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
//* ������
//*
//* **********************/
//
//void main()
//{
//	BinTree *bt;
//	bt = CreateBiTree();
//	printf("------------�������------------");
//	PreorderTraversal(bt);
//	printf("\n\n\n------------�������------------");
//	InorderTraversal(bt);
//	printf("\n\n\n------------�������------------");
//	PostorderTraversal(bt);
//	printf("\n\n\n");
//}