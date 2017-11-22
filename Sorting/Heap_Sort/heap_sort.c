#include <stdio.h>
#include <stdlib.h>

#define LEFT(i) (2*i+1)
#define RIGHT(i) 2*(i+1)

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void max_heapify(int A[], int index, int heapsize)
{
	int iMax, iLeft, iRight;
	
	while(1)
	{
		iMax = index;
		iLeft = LEFT(index);
		iRight = RIGHT(index);
		
		if(iLeft < heapsize && A[iLeft] > A[iMax])
			iMax = iLeft;
		if(iRight < heapsize && A[iRight] > A[iMax])
			iMax = iRight;
		
		if(iMax != index)
		{
			swap(&A[iMax], &A[index]);
			index = iMax;
		}
		else
			break;
	}
}

void build_max_heap(int A[], int heapsize)
{
	int i;
	for(i = (heapsize-1)/2; i >=0; i--)
		max_heapify(A, i, heapsize);
}

void heap_sort(int A[], int length)
{
	int i,k;

	build_max_heap(A, length);
	
	for(i = length-1; i > 0; i--)
	{
		swap(&A[i], &A[0]);
		max_heapify(A, 0, i);
/*	
		for(k = 0; k < length; k++)
			printf("%d   ",A[k]);
		printf("\n");
*/
	}
}


int main()
{
	int A[] = {89,23,101,16,43,20,3,11,67,17,8,99};
	int i;
	int n = sizeof(A)/sizeof(A[0]);

	heap_sort(A, n);

	printf("\n");
	for (i = 0; i < n; i++)
	{
        	printf("%d   ", A[i]);
	}
    	printf("\n");
}

