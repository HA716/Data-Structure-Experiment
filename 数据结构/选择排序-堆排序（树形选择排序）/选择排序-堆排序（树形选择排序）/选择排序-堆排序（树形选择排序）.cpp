#include<iostream>
using namespace std;

/*���������0   */
void sift_0(int R[], int low, int high);  //�ѵ���
void CreateHeap_0(int R[], int n);         //������
void HeapSort_0(int R[], int n);          //������

/*���������1   */
void sift_1(int R[], int low, int high);  //�ѵ���
void CreateHeap_1(int R[],int n);         //������
void HeapSort_1(int R[], int n);          //������

void Swap(int &a, int &b)
{
	int temp = 0;
	temp = a;
	a = b;
	b = temp;
}


/************************�����ΪR[0]�������0**************************/
//�ѵ���
void sift_0(int R[], int low, int n)   //n�ǽ�����
{
	int i = low;
	int j = 2 * i + 1;   //�������Ϊ0������µ����Һ���
	int temp = R[i];   //���������
	while (j <= n)
	{
		if (j < n && R[j] < R[j + 1])  //jָ�����������нϴ�Ľ��
			j++;

		if (temp < R[j]) //---�����
		{//������������С���������Һ���
			R[i] = R[j];   //����R[i]Ϊ�����µĸ����
			i = j;         //�޸�i��j,���ڼ�������ɸѡ
			j = 2 * i + 1;
		}
		else
			break;
	}
	R[i] = temp;   //����ɸѡ���������յ�λ����
}


void CreateHeap_0(int R[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--) //�������ϵ�����
	{
		sift_0(R, i, n);  //i�Ǳ�ɸѡ�Ľ��
	}
}


void HeapSort_0(int R[], int n)
{

	CreateHeap_0(R, n);

	/*��Ҫ����n�˲�����ɶ�����ÿ����һ�˶���Ԫ�ظ�����1*/
	for (int i = n - 1; i >= 0; i--)
	{
		Swap(R[0], R[i]);  //�����һ��Ԫ�����R[1]���н���
		sift_0(R, 0, i - 1); //��R[1,..i-1]����ɸѡ���õ���i-1�����Ķ�
	}

}

void func_0()
{
	//R[0]�Ǹ���㣬�����ı����0��û���ڱ�λ
	int R[] = { 6,8,7,9,0,1,3,2,4,5 };
	int n = sizeof(R) / sizeof(R[0]);
	for (int i = 0; i < n; i++)
	{
		cout << R[i] << "  ";
	}
	cout << endl;

	HeapSort_0(R, n);
	for (int i = 0; i < n; i++)
	{
		cout << R[i] << "  ";
	}
}



/********************�����ΪR[1]�������1********************/
//�ѵ���
void sift_1(int R[], int low, int n)   //n�ǽ�����
{
	int i = low;
	int j = 2 * i;
	int temp = R[i];   //���������
	while (j <= n)
	{
		if (j < n && R[j] < R[j + 1])  //jָ�����������нϴ�Ľ��
			j++;
		
		if (temp < R[j]) //---�����
		{//������������С���������Һ���
			R[i] = R[j];   //����R[i]Ϊ�����µĸ����
			i = j;         //�޸�i��j,���ڼ�������ɸѡ
			j = 2 * i;
		}
		else
			break;
	}
	R[i] = temp;   //����ɸѡ���������յ�λ����
}  


void CreateHeap_1(int R[],int n)
{
	for (int i = n / 2; i > 0; i--)
	{
		sift_1(R, i, n);  //i�Ǳ�ɸѡ�Ľ��
	}
}


void HeapSort_1(int R[], int n)
{

	CreateHeap_1(R, n);
	/*R[0]���ڱ���ʵ����ֻ��n-1����ЧԪ�أ�
	  ������Ҫ����n-1�˲�����ɶ�����ÿ����һ�˶���Ԫ�ظ�����1*/
	for (int i = n - 1; i > 0; i--) 
	{
		Swap(R[1], R[i]);  //�����һ��Ԫ�����R[1]���н���
		sift_1(R, 1, i - 1); //��R[1,..i-1]����ɸѡ���õ���i-1�����Ķ�
	}

}

void func_1()
{
	//R[0]���ڱ��������� ʹ����������ı����1
	int R[] = { 0,6,8,7,9,0,1,3,2,4,5 };
	int n = sizeof(R) / sizeof(R[0]);
	for (int i = 0; i < n; i++)
	{
		cout << R[i] << "  ";
	}
	cout << endl;

	HeapSort_1(R, n);
	for (int i = 1; i < n; i++)
	{
		cout << R[i] << "  ";
	}
}


/***************** main() *********************/
int main()
{
	cout << "�����ı��Ϊ0��" << endl;
	func_0();   //���������0�����
	cout << endl;
	cout << "�����ı��Ϊ1��" << endl;
	func_1();   //���������1�����
}

























