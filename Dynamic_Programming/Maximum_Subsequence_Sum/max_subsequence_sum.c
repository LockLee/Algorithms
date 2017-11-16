#include <stdio.h>
#include <stdlib.h>

#define max(a, b) a > b ? a : b

void Max_Subsequence_Sum(int arr[], int length)
{
	int i; 
	int left = 0;
	int right = 0;

	int maxsofar = 0;
	int maxendinghere = 0;
	int sumhere[length];

	for(i = 0; i < length; i++)
	{
		maxendinghere = max(maxendinghere + arr[i], 0);
		sumhere[i] = maxendinghere;
		maxsofar = max(maxsofar, maxendinghere);
	}
	
	for(i = 0; i < length; i++)
		printf("%d   ", sumhere[i]);
	
	printf("\nMax Subsequence Sum Is: %d\n", maxsofar);
	i = length-1;
	while(sumhere[i] != maxsofar)
		i--;
	right = i;
	for(i; i >= 0; i--)
	{
		if(sumhere[i] == 0 || i == 0)
		{
			left = i;	
			break;
		}
	}
	if(sumhere[i] == 0)
		left++;

	printf("\nLeft Is: %d \n Right Is: %d \n", left,right);
}

int main()
{
	int i;
	int arr[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
	int length = sizeof(arr)/sizeof(arr[0]);

	for(i = 0; i < length; i++)
                printf("%d   ", arr[i]);
	printf("\n");

	
	Max_Subsequence_Sum(arr, length);
}
