#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct NODE
{
	int key;
}Node;

typedef struct LIST
{
	Node arr[MAX];
	int len;    //��ǰ����
}List;


//���������
void CreateList(List*list)
{
	
	Node node;
	printf("�������������");
	//int n;
	scanf_s("%d", &list->len);
	printf("����������keyֵ��\n");
	//arr[0]���ڱ�
	for (int i = 1; i <= list->len; i++)
	{
		scanf_s("%d", &node.key);
		list->arr[i].key = node.key;
	}
	return list;
}


int Search_Bin(List* list, int value)
{
	//�����ڱ�
	list->arr[0].key = value;
	int low = 1;
	int high = list->len;
	int mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (list->arr[mid].key == list->arr[0].key) return mid; //�ҵ�
		else if (list->arr[mid].key > list->arr[0].key)
		{
			high = mid - 1;  //ȡ������
		}
		else if (list->arr[mid].key < list->arr[0].key)
		{
			low = mid + 1;  //ȡ������
		}
	}

	return 0;     //����0����û�ҵ�����ʱlow>high

}


void PrintList(List*list)
{
	for (int i = 1; i <= list->len; i++)
	{
		printf("%d ", list->arr[i].key);
	}
	printf("\n");
}

int main()
{
	List *list = (List*)malloc(sizeof(List));
	CreateList(list);
	printf("�����Ϊ��");
	PrintList(list);
	printf("������Ҫ���ҵĽ��keyֵ��");
	int value;
	scanf_s("%d", &value);
	int pos =Search_Bin(list, value);
	printf("��Ԫ����������е�λ��Ϊ��%d", pos);
}






















