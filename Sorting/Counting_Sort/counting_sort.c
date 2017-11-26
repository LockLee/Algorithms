/*
 *NAME:COUNTING SORT(O(n + k))
 *TIME:2016.10.2	
 *AUTHOR:LS
 * *UUPDATE:2017.11.26,Add some comments.
 */

/*
The Best-case performance O(n + k), Where k is the range of integers.

The Worst-case performance O(n + k).

The Average performance O(n + k).

The Counting Sort is Stability.

The Worst case space complexity is O(n + k) auxiliary.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maximum(int *,int );
void countingSort(int *,int ,int );

int main()
{
        int i, n, k, num;
        n = 0;
        printf("Please input the array numbers:");
        scanf("%d",&n);                                         //输入数组大小
        int A[n];
        printf("Please input %d numbers:",n);			
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }
	
	//maximum()函数计算A[]数组最大值，k表示A[]数组的范围，从0开始
	k = maximum(A, n) + 1;					
	
	//计数排序
	countingSort(A, n, k);
	
	for(i = 0;i < n;i++)
	{
		printf("%d	",A[i]);
	}	
        printf("\n");
        return 0;
}

//maximum()函数计算A[]数组最大值
int maximum(int *A,int n)					 
{
	int i,max;
	max = A[0];
	for(i = 1;i < n;i++)
	{
		if(max < A[i])
			max = A[i];		
	}
	return max;		
}

/*
 *计数排序
 *
 *参数  A：待排序数组
 *      n：数组大小
 *      k：数组最大元素值
 */
void countingSort(int *A,int n,int k)
{
	int i,j;
	
	//B[]数组用来排序，C[]数组用来计数
	int B[n],C[k];			
	
	//初始化C[]为0
	for(i = 0;i < k;i++)					
	{
		C[i] = 0;
	}
	
	//统计元素等于A[j]的元素个数
	for(j = 0;j < n;j++)					
	{
		C[A[j]]++;		
	}
	
	//统计有多少元素小于等于A[i]的
	for(i = 1;i < k;i++)					
	{
		C[i] += C[i-1];
	}
	
	//把每个元素A[j]放到B[]数组中的正确位置
	for(j = n-1;j >= 0;j--)					
	{
		//数组B[]下标从0开始，所以A[j]的正确位置是C[A[j]] - 1
		B[--C[A[j]]] = A[j];				
		
	}
	
	//把数组B[]复制给数组A[]
	for(j = 0;j < n;j++)					
		A[j] = B[j];	
}
