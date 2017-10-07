#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

typedef int Type;

struct splayNode;

typedef struct splayNode *splayTree;
typedef struct splayNode *Position;

struct splayNode
{
	Type Value;
	Position Left;
	Position Right;
};


void Preorder(splayTree T);

void Inorder(splayTree T);

splayTree Splay(Type X, Position P);

splayTree DestroyTree(splayTree T);

Position Find(Type X, splayTree T);

Position FindMin(splayTree T);

Position FindMax(splayTree T);

splayTree Initialize(void );

splayTree Insert(Type X, splayTree T);

splayTree Delete(Type X, splayTree T);

void PrintSplay(splayTree tree, Type Value, int direction);

#endif

