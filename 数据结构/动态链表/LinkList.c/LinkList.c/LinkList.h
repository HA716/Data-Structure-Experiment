#pragma once  //防止#pragma once所在的头文件被include多次，即防止被包含多次

//在头文件把代码框架写好，在.c文件中实现框架的功能

typedef struct 
{
	int data;        //结点的数据域
	struct LinkNode * next; //结点的指针域
}LinkNode;

//初始化链表 Init()返回头节点
LinkNode * Init();
//遍历链表
void Print(LinkNode * header);
//尾部插入数据
void Back_Insert(LinkNode * header);
//在指定位置oldvalue处插入新结点，且值为newvalue
void Insert(LinkNode * header,int oldvalue);
//清空链表：将所有除头节点以外的存放有数据的节点释放掉
void Clear(LinkNode * header);
//销毁链表：将包括头结点在内的所有节点释放掉
void Destory(LinkNode * header);
//删除结点
void Delete(LinkNode * header,int delValue);






















