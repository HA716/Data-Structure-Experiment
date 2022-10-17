#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct LinkNode
{
	//只维护指针域
	struct LinkNode * next;
};

struct LList
{
	struct LinkNode pHeader; //链表头节点
	int m_Size; //链表长度
};

typedef void * LinkList;
//初始化链表
LinkList init_LinkList()
{
	struct LList * myList = malloc(sizeof(struct LList));


	if (myList == NULL)
	{
		return NULL;
	}

	myList->pHeader.next = NULL;

	myList->m_Size = 0;

	return myList;
}


//插入链表
void insert_LinkList(LinkList list, int pos, void * data)
{
	if (list == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	struct LList * mylist = list;

	if (pos < 0 || pos >mylist->m_Size - 1)
	{
		pos = mylist->m_Size; // 无效位置 进行尾插
	}

	//将用户的数据 前4个字节转为 LinkNode类型
	struct LinkNode * myNode = data;

	//找到插入数据的前驱节点位置
	struct LinkNode * pCurrent = &mylist->pHeader;

	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//更改指针的指向
	myNode->next = pCurrent->next;
	pCurrent->next = myNode;

	//更新链表长度
	mylist->m_Size++;

}

//遍历链表
void foreach_LinkList(LinkList list, void(*myForeach)(void *))
{
	if (list == NULL)
	{
		return;
	}

	struct LList * myList = list;

	struct LinkNode * node = myList->pHeader.next; //第一个有数据的节点

	for (int i = 0; i < myList->m_Size; i++)
	{
		myForeach(node);
		node = node->next;
	}
}

//删除链表  按位置删除
void removeByPos_LinkList(LinkList list, int pos)
{
	if (list == NULL)
	{
		return;
	}
	struct LList * myList = list;
	if (pos < 0 || pos > myList->m_Size - 1)
	{
		return;
	}

	//找到删除位置的前驱节点位置
	struct LinkNode * pCurrent = &myList->pHeader;

	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//记录待删除的节点
	struct LinkNode * pDel = pCurrent->next;

	//更改指针的指向
	pCurrent->next = pDel->next;

	//free(pDel); //我们链表中是不维护数据域的，写了free反而会出错

	//更新链表长度
	myList->m_Size--;

}

//销毁链表
void destroy_LinkList(LinkList list)
{
	if (list == NULL)
	{
		return;
	}

	free(list);
	list = NULL;

}




//测试
struct Person
{
	struct LinkNode node; // 约定好的前四个字节给底层链表使用
	char name[64];
	int age;
};

void printPerson(void * data)
{
	struct Person * p = data;
	printf("姓名: %s 年龄: %d\n", p->name, p->age);
}


void test01()
{
	//初始化
	LinkList mylist = init_LinkList();

	//准备出数据
	struct Person p1 = { NULL, "aaa", 10 };
	struct Person p2 = { NULL, "bbb", 20 };
	struct Person p3 = { NULL, "ccc", 30 };
	struct Person p4 = { NULL, "ddd", 40 };
	struct Person p5 = { NULL, "eee", 50 };

	insert_LinkList(mylist, 0, &p1);
	insert_LinkList(mylist, 0, &p2);
	insert_LinkList(mylist, 0, &p3);
	insert_LinkList(mylist, 1, &p4);
	insert_LinkList(mylist, 100, &p5);
	// ccc ddd bbb aaa  eee

	//遍历链表
	foreach_LinkList(mylist, printPerson);

	////测试删除链表
	removeByPos_LinkList(mylist, 2);

	printf("------------------\n");

	foreach_LinkList(mylist, printPerson);


	//struct Person p = { "aaa", 10 };

	//removeByValue_LinkList(mylist, &p , myCompare);

	destroy_LinkList(mylist);
}

int main() {
	test01();


	system("pause");
	return EXIT_SUCCESS;
}