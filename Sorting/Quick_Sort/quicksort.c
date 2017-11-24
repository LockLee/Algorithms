/*
 *NAME: QUICKSORT BY NAIVE(AVE:O(nlgn))
 *TIME: 2016.9.30
 *AUTHOR: LS
 *UPDATE: 2017.11.24, ADD COMMENTS.
 */ 

/*
The Best-case performance O(nlogn).

The Worst-case performance O(n2).

The Average performance O(nlogn).

The Merge Sort is Not Stability.

The Worst-case space complexity О(n) total, O(1) auxiliary.
*/
#include <stdio.h>

//函数声明
int partition(int *A, int p, int r);
void quicksort(int *A, int p, int r);
void swap(int *,int *);

int main()
{
	int i;
	int A[] = {50, 38, 72, 39, 48, 62, 84, 73};
	int n = sizeof(A)/sizeof(A[0]);                                  	
	
	//调用quicksort()函数
        quicksort(A,0,n-1);                 			
	
	for(i = 0;i < n;i++)
        {
                printf("%d	",A[i]);
        } 
	printf("\n");
}

//partition()函数将数子组 A[p,...,r] 分为两部分，一部分大于主元，一部分小于主元
//参数 A[] : 待排序数组
//     p   : 待排序子数组开始下标
//     r   : 待排序子数组结束下标
int partition(int *A, int p,int r)				
{
	int i,j;
	i = p - 1;
	int pivot;
	//选取数组最后一个元素作为主元
	pivot = A[r];		
	
	//将子数组分为4个部分：
	//A[p...i]区间内的所有值都小于等于 pivot
	//A[i+1...j-1]区间内的所有值都大于 pivot
	//A[j...r-1]区间内的所有值可能大于、小于、等于 pivot
	//A[r] = pivot
	for(j = p;j < r;j++)					
	{
		if(A[j] <= pivot)
		{
			i++;
			swap(&A[i], &A[j]);			
		}	
	}
	swap(&A[r], &A[i+1]);
	return i+1;
}

//quicksort()函数实现对数组的递归排序
//参数 A[] : 待排序数组
//     p   : 待排序子数组开始下标
//     r   : 待排序子数组结束下标
void quicksort(int *A, int p, int r)				
{	
	int q;
	if(p < r)
	{
		//q 为已经正确排序的元素位置
		q = partition(A,p,r);			
		//递归调用quicksort()函数
		quicksort(A,p,q-1);				
		quicksort(A,q+1,r);	
	}
}

//交换两变量值
void swap(int *a,int *b)
{
        int tmp;
        tmp = *a;
        *a = *b;
        *b = tmp;
}
