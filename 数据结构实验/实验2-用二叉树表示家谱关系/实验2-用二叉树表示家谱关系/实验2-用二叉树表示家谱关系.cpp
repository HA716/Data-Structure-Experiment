#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
using namespace std;
typedef long long ll;

typedef struct Node {
	string name; //����
	Node* left;  //��ָ��
	Node* right;  //��ָ��
	Node* parent;  //˫��
	bool isBoy;  //1�� 0Ů
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

//�����ļ����ݽ���
void init(TreeNode* &t, int depth = 1) {

	t = new TreeNode();
	t->name = b;
	TreeNode* wife = 0;
	if (c != ".") {
		//������
		wife = new TreeNode();
		wife->name = c;
		wife->isBoy = 0;
		wife->parent = t;
		t->left = wife;
	}
	a = "";

	ifs >> a >> b >> c;	//��������3������
	if (ifs.eof()) {   //��������ˣ���ֱ�ӷ���
		return;
	}
	if (a.size() == depth) { //����һ����˵�����ֵ�
		init(t->right, depth);  //�ݹ齨��
		t->right->parent = t;
	}
	else if (a.size() == depth + 1 && wife) {
		//���Ƕ���
		init(wife->right, depth + 1);
		wife->right->parent = wife;
	}
	else {
		//��������ǣ���ô����ȥ����һ��
		return;
	}

	//����ݹ�return��Ļ�ʣ�µ�a b c�����ж�
	if (a.size() == depth) {
		init(t->right, depth);
		t->right->parent = t;
	}

}

//���ŷ����������
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

//��������Ѱ��
TreeNode* findPeople(string name, TreeNode* t = root) {
	if (!t) {
		return 0;
	}
	if (t->name == name) {
		return t;
	}
	TreeNode* n = findPeople(name, t->left);
	if (n) {
		return n;	//���������ҵ��ͷ�����ߵ�
	}
	return findPeople(name, t->right);	//���򷵻��ұߵ�
}

//����ĳ�˵����ж���
void findAllChildren(string name) {
	cout << "======================================" << endl;
	cout << "find all sons of " << name << endl;
	TreeNode* node = findPeople(name);
	if (!node) {
		cout << "People " << name << " Not Found!!!" << endl;   //�Ҳ��������
		return;
	}
	if (node->isBoy) {
		//������е�
		if (!(node->left)) {
			cout << name << " is no wife!" << endl;   //��û������
			return;
		}
		node = node->left;
	}
	//Ů��
	if (node->right) {
		node = node->right;
		cout << "All the sons of " << name << " are as follows" << endl;
		while (node) {
			cout << node->name << endl;
			node = node->right;
		}
	}
	else {
		//û�ж���
		cout << name << " is no sons!" << endl;
	}
}

void findAllAncestors(string name) {
	cout << "======================================" << endl;
	cout << "find all ancestors of " << name << endl;
	TreeNode* node = findPeople(name);
	if (!node) {
		cout << "People " << name << " Not Found!!!" << endl;   //�Ҳ��������
		return;
	}
	if (!node->isBoy) {
		//Ů���������ǲ�����ѪԵ��ϵ������
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
		node = node->parent;   //һֱ����Ѱ��
	}
}

/*
�������
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
������׵��ļ�
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
���ٶ�����
*/
void destory(TreeNode* node = root) {
	if (node == NULL) {
		return;  //�Ѿ�ΪNULL����������
	}
	destory(node->left);
	destory(node->right);
	node->left = NULL; //����֮����Ҫ��ָ���ÿ�
	node->right = NULL;
	delete node;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	ifs.open("DS Science\\02-05\\data.txt", ios::in); //��data.txt�ļ�
	ifs >> a >> b >> c;    //�����ļ������3������
	init(root);			//�ݹ齨��
	ifs.close();   //ʹ����ɺ�Ҫ�ر���
	bracketingPrint();   //���ŷ����
	cout << endl;
	findAllChildren("zhangsan");   //����zhangsan�����ж���
	findAllChildren("lujiajing");   //����lujiajing�����ж���
	findAllChildren("zhangsansanyi");   //�������ж���
	findAllChildren("wodian");   //�������ж���
	findAllAncestors("zhangsansanyi");   //����������������
	findAllAncestors("daoweizhi");   //����������������
	cout << "Output genealogy" << endl; // �������
	printGenealogy();
	//������׵��ļ�
	ofs.open("DS Science\\02-05\\data1.txt", ios::out);
	cout << "Output genealogy to file" << endl; // ������׵��ļ�
	printGenealogyToFile();
	destory();  //���ٶ�����
	root = 0;   //�ÿ�
	return 0;
}
