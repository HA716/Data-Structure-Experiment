//利用C++实现深度优先搜索算法，如有疑问请联系
//作者：cclplus 邮箱：maxwell970710@gmail.com
#include<iostream>
#include<vector>
#include<stack>
#include<memory.h>

using namespace std;

vector<vector<int>> tree;//声明一个二维向量
int flag[10];//用于搜索到了节点i的第几个节点
stack <int>stk;//声明一个堆栈
int ar_tree[8] = { 1,1,1,3,5,3,5,7 };
void DFS(int node) {
	cout << node << " ";
	if (flag[node] == 0) {
		stk.push(node);
	}
	int temp;
	//判断node的子节点是否搜索完成
	if (flag[node] < tree[node].size()) {
		temp = tree[node][flag[node]];
		flag[node]++;
		DFS(temp);
	}
	else {//若已经完成
		stk.pop();//弹出子节点
		if (!stk.empty()) {//若堆栈不为空
			temp = stk.top();//取此时的栈顶元素，即为node的上一级节点
			DFS(temp);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	memset(flag, 0, sizeof(flag));
	register int i, temp;
	tree.resize(10);//图中的数共有九个节点
	//生成树
	for (i = 2; i <= 9; i++) {
		temp = ar_tree[i - 2];
		tree[temp].push_back(i);//表示第i个节点为第temp个节点的子节点
	}
	//DFS
	cout << "DFS过程：" << endl;
	DFS(1);
	cout << endl;
	return 0;
}
















