#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAXVEX 100
int visited[MAXVEX];

//�߱��� 
typedef struct EdgeNode {
	int adjvex;                //����±� 
	int weight;                //���Ȩֵ 
	struct EdgeNode *next;     //nextָ�� 
} EdgeNode;

//������� 
typedef struct VertexNode {
	int data;                  //������ 
	EdgeNode *firstedge;       // �߱�ָ��
} VertexNode, AdjList[100];

//ͼ���ڽӱ�ṹ 
typedef struct {
	AdjList adjList;
	int maxVertexes, numEdge;   //�������ͱ��� 
} Graph;

void createALGraph(Graph *G) {
	int i, j;
	EdgeNode *e;
	printf("���붥�����ͱ�����");
	scanf("%d%d", &G->maxVertexes, &G->numEdge);
	//���붥��
	for (i = 0; i < G->maxVertexes; i++) {
		scanf("%d", &G->adjList[i].data);
		G->adjList[i].firstedge = NULL;
	}
	//�����
	printf("����ߣ�i, j���ϵĶ��㣺\n");
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