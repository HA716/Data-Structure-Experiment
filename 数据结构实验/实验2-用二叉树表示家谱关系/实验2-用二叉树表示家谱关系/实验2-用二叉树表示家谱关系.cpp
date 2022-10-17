#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
using namespace std;
typedef long long ll;

typedef struct Node {
	string name; //姓名
	Node* left;  //左指针
	Node* right;  //右指针
	Node* parent;  //双亲
	bool isBoy;  //1男 0女
	Node() {
		name = "";
		left = NULL;
		right = NULL;
		parent = NULL;
		isBoy = 1;
	}
}TreeNode;
Node* root = NULL;
ifstream ifs;
ofstream ofs;
string a, b, c;

//根据文件内容建树
void init(TreeNode* &t, int depth = 1) {

	t = new TreeNode();
	t->name = b;
	TreeNode* wife = 0;
	if (c != ".") {
		//有妻子
		wife = new TreeNode();
		wife->name = c;
		wife->isBoy = 0;
		wife->parent = t;
		t->left = wife;
	}
	a = "";

	ifs >> a >> b >> c;	//继续读入3个数据
	if (ifs.eof()) {   //如果读完了，就直接返回
		return;
	}
	if (a.size() == depth) { //辈分一样，说明是兄弟
		init(t->right, depth);  //递归建树
		t->right->parent = t;
	}
	else if (a.size() == depth + 1 && wife) {
		//这是儿子
		init(wife->right, depth + 1);
		wife->right->parent = wife;
	}
	else {
		//如果都不是，那么返回去给上一层
		return;
	}

	//上面递归return后的还剩下的a b c继续判断
	if (a.size() == depth) {
		init(t->right, depth);
		t->right->parent = t;
	}

}

//括号法输出二叉树
void bracketingPrint(TreeNode* t = root) {
	if (!t) {
		return;
	}
	cout << t->name;
	if (t->left || t->right) {
		cout << "(";
		bracketingPrint(t->left);
		if (t->right) {
			cout << ",";
			bracketingPrint(t->right);
		}
		cout << ")";
	}
}

//根据名称寻找
TreeNode* findPeople(string name, TreeNode* t = root) {
	if (!t) {
		return 0;
	}
	if (t->name == name) {
		return t;
	}
	TreeNode* n = findPeople(name, t->left);
	if (n) {
		return n;	//如果在左边找到就返回左边的
	}
	return findPeople(name, t->right);	//否则返回右边的
}

//查找某人的所有儿子
void findAllChildren(string name) {
	cout << "======================================" << endl;
	cout << "find all sons of " << name << endl;
	TreeNode* node = findPeople(name);
	if (!node) {
		cout << "People " << name << " Not Found!!!" << endl;   //找不到这个人
		return;
	}
	if (node->isBoy) {
		//如果是男的
		if (!(node->left)) {
			cout << name << " is no wife!" << endl;   //他没有妻子
			return;
		}
		node = node->left;
	}
	//女的
	if (node->right) {
		node = node->right;
		cout << "All the sons of " << name << " are as follows" << endl;
		while (node) {
			cout << node->name << endl;
			node = node->right;
		}
	}
	else {
		//没有儿子
		cout << name << " is no sons!" << endl;
	}
}

void findAllAncestors(string name) {
	cout << "======================================" << endl;
	cout << "find all ancestors of " << name << endl;
	TreeNode* node = findPeople(name);
	if (!node) {
		cout << "People " << name << " Not Found!!!" << endl;   //找不到这个人
		return;
	}
	if (!node->isBoy) {
		//女，与祖先们不构成血缘关系，忽略
		cout << name << " is not a men!!!" << endl;
		return;
	}
	cout << "All ancestors of " << name << " are as follows:" << endl;
	node = node->parent;
	while (node) {
		if (!node->isBoy) {
			cout << node->name << endl;
			node = node->parent;
			cout << node->name << endl;
		}
		node = node->parent;   //一直往上寻找
	}
}

/*
输出家谱
*/
void printGenealogy(TreeNode* t = root, int depth = 0) {
	if (!t) {
		return;
	}
	cout << string(depth + 1, '#') << " " << t->name << " ";
	if (t->left) {
		cout << t->left->name << endl;
		printGenealogy(t->left->right, depth + 1);
	}
	else {
		cout << "." << endl;
	}
	printGenealogy(t->right, depth);
}
/*
输出家谱到文件
*/
void printGenealogyToFile(TreeNode* t = root, int depth = 0) {
	if (!t || !ofs.is_open()) {
		return;
	}
	ofs << string(depth + 1, '#') << " " << t->name << " ";
	if (t->left) {
		ofs << t->left->name << endl;
		printGenealogyToFile(t->left->right, depth + 1);
	}
	else {
		ofs << "." << endl;
	}
	printGenealogyToFile(t->right, depth);
}

/*
销毁二叉树
*/
void destory(TreeNode* node = root) {
	if (node == NULL) {
		return;  //已经为NULL，无需销毁
	}
	destory(node->left);
	destory(node->right);
	node->left = NULL; //销毁之后需要把指针置空
	node->right = NULL;
	delete node;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	ifs.open("DS Science\\02-05\\data.txt", ios::in); //打开data.txt文件
	ifs >> a >> b >> c;    //读入文件里面的3个数据
	init(root);			//递归建树
	ifs.close();   //使用完成后要关闭流
	bracketingPrint();   //括号法输出
	cout << endl;
	findAllChildren("zhangsan");   //查找zhangsan的所有儿子
	findAllChildren("lujiajing");   //查找lujiajing的所有儿子
	findAllChildren("zhangsansanyi");   //查找所有儿子
	findAllChildren("wodian");   //查找所有儿子
	findAllAncestors("zhangsansanyi");   //查找他的所有祖先
	findAllAncestors("daoweizhi");   //查找他的所有祖先
	cout << "Output genealogy" << endl; // 输出家谱
	printGenealogy();
	//输出家谱到文件
	ofs.open("DS Science\\02-05\\data1.txt", ios::out);
	cout << "Output genealogy to file" << endl; // 输出家谱到文件
	printGenealogyToFile();
	destory();  //销毁二叉树
	root = 0;   //置空
	return 0;
}
