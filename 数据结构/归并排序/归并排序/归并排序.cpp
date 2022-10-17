#include<iostream>
using namespace std;

//n��������Ԫ�صĸ���
void Merge(int R[], int low, int mid, int high);  //�鲢R[low..high]
void MergePass(int R[], int lenght, int n);  //�������������н���һ�˹鲢
void MergeSort(int R[], int n);              //��·�鲢����

/*Լ������R[low,..mid]Ϊ��1�Σ���R[mid+1,..high]Ϊ��2�� */

void Merge(int R[], int low, int mid, int high)
{
	int i = low;   //i�ǵĵ�1���±�
	int j = mid + 1; //j�ǵĵ�2���±�
	int k = 0;     //k��R1���±�
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
	while (i <= mid)  //����һ����ʣ�����ݸ��Ƶ�R1��
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
	//���ݴ�����R1�е����ݸ��Ƶ�����R��
	for (k = 0,i=low; i<= high; i++,k++)
	{
		R[i] = R1[k];
	}
	free(R1);

}

//���������н���һ�˹鲢
void MergePass(int R[], int length, int n)
{//length��ÿ���ӱ�ĳ��ȣ�n������Ԫ�ص��ܸ���
	int i;
	for (i = 0; i + 2 * length - 1 < n; i = i+2*length)  //�鲢��Ϊlength�������ӱ�
	{
		Merge(R, i, i+length-1, i+ 2*length -1);
	}

	/*
	��Ҫ�ԡ��ӱ���������������һ���ӱ�ĳ���С��length������������������д���
	���ӱ������������ʱ�򣬱�Ȼ�ᵼ�����һ���ӱ�ĳ���С��length
	*/
	if (i + length - 1 < n - 1)   //�鲢��������ʣ�����������ӱ����߳���С��length
	{//ֻ�е���������ֻʣ�������ӱ��ʱ�򣬲Ż��������if()����
		Merge(R, i, i + length - 1, n - 1);
	}

}

//��·�鲢����
void MergeSort(int R[], int n)
{
	int length; //�ӱ�ĳ���

	/*ÿ���һ�˹鲢�����ӱ�ĳ��ȱ�Ϊԭ��������*/
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












