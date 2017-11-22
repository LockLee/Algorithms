/*
 *NAME:SHELL-SORT
 *TIME:2017.11.22
 *AUTHOR:LS
 */

/*
Best-case performance O(n log n).

Worst-case performance	O(n2) (worst known gap sequence)
O(n log2n) (best known gap sequence).

Average performance depends on gap sequence.

The Shell Sort is Not Stability.

Worst-case space complexity О(n) total, O(1) auxiliary.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
	
void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//Compute Hibbard's increments
//The worst-case running time of Shellsort using Hibbard's increments is (n3/2).
int Hibbard(int n)
{
	int i = 0;
	
	while((2 << i) < n)
		i++;
	return (2 << i-1)-1;
}

void shell_sort(int A[], int n)
{
	int i, j, k;
	int increment;
	int tmp;
	
	//计算增量
	increment = Hibbard(n);
	
	//缩小增量
	for(; increment > 0; increment /= 2)
	{
		////根据当前增量进行组内插入排序
		for(i = increment; i < n; i++)
		{
			tmp = A[i];
			for(j = i; j >= increment; j -= increment)
			{
				if(A[j-increment] > tmp)
					A[j] = A[j-increment];
				else
					break;
			}
			A[j] = tmp;
		}
/*
		printf("Increment = %d\n",increment);
		for(k = 0; k < n; k++)
			printf("%d   ",A[k]);
		printf("\n");
*/
	}
}

int main()
{
	int A[] = {1,5,3,6,10,55,9,2,87,12,34,75,33,47};
	int i;
	int n = sizeof(A)/sizeof(A[0]);
	shell_sort(A, n);

	printf("\n");
	for (i = 0; i < n; i++)
	{
        	printf("%d   ", A[i]);
	}
    	printf("\n");
}
