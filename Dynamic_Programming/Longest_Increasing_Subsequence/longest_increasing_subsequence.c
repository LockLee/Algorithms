/*
问题描述：
给定一个长度为N的数组，找出一个最长的单调自增子序列（不一定连续，但是顺序不能乱）。
例如：给定一个长度为6的数组A{5， 6， 7， 1， 2， 8}，则其最长的单调递增子序列为{5，6，7，8}，长度为4.

最优子结构：
对于长度为 N 的数组 A[N] = {a0, a1, a2, a3, . . . , an-1}, 假设我们想求以 ai 结尾的最大递增子序列长度，
设为 L[i], 那么
		max(L[j]) + 1,     where 0 < j < i and A[j] < A[i]
	L[i] = 
		1,                 otherwise
也就是 j 的范围是 0 到 i–1。这样，想求 ai 结尾的最大递增子序列的长度，我们就需要遍历 i 之前的所有位置 j（0 到 i-1），
找出 A[j] < A[i]，计算这些 j 中，能产生最大 L[i] 的 j，之后就可以求出L[i]。之后对每一个A[N]中的元素都计算以他们各自
结尾的最大递增子序列的长度，这些长度的最大值，就是我们要求的问题——数组A的最大递增子序列的长度

重叠子问题：
想求以 ai 结尾的最大递增子序列长度，需要求以 a0 到 ai-1 结尾的最大递增子序列长度 
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *最大递增子序列时间复杂度 O(N2)方法
 *
 *参数：数组和数组长度
 */
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
			//注意longest[j]<longest[i]+1这个条件，不能省略。  
			if(arr[i] > arr[j] && longest[i] < longest[j] + 1)
			{
				//计算以arr[j]结尾的序列的最长递增子序列长度 
				longest[i] = longest[j] + 1;		
			}
		}
	}

	//计算最大递增子序列个数
	for(i = 0; i < len; i++)
	{
		if(longest[i] > max)
		{
			max = longest[i];
			k = i;
		}
	}
	printf("%d\n",max);
	
	//打印最大递归子序列
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

/*
 *二分查找找到 w 应插入的位置
 *
 *参数 b：待插入数组
 *  max： 待插入数组大小
 *    w： 待插入值
 *
 *返回 w 应插入的下标
 */
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

/*
 *最大递增子序列时间复杂度 O(nlgn)方法
 *
 *参数：数组和数组长度
 */
void LIS_NlgN(int arr[], int len)
{
	int i, j;
	int k = 0;
	//保存最大递增子序列数
	int max= 0;
	int pos;
	//记录递增子序列
	int longest[len];
	//记录递增子序列顺序
	int subsequence[len];

	max = 1;
	longest[0] = arr[0];		
	subsequence[0] = arr[0];
	for(i = 1; i < len; i++)
	{
		//如果大于B中最大的元素，则直接插入到B数组末尾 
		//并将该值记录在 subsequence 数组中
		if(arr[i] > longest[max-1])
		{
			longest[max] = arr[i];
			subsequence[max] = arr[i];
			max++;
		}
		else
		{
			//二分查找需要插入的位置 
			pos = BiSearch(longest, max, arr[i]);
			longest[pos] = arr[i];
		}
	}
	printf("%d\n",max);

	//打印一个最大递增子序列
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




