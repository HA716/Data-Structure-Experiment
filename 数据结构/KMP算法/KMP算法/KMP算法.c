#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void GetNext(char*child, int *next)  //求子串child的next数组
{
	int Clen = strlen(child);
	next[0] = -1;              //next[0]默认为-1比较好算
	next[1] = 0;               //索引值为1的下标代表第二个字符，前面只有一个字符，所以没有最长相等前后缀
	int i = 2;  //当前i下标为2，因为索引值为0、1的位置已经设定默认值了
	int k = 0;  //代表next[i-1]的最长相等前后缀的长度
	while (i < Clen)
	{
		if (k==-1||child[i - 1] == child[k])       //结论：当p[i]==p[k]时，会有next[i+1] = next[i] + 1 = k + 1 
		{  
			next[i] = k + 1;      //对next数组的赋值，next[i+1]=k+1，但此时代码中的i相当于是i+1了
			i++;
			k++;
		}
		else
		{
			k= next[k];
		}
	}


	//int k = -1;   //子串前缀的索引值初始为-1
	//int j = 0;    //子串后缀的索引值初始为0
	//while (j < Clen-1)  //不超过子串长度
	//{
	//	if (k = -1 || child[k] == child[j])  //这一步可以自己用手画图证明：D A B C D A B D E
	//	{                                                             //  -1 0 0 0 0 1 2 3 3
	//		k++;
	//		j++;
	//		next[j] = k;
	//	}
	//	else
	//	{
	//		k = next[k];    //缩小范围来寻找前后缀的长度
	//	}
	//}

}

//next数组：next[i]=k表示 当第i号字符不匹配时，记录该字符前的字符串的最长公共前后缀长度k
int KMP(char *parent, char*child, int pos)
{
	int Plen = strlen(parent);     //主串长度
	int Clen = strlen(child);      //子串长度
	if (Plen == 0 || Clen == 0) return;
	if (pos<0 || pos>Plen)      return;

	int * next = (int *)malloc(sizeof(int)*Clen);      //next数组大小和子串长度一致

	GetNext(child, next);  //该函数用来获得子串对应的next数组

	int i = pos;  //遍历主串
	int j = 0;    //遍历子串
	while (i < Plen&&j < Clen)
	{
		//j==-1会发生数组越界，所以让j++，同时i++，这样能保证j处字符能与i+1处比较，因为此前与i处的比已经不相等了
		if (j==-1||parent[i] == child[j])  //若parent[i] == child[j]，则继续比较parent[i+1] == child[j+1]是否相等
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];     //指针回溯，让最长相等前缀移动到最长相等后缀的位置，移动了j-next[j]的长度
		}
	}
	if (j >= Clen)   //j用来遍历子串，Clen是子串长度，此时的j是已匹配字符串的下一个位置，当j==Clen时就已经表示模式串完全匹配，画图易知返回位置下标i-j即可
	{
		return i - j;
	}
	else
		return -1;

}


int main()
{
	char*parent = "abcabeabcabcmn";
	char*child = "abcabcmn";
	printf("%d",KMP("abcabeabcabcmn", "abcabcmn", 0));
}






















