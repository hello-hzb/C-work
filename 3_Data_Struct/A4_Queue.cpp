#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
typedef int datatype;
struct SqQueue
{
	datatype data[MAXSIZE];
	int front, rear;
};

void Init_SqQueue(SqQueue *Q)
{
	Q->front = Q->rear = 0;
}

bool Empty_SqQueue(SqQueue *Q)
{
	return (Q->front == Q->rear);
}

void In_SqQueue(SqQueue *Q, int x)
{
	if (Q->rear == MAXSIZE - 1)
	{
		printf("Queue is full!");
		return;
	}
	Q->data[++Q->rear] = x;
}

void Out_SqQueue(SqQueue *Q, datatype *x)
{
	if (Q->rear == Q->front)
	{
		printf("Queue is empty!");
		return;
	}
	*x = Q->data[Q->front];
	Q->front++;
}

int farmer(int location)
{
	return((location & 0x08) != 0);
}
int wolf(int location)
{
	return((location & 0x04) != 0);
}

int cabbage(int location)
{
	return((location & 0x02) != 0);
}

int goat(int location)
{
	return((location & 0x01) != 0);
}

int safe(int location)
{
	if (goat(location) == cabbage(location) && goat(location) != farmer(location))
		return 0;
	if (goat(location) == wolf(location) && goat(location) != farmer(location))
		return 0;
	return 1;
}

void farmerproblem()
{
	int movers, location, new_location;
	int route[16];
	int i;
	SqQueue *moveto;
	moveto = (SqQueue*)malloc(sizeof(SqQueue));
	Init_SqQueue(moveto);
	In_SqQueue(moveto, 0x00);
	for (i = 0; i < 16; i++)
	{
		route[i] = -1;
	}
	route[0] = 0;
	while (Empty_SqQueue(moveto) && route[15] == -1)
	{
		Out_SqQueue(moveto, &location);
		for (movers = 1; movers <= 8; movers <<= 1)
		{
			new_location = location ^ (0x88 | movers);
			if (safe(new_location) && (route[new_location] == -1))
			{
				route[new_location] = location;
				In_SqQueue(moveto, new_location);
			}
		}
	}
	if (route[15] != -1)
	{
		printf("\n the reverse path is: ");
		for (i = 15; i >= 0; i = route[i])
		{
			printf("\n the location is: %d", i);
			if (i == 0)
				break;
		}
	}
	else
		printf("no path");
}

void main()
{
	farmerproblem();
	getchar();
}

/***********************************************************************************/
struct SNode
{
	datatype data;
	struct SNode* next;
};

struct SnQueue
{
	SNode *front;
	SNode *rear;
};

void Init_SnQueue(SnQueue *Q)
{
	Q->front = Q->rear = NULL;
}

bool Empty_SnQueue(SnQueue *Q)
{
	return  (Q->front = Q->rear);
}

int Length_SnQueuue(SnQueue *Q)
{
	int len = 0;
	SNode *p = Q->front->next;   //这里认为front的地址不是队列的头
	while (p)
	{
		len++;
		p = p->next;
	}
	return len;
}

void In_SnQueue(SnQueue * Q, datatype x)
{
	SNode *p;
	p = (SNode*)malloc(sizeof(SNode));
	p->data = x;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}

void Out_SnQueue(SnQueue *Q, datatype *x)
{
	SNode *p;
	if (Q->front = Q->rear)
		return;
	p = Q->front->next;
	Q->front->next = p->next;
	if (p->next == NULL)
	{
		Q->front = Q->rear;     //当出队以后要给rear找个尾地址，否则释放掉以后就没有rear了
	}
	*x = p->data;
	free(p);
}
