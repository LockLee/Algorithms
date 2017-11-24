/*
 *NAME: A RANDOMIZED VERSION OF QUICKSORT(EXPECTED RUNNING TIME:O(nlgn))
 *TIME: 2017.11.24
 *AUTHOR: LS
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_partition(int *A, int p, int r);
void rand_quicksort(int *A, int p, int r);
void swap(int *,int *);

int main()
{
        int i, n;
	int A[] = {34,21,91,47,82,10,48,29};
	n = sizeof(A)/sizeof(A[0]);        
                                
        rand_quicksort(A,0,n-1);                 		

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
int rand_partition(int *A, int p,int r)				
{
	int i,j,randi;
	i = p - 1;
	int pivot;
	
	//随机产生一个[p,r]之间的一个随机数（包括 p 和 r）
	srand((unsigned int)time(NULL));	
	randi = (rand()%(r-p+1))+p;
	//printf("rand number = %d\n",randi);
	
	//将产生的随机主元与最后一个元素（A[r]）交换
	swap(&A[r], &A[randi]);
	
	pivot = A[r];						
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
void rand_quicksort(int *A, int p, int r)				
{	
	int i;
	int q;
	if(p < r)
	{
		q = rand_partition(A,p,r);				
		for(i = 0; i < 8; i++)
			printf("%d   ",A[i]);
		printf("\n\n");
		rand_quicksort(A,p,q-1);				
		rand_quicksort(A,q+1,r);	
	}
}

void swap(int *a,int *b)
{
        int tmp;
        tmp = *a;
        *a = *b;
        *b = tmp;
}

