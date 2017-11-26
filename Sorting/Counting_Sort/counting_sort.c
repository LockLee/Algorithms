/*
 *NAME:COUNTING SORT(O(n))
 *TIME:2016.10.2	
 *AUTHOR:LS
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
	k = maximum(A, n) + 1;					//maximum()函数计算A[]数组最大值，k表示A[]数组的范围，从0开始
	countingSort(A, n, k);
	for(i = 0;i < n;i++)
	{
		printf("%d	",A[i]);
	}	
        printf("\n");
        return 0;
}

int maximum(int *A,int n)					 //maximum()函数计算A[]数组最大值
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

void countingSort(int *A,int n,int k)
{
	int i,j;
	int B[n],C[k];						//B[]数组用来排序，C[]数组用来计数
	for(i = 0;i < k;i++)					//初始化C[]为0
	{
		C[i] = 0;
	}
	for(j = 0;j < n;j++)					//统计元素等于A[j]的元素个数
	{
		C[A[j]]++;		
	}
	for(i = 1;i < k;i++)					//统计有多少元素小于等于A[i]的
	{
		C[i] += C[i-1];
	}
	for(j = n-1;j >= 0;j--)					//把每个元素A[j]放到B[]数组中的正确位置
	{
		B[--C[A[j]]] = A[j];				//数组B[]下标从0开始，所以A[j]的正确位置是C[A[j]] - 1
		//C[A[j]]--;
	}
	for(j = 0;j < n;j++)					//把数组B[]复制给数组A[]
		A[j] = B[j];	
}
