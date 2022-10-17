#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define NO 0
#define MAXSIZE 100

//循环队列结构
typedef struct LoopQueue {
	char* base[MAXSIZE];//数据域由一个char*数组构成
	int front;//队头索引，指向队列第一个数据所在位置
	int rear; //队尾索引，指向队列最后一个数据后一个位置
}LoopQueue;

//循环队列初始化。该循环队列基于数组，因此一旦声明一个LoopQueue变量
//其内部的base数组空间便自动分配，不需要自己分配
//只需初始化队头和队尾索引
int initLQueue(LoopQueue *Q) {
	Q->front = Q->rear = 0;
	return OK;
}

//返回长度
int getLenth(LoopQueue *Q) {
	return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

//插入元素
int insertLQueue(LoopQueue *Q) {

	//这里牺牲掉了一个储存位置，用rear+1来和队头索引相比较以判断是否为满，
	//是为了和队列判空的条件相区分
   //判断队列是否为满，未满则可以入队。如果已满，返回NO
	if ((Q->rear + 1) % MAXSIZE == Q->front) return NO;
	char * stuId = (char*)malloc(sizeof(12));
	scanf("%s", stuId);
	Q->base[Q->rear] = stuId;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return  OK;
}

//元素出队
char* outLQueue(LoopQueue *Q) {
	//判断队列是否为空 
	if (Q->rear == Q->front) return NULL;
	char * data_return = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return data_return;
}

//销毁队列,也是由于该循环队列基于数组，不需要分配内存
//只需重置队头和队尾索引即可
int destroyLQueue(LoopQueue *Q) {
	Q->front = Q->rear = 0;
	return OK;
}

int main() {

	// 初始化队列 	
	LoopQueue Q;

	//定义一个选择变量 
	int choice;

	//元素插入个数 
	int num;

	//出队返回值
	char* back;
	do {
		printf("===========循环队列操作==========\n");
		printf("1.初始化循环队列\n");
		printf("2.元素入队\n");
		printf("3.元素出队\n");
		printf("4.销毁队列\n");
		printf("0.退出\n");
		printf("=====================\n");
		printf("请输入您的选择：");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			initLQueue(&Q) ? printf("------------\n -->> 循环队列初始化成功\n------------\n") : printf("------------\n -->> 循环队列初始化失败\n------------\n");
			break;
		case 2:

			printf("请输入插入元素个数：");
			scanf("%d", &num);
			int i;
			for (i = 0; i < num; i++) {
				printf(" 请输入第%d个学生的学号:", i + 1);
				if (!insertLQueue(&Q))printf("------------\n-->> 第%d元素入队失败\n", i + 1);
			}

			break;
		case 3:
			back = outLQueue(&Q);
			back ? printf("------------\n 元素: %s 出队，还剩%d个元素\n", back, getLenth(&Q)) : printf("------------\n队列为空，无法出队！\n");
			break;
		case 4:
			destroyLQueue(&Q) ? printf("------------\n队列销毁成功！\n") : printf("------------\n队列销毁失败！\n");
			break;
		case 0:
			printf("\n-->> 退出\n");
			exit(0);
			break;
		default:
			break;
		}
	} while (choice);


}