#include <stdio.h>
//动态二维数组的申请与释放
void main()
{
	//char a[100][100];   //这种方式定义数组变量已经把内存申请好了，sizeof(a)=10000
	int **a = (int **)malloc((sizeof(int *)) * 100);
	for (int i = 0; i < 100; i++)
	{
		a[i] = (int *)malloc(sizeof(int)*100);
	}

	//to do

	for (int i=0; i < 100; i++)
	{
		free(a[i]);
	}
	free(a);    //a的释放一定不要忘记！！！！！

	printf("size is %d", sizeof(a));
	system("pause");
}
