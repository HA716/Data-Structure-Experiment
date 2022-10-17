#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxsize 3       //�����������������Ϊmaxsize

//�������Ľڵ�
typedef struct LINKNODE
{
	char data [maxsize];        //�������������Ϊmaxsize
	struct LINKNODE * next;     //nextָ��ָ����һ�������ڵ�
}LinkNode;

//ͷ���
typedef struct HEADER
{
	struct HEADER * head;  //ͷָ��ָ����Ԫ���
	int len;               //��¼������
}Header;

//��ʼ������:��ͷ�ڵ�ĳ�ʼ��---------------------------------------------------------------------------------------------
Header * Init()
{
	Header * header = (Header*)malloc(sizeof(Header));
	header->head = NULL;
	header->len = 1;    //����ͷ�ڵ� 1 ��
	return header;
}


//����������-------------------------------------------------------------------------------------------------------------
LinkNode* Create(Header* header, char s[])
{
	int num = 0;
	int i = 0;
	//������һ���ڵ�
	LinkNode * linkNode = (LinkNode*)malloc(sizeof(LinkNode));
	linkNode->next = NULL;
	//ͷ�ڵ����ӵ�һ���ڵ�
	header->head = linkNode;

	while (s[num] != '\0')
	{
		if (i >= maxsize)        //����������ݵ��������ڻ�һ��������������ʹ����½ڵ㣬ֱ������ȫ���ɸ�����
		{
			LinkNode * newNode = (LinkNode*)malloc(sizeof(LinkNode));
			newNode->next = NULL;
			linkNode->next = newNode;        //�����½ڵ�

			//���½ڵ�λ�á�������
			linkNode = newNode;
			header->len++;

			//����i �� �����жϴ洢���ݵĿռ��Ƿ��㹻 !!!
			i = i % maxsize;
		}

		linkNode->data[i++] = s[num++];  

	}

	//����whileѭ���󣬴��������Ѿ���ȫ�����������
	//������һ���ڵ�û�б������������������#���룬�������
	for (int j = i; i != 0 && j < maxsize; j++)
	{
		linkNode->data[j] = '#';
	}

}


//BF�㷨:parent�Ǹ�����child���Ӵ���pos�ǿ�ʼ���ҵ�λ��-------------------------------------------------------------------------
int BFcompare(Header*parent, Header*child, int pos)
{
	int i = pos;
	int j = 1;
	while (i < parent->len&&j < child->len)       //i�������������ȣ�j��������ƥ����Ӵ�����
	{
		if ()
		{

		}



	}
}







//��ӡ-----------------------------------------------------------------------------------------------------------
void Print(Header*header)
{
	LinkNode * linkNode = NULL;
	linkNode = header->head;
	while (linkNode != NULL)
	{
		for (int i = 0; i < maxsize; i++)
		{
			if (linkNode->data[i] == '#')
			{
				return;
			}
			else
			{
				printf("%c", linkNode->data[i]);
			}
		}
		linkNode = linkNode->next;   //���½ڵ�λ��
		printf("|");

	}
}






int main()
{
	Header* header = Init();
	Create(header, "abcdefg");
	Print(header);


}



















