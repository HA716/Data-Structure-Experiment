#include<stdio.h>
#include<stdlib.h>
//void select(HuffMan * huffman, int len, int*pos1, int*pos2);

typedef struct HUFFMANTREE
{
	int weight;     
	int parent;             //˫�׽��������±�
	int leftChild;
	int rightChild;
}HuffMan;

typedef struct HUFFMANCODE
{
	char bit[1000];      //ÿ�����Ĺ���������ĳ��Ȳ�������Ҷ�ӽ�����n-1�������bit����ֻ��Ҫʹ��(n-1)�ĳ��ȡ�
	int start;
}HuffManCode;



//��"Ȩ����"��Ȩֵ��С��������㣺pos1��Ȩֵ��С�Ľ����±꣬pos2��Ȩֵ��С�Ľ����±�
void select(HuffMan * huffman, int len, int*pos1, int*pos2)
{

	int min1 = INT_MAX;       //��Сֵ��32768
	int min2 = INT_MAX;       //��Сֵ��32768
	*pos1 = *pos2 = -1;


	for (int k = 0; k < len ; k++)
	{
		if (huffman[k].parent == -1)         //˵��������û��˫�׽�㣬��δ�����������������
		{
			if (huffman[k].weight < min1)    //˵��huffman[k].weight������Сֵ����min1�Ǵ�Сֵ
			{
				min2 = min1;
				min1 = huffman[k].weight;
				//��Сֵ�±�����Ϊpos1��ֵΪk��pos2��Ȩֵ��С�Ľ����±�����
				*pos2 = *pos1;
				*pos1 = k;
			}

			else if (huffman[k].weight < min2)    //huffman[k].weight�ȴ�Сֵmin2С������huffman[k].weight�����µĴ�Сֵ
			{
				min2 = huffman[k].weight;
				*pos2 = k;           //��Сֵ�±�����Ϊk
			}

			else    //huffman[k].weight���ڴ�Сֵ�������κδ���
			{

			}


		}

	}


}


//                                ��Ȩ����     ��������
HuffMan*Create_HuffManTree(int arrWeight[],int len)
{
	//���ۣ���n��Ҷ�ӽ��Ĺ���������2n-1�����             ������д��(2*n-1) ��ԭ��
	HuffMan * huffman = (HuffMan*)malloc(sizeof(HuffMan)*(2*len-1));
	int n = len;
	//��ʼ��ǰlen��Ҷ�ӽ��
	for (int i = 0; i < len; i++)
	{
		huffman[i].weight = arrWeight[i];
		//��ʼ��Ҷ�ӽ���˫�ס����Һ��� Ϊ-1
		huffman[i].parent = -1;
		huffman[i].leftChild = -1;
		huffman[i].rightChild = -1;
	}
	//��ʼ����n-1����Ҷ�ӽ��
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

	//i�ǹ��������Ľ���������е��±�
	for (int i = len; i < (2 * len - 1); i++)      //����len-1����Ҷ�ӽ��
	{
		//         ��СȨֵ������     ����СȨֵ����
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


	printf("����������\n");
	printf("index\tweight\tparent\tleftChild\trightChild\n");
	for (int i = 0; i < 2 * len - 1; i++)
	{
		printf("%d\t%d\t%d\t%d\t\t%d\n", i, huffman[i].weight, huffman[i].parent, huffman[i].leftChild, huffman[i].rightChild);
	}
}


//HuffManCode* Huffman_Code(HuffMan*huffman, int len)
//{
//	HuffManCode*huffCode = (HuffManCode*)malloc(sizeof(HuffManCode));
//	//����Huffman���룬���н���Huffman��������HuffCodes�У�һ��λ�ô洢һ���ڵ�Ĺ��������룬�������Ĺ�����������bit�����У�
//	int start;
//	//i�ǵ�ǰ��Ҷ�ӽ��
//	for (int i = 0; i < len; i++) {
//		//ÿ�����Ĺ���������ĳ��Ȳ�������Ҷ�ӽ�����len������Ϊ��Ҷ�ӽ��ֻ��len-1�������bit����ֻ��Ҫʹ��(len-1)�ĳ��ȡ�
//        //�������������Ǵӹ���������Ҷ�ӽ�㿪ʼһֱ׷�ݵ�����㰴�����Ҹ���0/1ֵ�ģ����Ե��ű��룬bit������ʼ�±�Ӧ����(len-2)��ÿ����һλ�ͼ�1
//		start = len - 2;
//
//
//		//                                     ����f!=-1˵����û�б����������
//		//              ����ǰ����˫�׽��   ��       ��������һ��ѭ��������        
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
//		huffCode[i].start = start + 1;//��¼��i�����Ĺ��������������Ӧbit�����е���ʼλ��
//	}
//
//	return huffCode;
//}

void Huffman_Code(HuffMan**huffman, int len)
{
	int i = 0;
	int start;
	int parent; //��ǰ����˫�׽��
	int cur;  //��ǰ��Ҷ�ӽ��
	//n��Ҷ�ӽ�㶼���Լ��Ĺ���������
	char* strCode = (char *)malloc(sizeof(char*)*len);
	//��ǰ���Ĺ��������룬��Ϊ��Ҷ�ӽ�������len-1�����Է���len-1��С�ռ伴��
	char* curCode = (char*)malloc(sizeof(char)*(len-1));
	curCode[len - 1] = '\0';
	//��������Ҷ�ӽ��
	for (i = 0; i < len; i++)   
	{
		//��ʼ��������ʼָ��
		start = len - 1;  
		//��Ҷ�ӽ�㿪ʼ�����������
		//�õ�ǰ���curΪҶ�ӽ��i,���Ҷ�ӽ��Ĺ���������
		for (cur = i, parent = (*huffman)[i].parent; parent != 0; cur = parent, parent = (*huffman)[i].parent)
		{
			//Ϊʲô����д��(*huffman)[parent].leftChild ?
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


	//�������������
	for (i = 0; i < len; i++)
	{
		printf("ȨֵΪ%d��Ҷ�ӽ�㣺%d", (*huffman)[i].weight, strCode[i]);
	}

	printf("\n");

}

//��������������ϣ��� n ��Ҷ�ӽ�㵽����������ÿ��Ҷ�ӽ���Ӧ�Ĺ���������
void creatHuffmanCode(HuffMan **huffmanTree, int n)
{
	char **huffmanCode;
	//ָʾbiaoji
	int i;
	//�������ʼָ��
	int start;
	//ָ��ǰ���ĸ��ڵ�
	int p;
	//���� n ��Ҷ�ӽ���ָʾ��� c
	unsigned int c;
	//����n�������ͷָ��
	huffmanCode = (char **)malloc((n + 1) * sizeof(char *));
	//������ǰ����Ĺ����ռ�
	char *cd = (char *)malloc(n * sizeof(char));
	//����������λ��ű��룬���ȴ�ű��������
	cd[n - 1] = '\0';
	//��n��Ҷ�ӽ���Ӧ�Ĺ���������
	for (i = 0; i < n; i++)
	{
		//��ʼ��������ʼָ��
		start = n - 1;
		//��Ҷ�ӵ�����������
		for (c = i, p = (*huffmanTree)[i].parent; p != 0; c = p, p = (*huffmanTree)[p].parent)
		{
			if ((*huffmanTree)[p].leftChild == c)
			{
				//���ҵ����˳�������������
				cd[--start] = '0';  //���֧��0
			}
			else
			{
				cd[--start] = '1';  //�ҷ�֧��1
			}
		}// end of for
		//Ϊ��i���������ռ�
		huffmanCode[i] = (char *)malloc((n - start) * sizeof(char));
		strcpy(huffmanCode[i], &cd[start]);
	}

	free(cd);
	//��ӡ��������
	for (i = 0; i < n; i++)
	{
		printf("HuffmanCode of %3d is %s\n", (*huffmanTree)[i].weight, huffmanCode[i]);
	}

	printf("\n");
}



//��ʼ��Ȩ������
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
	printf("����������\n");
	printf("index\tweight\tparent\tleftChild\trightChild");
	for (int i = 0; i < 2 * len - 1; i++)
	{
		printf("%d  %d %d %d %d", i,huffman[i].weight, huffman[i].parent, huffman[i].leftChild, huffman[i].rightChild);
	}

}



int main()
{
	printf("�������������������Ȩ��\n");
	int len;
	scanf_s("%d", &len);

	//��ʼ��Ȩ�����飬����ȫ����
	int* arrWeight = (int *)malloc(sizeof(int)*len);
	Init(arrWeight, len);
	//BubbleSort(arrWeight, len);
	printf("Ȩ�����ǣ�");
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























