/*
 *NAME:THE MAX-SUBARRAY PROBLEM BY BRUTE-FORCE SOLUTION(O(n^2))
 *TIME:2016.9.16
 *AUTHOR:LS
 */

#include <stdio.h>

int maxSubarraySum(int A[],int n);            //函数声明

int main()
{
        int i, n;
        n = 0;
	int max = 0;
        printf("Please input the array numbers:");
        scanf("%d",&n);                         //输入数组大小
        int A[n];
        printf("Please input %d numbers:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }					//初始化数组
	max = maxSubarraySum(A,n);              //调用求和函数
        printf("The Max Sum is %d !\n",max);

}

int maxSubarraySum(int A[],int n)		//暴力求解最大子数列和
{
	int i,j;
	int thisSum,maxSum = 0;
	for(i = 0;i < n;i++)
	{
		thisSum = 0;
		for(j = i;j < n;j++)
		{
			thisSum += A[j];
			if(maxSum < thisSum)
				maxSum = thisSum;

		}		
	}
	return maxSum;
}
