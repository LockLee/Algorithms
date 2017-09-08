#include <stdio.h>
#include <stdlib.h>
#include "queuelink.h"

LinkQueue* CreateQueue()
{
	LinkQueue *ptrQueue;
	ptrQueue = (LinkQueue *)malloc(sizeof(LinkQueue));
	if(ptrQueue == NULL) 
	{
		printf("Create LinkQueue False!!!\n");
		return NULL;
	}
	else
	{
		ptrQueue->front = ptrQueue->rear = (QNode *)malloc(sizeof(QNode));
		if(ptrQueue->front == NULL)
		{
			printf("Malloc QNode False!\n");
			return NULL;
		}
		else
		{
			ptrQueue->front->next = NULL;
		}
	}

	return ptrQueue;
}

int IsQueueEmpty(LinkQueue *Q)
{
	if(Q->front->next == NULL)
		return 1;
	else
		return 0;
}

void MakeQueueEmpty(LinkQueue *Q)
{
	ptrQNode pQNode;	
	
	if(Q == NULL)
	{
		printf("Please Create Queue First!\n");
	}
	else if(Q->front->next != NULL)
	{
		while(Q->front->next)
		{
			pQNode = Q->front->next;
			Q->front->next = pQNode->next;
			free(pQNode);
		}
		Q->rear = Q->front;
	}
}

void DisposeQueue(LinkQueue *Q)
{
	if(Q == NULL)
		printf("Please Create Queue First!\n");
	else
	{
		MakeQueueEmpty( Q );
		free( Q );
	}
}

void EnQueue(Elemtype X, LinkQueue *Q)
{
	ptrQNode pqnode;

	pqnode = (ptrQNode)malloc(sizeof(QNode));
	
	if(pqnode == NULL)
	{
		printf("Malloc Space False!\n");
	}
	else
	{
		pqnode->value = X;
		pqnode->next = NULL;
		Q->rear->next = pqnode;
		Q->rear = pqnode;
	}
}

Elemtype Front(LinkQueue *Q)
{
	if(Q == NULL)	
		printf("Please Create Queue First!\n");
	else if(Q->front->next == NULL)
		printf("The Queue is Empty!\n");
	else
		return Q->front->next->value;
}

void DeQueue(LinkQueue *Q)
{
	ptrQNode pt;	

	if(Q == NULL)
                printf("Please Create Queue First!\n");
        else if(Q->front->next == NULL)
                printf("The Queue is Empty!\n");
        else
	{
		pt = Q->front->next;
		Q->front->next = pt->next;
		if(Q->front->next == NULL)
			Q->rear = Q->front;
		free(pt);
	}
}

Elemtype FrontAndDequeue(LinkQueue *Q)
{
	Elemtype t;
	if(Q == NULL)
                printf("Please Create Queue First!\n");
        else if(Q->front->next == NULL)
                printf("The Queue is Empty!\n");
	else
	{
		t = Front(Q);
		DeQueue(Q);
	}
}
