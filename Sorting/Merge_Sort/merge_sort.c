/*
 * NAME:MERGE-SORT BY DIVIDE-AND-CONQUER(O(nlgn))
 * TIME:2016.9.16
 * AUTHOR:LS
 */

#include <stdio.h>
#include <limits.h>				//该头文件定义了int类型的最大值INT_MAX

void merge_sort(int *A,int p,int r);             
void merge(int *A,int p,int q,int r);            //函数声明

int main()
{
	int i, n;
	n = 0;
	printf("Please input the array numbers:");
	scanf("%d",&n);				//输入数组大小
	int A[n];				
	printf("Please input %d numbers:",n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&A[i]);
	}					//初始化数组
	merge_sort(A,0,n-1);			//调用merge_sort()函数，对数组A[]排序
	for(i = 0;i < n;i++)
	{
		printf("%d	",A[i]);
	}					//打印输出数组A[]
	printf("\n");
	
}

void merge_sort(int *A,int p,int r)		//归并排序函数，传入参数分别表示待排序数组A[],数组元素第一个位置p，数组元素最后一个位子r
{
	if(p < r)
	{
		int q = (r + p) / 2;		//q将数组A[]分割为两部分
		merge_sort(A,p ,q);
		merge_sort(A,q+1,r);		//递归调用merge_sort()
		merge(A,p,q,r);			//将已排好序的数组A[]的两部分合并
	}
	
}

void merge(int *A,int p ,int q ,int r )		//合并函数merge(),参数分别为数组A[],数组元素第一个位置p，第一部分已排好序的最后一个位置q，最后一个位置r
{
	int n1,n2;
	int i, j, k;				//i,j,k表示循环变量
	n1 = q -p + 1;				
	n2 = r -q ;				//n1，n2分别表示第一部分数组和第二部分数组的元素个数
	int L[n1 + 1];
	int R[n2 + 1];				//分别创建新数组L[],R[].大小比元素个数多一，最后一个位置是‘哨兵’
	for(i = 0;i < n1;i++)
	{
		L[i] = A[p + i];
	}
	for(j = 0;j < n2;j++)
	{
		R[j] = A[q + j + 1];		//将数组A[]的第一部分，第二部分分别复制给L[],R[]数组
	}
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;			//数组L[],R[]的最后一个位置为 哨兵位，存放int型的最大值（+32767）
	i = 0;
	j = 0;
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
	
	}					//合并L[],R[].并复制给A[]


}
