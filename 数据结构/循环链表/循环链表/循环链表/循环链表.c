#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
//------------------------------------------------------------------------------------------------------------------------------------------
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

//���� λ�� ɾ��------------------------------------------------------------------------------------------------------------------------------------------
void RemovePos(LinkList*list, int pos)
{
	if (list == NULL)
	{
		return;
	}
	if (pos < 0 || pos >= list->size)
	{
		return;
	}

	LinkNode *pCurrent = &(list->header);
	for (int i = 0; i < pos; i++) //�ҵ�pos��ǰһ����㴦 ����pos-1�� ��Ϊͷ���û��ֵ�����Ա���һ��֮����ҵ���һ����ֵ�Ľ�㣬��������ĵڶ������
	{
		pCurrent = pCurrent->next;
	}

	LinkNode*pNext = pCurrent->next;  //�ȱ��������ɾ������λ��
	pCurrent->next = pNext->next;     //ɾ��pos���Ľ�� 

	list->size--;
}


//���� ֵ ɾ��------------------------------------------------------------------------------------------------------------------------------------------
void RemoveValue(LinkList*list, LinkNode*node, COMPARENODE compare)  //compare�����ж��㴫���ֵ�������д�ɾ����ֵ�Ƿ����
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

//������-------------------------------------------------------------------------------------------------------------------------------------------
int Size(LinkList*list)
{
	return list->size;
}



//����------------------------------------------------------------------------------------------------------------------------------------------
void Find(LinkList* list, LinkNode* node, COMPARENODE compare)
{
	if (list == NULL)
	{
		return;
	}
	if (node)
	{
		return;
	}
	int flag = -1; 

	LinkNode*pCurrent = list->header.next;    //pCurrentָ��ͷ������һ��λ�ã���Ϊ���λ�ò���ֵ
	for (int i = 0; i < list->size; i++)      //ʹpCurrentָ��ǰ i ����λ��
	{
		if (compare(pCurrent, node) == 1)
		{
			flag = i;   //��Ǵ����ҵ���λ��
			return;
		}
		//���û�ҵģ��Ϳ���һ��λ��
		pCurrent = pCurrent->next;
	}

	return  flag;  //���ر��ҵ�λ�ã�û�ҵ��ͷ���-1
}

//��ӡ------------------------------------------------------------------------------------------------------------------------------------------
void Print(LinkList *list, PRINTNODE myPrint)
{
	if (list == NULL)
	{
		return;
	}

	LinkNode*pCurrent = list->header.next;  //��������ֵ�������㿪ʼ����
	for (int i = 0; i < list->size*2; i++)  //�˴�size*2�����ӡ������������֤���������ѭ����
	{
		if (pCurrent->next == &(list->header)) //��ֹѭ����ʱ�� pCurrentָ��ͷ��㣬���´���
		{
			pCurrent->next=list->header.next;  //����ͷ���
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


//-----------------------------------------------------------------------------------------------------------------------------------------------

typedef struct Person1
{
	LinkNode node;
	char name[64];
	int age;
}Person;

//����ɾ���Ļص�����
void printPerson (LinkNode * node)      
{
	Person * p = (Person*)node;  //��Ϊ�����ӡ��Ҫ������ת��Person����
	printf("������%s   ���䣺%d  \n", p->name, p->age);
}

//���ڱȽϵĻص�����
void comparePerson(LinkNode * node1, LinkNode * node2)
{
	Person * p1 = (Person*)node1;   //�������Ǹ�����ͬ��
	Person * p2 = (Person*)node2;

	if (p1->name == p2->name&&p1->age == p2->age)
	{
		return 1;  // 1 ��ʾ�Ա���ͬ�����ҵ���
	}
	else return -1;
}

int main()
{
	Person p1, p2, p3;
	strcpy(p1.name, "����");
	strcpy(p2.name, "����");
	strcpy(p3.name, "����");

	
	p1.age = 10;
	p2.age = 20;
	p3.age = 30;

	//��ʼ������
	LinkList * list = Init();
	
	//����
	Insert(list, 100, &p1);  //��Ϊ100������Ч���ȣ�������Ĭ��β��������
	Insert(list, 100, &p2);
	Insert(list, 100, &p3);

	//��ӡ
	Print(list,printPerson);
	printf("%s \n", "-----------------------------------------------");
	//ɾ��p3
	remove(list, p3, comparePerson);
	Print(list, printPerson);
	printf("%s", "-----------------------------------------------");


}











