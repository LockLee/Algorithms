#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/*

#ifndef _Stack_Head_
#define _Stack_Head_

struct node;
typedef struct node Node;
typedef struct node *ptrNode;
typedef ptrNode Stack;
typedef ptrNode Position;

int IsEmpty(Stack S);
Stack CreateStack(void );
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(Elemtype X, Stack S);
Elemtype Top(Stack S);
void Pop(Stack S);
		                

struct node
{
        int value;
        struct node *next;
};

 */

Elemtype IsEmpty(Stack S)
{
	return S->next == NULL;
}

void Pop(Stack S)
{
	ptrNode firstCell;
	
	if(IsEmpty(S))
		printf("Empty Stack!!!");
	else
	{
		firstCell = S->next;
		S->next = S->next->next;
		free(firstCell);
	}
}

void Push(Elemtype X, Stack S)
{
	ptrNode tmpCell;
	tmpCell = (ptrNode)malloc(sizeof(Node));
	if(S == NULL)
		printf("Must use CreateStack first!!!");
	else if(tmpCell == NULL)
		printf("Out of Space!!!");
	else
	{
		tmpCell->value = X;
		tmpCell->next = S->next;
		S->next = tmpCell;
	}
}

void MakeEmpty(Stack S)
{
	if(S == NULL)
	{
		printf("Must use CreateStack first!!!");
	
	}
	else
	{
		while(!IsEmpty(S))
			Pop(S);
	}
}

Stack CreateStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(struct node));
	if(S == NULL)
	{
		printf("Out of Space!!!");
		return NULL;
	}
	S->next = NULL;
	MakeEmpty(S);
	return S;
}

Elemtype Top(Stack S)
{
	if(!IsEmpty(S))
		return S->next->value;
	printf("Empty Stack!!!");
	return 0;
}


