#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct myLinkNode
{
	struct myLinkNode * next;
}LinkNode;

typedef struct myLinkList1
{
	LinkNode header;  //此处不要放结构体指针，否则需要另外分配内存
	int size;
}LinkList;

//比较回调-----------------------------------------------------------------------------------------------------------------------------------------
typedef int(*COMPARENODE)(LinkNode*, LinkNode*);    //!!! 此处必须返回值是int类型，不能是void，否则 找到了值也拿不到那个位置
//打印回调
typedef void(*PRINTNODE)(LinkNode*);


//初始化链表-----------------------------------------------------------------------------------------------------------------------------------------
LinkList * Init()
{
	LinkList * list = (LinkList*)malloc(sizeof(LinkList));
	list->header.next = NULL;
	list->size = 0;

	return list;
}


//插入结点-----------------------------------------------------------------------------------------------------------------------------------------
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
		pos = list->size; //默认尾部插入
	}
	//LinkNode * pCurrent2 = list->header.next;   //指向头结点的下一个位置，所以下面遍历遍历pos次后，pCurrent2实际就指向pos处
	LinkNode * pCurrent = &(list->header);      //指向头结点，所以下面遍历pos次后，pCurrent实际指向pos-1处

	for (int i = 0; i < pos; i++)               //找到pos处的前一个结点，即pos-1处
	{
		pCurrent = pCurrent->next;
	}

	//插入新结点
	node->next = pCurrent->next;
	pCurrent->next = node;

	list->size++;

}

//根据 位置 删除-----------------------------------------------------------------------------------------------------------------------------------------
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
	LinkNode*pCurrent = &(list->header);   //先指向头结点
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;       //到了pos-1处
	}

	//删除结点（坏处：无法释放已删除结点的内存）
	pCurrent->next = pCurrent->next->next;

	list->size--;

}


//根据 值 删除-----------------------------------------------------------------------------------------------------------------------------------------
void removeValue(LinkList*list, LinkNode*node, COMPARENODE compare)  //COMPARENODE代表返回值为void*,参数为(LinkNode*, LinkNode*)的函数指针类型，
                                                                    //  而compare是函数指针类型COMPARENODE声明的函数指针变量
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
		pCurrent = pCurrent->next;   //找到就break,没找到就继续后移
		index++;
	}

	//到这个位置时，pCurrent指向了要删除的那个值所在的位置

	//删除结点（坏处：无法释放已删除结点的内存）
	pCurrent->next = pCurrent->next->next;

	list->size--;



}


//查找
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
	LinkNode*pCurrent = list->header.next;   //指向第一个有效值
	int index = 0;  //index用来保存被找到的值的位置
	int flag = -1;
	while (pCurrent != NULL)
	{
		if(compare(pCurrent, node)==1)
		{
			flag = index;
			break;
		}
		pCurrent = pCurrent->next;    //否则 继续向后移动
		index++;
	}

	return flag;




}



//打印-----------------------------------------------------------------------------------------------------------------------------------------
void Print(LinkList*list, PRINTNODE Print)
{
	if (list == NULL)
	{
		return;
	}
	LinkNode*pCurrent = list->header.next;     //pCurrent指向链表的第一个有效值，即第二个结点
	while (pCurrent != NULL)
	{
		Print(pCurrent);    //调用回调函数
		pCurrent = pCurrent->next;
	}

}


//释放-----------------------------------------------------------------------------------------------------------------------------------------
void Free(LinkList* list)
{
	if (list != NULL)
	{
		return;
	}
	free(list);

}

//测试-------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct Person666
{
	LinkNode * node;   //头结点
	char name[64];
	int age;
}Person;

void printPerson(LinkNode*node) //因为调用位置传的值是LinkNode* 类型，所以这个形参也必须是LinkNode*类型     //用于回调的函数
{
	Person *p = (Person*)node;
	printf("姓名 : %s     年龄 ：%d  \n", p->name, p->age);
}

void comparePerson(LinkNode*node1, LinkNode*node2)                                                          //用于回调的函数
{
	Person*p1 = (Person*)node1;
	Person*p2 = (Person*)node2;
	if ((p1->name== p2->name) && (p1->age == p2->age))    //判断是否相等，相等就代表找到了   
	{
		return 1;
	}
	else return -1;
}


int main()
{
  
	//先初始化链表
	LinkList *list = Init();

	//创建数据
	Person p1, p2, p3;
	strcpy(p1.name, "张三");
	strcpy(p2.name, "李四");
	strcpy(p3.name, "王五");
	p1.age = 10;
	p2.age = 20;
	p3.age = 30;


	//插入结点
	Insert(list, 0,(LinkNode* ) &p1);   //由于形参是LinkNode*类型，所以此处要强转为LinkNode *类型
	Insert(list, 0, (LinkNode*)&p2);
	Insert(list, 0, (LinkNode*)&p3); //插入位置存疑？？？

	Print(list, printPerson);  // 此处传的是函数地址 printPerson


	//删除 位置 删除
	removePos(list, 0);
	Print(list, printPerson);

	//根据 值 删除
	removeValue(list, &p2, comparePerson);
	Print(list, printPerson);

	//查找
	printf("%d",Find(list, &p2, comparePerson));










}












