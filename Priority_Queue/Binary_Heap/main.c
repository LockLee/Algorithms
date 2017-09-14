/*
 *Name: Binary_Queue
 *Author: LS
 *Time: 2017.9.14
 */


#include <stdio.h>
#include <netdb.h>
#include "binheap.h"

int main()
{
	int i;
	Elemtype tmp;
	Elemtype array[10] = {65, 24, 31, 26, 21, 32, 19, 68, 13,16};
	PriorityQueue H;
	
	printf("The First Array:\n");
	for(i = 0; i < 10; i++)
		printf("%d	",array[i]);
	printf("\n\n");

	printf("The BuildHeap After:\n");
	H = BuildHeap(array, 10);
        for(i = 1; i <= H->size; i++)
                printf("%d      ",H->Elements[i]);
        printf("\n\n");

	printf("The Insert 18 After:\n");
	Insert(18, H);
        for(i = 1; i <= H->size; i++)
                printf("%d      ",H->Elements[i]);
        printf("\n\n");

	printf("The DeleteMin After:\n");
        DeleteMin(H);
        for(i = 1; i <= H->size; i++)
                printf("%d      ",H->Elements[i]);
        printf("\n\n");

	printf("The FindMin After:\n");
        tmp = FindMin(H);
        printf("%d      ",tmp);
        printf("\n\n");
	
        printf("The Decrease Position 5 and Delta is 5 After:\n");
        DecreaseKey(5, 5, H);
        for(i = 1; i <= H->size; i++)
                printf("%d      ",H->Elements[i]);
        printf("\n\n");

        printf("The Increase Position 2 and Delta is 10 After:\n");
        IncreaseKey(2, 10, H);
        for(i = 1; i <= H->size; i++)
                printf("%d      ",H->Elements[i]);
        printf("\n\n");

        printf("The Delete Position 2 After:\n");
        Delete(2, H);
        for(i = 1; i <= H->size; i++)
                printf("%d      ",H->Elements[i]);
        printf("\n\n");

	Destroy(H);
}
