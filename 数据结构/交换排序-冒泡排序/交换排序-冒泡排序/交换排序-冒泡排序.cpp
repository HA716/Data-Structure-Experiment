#include<iostream>
using namespace std;

void BubbleSort(int arr[], int n)
{
	int i, j;
	bool flag = true;
	//int flag = 1;
	int temp = 0;
	//n��Ԫ�أ���Ҫ����n-1������
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

				flag = true;   //��Ƿ���������
			}
		}
	}
}


int main()
{
	int arr[] = { 5,4,3,2,1};
	int n = sizeof(arr) / sizeof(arr[0]);
	BubbleSort(arr, n);  //ð������
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "  ";
	}

}



















