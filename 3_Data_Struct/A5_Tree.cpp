#include<stdio.h>
#include<stdlib.h>

typedef char datatype;
struct BitTree
{
	datatype data;
	struct BitTree *lchild, *rchild;
};

/*********************************************
构造二叉树， 采用链表的方式来存储二叉树
若二叉树为空，则空操作，否则
1.获得键盘输入，并存入根节点
2.创建以左子树为根节点的子树
3.创建以右子树为根节点的子树
**********************************************/
void Create_BiTree(BitTree* T)
{
	/*构造二叉树的二叉链表T*/
	char ch;
	ch = getchar();
	if (ch == '@')    //终止创建树
		T = NULL;
	else
	{
		T = (BitTree*)malloc(sizeof(BitTree));
		T->data = ch;                         //生成根节点
		Create_BiTree(T->lchild);             //构造左子树
		Create_BiTree(T->rchild);			  //构造右子树
	}
}

/*********************************************
先序遍历
若二叉树为空，则空操作，否则
1.访问根节点
2.先序遍历左子树
3.先序遍历右子树
**********************************************/
void PreOrder(BitTree *bt)
{
	if (bt == NULL)
		return;
	printf("%3c", bt->data);
	PreOrder(bt->lchild);
	PreOrder(bt->rchild);
}


/*********************************************
中序遍历
若二叉树为空，则空操作，否则
1.中序遍历左子树
2.访问根节点
3.中序遍历右子树
**********************************************/
void InOrder(BitTree *bt)
{
	if (bt == NULL)
		return;
	InOrder(bt->lchild);
	printf("%3c", bt->data);
	InOrder(bt->rchild);
}


/*********************************************
后序遍历
若二叉树为空，则空操作，否则

1.后序遍历左子树
2.后序遍历右子树
3.访问根节点
**********************************************/
void PostOrder(BitTree *bt)
{
	if (bt == NULL)
		return;
	
	PreOrder(bt->lchild);
	PreOrder(bt->rchild);
	printf("%3c", bt->data);
}


/*********************************************
逐层访问二叉树
1.在访问当前层的节点时，按照顺序也将对应的左右子树存入队列中，front输出当前节点，rear用来保存队列最后一个节点

**********************************************/


void LevelOrder(BitTree* bt)
{
	/*层次遍历二叉树bt*/
	int MAXSIZE = 100;
	BitTree* Q[100];
	BitTree* p;
	if (bt == NULL)
		return;
	int front = 0;
	int rear = 0;
	Q[++rear] = bt;
	while (front != rear)
	{
		front++;					//front总是指向某一根节点，p取出根节点后，分别将p的左右子树存入rear中。
		p = Q[front];               //当前层访问的同时会把下一层的访问顺序确定并存入队列中
		printf("%3c", p->data);
		if (p->lchild != NULL)
		{
			Q[++rear] = p->lchild;
		}
		if (p->rchild != NULL)
		{
			Q[++rear] = p->rchild;
		}
	}
}


/*********************************************
非递归方式先序遍历二叉树
1.访问子树的根节点并存入栈，并优先打印出根节点的信息，然后将左子树的地址存入栈中，一直到最底层，总结起来就是一直靠左边走；
2.左节点访问结束后从最底层开始往上层访问，开始从最底层开始访问右子树。 这里要好好理解大循环嵌套小循环的含义， 
大循环保证完全遍历所有节点，小循环保证完全遍历左子树
/**********************************************************************/

void NRPreOrder(BitTree* bt)
{
	BitTree* S[100], *p;
	int top;
	if (bt == NULL)
		return;
	top = 0;
	p = bt;
	while (!(p == NULL&&top == 0))
	{
		while (p != NULL)    //这个循环会搜索到最深的左子树，并依次将遇到的左子树存到栈中
		{
			printf("%3c", p->data);
			if (top < 99)
			{
				S[++top] = p; //访问完根节点后要把根节点存起来，待会还有往回走访问右子树
			}
			else
			{
				printf("stack overflow");
				return;
			}
			p = p->lchild;
		}
		p = S[top];    //然后从最底部开始向顶层方向，访问每个子树的根节点的右子树，每访问一个右子树，也会搜索到该右子树的最底层
		top--;
		p = p->rchild;


	}
}



/*********************************************
非递归方式中序遍历二叉树， 和先序遍历的写法基本一致，就是打印信息的位置变化了，需要注意一下
1.访问子树的根节点并存入栈，然后将左子树的地址存入栈中，一直到最底层，总结起来就是一直靠左边走；然后开始打印出根节点的信息，
2.左节点访问结束后从最底层开始往上层访问，开始从最底层开始访问右子树。 这里要好好理解大循环嵌套小循环的含义， 大循环保证完全遍历所有节点，小循环保证完全遍历左子树
/**********************************************************************/

void NRMidOrder(BitTree* bt)
{
	BitTree* S[100], *p;
	int top;
	if (bt == NULL)
		return;
	top = 0;
	p = bt;
	while (!(p == NULL&&top == 0))
	{
		while (p != NULL)    //这个循环会搜索到最深的左子树，并依次将遇到的左子树存到栈中
		{
			
			if (top < 99)
			{
				S[++top] = p;
			}
			else
			{
				printf("stack overflow");
				return;
			}
			p = p->lchild;
		}
		p = S[top];    //然后从最底部开始向顶层方向，访问每个子树的根节点的右子树，每访问一个右子树，也会搜索到该右子树的最底层
		printf("%3c", p->data);
		top--;
		p = p->rchild;


	}
}

/*********************************************
非递归方式后遍历二叉树
下列写法不大对，会先打印右节点，再打印左节点
*********************************************/
struct Stack_Type
{
	BitTree* link;
	int flag;   //0:从该节点的左子树返回，节点不能被访问      1: 从该节点的右子树返回，节点可以访问并出栈
};

void NRPostOrder(BitTree* bt)
{
	BitTree* p;
	Stack_Type S[100];
	int top = 0;
	if (bt == NULL)
		return;
	p = bt;
	while (!(p == NULL&&top == 0))
	{

		while (p != NULL)
		{
			S[++top].link = p;  //
			S[top].flag = 0;
			p=p->lchild;       //左子树进栈
		}
		if (S[top].flag == 0)
		{
			S[top].flag = 1;   //代表右子树已经进准备进栈
			p = S[top].link;
			p = p->rchild;
		}
		else
		{
			p = S[top].link;
			printf("%3c", p->data);
			top--;
			//p = S[top].link;
		}
	}
}


/*********************************************
统计二叉树中叶节点的数目
1.若一棵二叉树为空，则他的叶节点数为0；
2.若二叉树只有一个节点，则他的叶节点数为1；否则他的叶节点数为左子树和叶节点数和右子树的叶节点数之和；
*********************************************/
int CountLeaf(BitTree* bt)
{
	if (bt == NULL)
		return 0;
	else if (bt->lchild == NULL&&bt->rchild == NULL)
		return 1;
	else
		return(CountLeaf(bt->lchild) + CountLeaf(bt->rchild));
}


/*********************************************
求二叉树的深度, 采用递归的方式
1.若一棵树的二叉树为空，则深度为0；
2.否则深度等于左子树和右子树中的最大深度加1.
*********************************************/
int BiTree_Deep(BitTree* bt)
{
	int h=0;
	int hl = 0;
	int hr = 0;
	if (bt == NULL)
	{
		return 0;
	}
	else
	{
		hl = BiTree_Deep(bt->lchild);
		hr = BiTree_Deep(bt->rchild);
		if (hl >= hr)
			h = hl + 1;
		else
			h = hr + 1;
	}
	return h;
}


/**********************************线索二叉树********************************************/





/***********************************哈尔曼编码器***********************************************/






/*******************************************************************************************
森林：m（m>=0)棵互不相交的树的集合。对于树的每个节点而言，其子树的集合就是森林，因此也可用森林和树互相递归的定义来描述树。
树型结构为非线性结构:数据一对多的关系
线性结构：数据元素之间存在一对一的线性关系。


**********************************************************************************************/
