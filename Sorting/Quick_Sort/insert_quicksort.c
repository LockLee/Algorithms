#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void  insertion_sort(int *A, int p, int r);
int rand_partition(int *A, int p, int r);
void rand_quicksort(int *A, int p, int r, int k);
void swap(int *,int *);
int rand_seq3(int A[], int N);


int main()
{
	time_t c_start, c_end;

        int i, n, k;
	n = 2000000;
	int A[n];

	rand_seq3(A, n);
                   
	k = 9;             

	c_start = clock();
        rand_quicksort(A,0,n-1,k);                 		
	c_end = clock();

	printf("The pause used %f s by clock()\n",(double)(c_end,c_start)/CLOCKS_PER_SEC);

	return 0;
}


int rand_partition(int *A, int p,int r)				
{
	int i,j,randi;
	i = p - 1;
	int pivot;
	
	srand((unsigned int)time(NULL));	
	randi = (rand()%(r-p+1))+p;
	
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


void rand_quicksort(int *A, int p, int r, int k)		//quicksort()函数实现对数组的递归排序
{	
	int q;
	if(r < p + k)
		insertion_sort(A,p,r);
	else
	{
		q = rand_partition(A,p,r);			//q 为主元位置
		rand_quicksort(A,p,q-1,k);			//递归调用quicksort()函数
		rand_quicksort(A,q+1,r,k);	
	}
}


void insertion_sort(int A[], int p, int r)
{
	int i, j, tmp;	

	
	for(i = p+1; i <= r; i++)
	{
		tmp = A[i];
		for(j = i; j > p && A[j-1] > tmp; j-- )
			A[j] = A[j-1];
		A[j] = tmp;
	}
}


int randInt(int N)
{
        int randNum;

        srand((unsigned)time(NULL));
        randNum = rand()%N;

        return randNum;

}


int rand_seq3(int A[], int N)
{
        int i,j;

        for(i=0; i<N; i++)
                A[i] = i;

        for(i=1; i<N; i++)
                swap(&A[i], &A[randInt(i)]);

        return 0;
}


void swap(int *a,int *b)
{
        int tmp;
        tmp = *a;
        *a = *b;
        *b = tmp;
}

