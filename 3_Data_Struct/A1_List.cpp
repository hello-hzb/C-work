#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define MAXSIZE 100
typedef int datatype;

/*********************************************************************************
*顺序表基本数据结构的定义
**********************************************************************************/
struct SqList
{
	datatype data[MAXSIZE];
	int length;
};
/**************************************************************
*逆转顺序表
***************************************************************/
void Reverse_SqList(SqList* L)
{
	int i, j, n, t;
	n = L->length;
	if (n == 0 || n == 1)
		return;
	i = 0;
	j = n - 1;
	while (i < j)
	{
		int temp = L->data[i];
		L->data[i] = L->data[j];
		L->data[j] = temp;
		i++;
		j--;
	}
}
/**************************************************************
*创建顺序表
*************************************************************/
void Creat_SqList(SqList* L, int n)
{
	int i = 0;
	L->length = n;
	printf("\ninput %d data: ", n);
	while (i < n)
	{
		scanf_s("%d", &L->data[i]);
		i++;
	}
}

/**************************************************************
*打印顺序表
*************************************************************/
void Print_SqList(SqList* L)
{
	int i = 0;
	printf("\nOutput %d data: ", L->length);
	while (i < L->length)
	{
		printf("%d ", L->data[i]);
		i++;
	}
}

/****************************************************************
*已知顺序表中的元素以值递增的顺序排列， 删除顺序表中所有值相同的多余元素，使操作后顺序表中的所有元素的值均不相同
***************************************************************/
void Del_SqList(SqList* L)
{
	/*删除顺序表中所有值相同的元素*/
	int i, j, k;
	int len = L->length;
	int count = 0;
	datatype temp;
	for (i = 0; i < len; i++)
	{
		temp = L->data[i];
		for (j = i + 1; j < len; j++)
		{
			if (L->data[j] = temp)
				count++;
			else
				break;
		}
		if (count != 0)
		{
			for (k = j; k < len; k++) //此时k已经是不重复对应的id
			{
				L->data[k - count] = L->data[k];
			}
			len = len - count;
			count = 0;
		}
	}
	L->length = len;
}
/***********************************************************************************************
*在顺序表中插入一个元素
*********************************************************************************************/
void Insert_SqList(SqList *L, int i, datatype x)
{
	if (L->length == MAXSIZE)
		printf("表满");
	if (i<0 || i>L->length)
		printf("位置错误");
	for (int j = L->length - 1; j > i; j--)
	{
		L->data[j + 1] = L->data[j];
	}
	L->data[i] = x;
	L->length++;
}
/************************************************************************
*删除顺序表中的一个元素
*************************************************************************/
void Delete_SqList(SqList *L, int i)
{
	if (i < 0 || i>L->length)
	{
		printf("位置错误");
		return;
	}
	if (L->length = 0)
	{
		printf("表空");
		return;
	}
	for (int j = i + 1; j < L->length; j++)
	{
		L->data[j - 1] = L->data[j];
	}
	L->length--;
}
/***********************************************************************
定位顺序表
***********************************************************************/
int Locate_SqList(SqList *L, datatype x)
{
	for(int i = 0; i < L->length; i++)
	{
		if (L->data[i] == x)
			return i;
	}
	return -1;
}

//顺序表的主要优缺点：
//线性表的主顺序存储结构的特点是线性表中逻辑关系上相邻的数据元素在物理存储的位置上也是相邻的，即物理上的相邻实现逻辑上的相邻，
//主要优点
//(1)无需为表示元素间的逻辑关系而添加额外的存储空间
//(2)可以方便地随机存取线性表中的任一元素
//主要的缺点
//(1)插入和删除不方便，为了保持顺序表中数据元素之间的逻辑关系，在插入和删除运算时需要移动大量的数据元素，影响了运算效率
//(2)顺序表的长度总有一定的限制，需要预先估算好所用空间的大小，估计小了会造成顺序表的溢出估计大了，会造成存储空间的浪费

//void main()
//{
//	SqList L;
//	int n;
//	printf("\ninput n: ");
//	scanf_s("%d", &n);
//	Creat_SqList(&L, n);
//	Print_SqList(&L);
//	Reverse_SqList(&L);
//	Print_SqList(&L);
//	printf("\ninput n: ");
//	scanf_s("%d", &n);
//}