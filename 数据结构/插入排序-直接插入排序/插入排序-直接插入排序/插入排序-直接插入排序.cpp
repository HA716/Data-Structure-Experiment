#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
void InsertSort(int arr[], int n)
{

	int i,j,temp;
	for (i = 1; i<n; i++)    //Ĭ��arr[0]����������
	{
		if (arr[i] < arr[i - 1])  //��Ϊ���������ǵ����ģ�����arr[i-1]�����ģ�ֻ�е�(arr[i] < arr[i - 1])ʱ������Ҫ��������ıȽ�
		{
			temp = arr[i];  //���浱ǰԪ��
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
	printf("�������鳤�ȣ�");
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	printf("\n");

	InsertSort(arr, n);  //ֱ�Ӳ�������

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}


}


















