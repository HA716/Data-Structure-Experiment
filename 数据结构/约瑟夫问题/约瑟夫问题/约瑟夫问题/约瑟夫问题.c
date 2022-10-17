#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

// �� 8 ���ˣ�������3��ʱ�����һ���˳���
#define M 8 
#define N 3

typedef struct LinkNode1  //����������ṹ��������ı�������Ҫ����struct
{
	struct LinkNode1 * next;  //����ط�����Ҫ������д�������� LinkNode  ��Ϊ��ⲻ��
}LinkNode;
typedef struct LinkList1
{
	LinkNode header;         //ͷ���
	int size;
}LinkList;

//------------------------------------------------------------------------------------------------------------------------------------------
//�Ƚϻص�
typedef int(*COMPARENODE)(LinkNode*, LinkNode*); //???ʲô��˼ �ص������������ж��Ƿ����
//��ӡ�ص�
typedef int(*PRINTNODE)(LinkNode*);


//��ʼ������------------------------------------------------------------------------------------------------------------------------------------------
LinkList * Init()
{
	LinkList *list = (LinkList*)malloc(sizeof(LinkList));  //Ϊͷ��㿪�ٿռ�
	list->header.next = &(list->header);   //��ʼ��ʱ��ͷ����nextָ��ָ��ͷ��㱾��
	list->size = 0;

	return list;
}


//����------------------------------------------------------------------------------------------------------------------------------------------------
void Insert(LinkList*list, int pos, LinkNode* node)  //node���Ǵ����������
{
	if (list == NULL)
	{
		return;
	}
	if (node == NULL)
	{
		return;
	}
	if (pos<0 || pos>list->size)
	{
		pos = list->size;       //Ĭ��β������
	}
	LinkNode * pCurrent = &(list->header);    //pCurrentָ��ָ��ͷ���

	for (int i = 0; i < pos; i++)  //�ҵ�pos����ǰһ��λ�ã���pos-1��
	{
		pCurrent = pCurrent->next;
	}

	//�����½��
	node->next = pCurrent->next;
	pCurrent->next = node;

	list->size++;
}


//���ص�һ��Ԫ��------------------------------------------------------------------------------------------------------------------------------------------
LinkNode* FirstElem(LinkList*list)
{
	return list->header.next;    //��Ϊͷ���û�����ݣ����� ͷ����next ��ָ�ĵط����ǵ�һ��Ԫ�ص�λ��
}

//���� ֵ ɾ��------------------------------------------------------------------------------------------------------------------------------------------
void  RemoveValue(LinkList*list, LinkNode*node, COMPARENODE compare)  //compare�����ж��㴫���ֵ�������д�ɾ����ֵ�Ƿ����
{
	if (list == NULL)
	{
		return;
	}
	if (node)
	{
		return;
	}
	LinkNode* pCurrent1 = &(list->header);  //ָ��ͷ��㣬û��ֵ
	LinkNode* pCurrent2 = list->header.next; //ָ��ͷ������һ�����,��ֵ
	int i = 0;
	for (i = 0; i < list->size; i++)
	{
		if (compare(pCurrent2, node) == 1)  //�ص��������Ƚ�node�뵱ǰλ��pCurrent2�Ƿ���ͬ������ͬ�򷵻�1����ʾ�ҵ���
		{
			pCurrent1->next = pCurrent2->next;  //ɾ��pCurrent2��ָ�Ľ��
			list->size--;
			break;
		}
		//���û�ҵ����Ͳ��Ϻ���ָ��
		pCurrent1 = pCurrent2;
		pCurrent2 = pCurrent2->next;
	}
}


//��ӡ------------------------------------------------------------------------------------------------------------------------------------------
void Print(LinkList *list, PRINTNODE myPrint)
{
	if (list == NULL)
	{
		return;
	}

	LinkNode*pCurrent = list->header.next;  //��������ֵ�������㿪ʼ����
	for (int i = 0; i < list->size ; i++) 
	{
		if (pCurrent->next == &(list->header)) //��ֹѭ����ʱ�� pCurrentָ��ͷ��㣬���´���
		{
			pCurrent->next = list->header.next;  //����ͷ���
		}
		myPrint(pCurrent);
		pCurrent = pCurrent->next;
	}

}


//�ͷ�-----------------------------------------------------------------------------------------------------------------------------------------------------
void Free(LinkList* list)
{
	if (list == NULL)
	{
		return;
	}
	free(list);
}

//Լɪ�����������������������������������������������������������������������������������������������������������
typedef struct MYNUM
{
	LinkNode  node;
	int val;
}MyNum;

void PrintMyNum(LinkNode* node)
{
	MyNum* num = (MyNum*)node;      //node����MyNum���ͣ��ȱ�ת����LinkNode* ,�˴��ֱ�ת��MyNum
	printf("%d   ", num->val);
}

void CompareMyNum(LinkNode* node1, LinkNode* node2)
{
	MyNum*num1 = (MyNum*)node1;
	MyNum*num2 = (MyNum*)node2;
	if (num1->val == num2->val)     //�Աȳɹ� ������ 1
	{
		return 1;
	}

	else return -1;
}


void deleteNum(LinkList*list)
{
	int index = 1;    //index�Ǽ������ã���index=N ʱ����һ�������У�ͬʱ�����Ҫ��ɾ��
	LinkNode* pCurrent = list->header.next;  //ָ���һ����Чֵ
	printf("\n");
	while (list->size > 1)      //Լɪ�����������Ŀ�ľ��� �˲��ϳ��У����ֻʣһ����
	{
		if (index == N)  //��ʱ�������Ҫ���У�ͬʱɾ�����ֵ
		{
			MyNum* temp = (MyNum*)pCurrent;
			printf("%d", temp->val);          //�����Ҫ���е���

		

			//ɾ��������е�ֵ
			//�ȼ�¼��ɾ��������һ��λ��
			LinkNode*pNext = pCurrent->next;

			//���� ֵ ɾ��
			RemoveValue(list, pCurrent, CompareMyNum);      // ���������ִ�� size--
			//ָ�����
			pCurrent = pNext;
			//ָ����ƵĹ����п�������ͷ��㣬��Ҫ����
			if (pCurrent == &(list->header))
			{
				pCurrent = pCurrent->next;  //���pCurrentָ����ͷ��㣬������ͷ���
			}
			index = 1;  //ÿ����һ�Σ������û�1
		
		}

		//��ʱindex!=N������ָ��������ƣ��迼��ͷ���������
		pCurrent = pCurrent->next;
		if (pCurrent == &(list->header))
		{
			pCurrent = pCurrent->next;  //���pCurrentָ����ͷ��㣬������ͷ���
		}

		index++;  //  !!!
	}

	if (list->size == 1)   //Լɪ�������������
	{
		LinkNode * temp = FirstElem(list);  //ȡ�����һ��Ԫ��
		MyNum * element = (MyNum*)temp;
		printf("%d  ", element->val);
	}





}


int main()
{
	//��ʼ������ 
	LinkList*list = Init();
	MyNum  num[M];         //��� 8 ���˵�����(ע������)
	for (int i = 0; i < M; i++)
	{
		num[i].val = i + 1;    // 1��2��3��4��5��6��7��8
		Insert(list, i, (LinkNode*)&num[i]); // �������е�ÿ��Ԫ����Ϊһ�������뵽������
	}

	Print(list, PrintMyNum);


	deleteNum(list);

	Print(list, PrintMyNum);


}









