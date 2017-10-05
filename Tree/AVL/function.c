/*
 *NAME:AVL TREE FUNCTION
 *TIME:2016.10.16
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*
 *递归前序遍历AVL树
 *
 *参数 T：AVL树
 *
 *前序打印输出AVL树
 */
void Preorder(AvlTree T)
{
	if(T)
	{
		printf("%d	",T->Value);
		Preorder(T->Left);
		Preorder(T->Right);
	}
}

/*
 *递归中序遍历AVL树
 *
 *参数 T：AVL树
 *
 *中序打印输出AVL树
 */
void Inorder(AvlTree T)
{
        if(T)
        {
                Inorder(T->Left);
                printf("%d      ",T->Value);
                Inorder(T->Right);
        }

}

/*
 *递归销毁AVL树
 *
 *参数 T：AVL树
 *
 */
void DestroyTree(AvlTree T)
{
	if(T)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

/*
 *在AVL树中查找元素X
 *
 *参数 T：AVL树
 *
 *如果找到则返回元素X的指针，否则返回NULL
 */
Position Find(int X,AvlTree T)
{
	if(!T || X == T->Value)
		return T;
	else if(X < T->Value)
		return Find(X,T->Left);
	else
		return Find(X,T->Right);
}

/*
 *在AVL树中找到最小元素
 *
 *参数 T：AVL树
 *
 *如果AVL树非空则返回最小元素的地址，否则返回NULL
 */
Position FindMin(AvlTree T)
{
	if(!T || !T->Left)
		return T;
	else 
		return FindMin(T->Left);		
}

/*
 *在AVL树中找到最大元素
 *
 *参数 T：AVL树
 *
 *如果AVL树非空则返回最大元素的地址，否则返回NULL
 */
Position FindMax(AvlTree T)
{
	if(!T || !T->Right)
		return T;
	else
		return FindMax(T->Right);
}
