#include<stdio.h>
#include<stdlib.h>


//顺序栈
#define MAXSIZE 100
typedef int datatype;
struct SqStack
{
	datatype data[MAXSIZE];
	int top;      //top代表栈顶所对应的数组ID
};

void Init_SqStack(SqStack *S)
{
	S->top = -1;
}

bool Empty_SqStack(SqStack *S)
{
	if (S->top == -1)
		return true;
	else
		return false;
}

void Push_SqStack(SqStack *S, datatype x)
{
	if (S->top == MAXSIZE - 1)
	{
		printf("The stack is full.");
		exit(0);
	}
	else
		S->data[++S->top] = x;
}

void Pop_SqStack(SqStack *S, datatype *x)
{
	if (S->top == -1)
	{
		printf("Stack is empty!");
		exit(0);
	}
	else
	{
		*x = S->data[S->top];
		S->top--;
	}
}

void Get_Top_SqStack(SqStack *S, datatype *x)
{
	if (S->top == -1)
	{
		printf("Stack is empty!");
		exit(0);
	}
	else
	{
		*x = S->data[S->top];
		//S->top--;
	}
}


struct SnStack
{
	datatype data;
	SnStack *next;
};

SnStack* Init_SnStack()
{
	SnStack* top;
	top = NULL;
	return top;
}

bool Empty_SnStack(SnStack* top)
{
	if (top == NULL)
	{
		return true;
	}
	else
		return false;
}

void Push_SnStack(SnStack* top, datatype x)
{
	SnStack *s;
	s = (SnStack*)malloc(sizeof(SnStack));
	s->data = x;
	s->next = top;
	top = s;
}

void Pop_SnStack(SnStack *top, datatype *x)
{
	SnStack *p;
	if (!Empty_SnStack(top))
	{
		*x = top->data;
		p = top;
		top = top->next;
		free(p);
	}
}


void Get_Top_SnStack(SnStack *top, datatype *x)
{
	if (top == NULL)
	{
		printf("The stack is empty!");
		exit(0);
	}
	else
		*x = top->data;
}
