/* Two-way partitioning */

#include <stdio.h>

//函数声明
int partition(int *A, int p, int r);
void quicksort(int *A, int p, int r);
void swap(int *,int *);

int main()
{
	int i;
	int A[] = {4,7,6,5,3,2,8,1};
	int n = sizeof(A)/sizeof(A[0]);                                  	
	
	//调用quicksort()函数
        quicksort(A,0,n-1);                 			
	
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
{	
	int i, j;
	int t;

	//选取数组第一个元素作为主元
	t = A[l];
	// i 和 j 是左右循环下标 
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
	
		if (i > j)
			break;
		swap(&A[i], &A[j]);
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
		//递归调用quicksort()函数
		quicksort(A,p,q-1);				
		quicksort(A,q+1,r);	
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
