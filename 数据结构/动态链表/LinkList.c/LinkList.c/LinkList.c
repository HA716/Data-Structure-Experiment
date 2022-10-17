#include<stdio.h>  //输入输出
#include<stdlib.h>  //动态内存分配
#include<stdbool.h>  //布尔值
#include"LinkList.h"  //引入框架
#pragma warning(disable:4996)  //防止scanf的不安全提示


//初始化链表 Init()返回头节点-----------------------------------------------------------------------------------------------
LinkNode * Init()
{
	LinkNode * header = (LinkNode*)malloc(sizeof(LinkNode)); // 指向头节点的指针
	header->data = 0;  //因为一般不对头节点数据进行操作，所以头节点data是什么都行
	header->next = NULL;  //初始时指向NULL

	int val;
	LinkNode* pRear = header;     //创建尾部指针，始终指向链表的最后一个结点，用于实现插入
	while (true)
	{
		LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode));  //插入新节点
		printf("%s","请输入结点data值");
		scanf("%d", &val);
		if (val == -1)
		{
			break;         //当输入-1时，认为不再插入新节点
		}
		//初始化新节点
		newNode->data = val;
		newNode->next = NULL;     //新节点一定是最后一个结点，所以指向NUll

		//新节点插入尾部
		pRear->next = newNode;

		//更新尾部指针位置，让它指向最后一个结点
		pRear = newNode;
		
	}
	return header;
}


//遍历链表------------------------------------------------------------------------------------------------------------------
void Print(LinkNode * header)
{
	//辅助指针遍历 用于遍历
	LinkNode*pCurrent = header->next;  //因为头节点的数据没用，所以从头节点的下一位开始遍历     

	while (pCurrent != NULL)
	{
		printf("%d\n", pCurrent->data);
		//指针后移
		pCurrent = pCurrent->next;
	}
}



//新结点的插入-------------------------------------------------------------------------------------------------------------
void Insert(LinkNode * header,int oldvalue)    
{
	int val;
	//两个辅助指针，一个指向头结点，另一个指向头结点的下一位
	LinkNode*pCurrent1 = header;      
	LinkNode*pCurrent2 = header->next;
	while (pCurrent2 != NULL)     //遍历链表中的结点
	{
		if (pCurrent2->data == oldvalue)  //在oldvalue的位置插入新结点
		{
			LinkNode*newNode = (LinkNode*)malloc(sizeof(LinkNode));
			printf("%s", "请输入新结点data值");
			scanf("%d", &val);		
			//初始化新节点
			newNode->data = val;
			//插入结点
			pCurrent1->next = newNode;            //画图就很容易明白
			newNode->next = pCurrent2;
			break;

		}
		//如果没有找到oldvalue就更新辅助指针的位置
		pCurrent2 = pCurrent2->next;
		pCurrent1 = pCurrent1->next;
	}


}




//尾部插入数据-------------------------------------------------------------------------------------------------------
void Back_Insert(LinkNode * header)
{
	int val;
	LinkNode* pRear = header;     //创建尾部指针，始终指向链表的最后一个结点，用于实现插入
	while (true)
	{
		LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode));  //插入新节点
		printf("%s", "请输入结点data值");
		scanf("%d", &val);
		if (val == -1)
		{
			break;         //当输入-1时，认为不再插入新节点
		}
		//初始化新节点
		newNode->data = val;
		newNode->next = NULL;     //新节点一定是最后一个结点，所以指向NUll

		//新节点插入尾部
		pRear->next = newNode;

		//更新尾部指针位置，让它指向最后一个结点
		pRear = newNode;

	}
}




//清空链表：将所有除头节点以外的存放有数据的节点释放掉----------------------------------------------------------------------
void Clear(LinkNode * header)
{
	//先指向头结点的下一个结点，因为不需要释放头结点
	LinkNode*pCurrent = header->next;
	LinkNode*pTemp;
	while (pCurrent != NULL)
	{
		pTemp = pCurrent->next; //先保存下一个结点的位置，否则一旦释放pCurrent就找不到了后面结点的位置了
		free(pCurrent);   //释放pCurrent当前所指向的内存空间
		pCurrent = pTemp; //指向下一个结点
	}

	header->next = NULL;  //释放其他结点后，头结点指向NULL,即恢复为空链表


}






//销毁链表：将包括头结点在内的所有节点释放掉------------------------------------------------------------------------------
void Destory(LinkNode * header)
{
	//先指向头结点
	LinkNode*pCurrent = header;   //唯一区别！！
	LinkNode*pTemp;
	while (pCurrent != NULL)
	{
		pTemp = pCurrent->next; //先保存下一个结点的位置，否则一旦释放pCurrent就找不到了后面结点的位置了
		free(pCurrent);   //释放pCurrent当前所指向的内存空间
		pCurrent = pTemp; //指向下一个结点
	}

	header->next = NULL;  //释放其他结点后，头结点指向NULL,即恢复为空链表

}




//删除结点------------------------------------------------------------------------------------------------------------------
void Delete(LinkNode * header, int delValue)
{
	if (header== NULL)   //判断是否为空链表，是空链表就直接返回
	{
		return;
	}

	//需要两个辅助指针变量
	LinkNode*pCurrent1 = header;
	LinkNode*pCurrent2 = pCurrent1->next;
	
	while (pCurrent2 != NULL)
	{
		if (pCurrent2->data == delValue)   //找到待删除的值
		{
		
			break;     //一定要退出,否则继续执行下面两行代码
		}

		//如果没有找到delValue就不断更新辅助指针的位置
		pCurrent2 = pCurrent2->next;
		pCurrent1 = pCurrent1->next;
	}
	
	pCurrent1->next = pCurrent2->next;
	free(pCurrent2);
	pCurrent2 = NULL;


}

//-----------------------------------------------------------------------------------------------------------------------------
void main()
{
	LinkNode*header = Init();
	Print(header);

	Insert(header, 3);   //在原本结点值为3的位置插入新结点
	Print(header);

	Clear(header);        //清空列表
	Back_Insert(header);  //插入新结点，用于验证释放成功清空列表
	Print(header);

	Delete(header, 3);   //删除值为3的结点
	Print(header);
}




























