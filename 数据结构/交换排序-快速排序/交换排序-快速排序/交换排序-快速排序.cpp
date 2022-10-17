#include<iostream>
using namespace std;


int Partition(int arr[], int low, int high);  //��λ����
void QuickSort(int arr[], int low, int high);  //��������


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

//Partition()������������ȷ����ǰ�ӱ������ڵ�����λ��
int Partition(int arr[], int low, int high)
{
	int pivot = arr[low];    //ѡ���ӱ�ĵ�һ��Ԫ����Ϊ����
	while (low < high)
	{
		/*������ѡ������ߵ�����ʱ����ô��Ӧ���ȴ��ұ߿�ʼ������
         ������ѡ�����ұߵ�����ʱ����ô��Ӧ���ȴ���߿�ʼ����*/
		while (low<high && arr[high]>pivot)  
			high--;
		arr[low] = arr[high];

		while (low < high && arr[low] < pivot)
			low++;
		arr[high] = arr[low];
	}

	//��low==highʱ������ѭ��
	arr[low] = pivot;   //������Ԫ�����뵽��ȷλ��
	return low;
}

void QuickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pivot = Partition(arr, low, high);
		QuickSort(arr, low, pivot - 1);   //�����ӱ�ݹ�
		QuickSort(arr, pivot + 1, high);  //�����ӱ�ݹ�
	}

}









