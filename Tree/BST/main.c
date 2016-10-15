#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
        SearchTree T;
        int i, n;
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

        return 0;
}

