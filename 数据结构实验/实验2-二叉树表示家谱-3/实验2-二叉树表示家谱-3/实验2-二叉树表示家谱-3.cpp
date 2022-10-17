#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include<iostream>
using namespace std;
#define MaxSize 30 //�����������ַ�����󳡿�����Ԫ����
#pragma warning (disable:4996)
typedef struct fnode
{
	char father[MaxSize]; //��
	char wife[MaxSize]; //ĸ
	char son[MaxSize]; //��
} FamType;
typedef struct tnode
{
	char name[MaxSize];
	struct tnode *lchild, *rchild;
} BTree; //����������
//����������
BTree *CreatBTree(char *root, FamType fam[], int n) //��fam(��n����¼)�ݹ鴴��һ�ö�����
{
	int i = 0, j;
	BTree *bt, *p;
	bt = (BTree *)malloc(sizeof(BTree)); //�������׽ڵ�
	strcpy(bt->name, root); //��root�е�COPY���Ƶ�bt->name��
	bt->lchild = bt->rchild = NULL;
	while (i < n && strcmp(fam[i].father, root) != 0) //�Ƚ������ַ����Ƿ���ͬ
		i++;
	if (i < n) //�ҵ��˸������ļ�¼
	{
		p = (BTree *)malloc(sizeof(BTree)); //����ĸ�׽ڵ�
		p->lchild = p->rchild = NULL;
		strcpy(p->name, fam[i].wife);
		bt->lchild = p;
		for (j = 0; j < n; j++) //�����ж���
			if (strcmp(fam[j].father, root) == 0) //�ҵ�һ������
			{
				p->rchild = CreatBTree(fam[j].son, fam, n);
				p = p->rchild;
			}
	}
	return(bt);
}
//�����ű�ʾ�����������
void DispTree1(BTree *b) //�������
{
	if (b != NULL)
	{
		cout << b->name;
		if (b->lchild != NULL || b->rchild != NULL)
		{
			cout << "(";
			DispTree1(b->lchild);
			if (b->rchild != NULL)
				cout << ",";
			DispTree1(b->rchild);
			cout << ")"; //�ۼ�
		}
	}
}
//���������ױ�ʾ��
void DispTree2(BTree *bt)
{
	BTree *St[MaxSize], *p;
	int Level[MaxSize][2], top, n, i, x = 0, width = 4;
	int flag = 0;
	if (bt != NULL)
	{
		cout << " >>���������ױ�ʾ��:" << endl;
		top = 1;
		St[top] = bt; //���ڵ��ջ
		Level[top][0] = width;
		while (top > 0)
		{
			p = St[top]; //��ջ��������ʾ�ýڵ�ֵ
			n = Level[top][0];
			for (i = 1; i <= n; i++) //����nΪ��ʾ����,�ַ����Ҷ�����ʾ
				cout << " ";
			cout << p->name << endl;
			if (Level[top][1] == 2 && p->lchild != NULL)
			{
				cout << p->lchild->name;
				flag = 1;
				n = 0;
			}
			top--;
			if (p->lchild != NULL)
			{ //�����������ڵ��ջ
				top++;
				St[top] = p->lchild;
				Level[top][0] = 0; //��ʾ������width
				Level[top][1] = 1; //Ϊ���ӽڵ�
			}
			if (p->lchild != NULL && p->rchild != NULL)
			{
				top++;
				St[top] = p->rchild;
				Level[top][0] = n + width; //��ʾ������width
				Level[top][1] = 2; //Ϊ�Һ��ӽڵ�
			}
			if (p->rchild != NULL && p->lchild == NULL)
			{
				//�����������ڵ��ջ
				top++;
				St[top] = p->rchild;
				Level[top][0] = n + width; //��ʾ������width
				Level[top][1] = 2; //Ϊ�Һ��ӽڵ�
			}
		}
	}
}
//�԰����ʾ�����
void DispTree3(BTree *bt)
{
	BTree *St[MaxSize], *p;
	int Level[MaxSize][2], top, n, i, width = 4;
	if (bt != NULL)
	{
		cout << " >>���װ����ʾ��:" << endl;
		top = 1;
		St[top] = bt; //���ڵ��ջ
		Level[top][0] = width;
		while (top > 0)
		{
			p = St[top]; //��ջ��������ʾ�ýڵ�ֵ
			n = Level[top][0];
			for (i = 1; i <= n; i++) //����nΪ��ʾ����,�ַ����Ҷ�����ʾ
				cout << " ";
			cout << p->name;
			if (Level[top][1] == 1)
				cout << "(l)";
			else
				cout << "(r)";
			for (i = n + 1; i <= MaxSize - 6; i += 2)
				cout << "--";
			cout << endl;
			top--;
			if (p->rchild != NULL)
			{ //�����������ڵ��ջ
				top++;
				St[top] = p->rchild;
				Level[top][0] = n + width; //��ʾ������width
				Level[top][1] = 2; //Ϊ�Һ��ӽڵ�
			}
			if (p->lchild != NULL)
			{ //�����������ڵ��ջ
				top++;
				St[top] = p->lchild;
				Level[top][0] = n + width; //��ʾ������width
				Level[top][1] = 1; //Ϊ���ӽڵ�
			}
		}
	}
}
//��������ݹ��㷨��nameΪxm�Ľڵ�
BTree *FindNode(BTree *bt, char xm[])
{
	BTree *p = bt;
	if (p == NULL)
		return(NULL);
	else
	{
		if (strcmp(p->name, xm) == 0)
			return(p);
		else
		{
			bt = FindNode(p->lchild, xm);
			if (bt != NULL)
				return(bt);
			else
				return(FindNode(p->rchild, xm));
		}
	}
}
//���ĳ�˵����ж���
void FindSon(BTree *bt)
{
	char xm[MaxSize];
	BTree *p;
	cout << " >>��������:";
	cin >> xm;
	p = FindNode(bt, xm);
	if (p == NULL)
		cout << " >>������" << xm << "�ĸ���" << endl;
	else
	{
		p = p->lchild;
		if (p == NULL)
			cout << " >>" << xm << "û������" << endl;
		else
		{
			p = p->rchild;
			if (p == NULL)
				cout << " >>" << xm << "û�ж���!" << endl;
			else
			{
				cout << " >>" << xm << "�Ķ���:" << " ";
				while (p != NULL)
				{
					cout << p->name << " ";
					p = p->rchild;
				}
				cout << endl;
			}
		}
	}
}
//���ú���ǵݹ������������Ӹ��ڵ㵽*s�ڵ��·��
int Path(BTree *bt, BTree *s)
{
	BTree *St[MaxSize];
	BTree *p;
	int i, flag, top = -1; //ջָ���ó�ֵ
	do
	{
		while (bt) //��bt��������ڵ��ջ
		{
			top++;
			St[top] = bt;
			bt = bt->lchild;
		}
		p = NULL; //pָ��ǰ�ڵ��ǰһ���ѷ��ʵĽڵ�
		flag = 1; //����bt�ķ��ʱ��Ϊ�ѷ��ʹ�
		while (top != -1 && flag)
		{
			bt = St[top]; //ȡ����ǰ��ջ��Ԫ��
			if (bt->rchild == p) //�����������ڻ��ѱ�����,����֮
			{
				if (bt == s) //��ǰ���ʵĽڵ�ΪҪ�ҵĽڵ�,���·��
				{
					cout << " >>��������:";
					for (i = 0; i < top; i++)
						cout << St[i]->name << " ";
					cout << endl;
					return 1;
				}
				else
				{
					top--;
					p = bt; //pָ���򱻷��ʵĽ�
				}
			}
			else
			{
				bt = bt->rchild; //btָ��������
				flag = 0; //����δ�����ʵı��
			}
		}
	} while (top != -1); //ջ����ʱѭ��
	return 0; //�������ʱ����0
}
//���ĳ�˵���������
void Ancestor(BTree *bt)
{
	BTree *p;
	char xm[MaxSize];
	cout << " >>��������:";
	cin >> xm;
	p = FindNode(bt, xm);
	if (p != NULL)
		Path(bt, p);
	else
		cout << " >>���޴���" << endl;
}
//��������ļ�ȫ����¼
void DelAll(FamType fam[], int &n)
{
	FILE *fp;
	if ((fp = fopen("fam.dat", "wb")) == NULL)
	{
		cout << " >>���ܴ򿪼����ļ�" << endl;
		return;
	}
	n = 0;
	fclose(fp);
}
//�������ļ�����fam������
void ReadFile(FamType fam[], int &n)
{
	FILE *fp;
	long len;
	int i;
	if ((fp = fopen("fam.dat", "rb")) == NULL)
	{
		n = 0;
		return;
	}
	fseek(fp, 0, 2); //�����ļ�λ��ָ���Ƶ������ļ�β
	len = ftell(fp); //len��������ļ�����
	rewind(fp); //�����ļ�λ��ָ���Ƶ������ļ���
	n = len / sizeof(FamType); //n��������ļ��еļ�¼����
	for (i = 0; i < n; i++)
		fread(&fam[i], sizeof(FamType), 1, fp);//�������ļ��е����ݶ���fam��
	fclose(fp);
}
//��fam����������ݼ����ļ�
void SaveFile(FamType fam[], int n)
{
	int i;
	FILE *fp;
	if ((fp = fopen("fam.dat", "wb")) == NULL)
	{
		cout << " >>���ݼ����ļ����ܴ�" << endl;;
		return;
	}
	for (i = 0; i < n; i++)
		fwrite(&fam[i], sizeof(FamType), 1, fp);
	fclose(fp);
}
//���һ����¼
void InputFam(FamType fam[], int &n)
{
	cout << " >>���븸�ס�ĸ�׺Ͷ�������:";
	cin >> fam[n].father;
	cin >> fam[n].wife;
	cin >> fam[n].son;
	n++;
}
//��������ļ�ȫ����¼
void OutputFile(FamType fam[], int n)
{
	int i;
	if (n <= 0)
	{
		cout << " >>û���κμ�¼" << endl;
		return;
	}
	cout << " ���� ĸ�� ����" << endl;
	cout << " ------------------------------" << endl;
	for (i = 0; i < n; i++)
		printf(" %10s%10s%10s\n", fam[i].father, fam[i].wife, fam[i].son);
	cout << " ------------------------------" << endl;
}
void main()
{
	//����ʼ������
	char b[MaxSize];
	cout << "���������ʼ���������";
	cin >> b;
	cout << "�����ع��ɹ���" << endl;
	cout << "�밴����������...";
	getch(); // �������
	system("cls");
	//������̨
	BTree *bt;
	FamType fam[MaxSize];
	int n, s, s1;
	ReadFile(fam, n);
	do
	{
		cout << "==================================================================" << endl;
		cout << "** ��ѡ��Ҫִ�еĲ����� **" << endl;
		cout << "** 1 --- �ļ����� **" << endl;
		cout << "** 2 --- ���ײ��� **" << endl;
		cout << "** 0 --- �˳�ϵͳ **" << endl;
		cout << "==================================================================" << endl;
		cout << "��ѡ��Ҫִ�еĲ�����";
		cin >> s;
		system("cls");
		switch (s)
		{
		case 1:
			do
			{
				cout << "==================================================================" << endl;
				cout << "** ��ѡ��Ҫִ�еĲ����� **" << endl;
				cout << "** 1 --- ���� **" << endl;
				cout << "** 2 --- ��� **" << endl;
				cout << "** 3 --- һ����� **" << endl;
				cout << "** 4 --- ����ʼ�� **" << endl;
				cout << "** 0 --- ���̷��� **" << endl;
				cout << "==================================================================" << endl;
				cout << "��ѡ��Ҫִ�еĲ�����";
				cin >> s1;
				switch (s1)
				{
				case 1:
					InputFam(fam, n);
					break;
				case 2:
					OutputFile(fam, n);
					break;
				case 3:
					DelAll(fam, n);
					system("cls");
					break;
				case 4:
					DelAll(fam, n);
					main();
					system("cls");
					break;
				case 0:
					SaveFile(fam, n);
					system("cls");
					break;
				default:
					cout << "��ǰ�����������,������������ȷ���" << endl;
				}
			} while (s1 != 0);
			break;
		case 2:
			bt = CreatBTree(b, fam, n);
			do
			{
				cout << "==================================================================" << endl;
				cout << "** ��ѡ��Ҫִ�еĲ����� **" << endl;
				cout << "** 1 --- ���ű�ʾ�� **" << endl;
				cout << "** 2 --- �����ʾ�� **" << endl;
				cout << "** 3 --- ���������� **" << endl;
				cout << "** 4 --- ��ĳ�����ж��� **" << endl;
				cout << "** 5 --- ��ĳ���������� **" << endl;
				cout << "** 0 --- ���� **" << endl;
				cout << "==================================================================" << endl;
				cout << "��ѡ��Ҫִ�еĲ�����";
				cin >> s1;
				switch (s1)
				{
				case 1:
					cout << " >>"; DispTree1(bt); cout << endl;
					break;
				case 2:
					DispTree3(bt);
					break;
				case 3:
					DispTree2(bt);
					break;
				case 4:
					FindSon(bt);
					break;
				case 5:
					cout << " >>"; Ancestor(bt);
					break;
				case 0:
					break;
				default:
					cout << "��ǰ�����������,������������ȷ���" << endl;
				}
			} while (s1 != 0);
			system("cls");
			break;
		}
	} while (s != 0);
}