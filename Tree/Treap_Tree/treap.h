#ifndef _TREAP_TREE_H
#define _TREAP_TREE_H

typedef int Type;

struct treapNode;

typedef struct treapNode *treapTree;
typedef struct treapNode *Position;

struct treapNode
{
	Type value;
	int fix;
	int size;
	int cnt;
	Position Left;
	Position Right;
};

void Preorder(treapTree T);

void Inorder(treapTree T);

void DestroyTree(treapTree T);

void PrintTree(treapTree T, Type Key, int direction);

treapTree Insert(treapTree T, Type X);

treapTree Delete(treapTree T, Type X);

Position FindX(treapTree T, Type X);

Position FindMin(treapTree T);

Position FindMax(treapTree T);

Position Predecessor(treapTree T, Position y, Type X);

Position Successor(treapTree T, Position y, Type X);

Position FindKth(treapTree T, int k);

int LessX(treapTree T, Type X, int cur);

#endif

