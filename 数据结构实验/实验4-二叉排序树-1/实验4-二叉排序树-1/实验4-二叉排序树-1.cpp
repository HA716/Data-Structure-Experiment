#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MIN  -256;
typedef struct NODE
{
	int key;
	struct NODE*lchild;
	struct NODE*rchild;
}BSNode;


//***********************************************************
//bool InsertBST(BSNode**bt, int key)
//{
//	//��Ϊ���������½�����
//	if (*bt == NULL)
//	{
//		(*bt) = (BSNode*)malloc(sizeof(BSNode));
//		(*bt)->key = key;
//		(*bt)->lchild = NULL;
//		(*bt)->rchild = NULL;
//		return true;
//	}
//	//�����д�����ͬ�ؼ��ֵĽ�㣬�򷵻ؼ�
//	else if (key == (*(*bt)).key)
//	{
//		return false;
//	}
//	else if (key < (*(*bt)).key)
//		InsertBST(&(*bt)->lchild, key);
//	else
//		InsertBST(&(*bt)->rchild, key);
//}
//
//void CraeteBST(BSNode**bt,int arr[], int n)
//{
//	//BSNode*bt = NULL;
//	//bt->key = arr[0];
//	
//	int i = 0;
//	while (i < n)
//	{
//		InsertBST(bt,arr[i]);
//		i++;
//	}
//	//return bt;
//}
//
//
//void Print_KUOHAO(BSNode*bt)
//{
//	if (bt != NULL)
//		printf("%d", bt->key);
//
//	if (bt->lchild != NULL || bt->rchild != NULL)
//	{
//		printf("(");
//		if (bt->lchild != NULL)
//		{
//			Print_KUOHAO(bt->lchild);
//		}
//		if (bt->rchild != NULL)
//		{
//			printf(",");
//			Print_KUOHAO(bt->rchild);
//		}
//		printf(")");
//	}
//
//
//}
//
//
//void Pre(BSNode*bt)
//{
//	if (bt != NULL)
//	{
//		printf("%d", bt->key);
//		Pre(bt->lchild);
//		Pre(bt->rchild);
//	}
//	
//
//}


//***********************************************************
bool InsertBST(BSNode*&bt, int key)
{
	//��Ϊ���������½�����
	if (bt == NULL)
	{
		bt = (BSNode*)malloc(sizeof(BSNode));
		bt->key = key;
		bt->lchild = NULL;
		bt->rchild = NULL;
		return true;
	}
	//�����д�����ͬ�ؼ��ֵĽ�㣬�򷵻ؼ�
	else if (key == bt->key)
	{
		return false;
	}
	else if (key < bt->key)
		InsertBST(bt->lchild, key);
	else
		InsertBST(bt->rchild, key);
}

BSNode* CraeteBST(int arr[], int n)
{
	BSNode*bt = NULL;
	int i = 0;
	while (i < n)
	{
		InsertBST(bt, arr[i]);
		i++;
	}
	return bt;
}

//�ݹ����
BSNode*SearchBST_1(BSNode*bt, int key)
{
	if (bt == NULL || bt->key == key)
	{
		return bt;
	}
	printf("->%d", bt->key);
	if (key < bt->key)
	{
		SearchBST_1(bt->lchild, key);
	}
	else
	{
	    SearchBST_1(bt->rchild, key);
	}
}



//�ǵݹ����
void SearchBST_2(BSNode*bt, int key)
{
	//������ֱ�ӷ���
	if (bt == NULL)
	{
		return;
	}
	while(bt!=NULL)
	{
		printf("->%d", bt->key);
		if (bt->key == key)
		{	
			return ;
		}
		else if (bt->key > key)
		{
			bt = bt->lchild;
		}
		else if (bt->key < key)
		{
			bt = bt->rchild;
		}

	}

}


//�ж��Ƿ����������
bool isBSTree(BSNode*bt)
{
	int prev = MIN;
	bool flag = true;
	if (bt->lchild != NULL && flag)
	{
		isBSTree(bt->lchild);
	}
	if (bt->key < prev)
	{
		flag = false;
	}
	prev = bt->key;
	if (bt->rchild != NULL && flag)
	{
		isBSTree(bt->rchild);
	}
	return flag;
}





//ɾ��:p�Ǵ�ɾ�����
void Delete_1(BSNode*p, BSNode*&r)
{//p�Ǵ�ɾ�����,r��p������
 //������������������������ɾ��������ֵ���Ľ��
	BSNode*temp;
	if (r->rchild != NULL)
	{
		Delete_1(p, r->rchild);
	}
	else
	{
		p->key = r->key;
		temp = r;
		r = r->lchild;
		
		free(temp);
		temp = NULL;
		
	}
}

void Delete(BSNode*&p)
{
	//BSNode*p = (BSNode*)malloc(sizeof(BSNode));
	//p->key = key;
	//p->lchild = p->rchild = NULL;

	BSNode*temp;
	if (p->lchild == NULL && p->rchild == NULL)
	{//Ҷ�ӽ�㣬ֱ��ɾ��
		temp = p;
		free(temp);
	}
	if (p->rchild == NULL)  
	{//��pû��������������p�����������
		temp = p;
		p = p->lchild;
	
		free(temp);
		temp = NULL;

	}
	else if (p->lchild == NULL)
	{//��pû��������������p���ҽ�������
		temp = p;
		p = p->rchild;
		
		free(temp);
		temp = NULL;
	
	}
	else
	{//��������������������
		Delete_1(p, p->lchild);
	}





}


void Print_KUOHAO(BSNode*&bt)
{
	/*if (bt == NULL)
	{
		printf("NULL");
	}*/
	if (bt != NULL)
	{
		printf("%d", bt->key);
	}


	if (bt->lchild != NULL || bt->rchild != NULL)
	{
		printf("(");
		if (bt->lchild != NULL)
		{
			Print_KUOHAO(bt->lchild);
		}
		if (bt->rchild != NULL)
		{
			printf(",");
			Print_KUOHAO(bt->rchild);
		}
		printf(")");
	}
}


void Pre(BSNode*&bt)
{
	if (bt != NULL)
	{
		printf("%d", bt->key);
		Pre(bt->lchild);
		Pre(bt->rchild);
	}
}





//***********************************************************
int main()
{
	//BSNode*bt = (BSNode*)malloc(sizeof(BSNode));
	int arr[] = { 4,9,0,1,8,6,3,5,2,7};
	int n = sizeof(arr) / sizeof(arr[0]);
	BSNode*bt;
	bt=CraeteBST(arr,n);
	Print_KUOHAO(bt);
	printf("\n");


	BSNode*find_1 = (BSNode*)malloc(sizeof(BSNode));
	BSNode*find_2 = (BSNode*)malloc(sizeof(BSNode));
	BSNode*find_3 = (BSNode*)malloc(sizeof(BSNode));
	printf("�ǵݹ飺");
	SearchBST_2(bt, 6);
	printf("\n�ݹ飺");
	find_1 = SearchBST_1(bt,6);
	printf("->%d\n", find_1->key);

	bool flag = isBSTree(bt);
	if (flag == true)
	{
		printf("���Ƕ���������\n");
	}
	else
		printf("�ⲻ�Ƕ���������\n");

	BSNode*p1;
	find_2 = SearchBST_1(bt, 4);
	Delete(find_2);


	printf("ɾ��4��");
	Print_KUOHAO(bt);


}
















