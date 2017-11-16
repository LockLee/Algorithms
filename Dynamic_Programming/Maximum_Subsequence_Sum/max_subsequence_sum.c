/*
Problem:
	Given (possibly negative) integers a1, a2, . . . , an, find the maximum value of subsequence sum. 
	(For convenience, themaximum subsequence sum is 0 if all the integers are negative.)
	Example:
	For input -2, 11, -4, 13, -5, -2, the answer is 20 (a1 through a3).
	
假设我们已经解决了针对于 x[1,...,i-1] 的问题，我们如何将其扩展为包含 x[i] de 问题呢？
我们使用类似递归思想：依次求解前 i 个元素的最大子序列和，其和如果小于 0 ，则替换为 0 (因为定义最大子序列和最小为 0 )，保存在数组 sumhere[] 中，
也就是说数组 sumhere[0,...,i-1] 保存以下标 k(0 <= k <= i-1) 结尾的最大连续子序列和。

Time Cost O(n)；Space Cost O(n).
*/

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
	//该数组保存以当前 i 结尾的最大子序列和
	int sumhere[length];

	//在每次循环之前，maxendinghere 是结束位置为 i-1 的最大子序列的和，也就是以位置 i-1 结尾的最大子序列和
	//循环开始后，赋值语句修改它以包含截止于位置 i 的最大子序列和，
	//当它变为负值时，就将它重新设为 0 （因为截止于 i 的最大子序列现在是空序列了）
	for(i = 0; i < length; i++)
	{
		maxendinghere = max(maxendinghere + arr[i], 0);
		sumhere[i] = maxendinghere;
		maxsofar = max(maxsofar, maxendinghere);
	}
	
	for(i = 0; i < length; i++)
		printf("%d   ", sumhere[i]);
	
	printf("\nMax Subsequence Sum Is: %d\n", maxsofar);
	
	//打印输出最大子序列和开始位置和结束位置
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
