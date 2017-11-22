#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble_sort(int A[], int n)
{
	int i,j,k;
	int flag = 1;
	
	for(i = 0; i < n && flag; i++)
	{
		flag = 0;
		for(j = n-1; j > i; j--)
		{
			if(A[j-1] > A[j])
			{
				swap(&A[j], &A[j-1]);
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
