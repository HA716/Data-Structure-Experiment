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
//                               ����������    ����������  ��������������еĳ���  
Node* CreateTree_PreMid(char* preTree, char* midTree, int len)
{
	Node* tree = (Node*)malloc(sizeof(Node));
	if (!tree)
		return;
	tree->data = preTree[0];   //�������еĵ�һ���������ĸ����
	tree->leftNode = NULL;
	tree->rightNode = NULL;
	if (len == 1)      //��ֻʣһ����㣬��ֱ�ӷ���������
		return tree;

	//leftLen���������Ľ������rightLen���������Ľ������midPos����������ĸ��������������е�λ��
	int  leftLen, rightLen;
	int midPos = 0;
	while (midTree[++midPos] != preTree[0]) {}    //�ҳ���������и��ڵ��λ��

	//��ͼ����
	leftLen = midPos;                   //�����������
	rightLen = len - leftLen - 1;       //�����������,��-1����ΪҪ��ȥ�����ĳ���
									  //  �� �µ���������Ҫȥ��ԭ�ȵĸ����  
	tree->leftNode = CreateTree_PreMid(&preTree[1], midTree, leftLen);                           //��ǰ������ ������
	tree->rightNode = CreateTree_PreMid(&preTree[leftLen + 1], &midTree[leftLen + 1], rightLen); //��ǰ������ ������
	return tree;
}


//************************************************************************************************************************
//                               ����������    ����������  ��������������еĳ���
Node* CreateTree_MidPost(char* midTree, char* postTree, int len)
{

	Node*tree = (Node*)malloc(sizeof(Node));
	tree->data = postTree[len - 1];             //������Ǻ������е����һ�����
	tree->leftNode = NULL;
	tree->rightNode = NULL;

	if (tree == NULL) return;
	if (len == 1) return;         //˵��ֻ��һ������ˣ�ֱ�ӷ���

	int  leftLen, rightLen;
	int midPos = 0;

	while (midTree[midPos] != postTree[len - 1])
	{
		midPos++;
	}

	//��ͼ����
	leftLen = midPos;
	rightLen = len - midPos - 1;

	tree->leftNode = CreateTree_MidPost(midTree, postTree, midPos);
	tree->rightNode = CreateTree_MidPost(&midTree[leftLen + 1], &postTree[leftLen], rightLen);
	//    ��  &midTree[leftLen + 1] �ȼ��� midTree + leftLen + 1
	return  tree;

}




//���ű�ʾ�����������*******************************************************************************************
void Print_KUOHAO(Node* tree)  //��ӡ����������
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


//���뷨���������*******************************************************************************************
//                         ��     �� ��n��k�����������ư����ʾ����ʽ�Ĳ�����
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
	//Ҫ��char*�����Ҫmalloc����ռ�,����Ҫʹ��char[]
	char * pre = (char*)malloc(sizeof(char)*MAX);
	char * mid = (char*)malloc(sizeof(char)*MAX);
	char * post = (char*)malloc(sizeof(char)*MAX);

	//scanf�����ʱ�򣬲��ö�char*���ͼ�'&',���������Ͷ�Ҫ
	printf("������������������");
	scanf_s("%s", pre, MAX);
	printf("������������������");
	scanf("%s", mid, MAX);
	printf("�����������������");
	scanf("%s", post, MAX);


	int len = strlen(pre);
	int len2 = strlen(mid);

	//���������򴴽�������
	Node* tree_pre_mid = CreateTree_PreMid(pre, mid, len);
	Node* tree_mid_post = CreateTree_MidPost(mid, post, len2);

	//���ű�ʾ�����������+���򣩶�����
	printf("\n�ɣ�����+���򣩴����Ķ�����:\n");
	Print_KUOHAO(tree_pre_mid);

	//�����ʾ�����������+���򣩶�����
	printf("\n�ɣ�����+���򣩴����Ķ�����:\n");
	Print_AORU(tree_mid_post, 14, 1);
	return 0;
}





















