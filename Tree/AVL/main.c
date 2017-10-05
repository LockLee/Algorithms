/*
 *NAME:AVL TREE OF MAIN FUNCTION
 *TIME:2016.10.16
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )
#define HEIGHT(p)    ( (p==NULL) ? -1 : (((Node *)(p))->Height) )

void main()
{

    int i,ilen;
    AvlTree root=NULL;

    int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};


    printf("== 高度: %d\n", HEIGHT(root));
    printf("== 依次添加: ");
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++)
    {
        printf("%d ", arr[i]);
        root = Insert(arr[i], root);
    }

    printf("\n== 前序遍历: ");
    Preorder(root);

    printf("\n== 中序遍历: ");
    Inorder(root);

    printf("\n");

    printf("== 高度: %d\n", HEIGHT(root));
    printf("== 最小值: %d\n", FindMin(root)->Value);
    printf("== 最大值: %d\n", FindMax(root)->Value);
    printf("== 树的详细信息: \n");
    print_avltree(root, root->Value, 0);


    i = 8;
    printf("\n== 删除根节点: %d", i);
    root = Delete(i, root);

    printf("\n== 高度: %d", HEIGHT(root));
    printf("\n== 中序遍历: ");
    Inorder(root);
    printf("\n== 树的详细信息: \n");
    print_avltree(root, root->Value, 0);


    DestroyTree(root);
}

