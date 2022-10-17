#include<iostream>
using namespace std;

void SelectSort(int arr[], int n);


void SelectSort(int arr[], int n)
{
	int i, j, k;  //k������¼δ�����б�����СԪ�ص�λ��
	int temp;  //���ڽ���
	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[k])
			{
				k = j;
			}
		}

		if (k != i) 
		{
			temp = arr[i];
			arr[i] = arr[k];
			arr[k] = temp;
		}
	}
}

int main()
{
	int arr[] = { 5,4,3,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	SelectSort(arr, n);
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "  ";
	}
}









