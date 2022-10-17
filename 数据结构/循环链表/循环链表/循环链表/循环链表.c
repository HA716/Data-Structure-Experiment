#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
//------------------------------------------------------------------------------------------------------------------------------------------
typedef struct LinkNode1  //凡是用这个结构体名定义的变量都需要加上struct
{
	  struct LinkNode1 * next;  //这个地方必须要这样子写，不能用 LinkNode  因为检测不到
}LinkNode;
typedef struct LinkList1
{
	LinkNode header;         //头结点
	int size;
}LinkList;

//------------------------------------------------------------------------------------------------------------------------------------------
//比较回调
typedef int(*COMPARENODE)(LinkNode*, LinkNode*); //???什么意思 回调函数，用于判断是否相等
//打印回调
typedef int(*PRINTNODE)(LinkNode*);


//初始化链表------------------------------------------------------------------------------------------------------------------------------------------
LinkList * Init()
{
	LinkList *list = (LinkList*)malloc(sizeof(LinkList));  //为头结点开辟空间
	list->header.next = &(list->header);   //初始化时，头结点的next指针指向头结点本身
	list->size = 0;

	return list;
}


//插入------------------------------------------------------------------------------------------------------------------------------------------------
void Insert(LinkList*list, int pos, LinkNode* node)  //node就是待插入的数据
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
		pos = list->size;       //默认尾部插入
	}
	LinkNode * pCurrent = &(list->header);    //pCurrent指针指向头结点

	for (int i = 0; i < pos; i++)  //找到pos处的前一个位置，即pos-1处
	{
		pCurrent = pCurrent->next;    
	}

	//插入新结点
	node->next = pCurrent->next;
	pCurrent->next = node;

	list->size++;
}

//返回第一个元素------------------------------------------------------------------------------------------------------------------------------------------
LinkNode* FirstElem(LinkList*list)
{
	return list->header.next;    //因为头结点没有数据，所以 头结点的next 所指的地方就是第一个元素的位置
}

//根据 位置 删除------------------------------------------------------------------------------------------------------------------------------------------
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
	for (int i = 0; i < pos; i++) //找到pos的前一个结点处 ，即pos-1。 因为头结点没有值，所以遍历一次之后才找到第一个有值的结点，这是链表的第二个结点
	{
		pCurrent = pCurrent->next;
	}

	LinkNode*pNext = pCurrent->next;  //先保存这个待删除结点的位置
	pCurrent->next = pNext->next;     //删除pos处的结点 

	list->size--;
}


//根据 值 删除------------------------------------------------------------------------------------------------------------------------------------------
void RemoveValue(LinkList*list, LinkNode*node, COMPARENODE compare)  //compare用于判断你传入的值与链表中待删除的值是否相等
{
	if (list == NULL)
	{
		return;
	}
	if (node)
	{
		return;
	}
	LinkNode* pCurrent1 = &(list->header);  //指向头结点，没有值
	LinkNode* pCurrent2 = list->header.next; //指向头结点的下一个结点,有值
	int i = 0;
	for (i = 0; i < list->size; i++)
	{
		if (compare(pCurrent2, node) == 1)  //回调函数，比较node与当前位置pCurrent2是否相同，若相同则返回1，表示找到了
		{
			pCurrent1->next = pCurrent2->next;  //删除pCurrent2所指的结点
			list->size--;
			break;
		}
		//如果没找到，就不断后移指针
		pCurrent1 = pCurrent2;
		pCurrent2 = pCurrent2->next;
	}




}

//链表长度-------------------------------------------------------------------------------------------------------------------------------------------
int Size(LinkList*list)
{
	return list->size;
}



//查找------------------------------------------------------------------------------------------------------------------------------------------
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

	LinkNode*pCurrent = list->header.next;    //pCurrent指向头结点的下一个位置，因为这个位置才有值
	for (int i = 0; i < list->size; i++)      //使pCurrent指向当前 i 处的位置
	{
		if (compare(pCurrent, node) == 1)
		{
			flag = i;   //标记处被找到的位置
			return;
		}
		//如果没找的，就看下一个位置
		pCurrent = pCurrent->next;
	}

	return  flag;  //返回被找的位置，没找到就返回-1
}

//打印------------------------------------------------------------------------------------------------------------------------------------------
void Print(LinkList *list, PRINTNODE myPrint)
{
	if (list == NULL)
	{
		return;
	}

	LinkNode*pCurrent = list->header.next;  //从真正有值的这个结点开始遍历
	for (int i = 0; i < list->size*2; i++)  //此处size*2代表打印两次链表，可以证明该链表的循环性
	{
		if (pCurrent->next == &(list->header)) //防止循环的时候 pCurrent指向头结点，导致错误
		{
			pCurrent->next=list->header.next;  //跳过头结点
		}
		myPrint(pCurrent);
		pCurrent = pCurrent->next;
	}

}


//释放-----------------------------------------------------------------------------------------------------------------------------------------------------
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

//用于删除的回调函数
void printPerson (LinkNode * node)      
{
	Person * p = (Person*)node;  //因为下面打印需要，所以转成Person类型
	printf("姓名：%s   年龄：%d  \n", p->name, p->age);
}

//用于比较的回调函数
void comparePerson(LinkNode * node1, LinkNode * node2)
{
	Person * p1 = (Person*)node1;   //与上面那个函数同理
	Person * p2 = (Person*)node2;

	if (p1->name == p2->name&&p1->age == p2->age)
	{
		return 1;  // 1 表示对比相同，即找到了
	}
	else return -1;
}

int main()
{
	Person p1, p2, p3;
	strcpy(p1.name, "张三");
	strcpy(p2.name, "李四");
	strcpy(p3.name, "王五");

	
	p1.age = 10;
	p2.age = 20;
	p3.age = 30;

	//初始化链表
	LinkList * list = Init();
	
	//插入
	Insert(list, 100, &p1);  //因为100不是有效长度，所以是默认尾部插入了
	Insert(list, 100, &p2);
	Insert(list, 100, &p3);

	//打印
	Print(list,printPerson);
	printf("%s \n", "-----------------------------------------------");
	//删除p3
	remove(list, p3, comparePerson);
	Print(list, printPerson);
	printf("%s", "-----------------------------------------------");


}











