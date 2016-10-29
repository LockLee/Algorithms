#include <stdio.h>
#include <stdlib.h>
#include "stackda.h"
#include "tree.h"

/*
struct stackRecord;
typedef struct stackRecord *pStack;

struct stackRecord
{
        Position *base;
        Position *top;
        int size;
};

pStack initStack( );
void destoryStack(pStack );
void clearStack(pStack );
int isEmpty(pStack );
int lengthStack(pStack );
void Push(int ,pStack );
Position Pop(pStack );
*/

pStack initStack()
{
	pStack S;
	S = (pStack)malloc(sizeof(struct stackRecord));
	if(!S)
	{
		printf("ERROR!");
		exit(1);
	}
	S->base = (Position* )malloc(sizeof(Position )*STACK_INIT_SIZE);
	if(!S->base)
	{
		printf("ERROR!");
		exit(1);
	}
	S->top = S->base;
	S->size = STACK_INIT_SIZE;
	return S;
}

void destoryStack(pStack S)
{
	if(!S)
	{
		printf("Stack is NULL!");
		exit(1);
	}
	free(S->base);
	free(S);
}

void clearStack(pStack S)
{
	S->top = S->base;	
}

int isEmpty(pStack S)
{
	return S->top == S->base;
}

int lengthStack(pStack S)
{
	return S->size;
}


void Push(Position X,pStack S)
{
	if((S->top - S->base)/sizeof(Position ) >= S->size)
	{
		S->base = (Position* )realloc(S->base,sizeof(Position )*(S->size + STACK_INCREASE));
		if(!S->base)
		{
			printf("ERROR!");
			exit(1);
		}
	S->top = S->base + S->size;
	S->size += STACK_INCREASE;
	}
	*(S->top) = X;
	(S->top)++;
}

Position Pop(pStack S)
{
	if(isEmpty(S))
	{
		printf("Stack is Empty!");
		exit(1);
	}
	S->top--;
	return *S->top;
}
