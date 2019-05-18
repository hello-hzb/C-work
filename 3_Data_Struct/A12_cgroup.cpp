#include <stdio.h>
#include <malloc.h>


//通过指针申请三维数组
float*** My_CreateGrid(int channel, int height, int weight)
{
	float*** output = (float***)malloc(channel * sizeof(float**));
	for (int i = 0; i < channel; i++)
	{
		output[i] = (float**)malloc(height*sizeof(float*));
		for (int j = 0; j < height; j++)
		{
			output[i][j] = (float*)malloc(weight*sizeof(float));
			for (int k = 0; k < weight; k++)
			{
				output[i][j][k] = 0.0;
			}
		}

	}
	return output;
}


int*** CreateGrid(int m, int n, int t)
{
	int i = 0;
	int k = 0;
	int*** result = NULL;
	if ((m > 0) && (n > 0) && (t > 0))
	{
		int** pp = NULL;
		int* p = NULL;
		result = (int***)malloc(m * sizeof(int**));     // key
		pp = (int**)malloc(m * n * sizeof(int*));      // key
		p = (int*)malloc(m * n * t * sizeof(int));     // key
		if ((result != NULL) && (pp != NULL) && (p != NULL))
		{
			for (i = 0; i < m; i++)
			{
				result[i] = pp + i * n; // 三维元素存二维地址
				for (k = 0; k < n; k++)
				{
					result[i][k] = p + k * t; // // 二维元素存一维地址
				}
				p = p + n*t;
			}
		}
		else
		{
			free(result);
			free(pp);
			free(p);
			result = NULL;
			pp = NULL;
			p = NULL;
		}
	}
	return result;
}



void FreeGrid(int*** p)
{
	if (*p != NULL)
	{
		if (**p != NULL)
		{
			free(**p);
			**p = NULL;
		}
		free(*p);
		*p = NULL;
	}
	free(p);
	p = NULL;
}

int main(void)
{
	float*** b = My_CreateGrid(3, 28, 28);
	int*** a = CreateGrid(3, 3, 3);
	int i = 0;
	int j = 0;
	int k = 0;
	int value = 1;
	printf("values[%d]",sizeof(*b)/sizeof(float));
	// 遍历三维数组赋值
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				*(*(*(a + i) + j) + k) = value++;

	// 遍历三维数组 打印元素地址
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				printf("values[%d][%d][%d] = %p\n", i, j, k, &b[i][j][k]);
	// 地址是连续的

	// 遍历三维数组 打印元素值
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				printf("values[%d][%d][%d] = %d\n", i, j, k, b[i][j][k]);

	// 堆空间回收
	if (a != NULL)
		FreeGrid(a);
	return 0;
}
//-------------------- -
//作者：码农u号
//来源：CSDN
//原文：https ://blog.csdn.net/qq_29545231/article/details/78662983 
//版权声明：本文为博主原创文章，转载请附上博文链接！