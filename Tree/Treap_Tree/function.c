#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "treap.h"

static int randNum()
{
	int num;
//	srand((unsigned)time(NULL));
	num = rand();

	return num;
}

static Position InitNode(Type e)
{
	Position P = NULL;

	P = (Position )malloc(sizeof(struct treapNode));
	if(P == NULL)
	{
		printf("Malloc A Node Out Space!");
		exit(1);
	}
	
	P->value = e;
	P->fix = randNum();
	P->size = 1;
	P->cnt = 1;
	P->Left = NULL;
	P->Right = NULL;	

	return P;
}

static Position RightRotation(Position x)
{
	Position y = NULL;
	
	y = x->Left;
	x->Left = y->Right;
	y->Right = x;
	
	x = y;
	
	y = x->Right;
	if(y != NULL)
	{
		y->size = y->cnt;
		if(y->Left != NULL)
			y->size = y->size + y->Left->size;
		if(y->Right != NULL)
			y->size = y->size + y->Right->size;
	}

	x->size = x->cnt;
	if(x->Left != NULL)
		x->size = x->size + x->Left->size;
        if(x->Right != NULL)
		x->size = x->size + x->Right->size;
	
	return x;
}

static Position LeftRotation(Position x)
{
	Position y = NULL;
	
	y = x->Right;
	x->Right = y->Left;
	y->Left = x;
	
	x = y;
	
	y = x->Left;
	if(y != NULL)
	{
		y->size = y->cnt;
		if(y->Left != NULL)
			y->size = y->size + y->Left->size;
		if(y->Right != NULL)
			y->size =y->size + y->Right->size;
	}
	
	x->size = x->cnt;
	if(x->Left != NULL)
		x->size = x->size + x->Left->size;
	if(x->Right != NULL)
		x->size = x->size + x->Right->size;

	return x;
}

void Preorder(treapTree T)
{
	if(T)
	{
		printf("%d	",T->value);
		Preorder(T->Left);
		Preorder(T->Right);
	}
}

void Inorder(treapTree T)
{
        if(T)
        {
                Inorder(T->Left);
                printf("%d      ",T->value);
                Inorder(T->Right);
        }
}

void DestroyTree(treapTree T)
{
	if(T)
	{
		DestroyTree(T->Left);
		DestroyTree(T->Right);
		free(T);
	}
}

Position FindX(treapTree T, Type X)
{
	while(T && X != T->value)
	{
		if(X < T->value)
			T = T->Left;
		else
			T = T->Right;
	}
	return T;
}

Position FindMin(treapTree T)
{
	while(T && T->Left)
		T = T->Left;
	
	return T;
}

Position FindMax(treapTree T)
{
	while(T && T->Right)
		T = T->Right;
	
	return T;
}

void PrintTree(treapTree T, Type Key, int direction)
{
	if(T != NULL)
	{
		if(direction == 0)
			printf("%3d is root.fix is %3d.size is %3d.count is %3d\n", T->value, T->fix, T->size, T->cnt);
		else
			printf("%3d is %3d's %6s child.fix is %3d.size is %3d.count is %3d\n", T->value, Key, direction==1?"right" : "left", T->fix, T->size, T->cnt);
	
		PrintTree(T->Left, T->value, -1);
		PrintTree(T->Right, T->value, 1);
	}
}

treapTree Insert(treapTree T, Type X)
{
	if(T == NULL)
	{
		T = InitNode(X);
		if( T == NULL)
	        {
        	        printf("Malloc A Node Out Space!");
                	exit(1);
        	}
	
	}
	else if(X < T->value)
	{
		T->size++;
		T->Left = Insert(T->Left, X);
		if(T->Left->fix < T->fix)
			T = RightRotation(T);
	}
	else if(X > T->value)
	{
		T->size++;
		T->Right = Insert(T->Right, X);
		if(T->Right->fix < T->fix)
			T = LeftRotation(T);
	}
	else
	{
		T->size++;
		T->cnt++;
	}

	return T;
}


treapTree Delete(treapTree T, Type X)
{
	Position Tmp = NULL;
	int count;

	if(T == NULL)
		return NULL;
	else if(X < T->value)
	{
		T->size--;
		T->Left = Delete(T->Left, X);
	}
	else if(X > T->value)
	{
		T->size--;
		T->Right = Delete(T->Right, X); 
	}
	else
	{
		//T->size--;
		count = T->cnt-1;
		if(count <= 0)
		{
			if(T->Left != NULL && T->Right != NULL)
			{
				if(T->Left->fix < T->Right->fix)
				{
					T = RightRotation(T);
					T->size--;
					T->Right = Delete(T->Right, X);
				}	
				else
				{
					T = LeftRotation(T);
					T->size--;
					T->Left = Delete(T->Left, X);
				}		
			}
                        else if(T->Left != NULL)
                        {
                                Tmp = T;
                                T = T->Left;
                                free(Tmp);
                        }
                        else if(T->Right != NULL)
                        {
                                Tmp = T;
                                T = T->Right;
                                free(Tmp);
                        }
                        else
                        {
                                Tmp = T;
                                T = NULL;
                                free(Tmp);
                        }
		}
		else
		{
			T->size--;
			T->cnt--;
		}
	}

	return T;
}

Position FindKth(treapTree T, int k)
{
	int leftsize = 0;
	
	if(T->Left != NULL)
		leftsize = T->Left->size;	

	if(k < (leftsize + 1))
		return FindKth(T->Left, k);
	else if(k > (leftsize + T->cnt))
		return FindKth(T->Right, k - ((T->Left ? T->Left->size : 0) + T->cnt));
	else 
		return T;
}

int LessX(treapTree T, Type X, int cur)
{	
	if(T == NULL)
		return cur + 0;
	if(T->value == X)
		return cur + (T->Left ? T->Left->size : 0);
	else if(X < T->value)
		return LessX(T->Left, X, cur);
	else 
	{
		cur += (T->Left ? T->Left->size : 0) + T->cnt;
		return LessX(T->Right, X, cur);
	}
}
