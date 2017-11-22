/*
 *NAME:BUBBLE-SORT
 *TIME:2017.11.22
 *AUTHOR:LS
 */

#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
The best case input is an array that is already sorted.
The Best Case Time Cost：O(n)

Bubble sort has worst-case and average complexity both О(n2).
It will not be efficient in the case of a reverse-ordered collection.

The Bubble Sort is Stability.

The Bubble Sort need other Memory is O(1).
*/

void bubble_sort(int A[], int n)
{
	int i,j,k;
	//设置标记变量 
	int flag = 1;
	
	//每一次由底至上地上升 
	//将剩余最小元素上升到端部
	for(i = 0; i < n && flag; i++)
	{
		//只要flag在下一次外循环条件检测的时候值为0，就说明已经排好序，不用继续循环 
		flag = 0;
		for(j = n-1; j > i; j--)
		{
			if(A[j-1] > A[j])
			{
				swap(&A[j], &A[j-1]);
				//如果有交换，就将标记变量赋1 
				flag = 1;
			}
		}
/*
		for(k = 0; k < n; k++)
			printf("%d   ",A[k]);
		printf("\n");
*/
	}

}

int main()
{
	int A[] = {2, 1, 3, 4, 5, 6, 7, 8, 9, 10};
	int i;
	int n = sizeof(A)/sizeof(A[0]);
	bubble_sort(A, n);

	printf("\n");
	for (i = 0; i < n; i++)
	{
        	printf("%d   ", A[i]);
	}
    	printf("\n");
}
