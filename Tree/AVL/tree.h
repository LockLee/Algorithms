#ifndef _Head_Tree_
#define _Head_Tree_

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
	AvlTree Right;
	int Height;
};

#endif
