#include <iostream>
#include <string.h>
#define INT_MAX 1000000000
using namespace std;

int matrix[100][100];//邻接矩阵
bool visited[100];//标记数组
int path[100];//记录生成树路径
int lowcost[100];//边的权值
int vertex_num, arc_num;//顶点数，弧数
int sum;//权值总和
int source;//源点
void prim(int source);
int main()
{
	cout << "请输入图的顶点数（<=100）：";
	cin >> vertex_num;
	cout << "请输入图的弧数：";
	cin >> arc_num;

	for (int i = 0; i < vertex_num; i++)
		for (int j = 0; j < vertex_num; j++)
			matrix[i][j] = INT_MAX;  //初始化matrix数组

	cout << "请输入弧的信息：\n";
	int u, v, w;
	for (int i = 0; i < arc_num; i++)
	{
		cin >> u >> v >> w;
		matrix[u][v] = matrix[v][u] = w;
	}


	cout << "请输入起点（<" << vertex_num << "）：";
	cin >> source;
	prim(source);

	cout << "最小生成树权和为：" << sum << endl;
	cout << "最小生成树路径为：\n";
	for (int i = 0; i < vertex_num; i++)
		if (i != source)
			cout << i << "----" << path[i] << endl;

	return 0;
}
void prim(int source) {
	memset(visited, 0, sizeof(visited));
	visited[source] = true;
	for (int i = 0; i < vertex_num; i++) {
		lowcost[i] = matrix[source][i];
		path[i] = source;
	}

	int min_cost, min_cost_index;//最小的权值，和其下标
	sum = 0;
	for (int i = 1; i < vertex_num; i++) {//找除源点外的n-1个点,如果这里写多了，
								//那么下边的for里if进不去，那么sum的值也会错误
		min_cost = INT_MAX;

		for (int j = 0; j < vertex_num; j++) {//遍历所有顶点
			if (visited[j] == false && lowcost[j] < min_cost) {//找到与源点的权值最小的点
				min_cost = lowcost[j];
				min_cost_index = j;
			}
		}
		visited[min_cost_index] = true;//将找到的顶点进行标记
		sum += min_cost;//权值总和

		for (int j = 0; j < vertex_num; j++) {
			if (visited[j] == false && matrix[min_cost_index][j] < lowcost[j]) {//更新lowcost，以便找下个顶点
				lowcost[j] = matrix[min_cost_index][j];
				path[j] = min_cost_index;
			}
		}
	}


}