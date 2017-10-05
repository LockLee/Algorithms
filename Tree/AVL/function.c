/*
 *NAME:AVL TREE FUNCTION
 *TIME:2016.10.16
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void Preorder(AvlTree T)
{
	if(T)
	{
		printf("%d	",T->Value);
		Preorder(T->Left);
		Preorder(T->Right);
	}
}

void Inorder(AvlTree T)
{
        if(T)
        {
                Inorder(T->Left);
                printf("%d      ",T->Value);
                Inorder(T->Right);
        }

}

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

Position Find(int X,AvlTree T)
{
	if(!T || X == T->Value)
		return T;
	else if(X < T->Value)
		return Find(X,T->Left);
	else
		return Find(X,T->Right);
}

Position FindMin(AvlTree T)
{
	if(!T || !T->Left)
		return T;
	else 
		return FindMin(T->Left);		
}

Position FindMax(AvlTree T)
{
	if(!T || !T->Right)
		return T;
	else
		return FindMax(T->Right);
}
