#include <stdio.h>
#include <stdlib.h>
#include "leftistheap.h"

/*
 *
 */
void PreorderLeftist(Leftist H)
{
	if(H != NULL)
	{
		printf("%d	",H->value);
		PreorderLeftist(H->left);
		PreorderLeftist(H->right);
	}
}

/*
 *
 */
void InorderLeftist(Leftist H)
{
	if(H != NULL)
	{
		InorderLeftist(H->left);
		printf("%d	",H->value);
		InorderLeftist(H->right);
	}
}

/*
 *
 */
void PostorderLeftist(Leftist H)
{
	if(H != NULL)
	{
		PostorderLeftist(H->left);
		PostorderLeftist(H->right);
		printf("%d	",H->value);
	}
}

/*
 *
 */
static void SwapNode(Leftist *L, Leftist *R)
{
	Leftist tmp;
	
	tmp = *L;
	*L = *R;
	*R = tmp;
}

/*
 *
 */
Elemtype GetMin(Leftist H)
{
	if(H == NULL)
	{
		printf("The Leftist Heap Is Empty.\n");
		return -1;
	}
	else
		return H->value;
}

/*
 *
 *
 *
 */
static Leftist Merge1(Leftist H1, Leftist H2)
{
	//
        if(H1->left == NULL)
                H1->left = H2;
        else
        {
		//
                H1->right = MergeLeftist(H1->right, H2);
		//
                if(H1->left->npl < H1->right->npl)
			//
                        SwapNode(&(H1->left), &(H1->right));

		//
                H1->npl = H1->right->npl + 1;
        }

        return H1;
}


/*
 *
 *
 *
 */
Leftist MergeLeftist(Leftist H1, Leftist H2)
{
	if(H1 == NULL)
		return H2;
	if(H2 == NULL)
		return H1;
	//
	if(H1->value < H2->value)
		return Merge1(H1, H2);
	else
		return Merge1(H2, H1);
}

/*
 *
 *
 *
 *
 *
 */
Leftist InsertLeftist(Elemtype X, Leftist H)
{
	Leftist pnode;
	pnode = (LNode *)malloc(sizeof(LNode));
	if(pnode == NULL)
		return H;
	
	pnode->value = X;
	pnode->npl = 0;
	pnode->left = pnode->right = NULL;
	
	return MergeLeftist(H, pnode);
}

/*
 *
 *
 *
 *
 */
Leftist DeleteMin(Leftist H)
{
	Leftist L,R;	

	if(H == NULL)
		return NULL;

	L = H->left;
	R = H->right;
	//
	free(H);
	
	//
	return MergeLeftist(L, R);
}

/*
 *
 *
 */
void DestroyLeftist(Leftist H)
{
	if(H == NULL)
		return;
	
	if(H->left != NULL)
		DestroyLeftist(H->left);
	if(H->right != NULL)
		DestroyLeftist(H->right);

	free(H);
}

/*
 *
 *
 *
 */
static void Leftist_Print(Leftist H, Elemtype value, int direction)
{
	if(H != NULL)
	{
		if(direction == 0)
			printf("%2d(%d) is root.\n",H->value,H->npl);
		else
			printf("%2d(%d) is %2d's %6s child.\n",H->value,H->npl,value,direction==1?"right" : "left");
	
		Leftist_Print(H->left, H->value, -1);
		Leftist_Print(H->right, H->value, 1);
	}
}

void PrintLeftist(Leftist H)
{
	if(H != NULL)
		Leftist_Print(H, H->value, 0);
}
