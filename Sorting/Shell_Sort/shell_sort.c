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
	
	increment = Hibbard(n);
	
	for(; increment > 0; increment /= 2)
	{
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
