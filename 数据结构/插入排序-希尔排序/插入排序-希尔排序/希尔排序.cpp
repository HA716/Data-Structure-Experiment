#include<iostream>
using namespace std;

void Shell(int arr[], int n,int inc[],int size)  //inc[]是增量序列
{
	int i, j ,k;  //循环变量
	int key;      //当前待插入的值

	for (i = 0; i < size; i++)  //遍历增量序列
	{
		//开始遍历，理解原理，画图会很容易分析
		for (j = inc[i]; j < n; j++)
		{
			key = arr[j];
			for (k = j; k >= inc[i] && key < arr[k - inc[i]]; k -= inc[i])
			{
				arr[k] = arr[k- inc[i]];
			}
			arr[k] = key;
		}

		//打印每一趟排序
		cout << "inc" << inc[i] << endl;
		for (int i = 0; i < n; i++)
		{
			cout<< arr[i] << " ";
		}
		cout << endl;
	}
	


}


int main()
{
	int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
	int inc[] = { 5,4,3,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int size =sizeof(inc) / sizeof(inc[0]);
	Shell(arr, n, inc,size);

}
















