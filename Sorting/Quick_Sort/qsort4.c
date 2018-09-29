/* Two-way partitioning */
/* qsort3(Two-way partitioning) + randomization + isort small subarrays + swap inline */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//当划分区间小于 CUTOFF 值时，停止划分 
#define CUTOFF 8

//函数声明
int partition(int *A, int p, int r);
void quicksort(int *A, int p, int r);
void isort3(int *A, int n);
void swap(int *,int *);
int randint(int l, int u);

int main()
{
	int i;
	int A[] = {8, 446, 540, 57, 812, 726, 647, 829, 745, 161, 531, 630, 325, 842, 926, 502, };
	int n = sizeof(A)/sizeof(A[0]);                                  	
	
	printf("n = %d\n",n);
	//调用quicksort()函数
   	quicksort(A,0,n-1);   
	//调用插入排序 
	isort3(A, n);              			
	
	for(i = 0;i < n;i++)
    {
        printf("%d	",A[i]);
    } 
	printf("\n");
}


/*
partition()函数将数子组 A[l,...,u] 分为两部分，一部分大于主元，一部分小于主元
参数 A[] : 待排序数组
     l   : 待排序子数组开始下标
     u   : 待排序子数组结束下标
*/
int partition(int *A, int l, int u)
{	int i, j;
	int t, temp;
	//
	if (u - l < CUTOFF)
		return -1;
		
	swap(&A[l], &A[randint(l, u)]);
	
	t = A[l];
	i = l;
	j = u+1;
	
	//将子数组分为4个部分：
	//A[l...i]区间内的所有值都小于等于 pivot
	//A[i...j]区间内的所有值可能大于、小于、等于 pivot
	//A[j...u]区间内的所有值都大于等于 pivot
	for (;;) 
	{
		
		do i++; 
		while (i <= u && A[i] < t);  //遇到相同的元素时停止扫描，并交换 i 和 j 的值 
	
		do j--;
		while (A[j] > t);  //遇到相同的元素时停止扫描，并交换 i 和 j 的值 
	
		if (i >= j)
			break;
		temp = A[i]; 
		A[i] = A[j]; 
		A[j] = temp;
	}
	swap(&A[l], &A[j]);
	
	return j;
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
		if(q != -1)
		{
		
			//递归调用quicksort()函数
			quicksort(A,p,q-1);				
			quicksort(A,q+1,r);
		}
	}
}


//插入排序 
void isort3(int *A, int n)
{	int i, j;
	int t;
	//将 A[i] 在 A[0]--A[i-1] 中找到正确位置并插入
	for (i = 1; i < n; i++) {
		t = A[i];
		for (j = i; j > 0 && A[j-1] > t; j--)
			A[j] = A[j-1];
		A[j] = t;
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

//随机数生成器 
int randint(int p, int r)
{
	//随机产生一个[p,r]之间的一个随机数（包括 p 和 r）
	srand((unsigned int)time(NULL));	
	int randi = (rand()%(r-p+1))+p;
	printf("\n randint = %d \n", randi);
	return randi;
	
}
