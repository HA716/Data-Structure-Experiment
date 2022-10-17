#include<iostream>
using namespace std;

//n是数组中元素的个数
void Merge(int R[], int low, int mid, int high);  //归并R[low..high]
void MergePass(int R[], int lenght, int n);  //对整个排序序列进行一趟归并
void MergeSort(int R[], int n);              //二路归并排序

/*约定：称R[low,..mid]为第1段，称R[mid+1,..high]为第2段 */

void Merge(int R[], int low, int mid, int high)
{
	int i = low;   //i是的第1段下标
	int j = mid + 1; //j是的第2段下标
	int k = 0;     //k是R1的下标
	int *R1 = (int *)malloc(sizeof(int)*(high - low + 1));

	while (i <= mid && j <= high)
	{
		if (R[i] <= R[j])
		{
			R1[k] = R[i];
			i++;
			k++;
		}
		else
		{
			R1[k] = R[j];
			j++;
			k++;
		}

	}
	while (i <= mid)  //将第一段中剩余内容复制到R1中
	{
		R1[k] = R[i];
		i++;
		k++;
	}
	while (j <= high)
	{
		R1[k] = R[j];
		j++;
		k++;
	}
	//将暂存数组R1中的内容复制到数组R中
	for (k = 0,i=low; i<= high; i++,k++)
	{
		R[i] = R1[k];
	}
	free(R1);

}

//对整个序列进行一趟归并
void MergePass(int R[], int length, int n)
{//length是每个子表的长度，n是数组元素的总个数
	int i;
	for (i = 0; i + 2 * length - 1 < n; i = i+2*length)  //归并长为length的两个子表
	{
		Merge(R, i, i+length-1, i+ 2*length -1);
	}

	/*
	需要对“子表个数是奇数、最后一个子表的长度小于length”这两种特殊情况进行处理，
	当子表个数是奇数的时候，必然会导致最后一个子表的长度小于length
	*/
	if (i + length - 1 < n - 1)   //归并整个序列剩余的最后两个子表，后者长度小于length
	{//只有当整趟序列只剩下两个子表的时候，才会满足这个if()条件
		Merge(R, i, i + length - 1, n - 1);
	}

}

//二路归并排序
void MergeSort(int R[], int n)
{
	int length; //子表的长度

	/*每完成一趟归并，则子表的长度变为原来的两倍*/
	for (length = 1; length < n; length *= 2)
	{
		MergePass(R, length, n);
	}
}




int main()
{
	int R[] = { 5,4,3,2,1 };
	int n = sizeof(R) / sizeof(R[0]);
	MergeSort(R, n);
	for (int i = 0; i < n; i++)
	{
		cout << R[i] << "  ";
	}

}












