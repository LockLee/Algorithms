/*
 *Name: Queue_Array
 *Author: LS
 *Time: 2017.9.9
 */


#include <stdio.h>
#include <stdlib.h>
#include "queuearray.h"

int main()
{
        int X;
        Queue Q;

        Q = CreateQueue();
        if(IsEmpty(Q))
                printf("The Queue is Empty!\n");
        printf("EnQueue 3 Elements!\n");
        EnQueue(34, Q);
        EnQueue(31, Q);
        EnQueue(100, Q);
        if(!IsEmpty(Q))
        {
                X = FrontAndDequeue(Q);
                printf("The Queue Element is %d\n", X);
        }
        printf("The Last Element is: %d\n",Q->array[Q->rear]);
        printf("The Queue is length:%d\n",QueueLen(Q));

        return 0;
}

