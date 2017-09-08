/*
 *Name: Link_Queue
 *Author: LS
 *Time: 2017.9.8
 */

#include <stdio.h>
#include <stdlib.h>
#include "queuelink.h"

int main()
{
	LinkQueue *Q;
	
	Q = CreateQueue();
	if(IsQueueEmpty(Q))
		printf("The Queue is Empty!\n");
	printf("EnQueue 3 Elements!\n");
	EnQueue(34, Q);
	EnQueue(31, Q);
	EnQueue(100, Q);
	if(!IsQueueEmpty(Q))
	{
		X = Front(Q);	
		printf("The Queue Element is %d\n", X);
		DeQueue(Q);
	}
	printf("The Last Element is: %d\n",Q->rear->value);
	printf("DeQueue A Element!\n");
	if(IsQueueEmpty(Q))
                printf("The Queue is Empty!\n");

	return 0;
}
