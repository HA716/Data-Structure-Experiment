#include<stdio.h>
#include<stdlib.h>
//void select(HuffMan * huffman, int len, int*pos1, int*pos2);

typedef struct HUFFMANTREE
{
	int weight;     
	int parent;             //双亲结点的数组下标
	int leftChild;
	int rightChild;
}HuffMan;

typedef struct HUFFMANCODE
{
	char bit[1000];      //每个结点的哈夫曼编码的长度不超过（叶子结点个数n-1），因此bit数组只需要使用(n-1)的长度。
	int start;
}HuffManCode;



//找"权数组"中权值最小的两个结点：pos1是权值最小的结点的下标，pos2是权值次小的结点的下标
void select(HuffMan * huffman, int len, int*pos1, int*pos2)
{

	int min1 = INT_MAX;       //最小值，32768
	int min2 = INT_MAX;       //次小值，32768
	*pos1 = *pos2 = -1;


	for (int k = 0; k < len ; k++)
	{
		if (huffman[k].parent == -1)         //说明这个结点没有双亲结点，还未被用来构造哈夫曼树
		{
			if (huffman[k].weight < min1)    //说明huffman[k].weight才是最小值，而min1是次小值
			{
				min2 = min1;
				min1 = huffman[k].weight;
				//最小值下标索引为pos1，值为k；pos2是权值次小的结点的下标索引
				*pos2 = *pos1;
				*pos1 = k;
			}

			else if (huffman[k].weight < min2)    //huffman[k].weight比次小值min2小，所以huffman[k].weight才是新的次小值
			{
				min2 = huffman[k].weight;
				*pos2 = k;           //次小值下标索引为k
			}

			else    //huffman[k].weight大于次小值，不做任何处理
			{

			}


		}

	}


}


//                                ↓权数组     ↓结点个数
HuffMan*Create_HuffManTree(int arrWeight[],int len)
{
	//结论：有n个叶子结点的哈夫曼树有2n-1个结点             ↓不能写成(2*n-1) ，原因？
	HuffMan * huffman = (HuffMan*)malloc(sizeof(HuffMan)*(2*len-1));
	int n = len;
	//初始化前len个叶子结点
	for (int i = 0; i < len; i++)
	{
		huffman[i].weight = arrWeight[i];
		//初始化叶子结点的双亲、左右孩子 为-1
		huffman[i].parent = -1;
		huffman[i].leftChild = -1;
		huffman[i].rightChild = -1;
	}
	//初始化后n-1个非叶子结点
	for (int i = len; i < 2*len-1; i++)
	{
		huffman[i].weight = -1;
		huffman[i].parent = -1;
		huffman[i].leftChild = -1;
		huffman[i].rightChild =-1;
	}

	int pos1 = 0;
	int pos2 = 0;
	double min1, min2;

	//i是哈夫曼树的结点在数组中的下标
	for (int i = len; i < (2 * len - 1); i++)      //创建len-1个非叶子结点
	{
		//         最小权值索引↓     ↓次小权值索引
		//select(huffman, n, &pos1, &pos2);
		//printf("pos1:%d\n", pos1);
		//printf("pos2:%d\n", pos2);

		min1 = min2 = INT_MAX;
		pos1 = pos2 = -1;
		for (int k = 0; k < i ;k++)
		{
			if (huffman[k].parent == -1)
			{
				if (huffman[k].weight < min1)
				{
					min2 = min1;
					pos2 = pos1;
					min1 = huffman[k].weight;
					pos1 = k;
				}
				else if (huffman[k].weight < min2)
				{
					min2 = huffman[k].weight;
					pos2 = k;
				}
			}
		}
	    printf("pos1:%d\n", pos1);
		printf("pos2:%d\n", pos2);

		huffman[pos1].parent = i;
		huffman[pos2].parent = i;
		huffman[i].leftChild = pos1; 
		huffman[i].rightChild = pos2;
		huffman[i].weight = huffman[pos1].weight + huffman[pos2].weight;
	
	}


	printf("哈夫曼树：\n");
	printf("index\tweight\tparent\tleftChild\trightChild\n");
	for (int i = 0; i < 2 * len - 1; i++)
	{
		printf("%d\t%d\t%d\t%d\t\t%d\n", i, huffman[i].weight, huffman[i].parent, huffman[i].leftChild, huffman[i].rightChild);
	}
}


//HuffManCode* Huffman_Code(HuffMan*huffman, int len)
//{
//	HuffManCode*huffCode = (HuffManCode*)malloc(sizeof(HuffManCode));
//	//生成Huffman编码，所有结点的Huffman编码存放在HuffCodes中（一个位置存储一个节点的哈夫曼编码，单个结点的哈夫曼编码在bit数组中）
//	int start;
//	//i是当前的叶子结点
//	for (int i = 0; i < len; i++) {
//		//每个结点的哈夫曼编码的长度不超过（叶子结点个数len），因为非叶子结点只有len-1个，因此bit数组只需要使用(len-1)的长度。
//        //而哈夫曼编码是从哈夫曼树的叶子结点开始一直追溯到根结点按照左右赋予0/1值的，所以倒着编码，bit数组起始下标应该是(len-2)，每编码一位就减1
//		start = len - 2;
//
//
//		//                                     ↓若f!=-1说明还没有遍历到根结点
//		//              ↓当前结点的双亲结点   ↓       ↓创建下一次循环的条件        
//		for (int c = i, f = huffman[i].parent; f != -1; c = f, f = huffman[f].parent) {
//			if (c == huffman[f].leftChild)
//			{
//				huffCode[i].bit[start--] = 0;
//			}
//			if (c == huffman[f].rightChild)
//			{
//				huffCode[i].bit[start--] = 1;
//			}	
//		}
//
//		huffCode[i].start = start + 1;//记录第i个结点的哈夫曼编码在其对应bit数组中的起始位置
//	}
//
//	return huffCode;
//}

void Huffman_Code(HuffMan**huffman, int len)
{
	int i = 0;
	int start;
	int parent; //当前结点的双亲结点
	int cur;  //当前的叶子结点
	//n个叶子结点都有自己的哈夫曼编码
	char* strCode = (char *)malloc(sizeof(char*)*len);
	//当前结点的哈夫曼编码，因为非叶子结点最多有len-1，所以分配len-1大小空间即可
	char* curCode = (char*)malloc(sizeof(char)*(len-1));
	curCode[len - 1] = '\0';
	//遍历所有叶子结点
	for (i = 0; i < len; i++)   
	{
		//初始化编码起始指针
		start = len - 1;  
		//从叶子结点开始求哈夫曼编码
		//置当前结点cur为叶子结点i,求该叶子结点的哈夫曼编码
		for (cur = i, parent = (*huffman)[i].parent; parent != 0; cur = parent, parent = (*huffman)[i].parent)
		{
			//为什么不是写成(*huffman)[parent].leftChild ?
			if ((*huffman)[i].leftChild == cur)
			{
				curCode[--start] = '0';
			}
			else
			{
				curCode[--start] = '1';
			}
		}
		strCode[i] = (char*)malloc((len - start) * sizeof(char));
		strcpy(strCode[i], &curCode[start]);
	}
	free(curCode);


	//输出哈夫曼编码
	for (i = 0; i < len; i++)
	{
		printf("权值为%d的叶子结点：%d", (*huffman)[i].weight, strCode[i]);
	}

	printf("\n");

}

//哈夫曼树建立完毕，从 n 个叶子结点到根，逆向求每个叶子结点对应的哈夫曼编码
void creatHuffmanCode(HuffMan **huffmanTree, int n)
{
	char **huffmanCode;
	//指示biaoji
	int i;
	//编码的起始指针
	int start;
	//指向当前结点的父节点
	int p;
	//遍历 n 个叶子结点的指示标记 c
	unsigned int c;
	//分配n个编码的头指针
	huffmanCode = (char **)malloc((n + 1) * sizeof(char *));
	//分配求当前编码的工作空间
	char *cd = (char *)malloc(n * sizeof(char));
	//从右向左逐位存放编码，首先存放编码结束符
	cd[n - 1] = '\0';
	//求n个叶子结点对应的哈夫曼编码
	for (i = 0; i < n; i++)
	{
		//初始化编码起始指针
		start = n - 1;
		//从叶子到根结点求编码
		for (c = i, p = (*huffmanTree)[i].parent; p != 0; c = p, p = (*huffmanTree)[p].parent)
		{
			if ((*huffmanTree)[p].leftChild == c)
			{
				//从右到左的顺序编码入数组内
				cd[--start] = '0';  //左分支标0
			}
			else
			{
				cd[--start] = '1';  //右分支标1
			}
		}// end of for
		//为第i个编码分配空间
		huffmanCode[i] = (char *)malloc((n - start) * sizeof(char));
		strcpy(huffmanCode[i], &cd[start]);
	}

	free(cd);
	//打印编码序列
	for (i = 0; i < n; i++)
	{
		printf("HuffmanCode of %3d is %s\n", (*huffmanTree)[i].weight, huffmanCode[i]);
	}

	printf("\n");
}



//初始化权重数组
void Init(int arr[], int len)
{
	int weight;
	for (int i = 0; i < len; i++)
	{
		scanf_s("%d", &weight);
		arr[i] = weight;
		getchar();
	}

}


void Print_HuffmanTree(HuffMan*huffman, int len)
{
	printf("哈夫曼树：\n");
	printf("index\tweight\tparent\tleftChild\trightChild");
	for (int i = 0; i < 2 * len - 1; i++)
	{
		printf("%d  %d %d %d %d", i,huffman[i].weight, huffman[i].parent, huffman[i].leftChild, huffman[i].rightChild);
	}

}



int main()
{
	printf("请输入结点个数、各结点的权重\n");
	int len;
	scanf_s("%d", &len);

	//初始化权重数组，并完全排序
	int* arrWeight = (int *)malloc(sizeof(int)*len);
	Init(arrWeight, len);
	//BubbleSort(arrWeight, len);
	printf("权数组是：");
	for (int i = 0; i < len; i++)
	{
		printf("%d  ", arrWeight[i]);
	}
	HuffMan * huffman = Create_HuffManTree(arrWeight, len);
	printf("\n");
	//Huffman_Code(&huffman, len);

	creatHuffmanCode(&huffman, len);
		//Print_HuffmanTree(huffman, len);

	//HuffManCode*huffCode = Huffman_Code(huffman, len);


}























