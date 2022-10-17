#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

// 共 8 个人，当数到3的时候就有一个人出列
#define M 8 
#define N 3

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

//根据 值 删除------------------------------------------------------------------------------------------------------------------------------------------
void  RemoveValue(LinkList*list, LinkNode*node, COMPARENODE compare)  //compare用于判断你传入的值与链表中待删除的值是否相等
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


//打印------------------------------------------------------------------------------------------------------------------------------------------
void Print(LinkList *list, PRINTNODE myPrint)
{
	if (list == NULL)
	{
		return;
	}

	LinkNode*pCurrent = list->header.next;  //从真正有值的这个结点开始遍历
	for (int i = 0; i < list->size ; i++) 
	{
		if (pCurrent->next == &(list->header)) //防止循环的时候 pCurrent指向头结点，导致错误
		{
			pCurrent->next = list->header.next;  //跳过头结点
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

//约瑟夫问题↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
typedef struct MYNUM
{
	LinkNode  node;
	int val;
}MyNum;

void PrintMyNum(LinkNode* node)
{
	MyNum* num = (MyNum*)node;      //node本是MyNum类型，先被转成了LinkNode* ,此处又被转回MyNum
	printf("%d   ", num->val);
}

void CompareMyNum(LinkNode* node1, LinkNode* node2)
{
	MyNum*num1 = (MyNum*)node1;
	MyNum*num2 = (MyNum*)node2;
	if (num1->val == num2->val)     //对比成功 ，返回 1
	{
		return 1;
	}

	else return -1;
}


void deleteNum(LinkList*list)
{
	int index = 1;    //index是计数作用，当index=N 时就有一个数出列，同时这个数要被删除
	LinkNode* pCurrent = list->header.next;  //指向第一个有效值
	printf("\n");
	while (list->size > 1)      //约瑟夫问题的最终目的就是 人不断出列，最后只剩一个人
	{
		if (index == N)  //此时，这个人要出列，同时删除这个值
		{
			MyNum* temp = (MyNum*)pCurrent;
			printf("%d", temp->val);          //这就是要出列的数

		

			//删除这个出列的值
			//先记录待删除结点的下一个位置
			LinkNode*pNext = pCurrent->next;

			//根据 值 删除
			RemoveValue(list, pCurrent, CompareMyNum);      // 这个函数会执行 size--
			//指针后移
			pCurrent = pNext;
			//指针后移的过程中可能遇到头结点，需要跳过
			if (pCurrent == &(list->header))
			{
				pCurrent = pCurrent->next;  //如果pCurrent指向了头结点，则跳过头结点
			}
			index = 1;  //每出列一次，就重置回1
		
		}

		//此时index!=N，所以指针继续后移（需考虑头结点的情况）
		pCurrent = pCurrent->next;
		if (pCurrent == &(list->header))
		{
			pCurrent = pCurrent->next;  //如果pCurrent指向了头结点，则跳过头结点
		}

		index++;  //  !!!
	}

	if (list->size == 1)   //约瑟夫问题结束条件
	{
		LinkNode * temp = FirstElem(list);  //取出最后一个元素
		MyNum * element = (MyNum*)temp;
		printf("%d  ", element->val);
	}





}


int main()
{
	//初始化链表 
	LinkList*list = Init();
	MyNum  num[M];         //存放 8 个人的数据(注意类型)
	for (int i = 0; i < M; i++)
	{
		num[i].val = i + 1;    // 1、2、3、4、5、6、7、8
		Insert(list, i, (LinkNode*)&num[i]); // 把数组中的每个元素作为一个结点插入到链表中
	}

	Print(list, PrintMyNum);


	deleteNum(list);

	Print(list, PrintMyNum);


}









