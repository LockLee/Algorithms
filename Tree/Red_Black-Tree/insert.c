/*
 *NAME:RED_BLACK TREE(INSERT FUNCTION)
 *TIME:2016.10.22
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

/*
#define RED   0
#define BLACK 1

typedef int Type;

struct RBTreeNode;
typedef struct RBTreeNode Node;
typedef struct RBTreeNode *Position;
typedef struct RBTreeNode *RBTree;

struct RBRootNode;
typedef struct RBRootNode RBNode;
typedef struct RBRootNode *RBRoot;

RBRoot Insert(Type ,RBRoot );

struct RBTreeNode{
        Type Value;
        bool Color;
        Position Parent;
        Position Left;
        Position Right;
};

struct RBRootNode{
        RBTree node;
};
*/

static void LeftRotation(RBRoot root,Position x)
{
	Position y;
	
	y = x->Right;
	x->Right = y->Left;
	if(y->Left != NULL)
		y->Left->Parent = x;
	y->Parent = x->Parent;
	if(x->Parent == NULL)
		root->node = y;
	else if(x == x->Parent->Left)
		x->Parent->Left = y;
	else
		x->Parent->Right = y;
	y->Left = x;
	x->Parent = y;
}

static void RightRotation(RBRoot root,Position x)
{
	Position y;
	
	y = x->Left;
	x->Left = y->Right;
	if(y->Right != NULL)
		y->Right->Parent = x;
	y->Parent = x->Parent;
	if(x->Parent == NULL)
		root->node = y;
	else if(x == x->Parent->Left)
		x->Parent->Left = y;
	else
		x->Parent->Right = y;
	y->Right = x;
	x->Parent = y;
}

static void RBInsertFixup(RBRoot root,Position z)
{
	Position uncle, parent, gparent;

	while((parent = z->Parent) && parent->Color == RED)
	{
		gparent = z->Parent->Parent;		

		if(parent == gparent->Left)				//gparent must be exist
		{
			uncle = gparent->Right;
			if(uncle && uncle->Color == RED)
			{
				parent->Color = BLACK;
				uncle->Color = BLACK;
				gparent->Color = RED;
				z = gparent;
			}
			else 
			{
				if(z == z->Parent->Right)		//if uncle is NULL,then uncle is black,if uncle not NULL,then is black
				{
					z = z->Parent;
					LeftRotation(root,z);
				}
				z->Parent->Color = BLACK;		//new z'parent 
				gparent->Color = RED;			//gparent not change
				RightRotation(root,gparent);
		 	}
		}
		else							//same as up with "right" and "left" exchanged
		{
			uncle = gparent->Left;
			if(uncle && uncle->Color == RED)
			{
				parent->Color = BLACK;
				uncle->Color = BLACK;
				gparent->Color = RED;
				z = gparent;
			}
			else
			{
				if(z == z->Parent->Left )
				{
					z = z->Parent;
					RightRotation(root,z);
				}
				z->Parent->Color = BLACK;
				gparent->Color = RED;
				LeftRotation(root,gparent);
			}
		}
	}

	root->node->Color = BLACK;

}


RBRoot Insert(Type X,RBRoot root)
{
	Position x,y,z;
	y = NULL;
	x = root->node;

	z = (Position)malloc(sizeof(Node));
	if(z == NULL)
	{
		printf("ERROR!");
		exit(1);
	}
	z->Value = X;
	z->Left = NULL;
	z->Right = NULL;
	z->Color = RED;

	while(x != NULL)
	{
		y = x;
		if(z->Value < x->Value)
			x = x->Left;
		else
			x = x->Right;		
	}	
	
	z->Parent = y;
	
	if(y == NULL)
		root->node = z;
	else if(z->Value < y->Value)
		y->Left = z;
	else
		y->Right = z;

	RBInsertFixup(root,z);	

	return root;
}

