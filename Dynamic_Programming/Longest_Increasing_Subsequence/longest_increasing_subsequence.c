#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LIS_N2(int arr[], int len)
{
	int i, j;
	int k = 0;
	int max = 0;
	int longest[len];
	
	for(i =0; i < len; i++)
	{
		longest[i] = 1;
	}

	for(i = 1; i < len; i++)
	{
		for(j = 0; j < i; j++)
		{
			if(arr[i] > arr[j] && longest[i] < longest[j] + 1)
			{
				longest[i] = longest[j] + 1;		
			}
		}
	}

	for(i = 0; i < len; i++)
	{
		if(longest[i] > max)
		{
			max = longest[i];
			k = i;
		}
	}
	printf("%d\n",max);
	
	
	i = 0;
	j = 1;
	while(i <= k && j <= max)
	{
		if(longest[i] == j)
		{
			printf("%d   ",arr[i]);
			i++;
			j++;
		}
		else
		{
			i++;
		}
	}
	printf("\n");
		
	return 0;
}

int BiSearch(int *b, int max, int w)  
{  
    int left = 0;  
    int right = max - 1;
    int mid;  
    while (left <= right)  
    {  
        mid = left + (right-left)/2;  
        if (b[mid] > w)  
            right = mid - 1;  
        else if (b[mid] < w)  
            left = mid + 1;  
        else    //找到了该元素，则直接返回  
            return mid;  
    }  
    return left;//数组b中不存在该元素，则返回该元素应该插入的位置  
}  

void LIS_NlgN(int arr[], int len)
{
	int i, j;
	int k = 0;
	int max= 0;
	int pos;
	int longest[len];	
	int subsequence[len];

	max = 1;
	longest[0] = arr[0];		
	subsequence[0] = arr[0];
	for(i = 1; i < len; i++)
	{
		if(arr[i] > longest[max-1])
		{
			longest[max] = arr[i];
			subsequence[max] = arr[i];
			max++;
		}
		else
		{
			pos = BiSearch(longest, max, arr[i]);
			longest[pos] = arr[i];
		}
	}
	printf("%d\n",max);

	for(i = 0; i < max; i++)
	{
		printf("%d   ",subsequence[i]);
	}		
	printf("\n");

	for(i = 0; i < max; i++)
	{
		printf("%d   ",longest[i]);
	}
	printf("\n");

}

int main()
{
	int arr[] = {2, 1, 5,  3, 6, 4, 8, 9, 7};
	int length = sizeof(arr)/sizeof(arr[0]);

	LIS_NlgN(arr, length);

}





