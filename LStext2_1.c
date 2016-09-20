/*
 *NAME:INSERTION-SORT(O(n^2))
 *TIME:2016.9.15
 *AUTHOR:LS
 */

#include <stdio.h>

int main()
{
	int n,i,j,key;                     //n表示数组大小，key表示交换变量
	n = 0;
	printf("Please input the array length:");
	scanf("%d",&n);                    //输入数组大小
 	int A[n];                               
	printf("Please input %d numbers:",n);
	for(i = 0;i < n ;i++)              //初始化数组A【】   
	{
		scanf("%d",&A[i]);	
	}
	for(i = 1;i < n;i++)              //插入排序主程序  
	{
		key = A[i];              //将A【i】插入到A【0】——A【i】中
		j = i - 1;               
		while(j >= 0 && A[j] > key )
		{
			A[j+1] = A[j];
			j--;		
		}
		A[j+1] = key;
	}
	for(i =0;i < n;i++)              //输出排好序的数组
	{
		printf("%d	",A[i]);
	}
	printf("\n");
}
