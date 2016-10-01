/*
 *NAME:SIMULTANEOUS MINIMUM AND MAXIMUN (O(3n/2))
 *TIME:2016.10.1
 *AUTHOR:LS
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *min_maximum(int *A, int n);            //函数声明

int main()
{
        int i, n;
        n = 0;
	int *p;
        printf("Please input the array numbers:");
        scanf("%d",&n);                         //输入数组大小
        int A[n];                            
        printf("Please input %d numbers:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }                                       //初始化数组
        p = min_maximum(A, n);                  //调用merge_sort()函数，对数组A[]排序
        printf("minimum is:%d\nmaximum is:%d\n ",*p,*(p + 1));
        //printf("%d",INT_MIN);
	//printf("\n");
	free(p);
	return 0;
 
}

int *min_maximum(int *A, int n)
{
	int i , j;
	int *m;
	m = (int *)malloc(sizeof(int)*2);
	*m = INT_MAX;			//初始化最小值为int类型最大值
	*(m + 1) = INT_MIN;		//初始化最大值为int类型最小值
	if(n == 0)			//如果数组没有元素，最大最小值设为0
	{
		*m = 0;
		*(m + 1) = 0;
	}
	else if(n%2 == 1)		//数组元素是奇数个
	{
		*m = *(m + 1) = A[0];
		for(i = 1;i < n;i = i + 2)
		{
			if(A[i] <= A[i + 1])
                        {
                                if(A[i] < *m)
                                        *m = A[i];
                                if(A[i + 1] > *(m + 1))
                                        *(m + 1) = A[i + 1];
                        }
                        else
                        {
                                if(A[i] > *(m + 1))
                                        *(m + 1) = A[i];
                                if(A[i + 1] < *m)
                                        *m = A[i + 1];
                        }

		}
	}
	else				//数组元素是偶数个
	{
		for(i = 0;i < n; i = i +2)
		{
			if(A[i] <= A[i + 1])
			{
				if(A[i] < *m)
					*m = A[i];
				if(A[i + 1] > *(m + 1))
					*(m + 1) = A[i + 1];
			}
			else 
			{
				if(A[i] > *(m + 1))
					*(m + 1) = A[i];
				if(A[i + 1] < *m)
					*m = A[i + 1];
			}
		}			

	}
	return m;
}







