/*
 *NAME:HEAP-SORT
 *TIME:2017.11.22
 *AUTHOR:LS
 */

/*
The Best-case performance O(n).

The Worst-case performance O(n log n).

The Average performance O(n log n).

The Heap Sort is Not Stability.

The Worst-case space complexity O(1) auxiliary.
*/

#include <stdio.h>
#include <stdlib.h>

//宏定义求下标为 i 的左孩子和右孩子
#define LEFT(i) (2*i+1)
#define RIGHT(i) 2*(i+1)

//交换两元素的值
void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//在小标为 index 处调整堆，维护堆序性质
//假设 index 左右孩子都满足堆序性质
void max_heapify(int A[], int index, int heapsize)
{
	int iMax, iLeft, iRight;
	
	//iMax 用于保存下标为 index 及其左、右孩子三者最大值
	while(1)
	{
		iMax = index;
		iLeft = LEFT(index);
		iRight = RIGHT(index);
		
		if(iLeft < heapsize && A[iLeft] > A[iMax])
			iMax = iLeft;
		if(iRight < heapsize && A[iRight] > A[iMax])
			iMax = iRight;
		
		//如果 iMax != index ,说明 index 左孩子或者右孩子大于 以 index 为下标的值,
		//违反堆序性质，需要交换调整.
		//否则说明该子树已经满足堆序性质，退出循环
		if(iMax != index)
		{
			swap(&A[iMax], &A[index]);
			index = iMax;
		}
		else
			break;
	}
}

//构建大根堆
void build_max_heap(int A[], int heapsize)
{
	int i;
	//从第一个非叶子节点开始，调整数组结构使之满足堆序性质
	for(i = (heapsize-1)/2; i >=0; i--)
		max_heapify(A, i, heapsize);
}

//将初始待排序关键字序列(A0,A1,A2,...,An-1)构建成大根堆，此堆为初始的无序区，堆大小为数组大小 n；
//将堆顶元素 A[0] 与最后一个元素 A[n-1] 交换，此时得到新的无序区(A1,A2,......An-2)
//和新的有序区(An-1),且满足 A[0,1,2...n-1] <= A[n-1]，并将堆大小减 1；
//在 A[0] 处维护堆序性质，再交换 A[0] 和 A[n-2]，重复此过程直至堆大小为 1；
void heap_sort(int A[], int length)
{
	int i,k;

	build_max_heap(A, length);
	
	for(i = length-1; i > 0; i--)
	{
		swap(&A[i], &A[0]);
		max_heapify(A, 0, i);
/*	
		for(k = 0; k < length; k++)
			printf("%d   ",A[k]);
		printf("\n");
*/
	}
}


int main()
{
	int A[] = {89,23,101,16,43,20,3,11,67,17,8,99};
	int i;
	int n = sizeof(A)/sizeof(A[0]);

	heap_sort(A, n);

	printf("\n");
	for (i = 0; i < n; i++)
	{
        	printf("%d   ", A[i]);
	}
    	printf("\n");
}

