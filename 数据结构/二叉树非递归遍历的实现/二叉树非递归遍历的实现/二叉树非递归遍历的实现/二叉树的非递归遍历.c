#include "ջ����ʽ�洢.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//����������
typedef struct BINARYNODE
{
	char ch;
	struct BINARYNODE * leftNode;
	struct BINARYNODE * rightNode;
}BinaryNode;

//Ϊ�˶������Ľڵ���ӱ�־��falg������Ҫ���·�װ�������ֽڵ�
typedef struct BITREENODE
{
	StackNode node;       //��ϵ�������Ľڵ�
	BinaryNode * root;    //���������ڵ�
	int flag;             //��ǽڵ���ܷ��������flag==1�������0�����
}BiTreeNode;

//����ջ����Ľڵ�
BiTreeNode * CreatNode(BinaryNode * node, int flag)
{
	BiTreeNode * newNode = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	newNode->root = node;
	newNode->flag = flag;

	return newNode;
}

//�ǵݹ����
void NonRecursion(BinaryNode * root)
{
	//�ȴ���ջ
	LStack *stack = Init();
	//�����������ڵ�
	BiTreeNode* newNode = CreatNode(root, 0);  //0��ζ��Ĭ�ϲ��ɼ�

	//�ýڵ���ջ
	Push(stack, (StackNode*)newNode);

	while (stack->size > 0)
	{
		//�õ�ջ��Ԫ��
		BiTreeNode * topNode = (BiTreeNode*)TopElement(stack);
		//����ջ��Ԫ��
		Pop(stack);
		 //�ж�ջ��Ԫ���Ƿ�Ϊ��
		if (topNode->root == NULL)
		{
			continue;   //�����˴�ѭ��
		}
		//�ж�ջ��Ԫ���ܷ����
		if (topNode->flag == 1)
		{
			printf("%c", topNode->root->ch);
		}
		//
		else  //��topNode->flag == 0  -->�����������ô�͸��ݱ�������Ҫ������ѹջ
			  //������������� �������� �� ��ôѹջ˳����� �ҡ��󡢸�
		{
			Push(stack, (StackNode*)topNode->root->rightNode);  //���ҽڵ�ѹ��ջ
			Push(stack, (StackNode*)topNode->root->leftNode);   //����ڵ�ѹ��ջ
			topNode->flag = 1;           //��һ������0����������ѹջ����1
			Push(stack, (StackNode*)topNode->root);             //�����ڵ�ѹ��ջ
		}

	}




}






//����������
void Print(BinaryNode * root)
{
	if (root == NULL)
	{
		return NULL;
	}

	//�������
	printf("%c", root->ch);
	Print(root->leftNode);     //����˼�� �ݹ�Ĺ���
	Print(root->rightNode);

}


/*��������ͼ
              A
         B          F
            C          G
          D  E        H
 */


//��ʼ��������
BinaryNode  CreatBinaryTree()
{
	//�����ڵ�
	BinaryNode nodeA = { 'A',NULL,NULL };
	BinaryNode nodeB = { 'B',NULL,NULL };
	BinaryNode nodeC = { 'C',NULL,NULL };
	BinaryNode nodeD = { 'D',NULL,NULL };
	BinaryNode nodeE = { 'E',NULL,NULL };
	BinaryNode nodeF = { 'F',NULL,NULL };
	BinaryNode nodeG = { 'G',NULL,NULL };
	BinaryNode nodeH = { 'H',NULL,NULL };

	//�����������ڵ�����ϵ
	nodeA.leftNode = &nodeB;
	nodeA.rightNode = &nodeF;

	nodeB.rightNode = &nodeC;

	nodeC.leftNode = &nodeD;
	nodeC.rightNode = &nodeE;

	nodeF.rightNode = &nodeG;
	nodeG.leftNode = &nodeH;

	//����������
	//Print(&nodeA);

   NonRecursion(&nodeA);
	//return nodeA;

}









int main()
{
	CreatBinaryTree();
}












