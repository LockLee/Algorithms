/*
 *NAME:RED_BLACK TREE(TREE.H)
 *TIME:2016.10.20
 *AUTHOR:LS
 */


#ifndef _Red_Black_Head_
#define _Red_Black_Head_

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

#endif
