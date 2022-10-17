#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable : 4996)

void HanoiTower(int n, char A, char B, char C)   //n为盘子数量，A、B、C是柱子名（只是泛指，并不一直是真正的A、B、C），
{                                                // A是待移动的盘子所在的柱子 ， B是所要借助的柱子 ， C是最终要移到的柱子
	/*
	 若 n=1:直接将A柱子上的盘子从A移到C上

	 否则：
    	1.先将A柱子上n-1个盘子借助C移到B
		2.再将A柱子上剩余的最后一个盘子直接从A移到C上
		3.在最后将B柱子上的n-1个盘子借助A移到C

	*/
	if (n == 1)
	{
		printf("将编号为%d的盘子直接从%c柱子移到%c柱子\n",n,A,C);
	}
	else
	{
		HanoiTower(n - 1, A, C, B);       //把共n-1盘子从A柱借助C柱放置B柱
		printf("将编号为%d的盘子直接从%c柱子移到%c柱子\n", n, A, C);
		HanoiTower(n - 1, B, A, C);       //把共n-1盘子从B柱借助A柱放置C柱
	}
}


void main()
{
	int n;
	printf("%s", "请输入汉诺塔中盘子的个数");
	scanf("%d", &n);

	//创建三个柱子：A柱子一开始存放了num个盘子，要借助B柱子，最终全部移到C柱子上去
	char ch1 = 'A';
	char ch2 = 'B';
	char ch3 = 'C';

	HanoiTower(n,'A','B','C'); //将n个盘子从A借助B移到C

}


















