#include < stdio.h>
#include<string.h>
#include<string.h>

#pragma warning(disable:4996)  //��ֹscanf�Ĳ���ȫ��ʾ

int main(int argc, char *argv[])
{
	int a = 2;
	double b = 2.0;
	void *c;                   //����void *
	int *p = &a;
	c = p;                    //��int * ת��void *��
	double *q = (double *)c;  //��void *ת��double *
	printf("%.f\n", *q);

	return 0;
}











