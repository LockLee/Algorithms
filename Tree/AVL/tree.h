#ifndef _AVL_TREE_H
#define _AVL_TREE_H

//定义结构体节点
struct AVLNode;

typedef struct AVLNode Node;
typedef struct AVLNode *Position;
typedef struct AVLNode *AvlTree;

//AVL数据结构
struct AVLNode
{
	int Value;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

//前序遍历AVL树
void Preorder(AvlTree );

//中序遍历AVL树
void Inorder(AvlTree );

//销毁AVL树
void DestroyTree(AvlTree );

//在AVL树中查找
Position Find(int ,AvlTree );

//查找AVL树中的最小值
Position FindMin(AvlTree );

//查找AVL树的最大值
Position FindMax(AvlTree );

//将元素插入AVL树中
AvlTree Insert(int ,AvlTree );

//在AVL树中删除元素
AvlTree Delete(int ,AvlTree);

//打印AVL树信息
void Print_avltree(AvlTree tree, int key, int direction);




#endif
