/*
 *NAME:RANDOMIZED-SELECT (EXPECTED RUNNING TIME(O(n)))
 *TIME:2016.10.1	
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *A, int p, int r);
int randPartition(int *,int ,int );
int randomSelect(int *A, int p, int r,int k);
void swap(int *,int *);

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
	printf("Please input the Kth(must 1<=k<=%d) :",n);	//k表示选择第几个数
	scanf("%d",&k);
	num = randomSelect(A,0,n-1,k);                          
        printf("%d\n",num);
	return 0;
}

int randomSelect(int *A, int p, int r,int k) 			//随机选择函数，参数分别表示：数组A，数组起始下标p，数组最后元素下标，选择第k个数
{
	int i,q;
	if(p == r)						//如果只有一个元素，则就是选择的数
		return A[p];
	q = randPartition(A,p,r);				//随机分割数组A
	i = q - p + 1;
	if(i == k)						//如果i==k，则A[q]就是第k个数
		return A[q];
	else if(i > k)						//注意这里的大小比较，第k个数在左半边
		return randomSelect(A,p,q-1,k);
	else							//第k个数在右半边
		return randomSelect(A,q+1,r,k-i);		

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

int randPartition(int *A, int p,int r)                          //randPartition()函数将产生一个随机数,使其成为主元
{
        srand((unsigned)time(NULL));
        int random;
        random = (rand()%(r-p+1)) + p;                          //随机产生一个p到r之间的一个随机数
        swap(&A[random], &A[r]);
        return partition(A,p,r);
}

void swap(int *a,int *b)                                        //交换函数
{
        int swap;
        swap = *a;
        *a = *b;
        *b = swap;
}

