#include<stdio.h>
#include<stdlib.h>

//ɸѡ�㷨
void sift(int arr[], int low, int high)
{
	int i = low;
	int j = 2 * i;
	int parent = arr[i];
	while (j <= high)
	{
		if (j < high&&arr[j] < arr[j + 1])
		{
			j++;
		}
		if (parent < arr[j])
		{
			arr[i] = arr[j];
			i = j;         //�޸�i��j��ֵ���Ա��������ɸѡ
			j = 2 * i;
		}
	}
	arr[i] = parent;
}

void HeapSort(int arr[], int n)
{
	int i;
	int temp = 0;
	for (i = n / 2; i >= 1; i--)
	{//ѭ��n/2�ν���ʼ��
		sift(arr, i, n);
	}

	for (i = n; i >= 2; i--)
	{//����n-1�ˣ���ɶ�����ÿ�˶��м���һ��Ԫ��

		//�����һ��Ԫ�����һ��Ԫ�ؽ���
		temp = arr[1];
		arr[1] = arr[i];
		arr[i] = temp;

		sift(arr, 1, i - 1); //����������ɸѡΪ�ѣ��õ�i-1�����Ķ�
	}

}



int main()
{
	int arr[] = { 5,4,3,2,1 };
	int len = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr, len);
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}


}













