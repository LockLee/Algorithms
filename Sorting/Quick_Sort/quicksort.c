/*
 *NAME:QUICKSORT BY NAIVE(AVE:O(nlgn))
 *TIME:2016.9.30
 *AUTHOR:LS
 */ 


#include <stdio.h>

int partition(int *A, int p, int r);
void quicksort(int *A, int p, int r);
void swap(int *,int *);
int main()
{
        int i, n;
        n = 0;
        printf("Please input the array numbers:");
        scanf("%d",&n);                                 	//输入数组大小
        int A[n];
        printf("Please input %d numbers:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }     	                                          	//初始化数组
        quicksort(A,0,n-1);                 			//调用quicksort()函数
	for(i = 0;i < n;i++)
        {
                printf("%d	",A[i]);
        } 
	printf("\n");
}


int partition(int *A, int p,int r)				//partition()函数将数组A[]划分为两部分，一部分大于主元，一部分小于主元
{
	int i,j;
	i = p - 1;
	int pivot;
	pivot = A[r];						//选取数组最后一个元素作为主元
	for(j = p;j < r;j++)					//遍历数组
	{
		if(A[j] <= pivot)
		{
			i++;
			swap(&A[i], &A[j]);			//交换函数
		}	
	}
	swap(&A[r], &A[i+1]);
	return i+1;
}


void quicksort(int *A, int p, int r)				//quicksort()函数实现对数组的递归排序
{	
	int q;
	if(p < r)
	{
		q = partition(A,p,r);				//q 为主元位置
		quicksort(A,p,q-1);				//递归调用quicksort()函数
		quicksort(A,q+1,r);	
	}
}

void swap(int *a,int *b)
{
        int swap;
        swap = *a;
        *a = *b;
        *b = swap;
}
