//����C++ʵ��������������㷨��������������ϵ
//���ߣ�cclplus ���䣺maxwell970710@gmail.com
#include<iostream>
#include<vector>
#include<stack>
#include<memory.h>

using namespace std;

vector<vector<int>> tree;//����һ����ά����
int flag[10];//�����������˽ڵ�i�ĵڼ����ڵ�
stack <int>stk;//����һ����ջ
int ar_tree[8] = { 1,1,1,3,5,3,5,7 };
void DFS(int node) {
	cout << node << " ";
	if (flag[node] == 0) {
		stk.push(node);
	}
	int temp;
	//�ж�node���ӽڵ��Ƿ��������
	if (flag[node] < tree[node].size()) {
		temp = tree[node][flag[node]];
		flag[node]++;
		DFS(temp);
	}
	else {//���Ѿ����
		stk.pop();//�����ӽڵ�
		if (!stk.empty()) {//����ջ��Ϊ��
			temp = stk.top();//ȡ��ʱ��ջ��Ԫ�أ���Ϊnode����һ���ڵ�
			DFS(temp);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	memset(flag, 0, sizeof(flag));
	register int i, temp;
	tree.resize(10);//ͼ�е������оŸ��ڵ�
	//������
	for (i = 2; i <= 9; i++) {
		temp = ar_tree[i - 2];
		tree[temp].push_back(i);//��ʾ��i���ڵ�Ϊ��temp���ڵ���ӽڵ�
	}
	//DFS
	cout << "DFS���̣�" << endl;
	DFS(1);
	cout << endl;
	return 0;
}
















