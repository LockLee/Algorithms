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


int rand_partition(int *A, int p,int r)				
{
	int i,j,randi;
	i = p - 1;
	int pivot;
	
	srand((unsigned int)time(NULL));	
	randi = (rand()%(r-p+1))+p;
	printf("rand number = %d\n",randi);
	
	swap(&A[r], &A[randi]);
	
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



void rand_quicksort(int *A, int p, int r)				//quicksort()函数实现对数组的递归排序
{	
	int i;
	int q;
	if(p < r)
	{
		q = rand_partition(A,p,r);				//q 为主元位置
		for(i = 0; i < 8; i++)
			printf("%d   ",A[i]);
		printf("\n\n");
		rand_quicksort(A,p,q-1);				//递归调用quicksort()函数
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

