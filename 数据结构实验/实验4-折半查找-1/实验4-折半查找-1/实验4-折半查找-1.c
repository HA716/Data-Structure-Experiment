#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct NODE
{
	int key;
}Node;

typedef struct LIST
{
	Node arr[MAX];
	int len;    //当前长度
}List;


//创建有序表
void CreateList(List*list)
{
	
	Node node;
	printf("请输入结点个数：");
	//int n;
	scanf_s("%d", &list->len);
	printf("请输入各结点key值：\n");
	//arr[0]是哨兵
	for (int i = 1; i <= list->len; i++)
	{
		scanf_s("%d", &node.key);
		list->arr[i].key = node.key;
	}
	return list;
}


int Search_Bin(List* list, int value)
{
	//设置哨兵
	list->arr[0].key = value;
	int low = 1;
	int high = list->len;
	int mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (list->arr[mid].key == list->arr[0].key) return mid; //找到
		else if (list->arr[mid].key > list->arr[0].key)
		{
			high = mid - 1;  //取左区间
		}
		else if (list->arr[mid].key < list->arr[0].key)
		{
			low = mid + 1;  //取右区间
		}
	}

	return 0;     //返回0代表没找到，此时low>high

}


void PrintList(List*list)
{
	for (int i = 1; i <= list->len; i++)
	{
		printf("%d ", list->arr[i].key);
	}
	printf("\n");
}

int main()
{
	List *list = (List*)malloc(sizeof(List));
	CreateList(list);
	printf("有序表为：");
	PrintList(list);
	printf("请输入要查找的结点key值：");
	int value;
	scanf_s("%d", &value);
	int pos =Search_Bin(list, value);
	printf("该元素在有序表中的位置为：%d", pos);
}






















