#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#pragma warning(disable:4996) 

#define maxSize 256
#define halfMax maxSize/2


//��Ŀ���ù�������ʵ���ļ��Ľ�ѹ������


//���������Ľ��
typedef struct HAFFMAN
{
	char data;       //������������������ַ�
	int weight;      //����Ȩ��
	struct HAFFMAN * leftChild;    //������
	struct HAFFMAN * rightChild;   //������

}HaffMan;

HaffMan nodeArr[maxSize];     //˳��洢�ķ�ʽ����������������������������Ź��������Ľ��
HaffMan leftChild[halfMax];   //������������
HaffMan rightChild[halfMax];  //���������Һ���



//ʹ�ö�ά�������洢���������룬���е�һά������±����ASCLL��ֵ���ڶ�ά���������洢������������ַ���
//��Ӣ�ļ��У�ASCLL�ķ�Χ��0-127,��128��
//!!!
char code[maxSize][halfMax];     //���磺 code={"0011","1010"...}  --> code[1]="1010"  --> code[1][0] ="1"



//��Ȩ�ؽ����ɴ�С�����򣬴˴�ѡ��ð������
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


//��������������nodeArr�Ǳ�����������������飬nodeArr[0]�ǹ��������ĸ��ڵ㣬len���������ĳ���
void Creat(HaffMan * nodeArr, int len)
{
	if (len <=1)   //��nodeArr�����Ǹ��ڵ㣬����������������һ�������
	{
		return;
	}
	Sort(nodeArr, len); //�Խ���Ȩ�ؽ����ɴ�С������
	//�������ڵ�parent:���и��ڵ�����ӡ��Һ��ӷֱ��ǽ��������������Ԫ�أ���Ϊ��һ������Ѿ���Ȩ�ؽ����˴Ӵ�С��������
	leftChild[len] = nodeArr[len - 1];   //�����ǽ����������һ��Ԫ�أ���Ϊ���Ԫ�ص�Ȩ����С
	rightChild[len] = nodeArr[len - 2];  //�Һ����ǽ������ĵ����ڶ���Ԫ�أ���Ϊ���Ԫ�ص�Ȩ�ش�С
	HaffMan parent;
	//�������ڵ�
	parent.leftChild  = &leftChild[len];
	parent.rightChild = &rightChild[len];
	parent.weight = leftChild[len].weight + rightChild[len].weight;
	//���������ĵ����ڶ���Ԫ���滻�ɸ���㣬Ȼ��������ĳ���-1,���ݹ鴴����������������
	nodeArr[len - 2] = parent;
	Creat(nodeArr, len - 1);


}


//����ԭ�������Ȩ��Ϊ0���ҽ���Ȩ��Ϊ1
//����ѹ��������������е�����ת���ɡ�0\1�ַ����С����浽��ʱ����temp��ȥ��temp���Ǳ����Ľ�����飩                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
void Coding(HaffMan * nodeArr, char * temp, int index)       //index�ǽ������nodeArr��ǰ�ַ����±�,��ʼֵΪ0
{
	if (nodeArr == NULL)
	{
		return;
	}
	//����Ҷ�ӽ�㣬��ʱ��Ҫ�������Ϣ���Ƶ���������temp��ȥ����temp��������ɡ�0\1�ַ����С����ɵ��ַ���
	if (nodeArr->leftChild == NULL && nodeArr->rightChild == NULL)
	{
		temp[index] = '\0';         //�ַ�����'\0'��β������γ� temp={'0','1',...,'\0'}����������
		//nodeArr->data���ǽ����������൱��A��B��C...,ǿת�����ξͱ�����Ӧ��ASCLL��ֵ��
		strcpy(code[(int)nodeArr->data], temp);       //code[(int)nodeArr->data]�൱�ڵ�һά��temp�൱�ڵڶ�ά
		return;
	}
	//������Ҷ�ӽ��
	else
	{
      //���֧����Ϊ��0�����ҷ�֧����Ϊ��1��
		temp[index] = '0';
		Coding(nodeArr->leftChild, temp, index + 1);
		temp[index] = '1';
		Coding(nodeArr->rightChild, temp, index + 1);


	}
}

//����ԭ������'0'��������'1'���ң�ֱ������Ҷ���ͷ�����ַ�
//�����ѹ��������0/1������������������� , ����flag��0/1�������ж�Ҫ���������������������
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
	unsigned int saveChar=0;     //���浽�������ļ��е��޷����ַ�
	unsigned int tempChar;
	FILE * inputFile = fopen("input.txt", "r");   //�������ļ���ֻ����ʽ���ļ�
	FILE * zipFile = fopen("ziped.txt", "wb");    //����ѹ������ļ��Զ����Ʒ�ʽд��

	int fileLength = 0;  //�ļ��д�ŵ��ַ�����
	//Ȩ���飺��ȡ�������ļ���ͳ�����и����ַ����ֵĴ���
	int AscllArr[128] = { 0 };  //��ʼ�������ַ����ֵĴ���Ϊ0
	char readChar;
	while ((readChar = fgetc(inputFile)) != EOF)      // fgetc()�����ַ���ȡ�ļ��ַ�
	{
		fileLength++;
		AscllArr[(int)readChar]++;    //��(int)readChar���ַ����ֵĴ���++
		//printf("%d", (int)readChar);
	}

	int num = 0; //ͳ����Ȩ�صĽ�������(num�Ǽ�����)
	for (int i = 0; i < 128; i++)  //Ӣ�ļ���Ӧ��ASCLL���������128
	{
	//	printf("%d", i);
		if (AscllArr[i] != 0)     //ASCLL��Ϊi���ַ���Ȩ�ز�Ϊ0
		{
			nodeArr[num].data = i;  //��num������ŵ���ASCLL��ֵi��Ӧ���ַ�
			
			nodeArr[num].weight = AscllArr[i]; //��num������Ȩ����AscllArr[i]
		//	printf("nodeArr[num].data:%c\n", nodeArr[num].data);
		//	printf("nodeArr[num].weight:%d\n", nodeArr[num].weight);
			num++;
		//	printf("num:%d\n", num);
			
		}

	}




	//������������
	Creat(nodeArr, num);
	//���й�����������
	char temp[maxSize];       //����ɽ����������0\1����
	Coding(nodeArr, temp, 0);  //�ӵ�0��Ԫ�ؿ�ʼ����

	//��λ�����뱣�浽�ļ�zipedFile��
	num = 0;    //num�Ǽ�������ͳ��
	//�ļ�ָ�븴λ���ƶ����ļ�ͷ
	fseek(inputFile, 0L, 0);  //���ļ�ָ��inputFile���ļ���ͷ��0���Ƶ����ļ���ͷ0��0L�����ֽڴ�
	int zipLen = 0;      //ѹ������ļ�����

	while ((readChar = fgetc(inputFile))!= EOF)  //����ַ����ļ�
	{
		//�����õ��ַ���Ӧ���ַ����루�� "1001"��"0001"....��

		//code[(int)A]==1001 �������Ϊ������Ҷ�ڵ�A��·����1001���� ��������
		//code[(int)A][0]=="1"

		for (int i = 0; i < strlen(code[(int)readChar]); i++)
		{   //code[(int)readChar����0��1������ɵ��ַ���
			//ͨ����λ����������������浽saceChar��
			saveChar |= (code[(int)readChar][i] - '0');   //code[(int)readChar][i]ֻ�ܵ���0��1

			num++;

			//ÿ����8��0/1�ַ� ��д��һ���ļ�,���ļ������ǰ�1���ֽڴ洢
			if (num == 8)
			{
		    //��zipFile�ж�ȡ��ÿ����saveChar��д��1����СΪsizeof(unsigned char)������
				fwrite(&saveChar, sizeof(unsigned char), 1, zipFile);
				zipLen++;   //ѹ�����ļ����ַ�������1
				num = 0;
				saveChar = 0;
			}
			else
			{
				saveChar <<= 1;  //����һλ����λ��0������ѭ����00000001����λ������

			}
		}
	}



	//������ʣ��ı��벻��8λ�����ƶ�������ˣ����ƶ�8-numλ���չ�8λ
	if (num < 8)
	{
		saveChar = saveChar << (8 - num);
		fwrite(&saveChar, sizeof(unsigned char), 1, zipFile);  //��1���ֽڵĴ�С����ÿ��д��
		zipLen++;
		saveChar = 0;
	}

	//�ر��ļ�
	fclose(inputFile);
	fclose(zipFile);
	printf("ѹ���ɹ���ѹ��ǰ�ַ�����Ϊ %d \n ѹ�����ַ����� %d", fileLength, zipLen);





	//��ѹ��
	zipFile = fopen("ziped.txt","rb");    //�Զ�����ֻ����ʽ��
	FILE* resultFile = fopen("result.txt", "w");   //ֻ����ʽд��
	num = 0;  //��������0
	HaffMan * currNode = &nodeArr[0];    //��ǰ����ʼ��Ϊ���ڵ�
	while (fread(&readChar, sizeof(unsigned char), 1, zipFile))  //���ļ�����zipFile��ÿ�ζ�ȡ1����СΪsizeof(unsigned char)��Ԫ�ص�readChar��
	{
		//fileLength���ļ����ַ��ĸ���
		if (fileLength == num) break;
		for (int i = 0; i < 8; i++)  // sizeof(unsigned char) = 8 
		{
			tempChar = readChar & 128;   // 128 = 10000000������tempChar����readChar�����λ
			tempChar >>= 7;    //Ĩ��0����ʣ���λ�� 10000000>>7 = 1    0000000>>7 = 0
			readChar <<= 1;    //���λ�Ѿ�����ȡ�������ôθ�λ����

			currNode = deCoding(currNode, (int)tempChar);  //���µ�ǰ���λ��

			//�ж�Ҷ�ڵ�
			if (currNode->leftChild == NULL && currNode->rightChild == NULL)
			{
				
				fprintf(resultFile, "%c", currNode->data);  //��currNode->dataд�뵽resultFile��
				num++;    //ͳ���ļ�resultFile�е��ַ�����
				currNode = &nodeArr[0];      //ÿ�ҵ�һ��Ҷ�ڵ㣬�ͽ���ǰ�������Ϊ���ڵ�
			}
		    	
		}


	}

	fclose(zipFile);
	fclose(resultFile);
	printf("\n%s", "��ѹ�����");

	return 0;

}

















