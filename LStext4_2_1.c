/*
 *NAME:SQUARE MATRIX MULTIPLY BY STANDARD (O(n^3))
 *TIME:2016.9.18
 *AUTHOR:LS
 */

#include<stdio.h>

int main()
{
        int i,j,k,n;
        n = 0;
        printf("Please input the array rows:");
        scanf("%d",&n);                                 //输入数组大小
        int A[n][n],B[n][n],C[n][n];
        printf("Please input %d^2 numbers of A[]:",n);
        for(i = 0;i < n;i++)
        {
		for(j = 0;j < n;j++)
                	scanf("%d",&A[i][j]);
        }                                               //初始化数组A[]
        printf("Please input %d^2 numbers of B[]:",n);
	for(i = 0;i < n;i++)
        {
                for(j = 0;j < n;j++)
                        scanf("%d",&B[i][j]);
        }                                               //初始化数组B[]	
	
	for(i = 0;i < n;i++)				//计算数组C[]
	{
		for(j = 0;j < n;j++)
		{
			C[i][j] = 0;
			for(k = 0;k < n;k++)
				C[i][j] += A[i][k] * B[k][j]; 
		}
	}
	for(i = 0;i < n;i++)
        {
                for(j = 0;j < n;j++)
                {
			printf("%d	",C[i][j]);		
		}
		printf("\n");
        }                                               //输出数组C[] 

}
 
