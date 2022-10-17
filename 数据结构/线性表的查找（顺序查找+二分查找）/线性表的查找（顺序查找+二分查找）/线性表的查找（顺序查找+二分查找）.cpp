#include<iostream>
using namespace std;
const int MAX = 100;
//结点
typedef struct NODE
{
	int key;
}Node;

//线性表
typedef struct TABLE
{
	Node * Arr;  //存储空间基地址
	int length;
}Table;

//顺序查找
int Seq_Search(Table * list, int key)
{
	int i = 0;
	list->Arr[0].key = key;  //哨兵
	for (i = list->length; list->Arr[i].key != key; i--);

	return i;   //返回0则代表没找到
	
}


//折半查找
int Binary_Search(Table*list,int key)
{
	int low = 1;
	int high = list->length;
	int mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (list->Arr[mid].key == key)
		{
			return mid;
		}
		else if (list->Arr[mid].key > key)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}

	//退出循环的条件是low>high，代表没找到，返回0
	return 0;


}


int main()
{
	/*******************顺序查找********************/
	Table * Seqlist = (Table*)malloc(sizeof(Table));   
	Seqlist->Arr = (Node*)malloc(sizeof(Node)*MAX);
	int arr[]= { 1,3,5,4,6,8,7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	Seqlist->length = n;
	for (int i = 0; i <n ; i++)
	{
		Seqlist->Arr[i].key = arr[i];
	}
	int pos1 = Seq_Search(Seqlist, 6);   //顺序查找元素6的位置
	cout << "pos : " << pos1 << endl;



	/*******************二分查找********************/
	Table * Binary_list = (Table*)malloc(sizeof(Table));   
	Binary_list->Arr = (Node*)malloc(sizeof(Node)*MAX);
	int arr2[] = { 1,2,3,4,5,6,7,8,9 };   //用于折半查找的查找表一定是有序的
	int n2 = sizeof(arr2) / sizeof(arr2[0]);
	Binary_list->length = n2;
	for (int i = 0; i < n2; i++)
	{
		Binary_list->Arr[i].key = arr2[i];
	}
	int pos2=Binary_Search(Binary_list, 3);   //折半查找元素3的位置
	cout << "pos : " << pos2 << endl;
}









