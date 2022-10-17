#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct myLinkNode
{
	struct myLinkNode * next;
}LinkNode;

typedef struct myLinkList1
{
	LinkNode header;  //�˴���Ҫ�Žṹ��ָ�룬������Ҫ��������ڴ�
	int size;
}LinkList;

//�Ƚϻص�-----------------------------------------------------------------------------------------------------------------------------------------
typedef int(*COMPARENODE)(LinkNode*, LinkNode*);    //!!! �˴����뷵��ֵ��int���ͣ�������void������ �ҵ���ֵҲ�ò����Ǹ�λ��
//��ӡ�ص�
typedef void(*PRINTNODE)(LinkNode*);


//��ʼ������-----------------------------------------------------------------------------------------------------------------------------------------
LinkList * Init()
{
	LinkList * list = (LinkList*)malloc(sizeof(LinkList));
	list->header.next = NULL;
	list->size = 0;

	return list;
}


//������-----------------------------------------------------------------------------------------------------------------------------------------
void Insert(LinkList*list, int pos, LinkNode* node)
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
		pos = list->size; //Ĭ��β������
	}
	//LinkNode * pCurrent2 = list->header.next;   //ָ��ͷ������һ��λ�ã����������������pos�κ�pCurrent2ʵ�ʾ�ָ��pos��
	LinkNode * pCurrent = &(list->header);      //ָ��ͷ��㣬�����������pos�κ�pCurrentʵ��ָ��pos-1��

	for (int i = 0; i < pos; i++)               //�ҵ�pos����ǰһ����㣬��pos-1��
	{
		pCurrent = pCurrent->next;
	}

	//�����½��
	node->next = pCurrent->next;
	pCurrent->next = node;

	list->size++;

}

//���� λ�� ɾ��-----------------------------------------------------------------------------------------------------------------------------------------
void removePos(LinkList*list, int pos)
{
	if (list == NULL)
	{
		return;
	}
	if (pos<0 || pos>list->size)
	{
		pos = list->size;
	}
	LinkNode*pCurrent = &(list->header);   //��ָ��ͷ���
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;       //����pos-1��
	}

	//ɾ����㣨�������޷��ͷ���ɾ�������ڴ棩
	pCurrent->next = pCurrent->next->next;

	list->size--;

}


//���� ֵ ɾ��-----------------------------------------------------------------------------------------------------------------------------------------
void removeValue(LinkList*list, LinkNode*node, COMPARENODE compare)  //COMPARENODE������ֵΪvoid*,����Ϊ(LinkNode*, LinkNode*)�ĺ���ָ�����ͣ�
                                                                    //  ��compare�Ǻ���ָ������COMPARENODE�����ĺ���ָ�����
{
	if (list == NULL)
	{
		return;
	}
	if (node == NULL)
	{
		return;
	}
	LinkNode*pCurrent = list->header.next;

	int index = 0;
	while (pCurrent != NULL)
	{
		if (compare(pCurrent, node))
		{
			break;
		}
		pCurrent = pCurrent->next;   //�ҵ���break,û�ҵ��ͼ�������
		index++;
	}

	//�����λ��ʱ��pCurrentָ����Ҫɾ�����Ǹ�ֵ���ڵ�λ��

	//ɾ����㣨�������޷��ͷ���ɾ�������ڴ棩
	pCurrent->next = pCurrent->next->next;

	list->size--;



}


//����
int Find(LinkList*list, LinkNode*node, COMPARENODE compare)
{
	
	if (list == NULL)
	{
		return;
	}
	if (node == NULL)
	{
		return;
	}
	LinkNode*pCurrent = list->header.next;   //ָ���һ����Чֵ
	int index = 0;  //index�������汻�ҵ���ֵ��λ��
	int flag = -1;
	while (pCurrent != NULL)
	{
		if(compare(pCurrent, node)==1)
		{
			flag = index;
			break;
		}
		pCurrent = pCurrent->next;    //���� ��������ƶ�
		index++;
	}

	return flag;




}



//��ӡ-----------------------------------------------------------------------------------------------------------------------------------------
void Print(LinkList*list, PRINTNODE Print)
{
	if (list == NULL)
	{
		return;
	}
	LinkNode*pCurrent = list->header.next;     //pCurrentָ������ĵ�һ����Чֵ�����ڶ������
	while (pCurrent != NULL)
	{
		Print(pCurrent);    //���ûص�����
		pCurrent = pCurrent->next;
	}

}


//�ͷ�-----------------------------------------------------------------------------------------------------------------------------------------
void Free(LinkList* list)
{
	if (list != NULL)
	{
		return;
	}
	free(list);

}

//����-------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct Person666
{
	LinkNode * node;   //ͷ���
	char name[64];
	int age;
}Person;

void printPerson(LinkNode*node) //��Ϊ����λ�ô���ֵ��LinkNode* ���ͣ���������β�Ҳ������LinkNode*����     //���ڻص��ĺ���
{
	Person *p = (Person*)node;
	printf("���� : %s     ���� ��%d  \n", p->name, p->age);
}

void comparePerson(LinkNode*node1, LinkNode*node2)                                                          //���ڻص��ĺ���
{
	Person*p1 = (Person*)node1;
	Person*p2 = (Person*)node2;
	if ((p1->name== p2->name) && (p1->age == p2->age))    //�ж��Ƿ���ȣ���Ⱦʹ����ҵ���   
	{
		return 1;
	}
	else return -1;
}


int main()
{
  
	//�ȳ�ʼ������
	LinkList *list = Init();

	//��������
	Person p1, p2, p3;
	strcpy(p1.name, "����");
	strcpy(p2.name, "����");
	strcpy(p3.name, "����");
	p1.age = 10;
	p2.age = 20;
	p3.age = 30;


	//������
	Insert(list, 0,(LinkNode* ) &p1);   //�����β���LinkNode*���ͣ����Դ˴�ҪǿתΪLinkNode *����
	Insert(list, 0, (LinkNode*)&p2);
	Insert(list, 0, (LinkNode*)&p3); //����λ�ô��ɣ�����

	Print(list, printPerson);  // �˴������Ǻ�����ַ printPerson


	//ɾ�� λ�� ɾ��
	removePos(list, 0);
	Print(list, printPerson);

	//���� ֵ ɾ��
	removeValue(list, &p2, comparePerson);
	Print(list, printPerson);

	//����
	printf("%d",Find(list, &p2, comparePerson));










}












