#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable : 4996)

void HanoiTower(int n, char A, char B, char C)   //nΪ����������A��B��C����������ֻ�Ƿ�ָ������һֱ��������A��B��C����
{                                                // A�Ǵ��ƶ����������ڵ����� �� B����Ҫ���������� �� C������Ҫ�Ƶ�������
	/*
	 �� n=1:ֱ�ӽ�A�����ϵ����Ӵ�A�Ƶ�C��

	 ����
    	1.�Ƚ�A������n-1�����ӽ���C�Ƶ�B
		2.�ٽ�A������ʣ������һ������ֱ�Ӵ�A�Ƶ�C��
		3.�����B�����ϵ�n-1�����ӽ���A�Ƶ�C

	*/
	if (n == 1)
	{
		printf("�����Ϊ%d������ֱ�Ӵ�%c�����Ƶ�%c����\n",n,A,C);
	}
	else
	{
		HanoiTower(n - 1, A, C, B);       //�ѹ�n-1���Ӵ�A������C������B��
		printf("�����Ϊ%d������ֱ�Ӵ�%c�����Ƶ�%c����\n", n, A, C);
		HanoiTower(n - 1, B, A, C);       //�ѹ�n-1���Ӵ�B������A������C��
	}
}


void main()
{
	int n;
	printf("%s", "�����뺺ŵ�������ӵĸ���");
	scanf("%d", &n);

	//�����������ӣ�A����һ��ʼ�����num�����ӣ�Ҫ����B���ӣ�����ȫ���Ƶ�C������ȥ
	char ch1 = 'A';
	char ch2 = 'B';
	char ch3 = 'C';

	HanoiTower(n,'A','B','C'); //��n�����Ӵ�A����B�Ƶ�C

}


















