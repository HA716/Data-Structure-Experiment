#include<stdio.h>
#include<stdlib.h>

//筛选算法
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
			i = j;         //修改i和j的值，以便继续向下筛选
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
	{//循环n/2次建初始堆
		sift(arr, i, n);
	}

	for (i = n; i >= 2; i--)
	{//进行n-1趟，完成堆排序，每趟堆中减少一个元素

		//将最后一个元素与第一个元素交换
		temp = arr[1];
		arr[1] = arr[i];
		arr[i] = temp;

		sift(arr, 1, i - 1); //交换后重新筛选为堆，得到i-1个结点的堆
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













