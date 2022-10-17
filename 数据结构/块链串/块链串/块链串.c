#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxsize 3       //单个块链的最大容量为maxsize

//块链串的节点
typedef struct LINKNODE
{
	char data [maxsize];        //块链的最大容量为maxsize
	struct LINKNODE * next;     //next指针指向下一个块链节点
}LinkNode;

//头结点
typedef struct HEADER
{
	struct HEADER * head;  //头指针指向首元结点
	int len;               //记录链表长度
}Header;

//初始化链表:对头节点的初始化---------------------------------------------------------------------------------------------
Header * Init()
{
	Header * header = (Header*)malloc(sizeof(Header));
	header->head = NULL;
	header->len = 1;    //仅有头节点 1 个
	return header;
}


//创建块链串-------------------------------------------------------------------------------------------------------------
LinkNode* Create(Header* header, char s[])
{
	int num = 0;
	int i = 0;
	//创建第一个节点
	LinkNode * linkNode = (LinkNode*)malloc(sizeof(LinkNode));
	linkNode->next = NULL;
	//头节点连接第一个节点
	header->head = linkNode;

	while (s[num] != '\0')
	{
		if (i >= maxsize)        //如果所存数据的数量大于或一个链块的容量，就创建新节点，直到能完全容纳该数据
		{
			LinkNode * newNode = (LinkNode*)malloc(sizeof(LinkNode));
			newNode->next = NULL;
			linkNode->next = newNode;        //连接新节点

			//更新节点位置、链表长度
			linkNode = newNode;
			header->len++;

			//更新i ： 用于判断存储数据的空间是否足够 !!!
			i = i % maxsize;
		}

		linkNode->data[i++] = s[num++];  

	}

	//结束while循环后，代表数据已经完全存入块链中了
	//如果最后一个节点没有被填满，则用特殊符号#填入，代表结束
	for (int j = i; i != 0 && j < maxsize; j++)
	{
		linkNode->data[j] = '#';
	}

}


//BF算法:parent是父串，child是子串，pos是开始查找的位置-------------------------------------------------------------------------
int BFcompare(Header*parent, Header*child, int pos)
{
	int i = pos;
	int j = 1;
	while (i < parent->len&&j < child->len)       //i不超过父串长度，j不超过待匹配的子串长度
	{
		if ()
		{

		}



	}
}







//打印-----------------------------------------------------------------------------------------------------------
void Print(Header*header)
{
	LinkNode * linkNode = NULL;
	linkNode = header->head;
	while (linkNode != NULL)
	{
		for (int i = 0; i < maxsize; i++)
		{
			if (linkNode->data[i] == '#')
			{
				return;
			}
			else
			{
				printf("%c", linkNode->data[i]);
			}
		}
		linkNode = linkNode->next;   //更新节点位置
		printf("|");

	}
}






int main()
{
	Header* header = Init();
	Create(header, "abcdefg");
	Print(header);


}



















