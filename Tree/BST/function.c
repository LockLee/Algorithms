#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*

fndef _Tree_Head_
#define _Tree_Head_

struct TreeNode;
typedef struct TreeNode Node;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(int ,SearchTree );
Position FindMin(SearchTree );
Position FindMax(SearchTree );
SearchTree Insert(int ,SearchTree );
SearchTree Delete(int ,SearchTree );
int Retrieve(Position );
void Inorder(SearchTree );

struct TreeNode{
        int value;
        Position Left;
        Position Right;
};

#endif

*/

void Inorder(SearchTree T)
{
	if(T)
	{
		Inorder(T->Left);
		printf("%d	",T->value);
		Inorder(T->Right);
	}

}

SearchTree MakeEmpty(SearchTree T)
{
	if(T)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(int X,SearchTree T)
{
	if(!T || X == T->value)
		return T;
	if(X < T->value)
		return Find(X,T->Left);
	else 
		return Find(X,T->Right);
}
/*
Position Iterative_Find(int X, SearchTree T)
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
*/
Position FindMin(SearchTree T)
{
	if(!T || !T->Left)
		return T;
	else 
		return FindMin(T->Left);	
}

/*
Position Iterative_FindMin(int X,SearchTree T)
{
	while(T && T->Left)
		T = T->Left;
	return T;
}
*/

Position FindMax(SearchTree T)
{
	if(!T || !T->Right)
		return T;
	else
		return FindMax(T->Right);
}

/*
Position Iterative_FindMax(int X,SearchTree T)
{
	while(T && T->Right)
		T = T->Right;
	return T;
}
*/

SearchTree Insert(int X,SearchTree T)
{
	if(!T)
	{
		T = (Position)malloc(sizeof(Node));
		if(!T)
		{
			printf("ERROR!");
			exit(1);
		}
		else
		{
			T->value = X;
			T->Left = T->Right = NULL;
		}
	}	
	else if(X < T->value)
		T->Left = Insert(X,T->Left);
	else if(X > T->value)
		T->Right = Insert(X,T->Right);	
	return T;
}

/*
SearchTree Iterative_Insert(int X,SearchTree T)
{
	Position p,q,x;
	
	x = (Position)malloc(sizeof(Node));
	if(!x)
	{
		printf("ERROR!");
		exit(1);
	}	
	else
	{
		x->value = X;
		x-Left = T->Right = NULL;
	}

	
	p = NULL;
	q = T;
	while(q)
	{
		p = q;
		if(X < q->value)
			q = q->Left;	
		else
			q = q->Right;
	}
	if(p == NULL)
		T = x;
	else if(X < p->value)
		p->Left = x;
	else 
		p->Right = x;

	return T;
}
*/


SearchTree Delete(int X,SearchTree T)
{
	Position TmpCell;
	if(!T)
	{
		printf("The Tree is NULL!");
		exit(1);
	}
	else if(X < T->value )
		T->Left = Delete(X,T->Left);
	else if(X > T->value )
		T->Right = Delete(X,T->Right);
	else if(T->Left && T->Right)
	{
		TmpCell = FindMin(T->Right);
		T->value = TmpCell->value;
		T->Right = Delete(T->value,T->Right);
	}
	else
	{
		TmpCell = T;
		if(T->Left == NULL)
			T = T->Right;
		else if(T->Right == NULL)
			T = T->Left;		
		free(TmpCell);  
	}
	return T;
}


