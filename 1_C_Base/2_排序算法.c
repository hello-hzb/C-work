#include<iostream>
using namespace std;
//稳定：如果a原本在b前面，而a = b，排序之后a仍然在b的前面。
//
//不稳定：如果a原本在b的前面，而a = b，排序之后 a 可能会出现在 b 的后面。
//
//时间复杂度：对排序数据的总的操作次数。反映当n变化时，操作次数呈现什么规律。
//
//空间复杂度：是指算法在计算机内执行时所需存储空间的度量，它也是数据规模n的函数。
/*总结：https://www.cnblogs.com/onepixel/articles/7674659.html

*/



/****************************************************************
* 1_选择排序,时间复杂度最大的是Ο(n 2 ),空间复杂度为O(1)
* @param a
* @param n
***************************************************************/
//时间复杂度Ο(1)<Ο(log 2 n)<Ο(n)<Ο(nlog 2 n)<Ο(n 2 )<Ο(n 3 )
//第一种写法好理解,但是不符合冒泡排序的原理,冒泡排序是一次相邻两个进行对比交换的
void Select_Sort(int a[], int n)
{
	int temp;
	for (int i = 0; i<n; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (a[i]>a[j])  //把小的数放到前面去
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}
/****************************************************************
* 2_冒泡排序,时间复杂度最大的是Ο(n 2 ),最小的是Ο(n),
* 加入一个标志位可以减少程序执行的次,但某一次没有发生交换说明已经排序完成就不要排序了
* @param a
* @param n
***************************************************************/
void Bubble_sort(int a[], int n)
{
	int temp;
	bool changed = true;
	for (int i = 0; i<n&&changed; i++)
	{
		changed = false;
		for (int j = n - 1; j>i; j--)
		{
			if (a[j]<a[j - 1])
			{
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
				changed = true;
			}
		}
	}
}
//https://www.cnblogs.com/lz3018/p/5742255.html

/***********************************************************************
*3_插入排序,从小到大排序
*将数组分为有序和无序，初始化时数组第一个元素就是有序的，然后每次从无序的那部分中取一个数和有序的每个数进行对比，当小于有序数时，对应的有序数往右移动一个位置
*时间复杂度O(n2)n的平方, 空间复杂度O(1)，稳定的
**********************************************************************/
void Insert_Sort(int a[], int n)
{
	int temp;
	for (int i = 1; i < n; i++)        //i代表无序部分的序号
	{
		temp = a[i];
		int j = i - 1;
		while (a[j]>temp&&j >= 0)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;

	}
}


/***********************************************************************
*4_快速排序, 从小到大排序
* 定义第一个元素为基准，从右向左查找小于基准的数，然后进行交换，交换一次换个方向，从从左往右找大于基准的数，然后进行交换。到i=j以后，就确定第一个基准的位置，
* 然后以基准为借分割原来数组，对分割得到的数组继续迭代进行，知道输入的low=high结束函数
*https://www.cnblogs.com/lz3018/p/5742255.html
*快速排序最好情况是每次分区后，都将序列等分为两个长度基本相等的子序列(也就是分区后基准元素都位于序列中间位置)。
*第一次分区后，子序列长度为n/2,第二次分区后，子序列长度为n/4，第i次分区后子序列长度为n/(2^i)，直到子序列长度为1。设经过x次分区后子序列长度为1，则有n/2^x=1,则x=log n，
*也就是说最好情况下经过log n次分区完成排序。使用递归树来理解快速排序的最好时间复杂度。递归树的高度就是分区次数，由上述计算可知，递归树的高度是log n。在递归树的每一层总共有n个节点，
*并且各子序列在分区的时候关键字的比较次数不超过n，所以就有基本操作次数不超过n*log n。所以，快排在理想情况下的时间复杂度是O(n*log n)。

最坏情况
当我们每次进行分区划分时，如果每次选择的基准元素都是当前序列中最大或最小的记录，这样每次分区的时候只得到了一个新分区，另一个分区为空，并且新分区只是比分区前少一个元素，
这是快速排序的最坏情况，时间复杂度上升为O(n^2)，因为递归树的高度为n。所以，有人提出随机选择基准元素，这样在一定程度上可以避免最坏情况的发生，但是理论上最坏情况还是存在的。
由于快速排序是使用递归实现的，所以其空间复杂度就是栈的开销，最坏情况下的递归树高度是n，此时空间复杂度是O(n)，一般情况下递归树的长度是log n，此时空间复杂度是O(log n)。
快速排序适用于待排序记录个数很多且分布随机的情况，并且快拍是目前内排序中排序算法最好的一种。
不稳定
**********************************************************************/
void Quick_Sort(int a[], int low, int high)
{
	if (low >= high)       //很重要，不然代码就死循环了
		return;
	int i = low;
	int j = high;
	int temp = a[i];
	while (i < j)
	{
		//从右向左找小于基准的数
		while (i < j&&a[j]>=temp)
		{
			j--;
		}
		if (i < j)
		{
			a[i] = a[j];
			i++;
		}
		//从左向右找大于基准的数
		while (i < j&&a[i] <= temp)
		{
			i++;
		}
		if (i < j)
		{
			a[j] = a[i];
			j--;
		}
	}
	//确认了基准的位置
	a[i] = temp;
	Quick_Sort(a, low, i - 1);
	Quick_Sort(a, i + 1, high);
}

void Swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

/**************************************************************************************
5_希尔排序，又叫缩小增量排序，增量按照增量间隔将原始数组分为多个小数组进行插入排序，但是只是在原始的数组中调整了位置
增量会不断缩小直到等于1，等于1时就是标准的插入排序。
我的认识是之前大增量的排序将数组大概排序（不是最准的排序），最后用标准排序进行排序，可以减少对比的次数
时间复杂度O(n^（1.3—2）)， 空间复杂度为O(1), 不稳定  https://baike.baidu.com/item/%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F/3229428?fr=aladdin
***************************************************************************************/
void Shell_Sort(int a[], int n)
{
	int d, i, j, temp; //d为增量
	for (d = n / 2; d >= 1; d = d / 2) //增量递减到1使完成排序
	{
		for (i = d; i < n; i++)   //插入排序的一轮   插入排序的话d=1;
		{
			temp = a[i];
			for (j = i - d; (j >= 0) && (a[j] > temp); j = j - d)
			{
				a[j + d] = a[j];
			}
			a[j + d] = temp;
		}
	}
}

void Hill_Sort(int a[], int n)
{
	for (int increament=n/2; increament>=1; increament = increament/2)
	{
		std::cout << increament << std::endl;
		for (int j = increament; j <n ; j++)
		//for (int j = n-1; j >=increament; j--)
		{
			int temp = a[j];
			int i;
			for ( i = j - increament; i >= 0; i = i - increament)
			{
				if (a[i] > temp)
				{
					a[i + increament]=a[i];
				}
			}
			a[i + increament] = temp;
			
		}
	}
}

/********************************************************************************
6_堆排序, 二叉树里面代表的是数组的id，不是对应的数值，第一次调整的调整的时候从最后一个有子节点的位置开始进行比较，将该分支的最大值放到父节点的位置上，
如果分支底下还有多层的话，会进行迭代，确保每一个分支的父节点都大于子节点，最后的完成以后，可以确认最顶层的父节点是最大值
下一步将最大值和数组最后一个数进行交换，再次进行Adust的时候就每次挪到最后面对最大数、第二大数。。。。这就是第二个循环内的adjust的作用了
							0
						   / \
						  1   2
					   /\		/\
                      3  4     5  6
					 /\  /\   /\  /\
					7  8 9
时间复杂度：创建初始堆的时间复杂度是O(n)，简单的解释是有n/2个节点需要调整，每次调整节点时只是上写移动常数个节点，因此创建初始堆的时间复杂度是O(n)。
而实际进行堆排序时，需要进行n趟，每趟进行堆重建时就是调整堆顶节点，最多移动次数不会超过书的高度O(log n)，因此时间复杂度是O(n*log n)。
堆排序对数据的原始排列状态并不敏感，所以其最坏时间复杂度、最好时间复杂度、平均时间复杂度均是O(n*log n)，堆排序不是一种稳定的排序算法。
https://www.cnblogs.com/lz3018/p/5742255.html
********************************************************************************/
void HeapAdjust(int arr[], int i, int length)
{
	// 调整i位置的结点
	// 先保存当前结点的下标
	int max = i;
	// 当前结点左右孩子结点的下标
	int lchild = i * 2 + 1;
	int rchild = i * 2 + 2;
	if (lchild < length && arr[lchild] > arr[max])
	{
		max = lchild;
	}
	if (rchild < length && arr[rchild] > arr[max])
	{
		max = rchild;
	}
	// 若i处的值比其左右孩子结点的值小，就将其和最大值进行交换
	if (max != i)
	{
		int temp;
		temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;
		// 递归  调整完以后对应的分支上的数发生了变化，需要重新对比一下确保父节点大于子节点，这是迭代的作用
		HeapAdjust(arr, max, length);
	}
}

// 堆排序
void HeapSort(int arr[], int length)
{
	// 初始化堆
	// length / 2 - 1是二叉树中最后一个非叶子结点的序号
	// 这个循环内能确保父节点大于子节点，节点实际上代表的是序号而已，
	//
	for (int i = length / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(arr, i, length);
	}
	// 每一次HeapAdjust能够找到最大值，所以将最大值原数组最后一个位置后，下次参与调整的数组中就不包含这个数组的最后一个数，每次都递减一个
	//交换堆顶元素和最后一个元素
	for (int i = length - 1; i >= 0; i--)
	{
		int temp;
		temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		HeapAdjust(arr, 0, i);
	}
}

/**************************************************************************************************************
7_归并排序
将数组对此拆分直到每个group只有两个数进行对比，然后依次组合，将相邻两个大小相同的进行合并，1+1, 1+1, 1+1, 1+1->2+2, 2+2, 而不是2+2, 2, 2->4+2, 2->6+2
时间O(n log n); 需要 O(n) 额外存储空间
https://www.cnblogs.com/skywang12345/p/3602369.html   这个链接里面的图解才是代码的反应
***************************************************************************************************************/

// 归并排序
void MergeSort(int arr[], int start, int end, int * temp)
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	MergeSort(arr, start, mid, temp);   //不断迭代，将前半部分中每次传入函数的mid值一直除于2，直到start=0， mid=1的时候执行下一步
	MergeSort(arr, mid + 1, end, temp); //

	// 合并两个有序序列
	int length = 0; // 表示辅助空间有多少个元素
	int i_start = start;
	int i_end = mid;
	int j_start = mid + 1;
	int j_end = end;
	while (i_start <= i_end && j_start <= j_end)
	{
		if (arr[i_start] < arr[j_start])
		{
			temp[length] = arr[i_start];
			length++;
			i_start++;
		}
		else
		{
			temp[length] = arr[j_start];
			length++;
			j_start++;
		}
	}
	while (i_start <= i_end)
	{
		temp[length] = arr[i_start];
		i_start++;
		length++;
	}
	while (j_start <= j_end)
	{
		temp[length] = arr[j_start];
		length++;
		j_start++;
	}
	// 把辅助空间的数据放到原空间
	for (int i = 0; i < length; i++)
	{
		arr[start + i] = temp[i];
	}
}
/******************************************************************************
8_二叉树排序，每一个分支的父节点大于左节点， 小于右节点，也是需要使用递归的思想
时间复杂度
二叉树排序

二叉树排序法借助了数据结构二叉排序树，二叉排序数满足三个条件：（1）若左子树不空，则左子树上所有结点的值均小于它的根结点的值； （2）若右子树不空，则右子树上所有结点的值均大于它的根结点的值； （3）左、右子树也分别为二叉排序树。根据这三个特点，用中序遍历二叉树得到的结果就是排序的结果。
二叉树排序法需要首先根据数据构建二叉排序树，然后中序遍历，排序时间复杂度为O(nlogn)，构建二叉树需要额外的O(n)的存储空间，有相同的元素是可以设置排在后边的放在右子树，在中序变量的时候也会在后边，所以二叉树排序是稳定的。

********************************************************************************/
struct BST{
	int number; //保存数组元素的值
	struct BST* left;
	struct BST* right;
};

void insertBST(BST** tree, int v) {
	if (*tree == NULL) {
		*tree = new BST;
		(*tree)->left = (*tree)->right = NULL;
		(*tree)->number = v;
		return;
	}
	if (v < (*tree)->number)
		insertBST(&((*tree)->left), v);
	else
		insertBST(&((*tree)->right), v);
}

void printResult(BST* tree) {
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		printResult(tree->left);
	cout << tree->number << "  ";
	if (tree->right != NULL)
		printResult(tree->right);
}

void createBST(BST** tree, int a[], int n) {
	*tree = NULL;
	for (int i = 0; i<n; i++)
		insertBST(tree, a[i]);
}




int main()
{
	int data[12] = {10, 9, 8, 7, 5, 4, 3, 6, 2, 1, 0, -1};
	int temp[12];
	HeapSort(data, 12);
	for (int i = 0; i < 12; i++)
		std::cout << data[i] << "  ";

	std::cout << "hello world" << std::endl;
	system("pause");
}