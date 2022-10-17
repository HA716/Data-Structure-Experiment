#include<iostream>
using namespace std;

void BubbleSort(int arr[], int n)
{
	int i, j;
	bool flag = true;
	//int flag = 1;
	int temp = 0;
	//n个元素，需要进行n-1次排序
	for (i = 0; i <(n-1) && flag==true ; i++)
	{
		flag = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;

				flag = true;   //标记发生了排序
			}
		}
	}
}


int main()
{
	int arr[] = { 5,4,3,2,1};
	int n = sizeof(arr) / sizeof(arr[0]);
	BubbleSort(arr, n);  //冒泡排序
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "  ";
	}

}



















