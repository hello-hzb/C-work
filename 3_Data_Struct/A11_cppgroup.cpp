#include<iomanip>
#include <iostream>
using namespace std;


//https://blog.csdn.net/cgcoder/article/details/7939836
//int main()
//{
//	int i, j, k;
//	int nWidth, nHeight, nThird;
//
//	cin >> nThird >> nHeight >> nWidth;
//
//	/***声明一个三维数组***/
//	int ***grayScale = new int **[nThird];
//	for (i = 0; i < nThird; i++)
//	{
//		grayScale[i] = new int*[nHeight];
//		for (j = 0; j < nHeight; j++)
//		{
//			grayScale[i][j] = new int[nWidth];
//		}
//	}
//	/***将数组元素都赋值为1***/
//	for (k = 0; k < nThird; k++)
//	{
//		for (j = 0; j < nHeight; j++)
//		{
//			for (i = 0; i < nWidth; i++)
//			{
//				grayScale[k][j][i] = 1;
//			}
//		}
//	}
//	/***打印数组元素***/
//	cout << setw(5);
//	for (k = 0; k < nThird; k++)
//	{
//		for (j = 0; j < nHeight; j++)
//		{
//			for (i = 0; i < nWidth; i++)
//			{
//				cout << grayScale[k][j][i] << setw(5);
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//	/***释放内存***/
//	for (j = 0; j < nThird; j++)
//	{
//		for (i = 0; i < nHeight; i++)
//		{
//			delete[]grayScale[j][i];
//		}
//	}
//	delete[]grayScale;
//	return 0;
//}
