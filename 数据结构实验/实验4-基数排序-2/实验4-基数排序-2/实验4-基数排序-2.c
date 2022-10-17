#include<stdio.h>
#include<stdlib.h>

#define MAXLEN  10 //���Ԫ�ظ���
#define MAXD 100   //ÿ��Ԫ�ص����ؼ���λ��

typedef struct NODE
{
	char data[MAXD];
	struct NODE *next;
}Node;


//�������
void Print(char R[MAXLEN][MAXD], int n)
{

	int i;
	for (i = 0; i < n; i++)
	{
		printf("[%s]", R[i]);
	}
	printf("\n");
}


//Ԥ������'  '�����е��ʲ���
void PreProcess(char R[][MAXD],int n)
{
	int i;
	int j;
	for (i = 0; i < n; i++)
	{
		if (strlen(R[i]) < MAXLEN)
		{
			for (j = strlen(R[i]); j < MAXLEN; j++)
			{
				R[i][j] = ' ';
			}
			R[i][j] = '\0';
		}
	}

}


//�ָ�����ɾ��ԭ�����Ŀո�'  '
void end_process(char R[][MAXD], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = MAXLEN - 1; R[i][j] == ' '; j--)
		{
			R[i][j + 1] = '\0';
		}
	}


}



//��ÿ��Ԫ�صĵ�j���ؼ��ֽ��з���           ��һάָ�����飬�����Ԫ����Node*
void Distribute(char R[MAXLEN][MAXD], Node *head[], Node *tail[], int n,int j)
{
	int i;  //Ԫ�ر��
	int k;  //���б��
	Node*p;

	for (i = 0; i < n; i++)
	{
		if (R[i][j] == ' ')
		{//����0�Ŷ���
			k = 0;
		}
		else
		{
			k = R[i][j] - 'a' + 1;
		}

		p = (Node*)malloc(sizeof(Node));
		strcpy(p->data, R[i]);
		p->next = NULL;

		if (head[k] == NULL)
		{
			head[k] = p;
			tail[k] = p;
		}
		else
		{
			tail[k]->next = p;
			tail[k] = p;
		}
	}

}


//�ռ�
void Collect(char R[][MAXD], Node*head[])
{
	int i;
	int k = 0;
	Node*pre, *p;
	
	for (i = 0; i < MAXD; i++)
	{
		if (head[i] != NULL)
		{//���зǿ�
			pre = head[i];
			p = pre->next;
			while (p != NULL)
			{
				strcpy(R[k++], pre->data);
				free(pre);
				pre = p;
				p = pre->next;
			}
			strcpy(R[k++], pre->data);
			free(pre);
		}
	}
}


//��R[0,...n-1]���л�������
void Radix_Sort(char R[MAXLEN][MAXD], int n)
{
	int i, j;
	Node*head[MAXD], *tail[MAXD];

	for (i = MAXLEN - 1; i >= 0; i--)
	{
		for (j = 0; j < MAXD; j++)
		{
			head[j] = tail[j] = NULL;
		}
		Distribute(R, head, tail, n, i);   //��i�˷���
		Collect(R, head);                  //��i���ռ�

	}

}





int main()
{
	char R[MAXLEN][MAXD] = { "while", "if", "if else", "do while", "for", "case" };
	int n = 6;

	printf("����ǰ:\n");
	Print(R, n);

	PreProcess(R, n);
	printf("Ԥ�����:\n");
	Print(R, n);

	Radix_Sort(R, n);
	printf("������:\n");
	Print(R, n);

	end_process(R, n);
	printf("���ս��:\n");
	Print(R, n);
}




















