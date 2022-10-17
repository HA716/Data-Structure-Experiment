#include < stdio.h>
#include<string.h>
#include<string.h>

#pragma warning(disable:4996)  //防止scanf的不安全提示

int main(int argc, char *argv[])
{
	int a = 2;
	double b = 2.0;
	void *c;                   //定义void *
	int *p = &a;
	c = p;                    //将int * 转成void *，
	double *q = (double *)c;  //将void *转成double *
	printf("%.f\n", *q);

	return 0;
}











