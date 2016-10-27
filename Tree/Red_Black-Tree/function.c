/*
 *NAME:RED_BLACK TREE(FUNCTION)
 *TIME:2016.10.27
 *AUTHOR:LS
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

/*

typedef int Type;

struct RBTreeNode;
typedef struct RBTreeNode Node;
typedef struct RBTreeNode *Position;
typedef struct RBTreeNode *RBTree;

struct RBRootNode;
typedef struct RBRootNode RBNode;
typedef struct RBRootNode *RBRoot;

RBRoot CreateTree();
void MakeEmpty(RBTree );
void DestoryTree(RBRoot );
Position Find(Type ,RBTree );
Position FindMin(RBTree );
Position FindMax(RBTree );
RBRoot Insert(Type ,RBRoot );
RBRoot Delete(Type ,RBTree );
Type Retrieve(Position );
void Inorder(RBTree );

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

RBRoot CreateTree()
{
	RBRoot root;
	root = (RBRoot)malloc(sizeof(RBNode));
	if(root == NULL)
	{
		printf("ERROR!");
		exit(1);
	}
	root->node = NULL;
	return root;
}

void Inorder(RBTree T)
{
        if(T)
        {
                Inorder(T->Left);
                printf("%d      ",T->Value);
                Inorder(T->Right);
        }
}

void MakeEmpty (RBTree T)
{
        if(T)
        {
                MakeEmpty(T->Left);
                MakeEmpty(T->Right);
                free(T);
        }
}

void DestoryTree(RBRoot root)
{
	if(root)
		MakeEmpty(root->node);
	free(root);
}

Position Find(Type X,RBTree T)
{
        if(!T || X == T->Value)
                return T;
        else if(X < T->Value)
                return Find(X,T->Left);
        else
                return Find(X,T->Right);
}

Position FindMin(RBTree T)
{
        if(!T || !T->Left)
                return T;
        else
                return FindMin(T->Left);
}

Position FindMax(RBTree T)
{
        if(!T || !T->Right)
                return T;
        else
                return FindMax(T->Right);
}

