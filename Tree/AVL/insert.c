#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

static int Max(int a,int b)
{
	return (a > b) ? a :b;
}

static int Height(Position P)
{
	if( P == NULL)
		return -1;
	else
		return P->Height;
}

static Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max( Height(K2->Left) , Height(K2->Right) ) + 1;
	K1->Height = Max( Height(K1->Left) , K2->Height ) + 1;
	
	return K1;
}

static Position SingleRotateWithRight(Position K2)
{
	Position K1;
	
	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K2->Height = Max( Height(K2->Left) , Height(K2->Right) ) + 1;
	K1->Height = Max( Height(K1->Right) , K2->Height ) + 1;

	return K1;
}

static Position DoubleRotateLeftAndRight( Position K3)
{
	K3->Left = SingleRotateWithRight( K3->Left );
	return SingleRotateWithLeft( K3 );
}
static Position DoubleRotateRightAndLeft( Position K3)
{
	K3->Right = SingleRotateWithLeft( K3->Right);
	return SingleRotateWithRight( K3 );
}

AvlTree Insert (int X,AvlTree T)
{
	if( !T )
	{
		T = (Position)malloc(sizeof(Node));
		if(!T)
		{
			printf("ERROR!");
			exit(1);
		}
		else
		{
			T->Value = X;
			T->Left = T->Right = NULL;
			T->Height = 0;
		}
	}
	else if(X < T->Value)
	{
		T->Left = Insert(X ,T->Left);
		if(Height(T->Left) - Height(T->Right) == 2)
			if(X < T->Left->Value)
				T = SingleRotateWithLeft( T );
			else
				T = DoubleRotateLeftAndRight( T );

	}
	else if(X > T->Value)
	{
		T->Right = Insert(X , T->Right);
		if(Height(T->Right) - Height(T->Left) == 2)
			if(X > T->Right->Value)
				T = SingleRotateWithRight( T );
			else
				T = DoubleRotateRightAndLeft( T );
	}
	
	T->Height = Max( Height(T->Left), Height(T->Right) ) + 1;
	
	return T;
}

