#include <iostream>
#include <string.h>
#define INT_MAX 1000000000
using namespace std;

int matrix[100][100];//�ڽӾ���
bool visited[100];//�������
int path[100];//��¼������·��
int lowcost[100];//�ߵ�Ȩֵ
int vertex_num, arc_num;//������������
int sum;//Ȩֵ�ܺ�
int source;//Դ��
void prim(int source);
int main()
{
	cout << "������ͼ�Ķ�������<=100����";
	cin >> vertex_num;
	cout << "������ͼ�Ļ�����";
	cin >> arc_num;

	for (int i = 0; i < vertex_num; i++)
		for (int j = 0; j < vertex_num; j++)
			matrix[i][j] = INT_MAX;  //��ʼ��matrix����

	cout << "�����뻡����Ϣ��\n";
	int u, v, w;
	for (int i = 0; i < arc_num; i++)
	{
		cin >> u >> v >> w;
		matrix[u][v] = matrix[v][u] = w;
	}


	cout << "��������㣨<" << vertex_num << "����";
	cin >> source;
	prim(source);

	cout << "��С������Ȩ��Ϊ��" << sum << endl;
	cout << "��С������·��Ϊ��\n";
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

	int min_cost, min_cost_index;//��С��Ȩֵ�������±�
	sum = 0;
	for (int i = 1; i < vertex_num; i++) {//�ҳ�Դ�����n-1����,�������д���ˣ�
								//��ô�±ߵ�for��if����ȥ����ôsum��ֵҲ�����
		min_cost = INT_MAX;

		for (int j = 0; j < vertex_num; j++) {//�������ж���
			if (visited[j] == false && lowcost[j] < min_cost) {//�ҵ���Դ���Ȩֵ��С�ĵ�
				min_cost = lowcost[j];
				min_cost_index = j;
			}
		}
		visited[min_cost_index] = true;//���ҵ��Ķ�����б��
		sum += min_cost;//Ȩֵ�ܺ�

		for (int j = 0; j < vertex_num; j++) {
			if (visited[j] == false && matrix[min_cost_index][j] < lowcost[j]) {//����lowcost���Ա����¸�����
				lowcost[j] = matrix[min_cost_index][j];
				path[j] = min_cost_index;
			}
		}
	}


}