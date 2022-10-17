
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)


//������������Ľṹ�壺
typedef struct BINARYNODE
{
	char ch;      //����������
	struct BINARYNODE * leftNode;       //ָ�� ��ڵ� ��ָ��
	struct BINARYNODE * rightNode;      //ָ�� �ҽڵ� ��ָ��

}BinaryNode;



//�������ĵݹ����
void recursion(BinaryNode *root)  //������ڵ�
{
	//�ݹ����������
	if (root == NULL)
	{
		return;
	}
	//�������
	printf("%c", root->ch);
	recursion(root->leftNode);      //����������
	recursion(root->rightNode);     //����������

	////�������
	//recursion(root->leftNode);
	//printf("%c", root->ch);
	//recursion(root->rightNode);

	////�������
	//recursion(root->leftNode);
	//recursion(root->rightNode);
	//printf("%c", root->ch);
}


//���� Ҷ����Ŀ
void calculateLeaf(BinaryNode *root, int * num)
{
	if (root == NULL)
	{
		return;
	}
	if (root->leftNode == NULL && root->rightNode == NULL)    //�ж��Ƿ�Ϊ Ҷ��
	{
		(*num)++;
	}
	calculateLeaf(root->leftNode, num);   //�ݹ飬�ȼ�����ڵ��Ҷ��
	calculateLeaf(root->rightNode, num);  //�ݹ飬�ټ����ҽڵ��Ҷ��

}

//�������ĸ߶�
int Height(BinaryNode *root)   //������ڵ�
{
	if (root == NULL)
	{
		return 0;
	}
	int leftHeight = Height(root->leftNode);     //�������߶�
	int rightHeight = Height(root->rightNode);   //�������߶�

	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1; //ȡ�ֵܽڵ��У��߶ȸ��ߵ��Ǹ�+1 �������������

}


//�Զ������Ŀ������ȿ������������ٿ������������ٴ����½ڵ㣬��󷵻��½ڵ�
BinaryNode * CopyTree(BinaryNode* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	 
	BinaryNode * LeftTree = CopyTree(root->leftNode);      //��������Ŀ���
	BinaryNode * RightTree = CopyTree(root->rightNode);    //���Ҳ����Ŀ���
	//���������д��룬���Ƶ���ײ㣬Ҳ����Ҷ�ӵ�λ��ʱ����ִ�оͻ����root=NULL�����������return,���ٵ��ƣ����ִ���������

	//�����½��
	BinaryNode *newNode = (BinaryNode*)malloc(sizeof(BinaryNode));
	newNode->ch = root->ch;
	newNode->leftNode = LeftTree;
	newNode->rightNode = RightTree;

	//�����½��
	return newNode;

}

//�ͷ��ڴ�
void Free(BinaryNode* root)
{
	if (root == NULL)
	{
		return;
	}
	//���ͷ�������
	free(root->leftNode);
	//���ͷ�������
	free(root->rightNode);
	//����ͷŸ��ڵ�
	free(root);

}



//��������������
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

	//������֪��Ϣ�������ڵ��Ĺ�ϵ
	nodeA.leftNode = &nodeB;
	nodeA.rightNode = &nodeF;

	nodeB.rightNode = &nodeC;

	nodeC.leftNode = &nodeD;
	nodeC.rightNode = &nodeE;

	nodeF.rightNode = &nodeG;

	nodeG.leftNode = &nodeH;

	//1.����������
/*	recursion(&nodeA);*/ 


	////2.��¼Ҷ������
	//int num = 0;   
	//calculateLeaf(&nodeA, &num);
	//printf("\nҶ����ĿΪ ��%d", num);

	////3.��¼���ĸ߶�
	//int height= Height(&nodeA);
	//printf("\n�������Ϊ ��%d", height);

	//4.�Զ������Ŀ���
	BinaryNode * newNode = CopyTree(&nodeA);
	recursion(newNode);

    //�ͷŶ�����
	Free(newNode);

	return;
}

int main()
{
	 test();
	


}
















