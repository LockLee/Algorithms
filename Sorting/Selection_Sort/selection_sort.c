/*
 *NAME:SELECTION-SORT
 *TIME:2017.11.21
 *AUTHOR:LS
 */

#include<stdio.h>
#include<stdlib.h>

/*
The best case execute O(n2) comparisons and O(n)swaps.
The Best Case Time Cost：O(n2)

The Worst case execute O(n2) comparisons and O(n)swaps.
The Worst Case Time Cost：O(n2)

The average case execute O(n2) comparisons and O(n)swaps.
The average Case Time Cost：O(n2)

The Selection Sort is Not Stability.

The Selection Sort need other Memory is O(1).
*/

/*
 *@param  A：待排序数组
 *@param  n：数组大小
 */
void selection_sort(int A[], int n)
{
	int i, j, k;
	int min;
	int tmp;

	//在数组 A[i...n-1] 中找到最小元素和 A[i] 交换
	// min 用来记录 A[i...n-1] 中的最小元素值
	// k 用来记录 A[i...n-1] 中最小元素的下标
	for(i = 0; i < n; i++)
	{
		min = A[i];
		k = i;
		j = i + 1;
		while(j < n)
		{
			if(A[j] < min)
			{
				min = A[j];
				k = j;
			}
			j++;
		}
		tmp = A[i];
		A[i] = min;
		A[k] = tmp;
	}
}

int main()
{
	int i;
	int A[] = {34,27,101,265,58,95,47,209};
	int n = sizeof(A)/sizeof(A[0]);
	
	selection_sort(A, n);
	for(i = 0; i < n; i++)
		printf("%d	",A[i]);
	printf("\n");
}
