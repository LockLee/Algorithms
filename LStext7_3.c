/*
 *NAME:QUICKSORT BY RANDOMIZED VERSION (EXPECTED RUNNING TIME : O(nlgn))
 *TIME:2016.9.30	
 *AUTHOR:LS
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *A, int p, int r);
int randPartition(int *,int ,int );
void quicksort(int *A, int p, int r);
void swap(int *,int *);
int main()
{
        int i, n;
        n = 0;
        printf("Please input the array numbers:");
        scanf("%d",&n);                                         //输入数组大小
        int A[n];
        printf("Please input %d numbers:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }                                                       //初始化数组
        quicksort(A,0,n-1);                                     //调用quicksort()函数
        for(i = 0;i < n;i++)
        {
                printf("%d      ",A[i]);
        } 
        printf("\n");
}

int partition(int *A, int p,int r)                              //partition()函数将数组A[]划分为两部分，一部分大于主元，一部分小于主元
{
        int i,j;
        i = p - 1;
        int pivot;
        pivot = A[r];                                           //选取数组最后一个元素作为主元
        for(j = p;j < r;j++)                                    //遍历数组
        {
                if(A[j] <= pivot)
                {
                        i++;
                        swap(&A[i], &A[j]);                     //交换函数
                }
        }
        swap(&A[r], &A[i+1]);
        return i+1;
}



int randPartition(int *A, int p,int r)      			//randPartition()函数将产生一个随机数,使其成为主元
{
	srand((unsigned)time(NULL));
	int random;
	random = (rand()%(r-p)) + p;				//随机产生一个p到r之间的一个随机数
	swap(&A[random], &A[r]);
        return partition(A,p,r);
}

void quicksort(int *A, int p, int r)                            //quicksort()函数实现对数组的递归排序
{
        int q;
        if(p < r)
        {
                q = randPartition(A,p,r);                       //q 为主元位置
                quicksort(A,p,q-1);                             //递归调用quicksort()函数
                quicksort(A,q+1,r);
        }
}

void swap(int *a,int *b)					//交换函数
{
        int swap;
        swap = *a;
        *a = *b;
        *b = swap;
}
 
