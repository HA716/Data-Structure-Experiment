#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAXVEX 100
int visited[MAXVEX];

//边表结点 
typedef struct EdgeNode {
	int adjvex;                //结点下标 
	int weight;                //结点权值 
	struct EdgeNode *next;     //next指针 
} EdgeNode;

//顶点表结点 
typedef struct VertexNode {
	int data;                  //顶点域 
	EdgeNode *firstedge;       // 边表指针
} VertexNode, AdjList[100];

//图的邻接表结构 
typedef struct {
	AdjList adjList;
	int maxVertexes, numEdge;   //顶点数和边数 
} Graph;

void createALGraph(Graph *G) {
	int i, j;
	EdgeNode *e;
	printf("输入顶点数和边数：");
	scanf("%d%d", &G->maxVertexes, &G->numEdge);
	//输入顶点
	for (i = 0; i < G->maxVertexes; i++) {
		scanf("%d", &G->adjList[i].data);
		G->adjList[i].firstedge = NULL;
	}
	//输入边
	printf("输入边（i, j）上的顶点：\n");
	for (int k = 0; k < G->numEdge; k++) {
		scanf("%d%d", &i, &j);
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;

		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}

void DFS(Graph *G, int i) {
	EdgeNode *p;
	visited[i] = 1;
	printf("%d", G->adjList[i].data);
	p = G->adjList[i].firstedge;
	while (p) {
		if (!visited[p->adjvex]) {
			DFS(G, p->adjvex);
		}
		p = p->next;
	}
}

void DFSTraverse(Graph *G) {
	int i;
	for (i = 0; i < G->maxVertexes; i++) {
		visited[i] = 0;
	}
	for (i = 0; i < G->maxVertexes; i++) {
		if (!visited[i]) {
			DFS(G, i);
		}
	}
}

int main() {
	Graph G;
	createALGraph(&G);
	DFSTraverse(&G);
}