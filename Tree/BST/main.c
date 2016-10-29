/*
 *NAME:BINARY SEARCH TREE OF MAIN
 *TIME:2016.10.16
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
        SearchTree T;
        int i, n,X;
        n = 0;
        printf("Please input the TreeNode numbers:");
        scanf("%d",&n);                                         //输入数组大小
        int A[n];
        printf("Please input %d TreeNodes:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }                                                       //初始化数组
        for(i = 0;i < n;i++)
        {
                T = Insert(A[i] , T);
        }

        printf("%d\n",sizeof(Node));

        Inorder(T);
	printf("\n");

	printf("Please input delete X:");
	scanf("%d",&X);
	Delete(X,T);

	Inorder(T);
	
	printf("\n");

        return 0;
}

