#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define NO 0
#define MAXSIZE 100

//ѭ�����нṹ
typedef struct LoopQueue {
	char* base[MAXSIZE];//��������һ��char*���鹹��
	int front;//��ͷ������ָ����е�һ����������λ��
	int rear; //��β������ָ��������һ�����ݺ�һ��λ��
}LoopQueue;

//ѭ�����г�ʼ������ѭ�����л������飬���һ������һ��LoopQueue����
//���ڲ���base����ռ���Զ����䣬����Ҫ�Լ�����
//ֻ���ʼ����ͷ�Ͷ�β����
int initLQueue(LoopQueue *Q) {
	Q->front = Q->rear = 0;
	return OK;
}

//���س���
int getLenth(LoopQueue *Q) {
	return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

//����Ԫ��
int insertLQueue(LoopQueue *Q) {

	//������������һ������λ�ã���rear+1���Ͷ�ͷ������Ƚ����ж��Ƿ�Ϊ����
	//��Ϊ�˺Ͷ����пյ�����������
   //�ж϶����Ƿ�Ϊ����δ���������ӡ��������������NO
	if ((Q->rear + 1) % MAXSIZE == Q->front) return NO;
	char * stuId = (char*)malloc(sizeof(12));
	scanf("%s", stuId);
	Q->base[Q->rear] = stuId;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return  OK;
}

//Ԫ�س���
char* outLQueue(LoopQueue *Q) {
	//�ж϶����Ƿ�Ϊ�� 
	if (Q->rear == Q->front) return NULL;
	char * data_return = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return data_return;
}

//���ٶ���,Ҳ�����ڸ�ѭ�����л������飬����Ҫ�����ڴ�
//ֻ�����ö�ͷ�Ͷ�β��������
int destroyLQueue(LoopQueue *Q) {
	Q->front = Q->rear = 0;
	return OK;
}

int main() {

	// ��ʼ������ 	
	LoopQueue Q;

	//����һ��ѡ����� 
	int choice;

	//Ԫ�ز������ 
	int num;

	//���ӷ���ֵ
	char* back;
	do {
		printf("===========ѭ�����в���==========\n");
		printf("1.��ʼ��ѭ������\n");
		printf("2.Ԫ�����\n");
		printf("3.Ԫ�س���\n");
		printf("4.���ٶ���\n");
		printf("0.�˳�\n");
		printf("=====================\n");
		printf("����������ѡ��");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			initLQueue(&Q) ? printf("------------\n -->> ѭ�����г�ʼ���ɹ�\n------------\n") : printf("------------\n -->> ѭ�����г�ʼ��ʧ��\n------------\n");
			break;
		case 2:

			printf("���������Ԫ�ظ�����");
			scanf("%d", &num);
			int i;
			for (i = 0; i < num; i++) {
				printf(" �������%d��ѧ����ѧ��:", i + 1);
				if (!insertLQueue(&Q))printf("------------\n-->> ��%dԪ�����ʧ��\n", i + 1);
			}

			break;
		case 3:
			back = outLQueue(&Q);
			back ? printf("------------\n Ԫ��: %s ���ӣ���ʣ%d��Ԫ��\n", back, getLenth(&Q)) : printf("------------\n����Ϊ�գ��޷����ӣ�\n");
			break;
		case 4:
			destroyLQueue(&Q) ? printf("------------\n�������ٳɹ���\n") : printf("------------\n��������ʧ�ܣ�\n");
			break;
		case 0:
			printf("\n-->> �˳�\n");
			exit(0);
			break;
		default:
			break;
		}
	} while (choice);


}