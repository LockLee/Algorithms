/*
 *NAME:SELECTION-SORT(O(n^2))
 *TIME:2017.11.21
 *AUTHOR:LS
 */

#include<stdio.h>
#include<stdlib.h>

/*



*/

void selection_sort(int A[], int n)
{
	int i, j, k;
	int min;
	int tmp;
	
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
