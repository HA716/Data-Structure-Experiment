#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#pragma warning(disable:4996) 

#define maxSize 256
#define halfMax maxSize/2


//题目：用哈夫曼树实现文件的解压缩过程


//哈夫曼树的结点
typedef struct HAFFMAN
{
	char data;       //结点的数据域，用来存放字符
	int weight;      //结点的权重
	struct HAFFMAN * leftChild;    //左子树
	struct HAFFMAN * rightChild;   //右子树

}HaffMan;

HaffMan nodeArr[maxSize];     //顺序存储的方式来构建哈夫曼树，用数组用来存放哈夫曼树的结点
HaffMan leftChild[halfMax];   //用来保存左孩子
HaffMan rightChild[halfMax];  //用来保存右孩子



//使用二维数组来存储哈夫曼编码，其中第一维数组的下标就是ASCLL码值，第二维数组用来存储结点编码出来的字符串
//在英文集中，ASCLL的范围是0-127,共128个
//!!!
char code[maxSize][halfMax];     //例如： code={"0011","1010"...}  --> code[1]="1010"  --> code[1][0] ="1"



//对权重进行由大到小的排序，此处选择冒泡排序
void Sort(HaffMan*nodeArr, int len)
{
	HaffMan temp;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (nodeArr[j].weight < nodeArr[j + 1].weight)
			{
				temp = nodeArr[j];
				nodeArr[j] = nodeArr[j + 1];
				nodeArr[j + 1] = temp;
			}
		}
	}
}


//创建哈夫曼树：nodeArr是保存哈夫曼树结点的数组，nodeArr[0]是哈夫曼树的根节点，len是这个数组的长度
void Creat(HaffMan * nodeArr, int len)
{
	if (len <=1)   //把nodeArr看成是根节点，所以数组中至少有一个结点了
	{
		return;
	}
	Sort(nodeArr, len); //对结点的权重进行由大到小的排序
	//构建父节点parent:其中父节点的左孩子、右孩子分别是结点数组的最后两个元素，因为上一条语句已经对权重进行了从大到小的排序了
	leftChild[len] = nodeArr[len - 1];   //左孩子是结点数组的最后一个元素，因为这个元素的权重最小
	rightChild[len] = nodeArr[len - 2];  //右孩子是结点数组的倒数第二个元素，因为这个元素的权重次小
	HaffMan parent;
	//构建父节点
	parent.leftChild  = &leftChild[len];
	parent.rightChild = &rightChild[len];
	parent.weight = leftChild[len].weight + rightChild[len].weight;
	//将结点数组的倒数第二个元素替换成父结点，然后结点数组的长度-1,最后递归创建哈夫曼树！！！
	nodeArr[len - 2] = parent;
	Creat(nodeArr, len - 1);


}


//编码原理：左结点的权记为0，右结点的权记为1
//编码压缩：将结点数组中的数据转换成‘0\1字符序列’保存到临时数组temp中去（temp就是编码后的结点数组）                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
void Coding(HaffMan * nodeArr, char * temp, int index)       //index是结点数组nodeArr当前字符的下标,初始值为0
{
	if (nodeArr == NULL)
	{
		return;
	}
	//发现叶子结点，此时就要将结点信息复制到编码数组temp中去，而temp数组就是由‘0\1字符序列’构成的字符串
	if (nodeArr->leftChild == NULL && nodeArr->rightChild == NULL)
	{
		temp[index] = '\0';         //字符串以'\0'结尾，最后形成 temp={'0','1',...,'\0'}这样的数组
		//nodeArr->data就是结点的数据域，相当于A、B、C...,强转成整形就变成其对应的ASCLL码值了
		strcpy(code[(int)nodeArr->data], temp);       //code[(int)nodeArr->data]相当于第一维，temp相当于第二维
		return;
	}
	//当不是叶子结点
	else
	{
      //左分支编码为‘0’，右分支编码为‘1’
		temp[index] = '0';
		Coding(nodeArr->leftChild, temp, index + 1);
		temp[index] = '1';
		Coding(nodeArr->rightChild, temp, index + 1);


	}
}

//译码原理：遇到'0'向左，遇到'1'向右，直到遇到叶结点就翻译出字符
//译码解压缩：将‘0/1’序列译码成左右子树 , 其中flag是0/1，用来判断要翻译成左子树还是右子树
HaffMan* deCoding(HaffMan * nodeArr, int flag)
{
	if (flag == 0)
	{
		return nodeArr->leftChild;
	}
	if (flag == 1)
	{
		return nodeArr->rightChild;
	}
	else
	{
	   return NULL;
	}
}




int main()
{
	unsigned int saveChar=0;     //保存到二进制文件中的无符号字符
	unsigned int tempChar;
	FILE * inputFile = fopen("input.txt", "r");   //待解码文件以只读方式打开文件
	FILE * zipFile = fopen("ziped.txt", "wb");    //编码压缩后的文件以二进制方式写入

	int fileLength = 0;  //文件中存放的字符个数
	//权数组：读取待编码文件，统计其中各个字符出现的次数
	int AscllArr[128] = { 0 };  //初始话各个字符出现的次数为0
	char readChar;
	while ((readChar = fgetc(inputFile)) != EOF)      // fgetc()是逐字符读取文件字符
	{
		fileLength++;
		AscllArr[(int)readChar]++;    //第(int)readChar号字符出现的次数++
		//printf("%d", (int)readChar);
	}

	int num = 0; //统计有权重的结点的数量(num是计数器)
	for (int i = 0; i < 128; i++)  //英文集对应的ASCLL码的数量是128
	{
	//	printf("%d", i);
		if (AscllArr[i] != 0)     //ASCLL码为i的字符的权重不为0
		{
			nodeArr[num].data = i;  //第num个结点存放的是ASCLL码值i对应的字符
			
			nodeArr[num].weight = AscllArr[i]; //第num个结点的权重是AscllArr[i]
		//	printf("nodeArr[num].data:%c\n", nodeArr[num].data);
		//	printf("nodeArr[num].weight:%d\n", nodeArr[num].weight);
			num++;
		//	printf("num:%d\n", num);
			
		}

	}




	//创建哈夫曼树
	Creat(nodeArr, num);
	//进行哈夫曼树编码
	char temp[maxSize];       //存放由结点编码而来的0\1序列
	Coding(nodeArr, temp, 0);  //从第0个元素开始编码

	//逐位将编码保存到文件zipedFile中
	num = 0;    //num是计数器，统计
	//文件指针复位：移动到文件头
	fseek(inputFile, 0L, 0);  //将文件指针inputFile从文件开头（0）移到离文件开头0（0L）个字节处
	int zipLen = 0;      //压缩后的文件数量

	while ((readChar = fgetc(inputFile))!= EOF)  //逐个字符读文件
	{
		//遍历得到字符对应的字符编码（如 "1001"，"0001"....）

		//code[(int)A]==1001 可以理解为：到达叶节点A的路径是1001，即 左右右左
		//code[(int)A][0]=="1"

		for (int i = 0; i < strlen(code[(int)readChar]); i++)
		{   //code[(int)readChar是由0、1序列组成的字符串
			//通过按位或操作将运算结果保存到saceChar中
			saveChar |= (code[(int)readChar][i] - '0');   //code[(int)readChar][i]只能等于0或1

			num++;

			//每读完8个0/1字符 就写入一次文件,在文件里面是按1个字节存储
			if (num == 8)
			{
		    //从zipFile中读取，每次向saveChar中写入1个大小为sizeof(unsigned char)的数据
				fwrite(&saveChar, sizeof(unsigned char), 1, zipFile);
				zipLen++;   //压缩后文件的字符个数加1
				num = 0;
				saveChar = 0;
			}
			else
			{
				saveChar <<= 1;  //左移一位，低位补0，继续循环与00000001做按位或运算

			}
		}
	}



	//如果最后剩余的编码不足8位，就移动到最左端，即移动8-num位，凑够8位
	if (num < 8)
	{
		saveChar = saveChar << (8 - num);
		fwrite(&saveChar, sizeof(unsigned char), 1, zipFile);  //按1个字节的大小进行每次写入
		zipLen++;
		saveChar = 0;
	}

	//关闭文件
	fclose(inputFile);
	fclose(zipFile);
	printf("压缩成功：压缩前字符个数为 %d \n 压缩后字符个数 %d", fileLength, zipLen);





	//解压缩
	zipFile = fopen("ziped.txt","rb");    //以二进制只读方式打开
	FILE* resultFile = fopen("result.txt", "w");   //只读方式写入
	num = 0;  //计数器清0
	HaffMan * currNode = &nodeArr[0];    //当前结点初始化为根节点
	while (fread(&readChar, sizeof(unsigned char), 1, zipFile))  //从文件对象zipFile中每次读取1个大小为sizeof(unsigned char)的元素到readChar中
	{
		//fileLength是文件中字符的个数
		if (fileLength == num) break;
		for (int i = 0; i < 8; i++)  // sizeof(unsigned char) = 8 
		{
			tempChar = readChar & 128;   // 128 = 10000000，所以tempChar就是readChar的最高位
			tempChar >>= 7;    //抹掉0，仅剩最高位： 10000000>>7 = 1    0000000>>7 = 0
			readChar <<= 1;    //最高位已经被提取，所以让次高位补上

			currNode = deCoding(currNode, (int)tempChar);  //更新当前结点位置

			//判断叶节点
			if (currNode->leftChild == NULL && currNode->rightChild == NULL)
			{
				
				fprintf(resultFile, "%c", currNode->data);  //把currNode->data写入到resultFile中
				num++;    //统计文件resultFile中的字符数量
				currNode = &nodeArr[0];      //每找到一个叶节点，就将当前结点重置为根节点
			}
		    	
		}


	}

	fclose(zipFile);
	fclose(resultFile);
	printf("\n%s", "解压缩完成");

	return 0;

}

















