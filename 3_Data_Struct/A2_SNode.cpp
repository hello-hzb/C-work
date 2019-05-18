#include<stdio.h>
#include<stdlib.h>

typedef int datatype;

/*********************************************
*链表节点的基本结构
**********************************************/
struct SNode
{
	datatype data;
	struct SNode *next;
};
/*********************************************
*初始化链表节点
**********************************************/
SNode* Init_SNode()
{
	SNode *L;
	L = (SNode*)malloc(sizeof(SNode));
	L->next = NULL;
	return L;
}
/*********************************************
*获得链表的结构
**********************************************/
int Get_SNode_Length(SNode* L)
{
	SNode *p;
	p = L ->next;
	int len = 0;
	while (p)
	{
		len++;
		p = p->next;
	}
	return len;
}


/**************************************************************
*逆转链表
总结起来：每次反转都涉及到3个node，所以要把用3个node存地址但是什么时候存有讲究.
1.被反转的节点的下一个节点地必须先存，否则反转以后就找不到了；


***************************************************************/
SNode* Reverse_SqList(SNode* L)
{
	if (L == NULL || L->next == NULL)
		return;
	
	SNode* head = L;
	SNode* next;
	SNode* prev = NULL;
	while (head != NULL)
	{
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}
	return prev;


}

//递归形式实现反转
//递归的反转实质上就是从最后一个节点开始反转
SNode* reverseList_reverse(SNode* head)
{
	SNode* newHead;
	if ((head == NULL) || (head->next == NULL))
		return head;
	newHead = reverseList_reverse(head->next);   //迭代进去后第一个返回时最后一个节点，此时head为最后第二个节点
	head->next->next = head;                     //第一次执行这一条指令的时候head为最后第二个节点
	head->next = NULL;                           //这是为了保证反转后最后一个节点指向空，
												 //不用纠结，虽然在这个递归会给他赋NULL，但是在下一个递归的位置又给他赋值了一个新的node，最终结果不是null
												 //但是在最外层的递归时就只赋值NULL，最终结果解释反转后最后一个节点是NULL，符合要求

	return newHead;
}




/*********************************************
* 根据位置来返回链表中的某个节点
**********************************************/
SNode* Locate_SNode_Pos(SNode* L, int i)
{
	SNode *p = L;
	int pos = 0;
	while (pos < i&&p->next != NULL)
	{
		p = p->next;
		pos++;
	}
	if (pos == i)
		return p;
	else
		return NULL;
}

/*********************************************
* 根据想要获得值来返回链表中的某个节点
**********************************************/
SNode* Locate_SNode_Value(SNode* L, datatype x)
{
	SNode* p;
	p = L;
	while (p != NULL&&p->data != x)
		p = p->next;
	return p;
}

/****************************************************
* 在给定的节点之后插入一个节点
******************************************************/
void Insert_After(SNode* L, datatype x)
{
	SNode* p;
	p = (SNode*)malloc(sizeof(SNode));
	p->data = x;
	p->next = L->next;
	L->next = p;
}
/****************************************************
* 在给定的节点之前插入一个节点
******************************************************/
void Insert_Before(SNode* L, SNode* p, datatype x)
{
	SNode *temp, *s;
	s = (SNode*)malloc(sizeof(SNode));
	s->data = x;
	temp = L;
	while (temp->next!= p&&temp->next!=NULL)
	{
		temp = temp->next;
	}
	s->next = temp->next;
	temp->next = s;
}
/****************************************************
* 给定想要在链表中的某个位置，插入一个节点
******************************************************/
void Insert_SNode(SNode* L, int i, datatype x)
{
	SNode *p, *temp;
	p = Locate_SNode_Pos(L, i-1);
	if (p == NULL)
	{
		printf("position i does not exist!");
	}
	else
	{
		temp = (SNode*)malloc(sizeof(SNode));
		temp->data = x;
		temp->next = p->next;
		p->next = temp;
	}
}
/****************************************************
* 删除某个节点后面一个节点
******************************************************/
int DeleteAfter(SNode *p)
{
	SNode *r;
	if (p->next != NULL)
	{
		r = p->next;
		p->next = r->next;
		free(r);
		return 1;
	}
	return 0;
}

/****************************************************
* 删除指定节点
******************************************************/
void Delete_Node(SNode *L, SNode *p)
{
	SNode *q;
	q = L;
	while (q->next != p&&q->next!=NULL)
		q = q->next;
	q->next = p->next;
	free(q);
}
/****************************************************
* 删除指定位置的节点
******************************************************/
void Delete_Node_Pos(SNode *L, int i)
{
	SNode *q;
	q = Locate_SNode_Pos(L, i-1);
	if (q == NULL||q->next ==NULL)
	{
		printf("Position i does not exit!");
	}
	else
	{
		q->next = q->next->next;
		free(q->next);
	}
}
/****************************************************
* 删除节点的value值为x的节点
******************************************************/
int Delete_Node_Value(SNode *L, datatype x)
{
	SNode *p, *q;
	int count = 0;
	p = L;
	if(p==NULL)
	    return 0;
	while (p->next)
	{
		q = p->next;
		if (q->data == x)
		{
			p->next = q->next;
			free(q);
			count++;
		}
		else
			p = q;
	}
	return count;
}

/****************************************************
* 创建一串链表
******************************************************/
SNode* Create_SNodeF(int n)
{
	SNode *L, *s;
	int x;
	L = (SNode*)malloc(sizeof(SNode));
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &x);
		s = (SNode*)malloc(sizeof(SNode));
		s->data = x;
		s->next = L->next;
		L->next = s;
	}
	return L;
}

SNode * Insert_NodeR(int n)
{
	SNode *L, *q, *p;
	int x;
	L = (SNode*)malloc(sizeof(SNode));
	p = L;
	for (int i = 0; i < n; i++)
	{
		q = (SNode*)malloc(sizeof(SNode));
		scanf_s("%d", &x);
		q->data = x;
		q->next = p->next;
		p->next = q;
		p = q;
	}
	p->next = NULL;
	return L;
}

/****************************************************
* 将两个链表R1和R2首尾互联成一个循环链表
******************************************************/
SNode *Connect(SNode *R1, SNode *R2)
{
	SNode *p = R2->next;
	R2->next = R1->next;
	R1->next=p->next;    //去掉R2的头结点
	free(p);
	R1 = R2;             //使R1指向尾节点
	return R1;
}
/****************************************************
* 双向链表的基本节点结构定义
******************************************************/
struct DNode
{
	datatype data;
	struct DNode *prior, *next;
};
/****************************************************
* 在给定的双向链表的节点之前插入一个节点
******************************************************/
void Inset_DNode(DNode *p, int x)   //将节点插入到p之前
{
	DNode *s;
	s = (DNode*)malloc(sizeof(DNode));
	s->data = x;
	s->prior = p->prior;
	p->prior->next = s;
	p->prior = s;
	s->next = p;
}

/****************************************************
* 删除一个双向链表节点
******************************************************/
void Delete_DNode(DNode *p)
{
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
}

/*
几种链表的比较
共同点：采用指针表示线性表中元素之间的逻辑关系
（1）在单链表中只能沿着指针所指向的方向从头到尾 扫描，不能访问已经查找过的节点，
而在循环链表中则可以从表中的任一节点出发找到表中的其他节点。
（2）判别表尾的方式不同，假设p为指向链表中节点的指针，则对于单链表判断表尾的条件是p->next = NULL;
对于循环链表判断表尾的条件是p->next=L,L为头指针。
（3）若指向链表的头指针为L， 不头结点的链表中的第一个数据节点是L， 带头节点的链表中的第一个数据节点为L->next。
*/

/************************************************************************************************************************/
/************************************************************************************
*多项式的求和问题
************************************************************************************/
struct PLNode
{
	float coef;
	float expn;
	struct PLNode *next;
};

void Createpolyn(PLNode *L, int m)
{
	float coef;
	int expn;
	PLNode *tail;
	PLNode *new_item;
	L->coef = m;
	L->expn = -1;
	tail = L;
	for (int i = 0; i < m; i++)
	{
		new_item = (PLNode*)malloc(sizeof(PLNode));
		printf("input coef and expn: ");
		scanf_s("%f", &coef);
		scanf_s("%d", &expn);
		new_item->coef = coef;
		new_item->expn = expn;
		new_item->next = NULL;
		tail->next = new_item;
		tail = new_item;
	}
}

PLNode* Addpolyn(PLNode *La, PLNode *Lb)
{
	PLNode *pa, *pb, *pc, *Lc, *u;
	pa = La;
	pb = Lb;
	pc = (PLNode *)malloc(sizeof(PLNode));
	u = pc;
	Lc = (PLNode *)malloc(sizeof(PLNode));
	Lc->coef = 0;
	Lc->expn = -1;
	Lc->next = NULL;
	int len = 0;
	while (pa&&pb)
	{
		int x = pa->expn - pb->expn;
		if (x < 0)
		{
			pc->next = pa;
			pc = pc->next;
			pa = pa->next;
			len++;
		}
		else if (x == 0)
		{
			int y = pa->coef + pb->coef;
			if (y != 0)
			{
				pa->coef = y;
				pc->next = pa;
				pc = pc->next;

				pa = pa->next;
				pb = pb->next;

				len++;

			}
			else
			{
				pa = pa->next;
				pb = pb->next;
			}
		}
		else
		{
			pc->next = pb;
			pc = pc->next;

			pb = pb->next;
		}
	}
	if (pa)
	{
		pc->next = pa;
		while (pa)
		{
			len++;
			pa = pa->next;
		}
	}
	if (pb)
	{
		pc->next = pb;
		while (pb)
		{
			len++;
			pb = pb->next;
		}
	}
	Lc->coef = len;
	Lc->next = u->next;
	return Lc;
}

void Printpoly(PLNode *q)
{
	if (q->expn == 0)
	{
		printf("%.0f", q->coef);
	}
	else if (q->expn == 1)
	{
		if (q->coef == 1)
			printf("x");
		else if (q->coef == -1)
			printf("-x");
		else{
			printf("%.0f", q->coef);
			printf("x");
		}
	}
	else if (q->coef == 1)
		printf("x^%d", q->expn);
	else if (q->coef == -1)
		printf("-x^%d", q->expn);
	else
		printf("%.0fx^%f", q->coef, q->expn);
}

void Printpolyn(PLNode *L)
{
	PLNode *p;
	p = L;
	int n = 0;
	while (p)
	{
		n++;
		if (n == 1)
		{
			Printpoly(p);
		}
		else if (p->coef > 0)
		{
			printf("+");
			Printpoly(p);
		}
		else
		{
			printf("-");
			Printpoly(p);
		}
		p = p->next;
	}
}

//void main()
//{
//	PLNode *La, *Lb, *Lc;
//	int m, n;
//	printf("\n\ninput n of La: ");
//	scanf_s("%d", &n);
//	La = (PLNode*)malloc(sizeof(PLNode));
//	Createpolyn(La, n);
//	printf("\n\ninput n of Lb: ");
//	scanf_s("%d", &m);
//	Lb = (PLNode*)malloc(sizeof(PLNode));
//	Createpolyn(Lb, m);
//	printf("\nLa=");
//	Printpolyn(La->next);
//	printf("\nLb=");
//	Printpolyn(Lb->next);
//	Lc = Addpolyn(La->next, Lb->next);
//	printf("\nLc=");
//	Printpolyn(Lc->next);
//	scanf_s("%d", &n);
//}

/************************************************************************************
约瑟夫(Joseph)问题
编号为1，......，n的n个人顺时针方向围坐一圈，从第1号人喀什顺时针方向自1开始报数，遇到m停止报数。报m的人出列，然后从此人的下一个人开始重新报数
直到所有的人全部出列位置
************************************************************************************/
struct Point
{
	int data;
	int No;
	struct Point *next;
};

int m, n;
Point *Creat_PList()                //生成单向循环列表
{
	int i;
	Point *head, *tail, *new_item;
	tail = (Point*)malloc(sizeof(Point));
	head = NULL;
	printf("\ninput n: ");
	scanf_s("%d", &n);
	printf("\ninput m: ");
	scanf_s("%d", &m);
	for (int i = 1; i <= n; i++)
	{
		new_item = (Point*)malloc(sizeof(Point));
		new_item->No = i;
		if (head == NULL)
		{
			head = new_item;
			tail = head;
		}
		else
		{
			tail->next = new_item;
			tail = new_item;
		}
	}
	tail->next = head;
	return head;
}

void Search(Point *head)
{
	int count, num;
	Point *pre, *p;
	num = 0;
	count = 1;
	p = head;
	printf("\noutput data: ");
	while (num < n)
	{
		do{
			count++;
			pre = p;
			p = p->next;
		} while (count < m);
		pre->next = p->next;
		printf("%3d", p->No);
		free(p);
		p = pre->next;
		count = 1;
		num++;
	}
}

//void main()
//{
//	Point *head;
//	head = Creat_PList();
//	Search(head);
//
//	PLNode *La, *Lb, *Lc;
//	int m, n;
//	printf("\n\ninput n of La: ");
//	scanf_s("%d", &n);
//	La = (PLNode*)malloc(sizeof(PLNode));
//	Createpolyn(La, n);
//	printf("\n\ninput n of Lb: ");
//	scanf_s("%d", &m);
//	Lb = (PLNode*)malloc(sizeof(PLNode));
//	Createpolyn(Lb, m);
//	printf("\nLa=");
//	Printpolyn(La->next);
//	printf("\nLb=");
//	Printpolyn(Lb->next);
//	Lc = Addpolyn(La->next, Lb->next);
//	printf("\nLc=");
//	Printpolyn(Lc->next);
//	scanf_s("%d", &n);
//}
