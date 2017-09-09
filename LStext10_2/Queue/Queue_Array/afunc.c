#include <stdio.h>
#include <stdlib.h>
#include "queuearray.h"

#define MAXLEN 100

int IsEmpty(Queue Q)
{
	return Q->front == Q->rear;
}

int IsFull(Queue Q)
{
	return (Q->rear + 1) % MAXLEN == Q->front;
}

Queue CreateQueue()
{
	Queue Q;
	Q = (ptrANode)malloc(sizeof(ANode));
	if(Q == NULL)
	{
		printf("Create Queue False!\n");
		return NULL;
	}
	else
	{
		Q->array = (Elemtype *)malloc(MAXLEN * sizeof(Elemtype));
		if(Q->array == NULL)
	        {
        	        printf("Create Queue False!\n");
                	return NULL;
        	}
		else
		{
			Q->front = Q->rear = 0;
			return Q;
		}
	}
}

void MakeEmpty(Queue Q)
{
	if(Q == NULL)
		printf("Please Create Queue First!\n");
	else
		Q->front = Q->rear = 0;
}

void DisposeQueue(Queue Q)
{
	free(Q->array);
	free(Q);
}

int QueueLen(Queue Q)
{
	if(Q == NULL)
		printf("Please Create Queue First\n");
	else
		return (Q->rear - Q->front + MAXLEN) % MAXLEN;	
}

Elemtype Front(Queue Q)
{
        if(Q == NULL)
                printf("Please Create Queue First\n");
        else if(IsEmpty(Q))
		printf("The Queue Is Empty!\n");
	else
		return Q->array[Q->front];
}

void EnQueue(Elemtype X, Queue Q)
{
	if(IsFull(Q))
		printf("The Queue is Full!\n");
	else
	{
		Q->array[Q->rear] = X;
		Q->rear = (Q->rear + 1)	% MAXLEN;
	}
}

void DeQueue(Queue Q)
{
        if(Q == NULL)
                printf("Please Create Queue First\n");
        else if(IsEmpty(Q))
                printf("The Queue Is Empty!\n");
        else
		Q->front = (Q->front + 1) % MAXLEN;
}

Elemtype FrontAndDequeue(Queue Q)
{
	Elemtype t;
        if(Q == NULL)
                printf("Please Create Queue First\n");
        else if(IsEmpty(Q))
                printf("The Queue Is Empty!\n");
        else
	{
		t = Front(Q);
		DeQueue(Q);
		return t;
	} 
}

