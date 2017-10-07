/*
 *Name: Splay_Tree
 *Time: 2017.10.7
 *Author: LS
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "splay.h"

//static Position NullNode = NULL;
static int arr[]= {16,18,13,15,24,20,30,5,25,12};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
	Type i; 
	int ilen;
	splayTree root = NULL;
	
	root = Initialize();

	printf("== 依次添加: ");
	ilen = TBL_SIZE(arr);
	for(i=0; i<ilen; i++)
	{
		printf("%d ", arr[i]);
		root = Insert(arr[i], root);
	}

	printf("\n== 前序遍历: ");
	Preorder(root);

	printf("\n== 中序遍历: \n");
	Inorder(root);


	printf("== 树的详细信息: \n");
	PrintSplay(root, root->Value, 0);

	i = 12;
        printf("== Delete Root:\n");
        root = Delete(i, root);


        printf("== 树的详细信息: \n");
        PrintSplay(root, root->Value, 0);
	
	printf("Find 0:\n");
        root = Find(100, root);
        printf("== 树的详细信息: \n");
        PrintSplay(root, root->Value, 0);


	root = DestroyTree(root);	
}
