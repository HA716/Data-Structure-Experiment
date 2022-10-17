#include<iostream>
using namespace std;

/*根结点编号是0   */
void sift_0(int R[], int low, int high);  //堆调整
void CreateHeap_0(int R[], int n);         //创建堆
void HeapSort_0(int R[], int n);          //堆排序

/*根结点编号是1   */
void sift_1(int R[], int low, int high);  //堆调整
void CreateHeap_1(int R[],int n);         //创建堆
void HeapSort_1(int R[], int n);          //堆排序

void Swap(int &a, int &b)
{
	int temp = 0;
	temp = a;
	a = b;
	b = temp;
}


/************************根结点为R[0]，编号是0**************************/
//堆调整
void sift_0(int R[], int low, int n)   //n是结点个数
{
	int i = low;
	int j = 2 * i + 1;   //根结点编号为0的情况下的左右孩子
	int temp = R[i];   //子树根结点
	while (j <= n)
	{
		if (j < n && R[j] < R[j + 1])  //j指向左、右子树中较大的结点
			j++;

		if (temp < R[j]) //---大根堆
		{//如果子树根结点小于它的左、右孩子
			R[i] = R[j];   //设置R[i]为子树新的根结点
			i = j;         //修改i和j,便于继续向下筛选
			j = 2 * i + 1;
		}
		else
			break;
	}
	R[i] = temp;   //将被筛选结点放在最终的位置上
}


void CreateHeap_0(int R[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--) //由下往上调整堆
	{
		sift_0(R, i, n);  //i是被筛选的结点
	}
}


void HeapSort_0(int R[], int n)
{

	CreateHeap_0(R, n);

	/*需要进行n趟才能完成堆排序，每进行一趟堆中元素个数减1*/
	for (int i = n - 1; i >= 0; i--)
	{
		Swap(R[0], R[i]);  //将最后一个元素与根R[1]进行交换
		sift_0(R, 0, i - 1); //对R[1,..i-1]进行筛选，得到有i-1个结点的堆
	}

}

void func_0()
{
	//R[0]是根结点，根结点的编号是0，没有哨兵位
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



/********************根结点为R[1]，编号是1********************/
//堆调整
void sift_1(int R[], int low, int n)   //n是结点个数
{
	int i = low;
	int j = 2 * i;
	int temp = R[i];   //子树根结点
	while (j <= n)
	{
		if (j < n && R[j] < R[j + 1])  //j指向左、右子树中较大的结点
			j++;
		
		if (temp < R[j]) //---大根堆
		{//如果子树根结点小于它的左、右孩子
			R[i] = R[j];   //设置R[i]为子树新的根结点
			i = j;         //修改i和j,便于继续向下筛选
			j = 2 * i;
		}
		else
			break;
	}
	R[i] = temp;   //将被筛选结点放在最终的位置上
}  


void CreateHeap_1(int R[],int n)
{
	for (int i = n / 2; i > 0; i--)
	{
		sift_1(R, i, n);  //i是被筛选的结点
	}
}


void HeapSort_1(int R[], int n)
{

	CreateHeap_1(R, n);
	/*R[0]是哨兵，实际上只有n-1个有效元素，
	  所以需要进行n-1趟才能完成堆排序，每进行一趟堆中元素个数减1*/
	for (int i = n - 1; i > 0; i--) 
	{
		Swap(R[1], R[i]);  //将最后一个元素与根R[1]进行交换
		sift_1(R, 1, i - 1); //对R[1,..i-1]进行筛选，得到有i-1个结点的堆
	}

}

void func_1()
{
	//R[0]是哨兵，作用是 使树满足根结点的编号是1
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
	cout << "根结点的编号为0：" << endl;
	func_0();   //根结点编号是0的情况
	cout << endl;
	cout << "根结点的编号为1：" << endl;
	func_1();   //根结点编号是1的情况
}

























