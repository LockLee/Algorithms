#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "splay.h"

static Position NullNode = NULL;

Position Initialize(void )
{
	if(NullNode == NULL)
	{
		NullNode = (Position )malloc(sizeof(struct splayNode));
		if(NullNode == NULL)
		{
			printf("The Space Out!");
			exit(1);
		}
		
		NullNode->Left = NullNode->Right = NullNode;
	}
	
	return NullNode;
}

void Preorder(splayTree T)
{
	if((T != NULL) && (T != NullNode))
	{
		printf("%d	",T->Value);
		Preorder(T->Left);
		Preorder(T->Right);
	}
}

void Inorder(splayTree T)
{
	if((T != NULL) && (T != NullNode))
	{
		Inorder(T->Left);
		printf("%d	",T->Value);
		Inorder(T->Right);
	}
}

splayTree DestroyTree(splayTree T)
{
	if((T != NULL) && (T != NullNode))
	{
		DestroyTree(T->Left);
		DestroyTree(T->Right);
		free(T);
	}

	return NullNode;
}

Position Find(Type X, splayTree T)
{
	if(T == NULL)
		return NULL;
	else 
		return Splay(X, T);
}

Position FindMin(splayTree T)
{
	if(T == NULL)
		return NULL;
	else 
		return Splay(INT_MIN, T);
}

Position FindMax(splayTree T)
{
        if(T == NULL)
                return NULL;

        else
		return Splay(INT_MAX, T);
}

static Position SingleRotateWithRight(Position K2)
{
	Position K1;
	
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	return K1;
}

static Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	
	return K1;
}

splayTree Splay(Type X, Position P)
{
	static struct splayNode header;
	Position leftMax, rightMin;
	
	//NullNode = Initialize();

	header.Left = header.Right = NullNode;
	leftMax = rightMin = &header;

	NullNode->Value = X;

	while(X != P->Value)
	{
		if(X < P->Value)
		{
			if(X < P->Left->Value)
				P = SingleRotateWithRight( P );		
			if(P->Left == NullNode)
				break;
	
			rightMin->Left = P;
			rightMin = P;
			P = P->Left;
		}
		else
		{
			if(X > P->Right->Value)
				P = SingleRotateWithLeft( P );
			if(P->Right == NullNode)
				break;
			
			leftMax->Right = P;
			leftMax = P;
			P = P->Right; 
		}
	}
	
	leftMax->Right = P->Left;
	rightMin->Left = P->Right;
	P->Left = header.Right;
	P->Right = header.Left;

	return P;
}

splayTree Insert(Type X, splayTree T)
{
	static Position NewNode = NULL;
	
	if(NewNode == NULL)
	{
		NewNode = (Position )malloc(sizeof(struct splayNode));
		if(NewNode == NULL)
		{
			printf("The Space Out!");
			exit(1);
		}
	}
	NewNode->Value = X;

	if(T == NullNode)
	{
		NewNode->Left = NewNode->Right = NullNode;
		T = NewNode;
	}
	else
	{
		T = Splay(X, T);
		if(X < T->Value)
		{
			NewNode->Left = T->Left;
			NewNode->Right = T;
			T->Left = NullNode;
			T = NewNode;
		}
		else if(X > T->Value)
		{
			NewNode->Right = T->Right;
			NewNode->Left = T;
			T->Right = NullNode;
			T = NewNode;
		}
		else
			return T;
	}

	NewNode = NULL;
	
	return T;
}

splayTree Delete(Type X, splayTree T)
{
	Position NewTree;
	
	if( T != NullNode)
	{
		T = Splay(X, T);
		if(X == T->Value)
		{
			if(T->Left == NullNode)
				NewTree = T->Right;
			else
			{
				NewTree = T->Left;
				NewTree = Splay(X, NewTree);
				NewTree->Right = T->Right;
			}
	
			free(T);
			T = NewTree;
		}
	}

	return T;
}


void PrintSplay(splayTree tree, Type Value, int direction)
{
	if((tree != NULL) && (tree != NullNode))
	{
        	if(direction==0)    // tree是根节点
            		printf("%2d is root\n", tree->Value, Value);
        	else                // tree是分支节点
            		printf("%2d is %2d's %6s child\n", tree->Value, Value, direction==1?"right" : "left");

        	PrintSplay(tree->Left, tree->Value, -1);
        	PrintSplay(tree->Right,tree->Value,  1);
    }
}

