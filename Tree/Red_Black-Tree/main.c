/*
 *NAME:RED_BLACK TREE(MAIN FUNCTION)
 *TIME:2016.10.27
 *AUTHOR:LS
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
 
#define CHECK_INSERT 1    //switch

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

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
RBRoot Delete(Type ,RBRoot );
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
 
static void rbtree_print(Position tree, Type key, int direction)
{
	if(tree != NULL)
	{
		if(direction == 0)
			printf("%2d(B) is root\n",tree->Value);
		else
			printf("%2d(%s) is %2d's %6s child\n", tree->Value, (tree->Color == RED) ? "R" : "B", key, direction == 1 ? "Right" : "Left");
		rbtree_print(tree->Left, tree->Value, -1);
		rbtree_print(tree->Right, tree->Value, 1);
	}
}

void print_rbtree(RBRoot root)
{
	if(root != NULL && root->node != NULL)
		rbtree_print(root->node, root->node->Value, 0);
}


int main()
{

     	int a[] = {41,38,31,12,19,8};
     	int i, ilen=LENGTH(a);
     	RBRoot root=NULL;
 
     	root = CreateTree();
	printf("== Original Data: ");
     	for(i=0; i<ilen; i++)
         	printf("%d	", a[i]);
     	printf("\n");
 
     	for(i=0; i<ilen; i++)
     	{
         	root = Insert(a[i], root );

 
#if CHECK_INSERT
         	printf("== Add Node: %d\n", a[i]);
         	printf("== Tree's Details: \n");
         	print_rbtree(root);
         	printf("\n");
 #endif
  
   	}	
 
     	printf("== Inorder: ");
     	Inorder(root->node);
 
     	printf("\n");
 
     	printf("== Tree's Details: \n");
     	print_rbtree(root);
     	printf("\n");

	Delete(38, root);
	
	print_rbtree(root);
	printf("\n");

	Delete(19, root);

	print_rbtree(root);
	printf("\n");

	Delete(41, root);
	print_rbtree(root);
	printf("\n");

	return 0;
}
