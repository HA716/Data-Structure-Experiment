#include<iostream>
using namespace std;

void Shell(int arr[], int n,int inc[],int size)  //inc[]����������
{
	int i, j ,k;  //ѭ������
	int key;      //��ǰ�������ֵ

	for (i = 0; i < size; i++)  //������������
	{
		//��ʼ���������ԭ����ͼ������׷���
		for (j = inc[i]; j < n; j++)
		{
			key = arr[j];
			for (k = j; k >= inc[i] && key < arr[k - inc[i]]; k -= inc[i])
			{
				arr[k] = arr[k- inc[i]];
			}
			arr[k] = key;
		}

		//��ӡÿһ������
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
















