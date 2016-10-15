#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*
struct AVLNode;
typedef struct AVLNode Node;
typedef struct AVLNode *Position;
typedef struct AVLNode *AvlTree;

void Inorder(AvlTree );
AvlTree MakeEmpty (AvlTree );
Position Find(int ,AvlTree );
Position FindMin(AvlTree );
Position FindMax(AvlTree );
AvlTree Insert(int ,AvlTree );
AvlTree Delete(int ,AvlTree);

struct AVLNode
{
        int Value;
        AvlTree Left;
        Avltree Right;
        int Height;
};
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

AvlTree MakeEmpty (AvlTree T)
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
