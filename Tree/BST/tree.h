#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

//定义结构体节点
struct TreeNode;

typedef struct TreeNode Node;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

//递归销毁二叉搜索树
SearchTree MakeEmpty(SearchTree T);

//在二叉搜索树中查找元素X
Position Find(int X, SearchTree T);

//查找二叉搜索树的最小元素
Position FindMin(SearchTree );

//查找二叉搜索树的最大元素
Position FindMax(SearchTree );

//将元素X插入二叉搜索树中
SearchTree Insert(int X,SearchTree );

//删除二叉搜索树的X元素
SearchTree Delete(int X,SearchTree );

//
int Retrieve(Position );

//中序遍历二叉搜索树
void Inorder(SearchTree );

struct TreeNode{
	int value;
	Position Left;
	Position Right;
};

#endif
