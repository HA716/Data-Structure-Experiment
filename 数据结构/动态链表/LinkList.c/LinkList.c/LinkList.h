#pragma once  //��ֹ#pragma once���ڵ�ͷ�ļ���include��Σ�����ֹ���������

//��ͷ�ļ��Ѵ�����д�ã���.c�ļ���ʵ�ֿ�ܵĹ���

typedef struct 
{
	int data;        //����������
	struct LinkNode * next; //����ָ����
}LinkNode;

//��ʼ������ Init()����ͷ�ڵ�
LinkNode * Init();
//��������
void Print(LinkNode * header);
//β����������
void Back_Insert(LinkNode * header);
//��ָ��λ��oldvalue�������½�㣬��ֵΪnewvalue
void Insert(LinkNode * header,int oldvalue);
//������������г�ͷ�ڵ�����Ĵ�������ݵĽڵ��ͷŵ�
void Clear(LinkNode * header);
//��������������ͷ������ڵ����нڵ��ͷŵ�
void Destory(LinkNode * header);
//ɾ�����
void Delete(LinkNode * header,int delValue);






















