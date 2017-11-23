/*
 * NAME: MERGE-SORT BY DIVIDE-AND-CONQUER(O(nlgn))
 * TIME: 2016.9.16
 * AUTHOR: LS
 * UPDATE: 2017.11.23; ADD SOME COMMENTS.
 */

/*
The Best-case performance O(n log n).

The Worst-case performance O(n log n).

The Average performance O(n log n).

The Merge Sort is Stability.

The Worst-case space complexity О(n) total, O(n) auxiliary.
*/

#include <stdio.h>
//该头文件定义了int类型的最大值INT_MAX(+2147483647)
#include <limits.h>				

//函数声明归并例程和归并排序例程
void merge_sort(int *A,int p,int r);             
void merge(int *A,int p,int q,int r);            

int main()
{
	int i;
	int A[] = {50, 10, 20, 30, 70, 40, 80, 60};
	int n = sizeof(A)/sizeof(A[0]);
	
	//调用merge_sort()函数，对数组A[]排序
	merge_sort(A,0,n-1);
	
	//打印输出数组A[]
	printf("\n");
	for(i = 0;i < n;i++)
	{
		printf("%d	",A[i]);
	}					
	printf("\n");

	return 0;
}

//归并排序函数，
//传入参数分别表示待排序数组A[],数组元素第一个位置p，数组元素最后一个位子r
void merge_sort(int *A,int p,int r)		
{
	if(p < r)
	{
		//q将数组A[]分割为两部分
		int q = (r + p) / 2;		
		//递归调用merge_sort()
		merge_sort(A,p ,q);
		merge_sort(A,q+1,r);		
		//将已排好序的数组A[]的两部分合并
		merge(A,p,q,r);			
	}
	
}

//合并函数merge(),
//参数分别为数组A[],数组元素第一个位置p，第一部分已排好序的最后一个位置q，最后一个位置r
void merge(int *A,int p ,int q ,int r )		
{
	int n1,n2;
	int i, j, k;				
	//n1，n2分别表示第一部分数组和第二部分数组的元素个数
	n1 = q -p + 1;				
	n2 = r -q ;		
	//分别创建新数组L[],R[].大小比元素个数多一，最后一个位置是‘哨兵’
	int L[n1 + 1];
	int R[n2 + 1];			
	
	//将数组A[]的第一部分，第二部分分别复制给L[],R[]数组
	for(i = 0;i < n1;i++)
	{
		L[i] = A[p + i];
	}
	for(j = 0;j < n2;j++)
	{
		R[j] = A[q + j + 1];		
	}
	
	//数组L[],R[]的最后一个位置为 哨兵位，存放int型的最大值（64bit,INT_MAX = 2147483647）
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;			
	i = 0;
	j = 0;
	//合并L[],R[].并复制给A[]
	for(k = p;k < r + 1;k++)
	{
		if(L[i] < R [j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;			
		}
	
	}					


}
