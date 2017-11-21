/*
 *NAME:INSERTION-SORT(O(n^2))
 *TIME:2016.9.15
 *AUTHOR:LS
 *UUPDATE:2017.11.21
 *Add some comments.
 */

#include<stdio.h>
#include<stdlib.h>

/*
The best case input is an array that is already sorted.
The Best Case Time Cost：O(n)

The simplest worst case input is an array sorted in reverse order. 
The Worst Case Time Cost：O(N2)

The average case is also quadratic：O(n2), which makes insertion sort 
impractical for sorting large arrays. 

The Insertion Sort is Stability.

The Insertion Sort need other Memory is O(1).
*/

/*
 *@param  A：待排序数组
 *@param  n：数组大小
 */
void insertion_sort(int A[], int n)
{
	int i, j, tmp;	

	////将 A[i] 在 A[0]--A[i-1] 中找到正确位置并插入
	for(i = 1; i < n; i++)
	{
		tmp = A[i];
		for(j = i; j > 0 && A[j-1] > tmp; j-- )
			A[j] = A[j-1];
		A[j] = tmp;
	}
}

int main()
{
	int i;
	int A[] = {3,7,1,2,8,5};
	int n = sizeof(A)/sizeof(A[0]);
	
	insertion_sort(A, n);
	for(i = 0; i < n; i++)
		printf("%d	",A[i]);
	printf("\n");
}
