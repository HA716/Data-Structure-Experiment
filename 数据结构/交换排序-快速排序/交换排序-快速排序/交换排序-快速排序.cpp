#include<iostream>
using namespace std;


int Partition(int arr[], int low, int high);  //定位枢轴
void QuickSort(int arr[], int low, int high);  //快速排序


int main()
{
	int arr[] = { 5,4,3,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	QuickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}


}

//Partition()函数的作用是确定当前子表枢轴在的最终位置
int Partition(int arr[], int low, int high)
{
	int pivot = arr[low];    //选择子表的第一个元素作为枢轴
	while (low < high)
	{
		/*当枢轴选择最左边的数字时，那么就应该先从右边开始搜索；
         当枢轴选择最右边的数字时，那么就应该先从左边开始搜索*/
		while (low<high && arr[high]>pivot)  
			high--;
		arr[low] = arr[high];

		while (low < high && arr[low] < pivot)
			low++;
		arr[high] = arr[low];
	}

	//当low==high时，跳出循环
	arr[low] = pivot;   //将枢轴元素填入到正确位置
	return low;
}

void QuickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pivot = Partition(arr, low, high);
		QuickSort(arr, low, pivot - 1);   //对左子表递归
		QuickSort(arr, pivot + 1, high);  //对右子表递归
	}

}









