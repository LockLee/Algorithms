/*
 *NAME:MAXIMUM-SUBARRAY-SUM(O(nlgn))
 *TIME:2017.12.5
 *AUTHOR:LS
 */

/*
 PROBLEM:
 You are given a one dimensional array that may contain both positive and negative integers, 
 find the sum of contiguous subarray of numbers which has the largest sum.
 For example, if the given array is {-2, -5, 6, -2, -3, 1, 5, -6}, then the maximum subarray 
 sum is 7 (see highlighted elements).
 
 Using Divide and Conquer approach, we can find the maximum subarray sum in O(nLogn) time. 
 Following is the Divide and Conquer algorithm.
 1) Divide the given array in two halves
 2) Return the maximum of following three
 ….a) Maximum subarray sum in left half (Make a recursive call)
 ….b) Maximum subarray sum in right half (Make a recursive call)
 ….c) Maximum subarray sum such that the subarray crosses the midpoint
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define max3(a, b, c) (max(a, b)) > (c) ? max(a, b) : (c)

static int maxSubSum(const int A[], int left, int right)
{
	int i, mid;
	int leftsum, rightsum, sum;
	int maxleftsum, maxrightsum;
	int leftborder, rightborder;
	
	if(left == right)
		return A[left];
	
	mid = (left + right)/2;
	
	maxleftsum = maxSubSum(A, left, mid);
	maxrightsum = maxSubSum(A, mid+1, right);
	
	sum = 0;
	leftsum = INT_MIN;
	for(i = mid; i >= left; i--)
	{
		sum += A[i];
		if(sum > leftsum)
			leftsum = sum;
	}

	sum = 0;
	rightsum = INT_MIN;
	for(i = mid+1; i <= right; i++)
	{
		sum += A[i];
		if(sum > rightsum)
			rightsum = sum;
	}
	
	return max3(maxleftsum, maxrightsum, leftsum + rightsum);
} 

int maxSubsequenceSum(const int A[], int n)
{
	return maxSubSum(A, 0, n-1);
}

int main()
{
   int arr[] = {-2, 3, 4, -5, 7};
   int n = sizeof(arr)/sizeof(arr[0]);
   int max_sum = maxSubsequenceSum(arr, n);
   printf("Maximum contiguous sum is %d\n", max_sum);
   return 0;
}
