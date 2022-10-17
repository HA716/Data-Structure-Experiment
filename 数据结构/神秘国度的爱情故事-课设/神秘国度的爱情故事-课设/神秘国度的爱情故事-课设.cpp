#include<iostream>
using namespace std;

const int MAX = 100; //最大顶点数
const int MAX_NAME = 50;  //结点信息最大长度
bool flag_1 = false;  //用来判断是否路过C，但路过C不说明能表白
bool flag_2 = false;  //用来判断最终是否表白成功：条件是路过C且到达终点B
//bool flag_3 = false;  //用来判断以c为起点，在不经过结点c的前趋结点的情况下，能否找到结点b。
int visited[MAX];    //标记顶点是否已经被访问--以a为起点
int visited_2[MAX];  //标记顶点是否已经被访问--以c为起点

//边表
typedef struct EDGE
{
	int adjvex;
	struct EDGE * next;
}Edge;

//顶点
typedef struct NODE
{
	char data[MAX_NAME];  //结点信息
	Edge*firstEdge;
}Node;

//邻接表
typedef struct ADJLIST
{
	Node vertex[MAX]; //顶点数组
	int verNum;       //当前顶点数
	int arcNum;       //当前边的数量
}AdjList;

//函数原型
int Located(AdjList*list, char*str);                   //定位结点ver在顶点表中的位置
void CreateGraph(AdjList**list);                       //创建图
void PrintGraph(AdjList*list);                         //打印邻接表
bool DFS_1(AdjList*list, char*a, char*b, char*c);           //以a为起点,b为终点，c为ab路径上的点
bool DFS_2(AdjList*list, char*c, char*b, int index);   /*判断是否有以c为起点，且能经过b，但不能经过index结点的路径。
														 因为由index才搜索到c，同时index是c的邻接点，所以一旦经过index就意味着会去c所在主分支以外的分支寻找，这是错误的*/
														 /*创建图*/
void CreateGraph(AdjList**list)
{
	int i; //循环变量
	char* str;

	cout << "请输入小村(顶点)个数：";
	cin >> (*list)->verNum;
	cout << "请输入小村之间路径(边)的数量：";
	cin >> (*list)->arcNum;
	getchar();


	//创建顶点表
	cout << "请输入小村(顶点)信息：" << endl;
	for (i = 0; i < (*list)->verNum; i++)
	{
		cout << i + 1 << ":";
		gets_s((*list)->vertex[i].data);
		(*list)->vertex[i].firstEdge = NULL;
	}

	//创建邻接表
	cout << "创建邻接表：" << endl;
	for (i = 0; i < (*list)->arcNum; i++)
	{

		char strVer1[MAX_NAME];
		char strVer2[MAX_NAME];
		cout << "顶点：";
		cin >> strVer1;
		cout << "邻接点：";
		cin >> strVer2;
		int ver1, ver2;
		ver1 = Located((*list), strVer1);
		ver2 = Located((*list), strVer2);

		//无向图

		Edge*adjNode_1 = (Edge*)malloc(sizeof(Edge));  //邻接点(边表结点)
		adjNode_1->adjvex = ver2;
		//头插法：将邻接点插入到边表中
		adjNode_1->next = (*list)->vertex[ver1].firstEdge;
		(*list)->vertex[ver1].firstEdge = adjNode_1;

		Edge*adjNode_2 = (Edge*)malloc(sizeof(Edge));  //邻接点(边表结点)
		adjNode_2->adjvex = ver1;
		//头插法：将邻接点插入到边表中
		adjNode_2->next = (*list)->vertex[ver2].firstEdge;
		(*list)->vertex[ver2].firstEdge = adjNode_2;

	}

}


/*打印邻接表*/
void PrintGraph(AdjList*list)
{
	if (list == NULL) return;

	cout << "邻接表：" << endl;
	for (int i = 0; i < list->verNum; i++)
	{
		cout << i << "  " << list->vertex[i].data;
		Edge *p = (list->vertex[i].firstEdge);  //p指向第一个边表结点
		while (p)
		{
			cout << "->" << list->vertex[p->adjvex].data;
			p = p->next;
		}
		if (p == NULL)
		{
			cout << "-> NULL";
		}
		cout << endl;
	}
}


/*定位结点ver在顶点表中的位置*/
int Located(AdjList*list, char*str)
{
	int index = -1;
	bool flag = false;
	for (int i = 0; i < list->verNum; i++)
	{
		if (strcmp(list->vertex[i].data, str) == 0)
		{
			index = i;
			flag = true;
			break;
		}
	}
	if (flag == false)
	{
		cout << "输入有误，请重新输入！" << endl;
	}
	return index;
}


/*判断是否有以c为起点，且能经过b，但不能经过index结点的路径(防止往回走)*/
bool DFS_2(AdjList*list, char*c, char*b, int index)
{

	int Stack[MAX];  //栈中的元素是结点在顶点表中的下标
	int topNode = 0; //栈顶元素
	Edge*p;
	int top = -1;  //栈顶指针
	int i, j, k;
	int size = 0;  //栈的大小
	int pos_c, pos_b;
	bool flag_3 = false;  //用来判断以c为起点，在不经过结点c的前趋结点的情况下，能否找到结点b。

	pos_c = Located(list, c); //定位 c在顶点表中的索引
	pos_b = Located(list, b);


	for (i = 0; i < list->verNum; i++)
	{//初始化visited数组
		visited_2[i] = 0;
	}

	//从起点pos_c开始遍历
	i = pos_c;
	if (visited_2[i] == 0)
	{//若该顶点未被访问则访问且让它入栈
		visited_2[i] = 1;
		Stack[++top] = i;
		size++;
	}

	/*当栈不为空，弹出栈顶元素并输出，然后访问它的邻接点*/
	while (size > 0)
	{
		//获取栈顶元素 并将其弹出
		topNode = Stack[top--];
		size--;

		if (topNode == index)
		{//如果栈顶元素是index,则跳过，这样才能避免跑到其他分支上去搜索
			continue;
		}

		if (topNode == pos_b)
		{//如果以c为起点进行遍历能到达b,则置标志flag_3=true
			flag_3 = true;
			break;
		}

		//p指向栈顶元素的第一个边表结点
		p = list->vertex[topNode].firstEdge;
		while (p)
		{
			if (visited_2[p->adjvex] == 0)
			{//存在邻接点，且该邻接点未被访问，则访问且让它入栈
				visited_2[p->adjvex] = 1;
				Stack[++top] = p->adjvex;
				size++;
			}
			p = p->next;
		}
	}
	return flag_3;
}



//非递归（栈）：a是起点，b是终点，c是ab路径上的点
bool DFS_1(AdjList*list, char*a, char*b, char*c)
{
	int Stack[MAX];  //栈中的元素是结点在顶点表中的下标
	int topNode = 0; //栈顶元素
	Edge*p;
	int top = -1;  //栈顶指针
	int i, j, k;
	int size = 0;  //栈的大小
	int pos_a, pos_b, pos_c;
	int index = -1;
	bool flag_3 = false; //用来判断以c为起点，在不经过结点c的前趋结点的情况下，能否找到结点b。



	pos_a = Located(list, a); //定位 a在顶点表中的索引
	pos_b = Located(list, b);
	pos_c = Located(list, c);

	for (i = 0; i < list->verNum; i++)
	{//初始化visited数组
		visited[i] = 0;
	}

	//从起点pos_a开始遍历
	i = pos_a;

	if (visited[i] == 0)
	{//若该顶点未被访问则访问且让它入栈
		visited[i] = 1;
		Stack[++top] = i;
		size++;
	}

	/*当栈不为空，弹出栈顶元素并输出，然后访问它的邻接点*/
	while (size > 0)
	{
		//获取栈顶元素 并将其弹出
		topNode = Stack[top--];
		size--;


		if (topNode == pos_c)
		{//如果路径经过c，那么标记为 flag_1=true
			flag_1 = true; //说明现在走的路线会经过C村，但还不能说明能表白，因为这条路是要能去到b村的路才行
		}


		//p指向栈顶元素的第一个边表结点
		p = list->vertex[topNode].firstEdge;

		if (p->adjvex == pos_c)
		{//记录c的双亲结点
			if (flag_3 == false)
			{ //一旦flase_3置为true就不再进行DFS遍历
				index = topNode;
				flag_3 = DFS_2(list, c, b, index);
			}
		}



		while (p)
		{
			if (visited[p->adjvex] == 0)
			{//存在邻接点，且该邻接点未被访问，则访问且让它入栈
				visited[p->adjvex] = 1;
				Stack[++top] = p->adjvex;
				size++;
			}

			if (p->next != NULL)
			{//记录c的双亲结点
				if (p->next->adjvex == pos_c)
				{//p非空 且 p的邻接点是c，则记录p的位置，此时p就是c的前趋节点
					if (flag_3 == false)
					{//一旦flase_3置为true就不再进行DFS遍历
						index = p->adjvex;  //记录c的双亲结点
						flag_3 = DFS_2(list, c, b, index);
					}

				}
			}

			//必须要三个条件同时满足才能置flag_2为true，表示能表白成功
			if (flag_3 == true && flag_1 == true && topNode == pos_b)
			{
				flag_2 = true;
				break;
			}
			p = p->next;
		}
	}

	return flag_2;
}


void Test(AdjList*list)
{
	char a[MAX_NAME];
	char b[MAX_NAME];
	char c[MAX_NAME];
	int M;
	cout << "请输入数据量M：";
	cin >> M;
	cout << "请分别输入A,B,C村子的编号，用空格隔开" << endl;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b >> c;
		bool flag = DFS_1(list, a, b, c);
		if (flag == true) cout << "Yes!" << endl;
		else cout << "No" << endl;
		cout << endl;
		for (int j = 0; j < list->verNum; j++)
		{
			visited[j] = 0;
		}
		flag_2 = false;   //重置flag_2
	}

}


int main()
{
	AdjList*list = (AdjList*)malloc(sizeof(AdjList));
	CreateGraph(&list);
	cout << endl;
	PrintGraph(list);
	cout << endl;
	Test(list);   //创建测试数据

}

















