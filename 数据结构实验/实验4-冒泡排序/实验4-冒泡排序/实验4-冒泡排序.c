#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

bool BubbleSort(int *arr,int n)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	for (int i = 0; i < n - 1; i++)
	{
		bool flag = false;
		for (int j = n - 1; j > i; j--)
		{
			if (arr[j] < arr[j - 1])
			{//交换
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
				flag = true;
			}

			if (flag == false)
			{//若本趟没有交换，就退出，代表全部排好序了
				return;
			}

		}

	}

}

int main()
{
	int arr[] = { 5,4,3,2,1,0 };
	int len = sizeof(arr) / sizeof(arr[0]);
	BubbleSort(arr, len);
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}

}
















