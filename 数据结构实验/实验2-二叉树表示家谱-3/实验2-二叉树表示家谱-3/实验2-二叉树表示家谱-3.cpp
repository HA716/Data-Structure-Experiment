#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include<iostream>
using namespace std;
#define MaxSize 30 //代表了姓名字符、最大场宽、数组元素树
#pragma warning (disable:4996)
typedef struct fnode
{
	char father[MaxSize]; //父
	char wife[MaxSize]; //母
	char son[MaxSize]; //子
} FamType;
typedef struct tnode
{
	char name[MaxSize];
	struct tnode *lchild, *rchild;
} BTree; //家谱树类型
//创建二叉树
BTree *CreatBTree(char *root, FamType fam[], int n) //从fam(含n个记录)递归创建一棵二叉树
{
	int i = 0, j;
	BTree *bt, *p;
	bt = (BTree *)malloc(sizeof(BTree)); //创建父亲节点
	strcpy(bt->name, root); //将root中的COPY复制到bt->name中
	bt->lchild = bt->rchild = NULL;
	while (i < n && strcmp(fam[i].father, root) != 0) //比较两个字符串是否相同
		i++;
	if (i < n) //找到了该姓名的记录
	{
		p = (BTree *)malloc(sizeof(BTree)); //创建母亲节点
		p->lchild = p->rchild = NULL;
		strcpy(p->name, fam[i].wife);
		bt->lchild = p;
		for (j = 0; j < n; j++) //找所有儿子
			if (strcmp(fam[j].father, root) == 0) //找到一个儿子
			{
				p->rchild = CreatBTree(fam[j].son, fam, n);
				p = p->rchild;
			}
	}
	return(bt);
}
//以括号表示法输出二叉树
void DispTree1(BTree *b) //先序遍历
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
			cout << ")"; //累计
		}
	}
}
//二叉树家谱表示法
void DispTree2(BTree *bt)
{
	BTree *St[MaxSize], *p;
	int Level[MaxSize][2], top, n, i, x = 0, width = 4;
	int flag = 0;
	if (bt != NULL)
	{
		cout << " >>二叉树家谱表示法:" << endl;
		top = 1;
		St[top] = bt; //根节点进栈
		Level[top][0] = width;
		while (top > 0)
		{
			p = St[top]; //退栈并凹入显示该节点值
			n = Level[top][0];
			for (i = 1; i <= n; i++) //其中n为显示场宽,字符以右对齐显示
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
			{ //将左子树根节点进栈
				top++;
				St[top] = p->lchild;
				Level[top][0] = 0; //显示场宽增width
				Level[top][1] = 1; //为左孩子节点
			}
			if (p->lchild != NULL && p->rchild != NULL)
			{
				top++;
				St[top] = p->rchild;
				Level[top][0] = n + width; //显示场宽增width
				Level[top][1] = 2; //为右孩子节点
			}
			if (p->rchild != NULL && p->lchild == NULL)
			{
				//将右子树根节点进栈
				top++;
				St[top] = p->rchild;
				Level[top][0] = n + width; //显示场宽增width
				Level[top][1] = 2; //为右孩子节点
			}
		}
	}
}
//以凹入表示法输出
void DispTree3(BTree *bt)
{
	BTree *St[MaxSize], *p;
	int Level[MaxSize][2], top, n, i, width = 4;
	if (bt != NULL)
	{
		cout << " >>家谱凹入表示法:" << endl;
		top = 1;
		St[top] = bt; //根节点进栈
		Level[top][0] = width;
		while (top > 0)
		{
			p = St[top]; //退栈并凹入显示该节点值
			n = Level[top][0];
			for (i = 1; i <= n; i++) //其中n为显示场宽,字符以右对齐显示
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
			{ //将右子树根节点进栈
				top++;
				St[top] = p->rchild;
				Level[top][0] = n + width; //显示场宽增width
				Level[top][1] = 2; //为右孩子节点
			}
			if (p->lchild != NULL)
			{ //将左子树根节点进栈
				top++;
				St[top] = p->lchild;
				Level[top][0] = n + width; //显示场宽增width
				Level[top][1] = 1; //为左孩子节点
			}
		}
	}
}
//采用先序递归算法找name为xm的节点
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
//输出某人的所有儿子
void FindSon(BTree *bt)
{
	char xm[MaxSize];
	BTree *p;
	cout << " >>父亲姓名:";
	cin >> xm;
	p = FindNode(bt, xm);
	if (p == NULL)
		cout << " >>不存在" << xm << "的父亲" << endl;
	else
	{
		p = p->lchild;
		if (p == NULL)
			cout << " >>" << xm << "没有妻子" << endl;
		else
		{
			p = p->rchild;
			if (p == NULL)
				cout << " >>" << xm << "没有儿子!" << endl;
			else
			{
				cout << " >>" << xm << "的儿子:" << " ";
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
//采用后序非递归遍历方法输出从根节点到*s节点的路径
int Path(BTree *bt, BTree *s)
{
	BTree *St[MaxSize];
	BTree *p;
	int i, flag, top = -1; //栈指针置初值
	do
	{
		while (bt) //将bt的所有左节点进栈
		{
			top++;
			St[top] = bt;
			bt = bt->lchild;
		}
		p = NULL; //p指向当前节点的前一个已访问的节点
		flag = 1; //设置bt的访问标记为已访问过
		while (top != -1 && flag)
		{
			bt = St[top]; //取出当前的栈顶元素
			if (bt->rchild == p) //右子树不存在或已被访问,访问之
			{
				if (bt == s) //当前访问的节点为要找的节点,输出路径
				{
					cout << " >>所有祖先:";
					for (i = 0; i < top; i++)
						cout << St[i]->name << " ";
					cout << endl;
					return 1;
				}
				else
				{
					top--;
					p = bt; //p指向则被访问的结
				}
			}
			else
			{
				bt = bt->rchild; //bt指向右子树
				flag = 0; //设置未被访问的标记
			}
		}
	} while (top != -1); //栈不空时循环
	return 0; //其他情况时返回0
}
//输出某人的所有祖先
void Ancestor(BTree *bt)
{
	BTree *p;
	char xm[MaxSize];
	cout << " >>输入姓名:";
	cin >> xm;
	p = FindNode(bt, xm);
	if (p != NULL)
		Path(bt, p);
	else
		cout << " >>查无此人" << endl;
}
//清除家谱文件全部记录
void DelAll(FamType fam[], int &n)
{
	FILE *fp;
	if ((fp = fopen("fam.dat", "wb")) == NULL)
	{
		cout << " >>不能打开家谱文件" << endl;
		return;
	}
	n = 0;
	fclose(fp);
}
//读家谱文件存入fam数组中
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
	fseek(fp, 0, 2); //家谱文件位置指针移到家谱文件尾
	len = ftell(fp); //len求出家谱文件长度
	rewind(fp); //家谱文件位置指针移到家谱文件首
	n = len / sizeof(FamType); //n求出家谱文件中的记录个数
	for (i = 0; i < n; i++)
		fread(&fam[i], sizeof(FamType), 1, fp);//将家谱文件中的数据读到fam中
	fclose(fp);
}
//将fam数组存入数据家谱文件
void SaveFile(FamType fam[], int n)
{
	int i;
	FILE *fp;
	if ((fp = fopen("fam.dat", "wb")) == NULL)
	{
		cout << " >>数据家谱文件不能打开" << endl;;
		return;
	}
	for (i = 0; i < n; i++)
		fwrite(&fam[i], sizeof(FamType), 1, fp);
	fclose(fp);
}
//添加一个记录
void InputFam(FamType fam[], int &n)
{
	cout << " >>输入父亲、母亲和儿子姓名:";
	cin >> fam[n].father;
	cin >> fam[n].wife;
	cin >> fam[n].son;
	n++;
}
//输出家谱文件全部记录
void OutputFile(FamType fam[], int n)
{
	int i;
	if (n <= 0)
	{
		cout << " >>没有任何记录" << endl;
		return;
	}
	cout << " 父亲 母亲 儿子" << endl;
	cout << " ------------------------------" << endl;
	for (i = 0; i < n; i++)
		printf(" %10s%10s%10s\n", fam[i].father, fam[i].wife, fam[i].son);
	cout << " ------------------------------" << endl;
}
void main()
{
	//创建始祖名称
	char b[MaxSize];
	cout << "请输入家族始祖的姓名：";
	cin >> b;
	cout << "家谱重构成功！" << endl;
	cout << "请按任意键后继续...";
	getch(); // 按任意键
	system("cls");
	//主控制台
	BTree *bt;
	FamType fam[MaxSize];
	int n, s, s1;
	ReadFile(fam, n);
	do
	{
		cout << "==================================================================" << endl;
		cout << "** 请选择要执行的操作： **" << endl;
		cout << "** 1 --- 文件操作 **" << endl;
		cout << "** 2 --- 家谱操作 **" << endl;
		cout << "** 0 --- 退出系统 **" << endl;
		cout << "==================================================================" << endl;
		cout << "请选择要执行的操作：";
		cin >> s;
		system("cls");
		switch (s)
		{
		case 1:
			do
			{
				cout << "==================================================================" << endl;
				cout << "** 请选择要执行的操作： **" << endl;
				cout << "** 1 --- 输入 **" << endl;
				cout << "** 2 --- 输出 **" << endl;
				cout << "** 3 --- 一键清空 **" << endl;
				cout << "** 4 --- 更换始祖 **" << endl;
				cout << "** 0 --- 存盘返回 **" << endl;
				cout << "==================================================================" << endl;
				cout << "请选择要执行的操作：";
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
					cout << "当前命令操作错误,请重新输入正确命令！" << endl;
				}
			} while (s1 != 0);
			break;
		case 2:
			bt = CreatBTree(b, fam, n);
			do
			{
				cout << "==================================================================" << endl;
				cout << "** 请选择要执行的操作： **" << endl;
				cout << "** 1 --- 括号表示法 **" << endl;
				cout << "** 2 --- 凹入表示法 **" << endl;
				cout << "** 3 --- 二叉树家谱 **" << endl;
				cout << "** 4 --- 找某人所有儿子 **" << endl;
				cout << "** 5 --- 找某人所有祖先 **" << endl;
				cout << "** 0 --- 返回 **" << endl;
				cout << "==================================================================" << endl;
				cout << "请选择要执行的操作：";
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
					cout << "当前命令操作错误,请重新输入正确命令！" << endl;
				}
			} while (s1 != 0);
			system("cls");
			break;
		}
	} while (s != 0);
}