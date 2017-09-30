#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

//定义结构体节点
struct TreeNode;

typedef struct TreeNode Node;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

//二叉搜索树数据结构
struct TreeNode{
        int value;
        Position Left;
        Position Right;
};

//递归销毁二叉搜索树
SearchTree MakeEmpty(SearchTree T);

//在二叉搜索树中查找元素X
Position Find(int X, SearchTree T);

Position Iterative_Find(int X, SearchTree T);

//查找二叉搜索树的最小元素
Position FindMin(SearchTree );

Position Iterative_FindMin(SearchTree T);

//查找二叉搜索树的最大元素
Position FindMax(SearchTree );

Position Iterative_FindMax(SearchTree T);

//将元素X插入二叉搜索树中
SearchTree Insert(int X,SearchTree );

SearchTree Iterative_Insert(int X, SearchTree T);

//删除二叉搜索树的X元素
SearchTree Delete(int X,SearchTree );

SearchTree Iterative_Delete(int X, SearchTree T);

//
int Retrieve(Position );

//中序遍历二叉搜索树
void Inorder(SearchTree );

void Iterative_Inorder(SearchTree T);


#endif
