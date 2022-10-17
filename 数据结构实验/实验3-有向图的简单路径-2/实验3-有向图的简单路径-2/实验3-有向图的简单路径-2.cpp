#include<iostream>
#include<stdlib.h>
using namespace std;
#define VEX_MAXNUM 20
#define STACK_H_INCLUDED
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10   //存储空间分配增量

typedef struct SqStack {
	int* base;
	int* top;
	int stacksize;
}SqStack;

void CreateStack(SqStack* S) {
	S->base = (int*)malloc(STACK_INIT_SIZE * sizeof(int*));
	if (!S->base) {
		cout << "存储空间分配失败!" << endl;
		exit(-1);
	}
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
}

void DestroySqStack(SqStack* S) {
	free(S->base);
	S->base = S->top = NULL;
	S->stacksize = 0;
}

void DisplaySqStack(SqStack* S) {
	int* p;
	if (S->top == S->base) {
		cout << "栈空!" << endl;
		exit(-1);
	}
	p = S->base;
	while (p < S->top - 1)
		cout << *p++ << "->";
	cout << *p++;
}

void Push(SqStack* S, int data) {
	if (S->top - S->base == S->stacksize) {
		int* newbase = (int*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(int));
		if (!newbase) {
			cout << "存储空间分配失败!" << endl;
			exit(-1);
		}
		S->base = newbase;
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = data;
}

void Pop(SqStack* S) {
	if (S->top == S->base) {
		cout << "栈空!" << endl;
		exit(-1);
	}
	S->top--;
}

int GetTop(SqStack* S) {
	if (S->top == S->base) {
		cout << "栈空!" << endl;
		exit(-1);
	}
	return *(S->top - 1);
}

int StackLength(SqStack* S) {
	return S->top - S->base;
}

int visited[VEX_MAXNUM];

typedef struct EdgeNode {
	int vex_index;
	struct EdgeNode* next;
}EdgeNode;

typedef struct VexNode {
	int data;
	EdgeNode* edge;
}VexNode, AdjList[VEX_MAXNUM];

typedef struct Graph {
	AdjList list;
	int vexnum, edgenum;
}Graph;

int LocateIndex(Graph* G, int v) {
	int i = 0, j = G->vexnum - 1, mid;
	while (i <= j) {
		mid = (i + j) / 2;
		if (G->list[mid].data == v)
			break;
		else if (v > G->list[mid].data)
			i = mid + 1;
		else
			j = mid - 1;
	}

	if (i > j) {
		cout << "顶点不存在!" << endl;
		exit(-1);
	}

	return mid;
}

void CreateGraph(Graph* G) {
	cout << "请输入图的顶点数和边数:" << endl;
	cin >> G->vexnum >> G->edgenum;

	cout << "请输入顶点:" << endl;
	for (int i = 0; i < G->vexnum; i++) {
		cin >> G->list[i].data;
		G->list[i].edge = NULL;
	}

	cout << "请输入边:" << endl;
	for (int k = 0; k < G->edgenum; k++) {
		int v1, v2, i, j;
		EdgeNode* p, *q;
		cin >> v1 >> v2;
		i = LocateIndex(G, v1);
		j = LocateIndex(G, v2);

		p = (EdgeNode*)malloc(sizeof(EdgeNode));
		p->vex_index = j;
		p->next = NULL;
		q = G->list[i].edge;
		if (!q)
			G->list[i].edge = p;
		else {
			while (q->next)
				q = q->next;
			q->next = p;
		}

		/*p = (EdgeNode*)malloc(sizeof(EdgeNode));
		p->vex_index = i;
		p->next = NULL;
		q = G->list[j].edge;
		if (!q)
			G->list[j].edge = p;
		else {
			while (q->next)
				q = q->next;
			q->next = p;
		}*/
	}
}

void DestroyGraph(Graph* G) {
	VexNode* p;
	EdgeNode* q;
	for (int i = 0; i < G->vexnum; i++) {
		p = &G->list[i];
		while (p->edge) {
			q = p->edge;
			p->edge = q->next;
			free(q);
		}
	}
}

void DFSALLPath(Graph* G, int index1, int index2, SqStack*S) {
	EdgeNode* p;
	visited[index1] = 1;
	Push(S, index1);
	if (index1 == index2) {
		DisplaySqStack(S);
		cout << endl;
		Pop(S);
		visited[index1] = 0;
		return;
	}

	p = G->list[index1].edge;
	while (p) {
		if (!visited[p->vex_index])
			DFSALLPath(G, p->vex_index, index2, S);
		p = p->next;
	}

	Pop(S);
	visited[index1] = 0;
}

void PrintAllPath(Graph* G, int index1, int index2) {
	SqStack S;
	CreateStack(&S);
	for (int i = 0; i < G->vexnum; i++)
		visited[i] = 0;
	DFSALLPath(G, index1, index2, &S);
}

int main() {
	Graph G;
	int start, end;

	CreateGraph(&G);
	cout << "请输入起点:" << endl;
	cin >> start;
	cout << "请输入终点:" << endl;
	cin >> end;
	cout << "两顶点间的所有路径:" << endl;

	PrintAllPath(&G, LocateIndex(&G, start), LocateIndex(&G, end));
	DestroyGraph(&G);
	return 0;
}
