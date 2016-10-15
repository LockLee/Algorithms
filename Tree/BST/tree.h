#ifndef _Tree_Head_
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
