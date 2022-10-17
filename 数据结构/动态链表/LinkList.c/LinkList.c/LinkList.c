#include<stdio.h>  //�������
#include<stdlib.h>  //��̬�ڴ����
#include<stdbool.h>  //����ֵ
#include"LinkList.h"  //������
#pragma warning(disable:4996)  //��ֹscanf�Ĳ���ȫ��ʾ


//��ʼ������ Init()����ͷ�ڵ�-----------------------------------------------------------------------------------------------
LinkNode * Init()
{
	LinkNode * header = (LinkNode*)malloc(sizeof(LinkNode)); // ָ��ͷ�ڵ��ָ��
	header->data = 0;  //��Ϊһ�㲻��ͷ�ڵ����ݽ��в���������ͷ�ڵ�data��ʲô����
	header->next = NULL;  //��ʼʱָ��NULL

	int val;
	LinkNode* pRear = header;     //����β��ָ�룬ʼ��ָ����������һ����㣬����ʵ�ֲ���
	while (true)
	{
		LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode));  //�����½ڵ�
		printf("%s","��������dataֵ");
		scanf("%d", &val);
		if (val == -1)
		{
			break;         //������-1ʱ����Ϊ���ٲ����½ڵ�
		}
		//��ʼ���½ڵ�
		newNode->data = val;
		newNode->next = NULL;     //�½ڵ�һ�������һ����㣬����ָ��NUll

		//�½ڵ����β��
		pRear->next = newNode;

		//����β��ָ��λ�ã�����ָ�����һ�����
		pRear = newNode;
		
	}
	return header;
}


//��������------------------------------------------------------------------------------------------------------------------
void Print(LinkNode * header)
{
	//����ָ����� ���ڱ���
	LinkNode*pCurrent = header->next;  //��Ϊͷ�ڵ������û�ã����Դ�ͷ�ڵ����һλ��ʼ����     

	while (pCurrent != NULL)
	{
		printf("%d\n", pCurrent->data);
		//ָ�����
		pCurrent = pCurrent->next;
	}
}



//�½��Ĳ���-------------------------------------------------------------------------------------------------------------
void Insert(LinkNode * header,int oldvalue)    
{
	int val;
	//��������ָ�룬һ��ָ��ͷ��㣬��һ��ָ��ͷ������һλ
	LinkNode*pCurrent1 = header;      
	LinkNode*pCurrent2 = header->next;
	while (pCurrent2 != NULL)     //���������еĽ��
	{
		if (pCurrent2->data == oldvalue)  //��oldvalue��λ�ò����½��
		{
			LinkNode*newNode = (LinkNode*)malloc(sizeof(LinkNode));
			printf("%s", "�������½��dataֵ");
			scanf("%d", &val);		
			//��ʼ���½ڵ�
			newNode->data = val;
			//������
			pCurrent1->next = newNode;            //��ͼ�ͺ���������
			newNode->next = pCurrent2;
			break;

		}
		//���û���ҵ�oldvalue�͸��¸���ָ���λ��
		pCurrent2 = pCurrent2->next;
		pCurrent1 = pCurrent1->next;
	}


}




//β����������-------------------------------------------------------------------------------------------------------
void Back_Insert(LinkNode * header)
{
	int val;
	LinkNode* pRear = header;     //����β��ָ�룬ʼ��ָ����������һ����㣬����ʵ�ֲ���
	while (true)
	{
		LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode));  //�����½ڵ�
		printf("%s", "��������dataֵ");
		scanf("%d", &val);
		if (val == -1)
		{
			break;         //������-1ʱ����Ϊ���ٲ����½ڵ�
		}
		//��ʼ���½ڵ�
		newNode->data = val;
		newNode->next = NULL;     //�½ڵ�һ�������һ����㣬����ָ��NUll

		//�½ڵ����β��
		pRear->next = newNode;

		//����β��ָ��λ�ã�����ָ�����һ�����
		pRear = newNode;

	}
}




//������������г�ͷ�ڵ�����Ĵ�������ݵĽڵ��ͷŵ�----------------------------------------------------------------------
void Clear(LinkNode * header)
{
	//��ָ��ͷ������һ����㣬��Ϊ����Ҫ�ͷ�ͷ���
	LinkNode*pCurrent = header->next;
	LinkNode*pTemp;
	while (pCurrent != NULL)
	{
		pTemp = pCurrent->next; //�ȱ�����һ������λ�ã�����һ���ͷ�pCurrent���Ҳ����˺������λ����
		free(pCurrent);   //�ͷ�pCurrent��ǰ��ָ����ڴ�ռ�
		pCurrent = pTemp; //ָ����һ�����
	}

	header->next = NULL;  //�ͷ���������ͷ���ָ��NULL,���ָ�Ϊ������


}






//��������������ͷ������ڵ����нڵ��ͷŵ�------------------------------------------------------------------------------
void Destory(LinkNode * header)
{
	//��ָ��ͷ���
	LinkNode*pCurrent = header;   //Ψһ���𣡣�
	LinkNode*pTemp;
	while (pCurrent != NULL)
	{
		pTemp = pCurrent->next; //�ȱ�����һ������λ�ã�����һ���ͷ�pCurrent���Ҳ����˺������λ����
		free(pCurrent);   //�ͷ�pCurrent��ǰ��ָ����ڴ�ռ�
		pCurrent = pTemp; //ָ����һ�����
	}

	header->next = NULL;  //�ͷ���������ͷ���ָ��NULL,���ָ�Ϊ������

}




//ɾ�����------------------------------------------------------------------------------------------------------------------
void Delete(LinkNode * header, int delValue)
{
	if (header== NULL)   //�ж��Ƿ�Ϊ�������ǿ������ֱ�ӷ���
	{
		return;
	}

	//��Ҫ��������ָ�����
	LinkNode*pCurrent1 = header;
	LinkNode*pCurrent2 = pCurrent1->next;
	
	while (pCurrent2 != NULL)
	{
		if (pCurrent2->data == delValue)   //�ҵ���ɾ����ֵ
		{
		
			break;     //һ��Ҫ�˳�,�������ִ���������д���
		}

		//���û���ҵ�delValue�Ͳ��ϸ��¸���ָ���λ��
		pCurrent2 = pCurrent2->next;
		pCurrent1 = pCurrent1->next;
	}
	
	pCurrent1->next = pCurrent2->next;
	free(pCurrent2);
	pCurrent2 = NULL;


}

//-----------------------------------------------------------------------------------------------------------------------------
void main()
{
	LinkNode*header = Init();
	Print(header);

	Insert(header, 3);   //��ԭ�����ֵΪ3��λ�ò����½��
	Print(header);

	Clear(header);        //����б�
	Back_Insert(header);  //�����½�㣬������֤�ͷųɹ�����б�
	Print(header);

	Delete(header, 3);   //ɾ��ֵΪ3�Ľ��
	Print(header);
}




























