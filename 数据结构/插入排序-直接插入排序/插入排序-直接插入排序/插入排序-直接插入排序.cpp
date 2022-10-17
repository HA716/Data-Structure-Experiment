#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
void InsertSort(int arr[], int n)
{

	int i,j,temp;
	for (i = 1; i<n; i++)    //默认arr[0]是有序序列
	{
		if (arr[i] < arr[i - 1])  //因为已排序列是递增的，所以arr[i-1]是最大的，只有当(arr[i] < arr[i - 1])时，才需要进行下面的比较
		{
			temp = arr[i];  //保存当前元素
			arr[i] = arr[i - 1];

			for (j = i - 1; temp < arr[j]; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}
}


int main()
{

	int *arr = (int *)malloc(sizeof(int) * 100);
	int n;
	printf("输入数组长度：");
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	printf("\n");

	InsertSort(arr, n);  //直接插入排序

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}


}


















