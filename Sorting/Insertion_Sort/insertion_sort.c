#include<stdio.h>
#include<stdlib.h>

void insertion_sort(int A[], int n)
{
	int i, j, tmp;	

	for(i = 1; i < n; i++)
	{
		tmp = A[i];
		for(j = i; A[j-1] > tmp && j > 0; j-- )
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
