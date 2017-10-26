#ifndef _TREAP_TREE_H
#define _TREAP_TREE_H

//定义节点元素类型
typedef int Type;

struct treapNode;

typedef struct treapNode *treapTree;
typedef struct treapNode *Position;

/*
 *定义Treap结构体
 *value 表示元素值
 *fix 表示随机值
 *cnt 表示该元素值得个数
 *Left、Right 表示左右孩子节点
 */
struct treapNode
{
	Type value;
	int fix;
	int size;
	int cnt;
	Position Left;
	Position Right;
};

//前序遍历Treap
void Preorder(treapTree T);

//中序遍历Treap
void Inorder(treapTree T);

//销毁Treap
void DestroyTree(treapTree T);

//打印Treap信息
void PrintTree(treapTree T, Type Key, int direction);

//将元素X插入Treap
treapTree Insert(treapTree T, Type X);

//在Treap中删除元素值X
treapTree Delete(treapTree T, Type X);

//查找元素X
Position FindX(treapTree T, Type X);

//查找最小值
Position FindMin(treapTree T);

//查找最大值
Position FindMax(treapTree T);

//在位置 y 处查找元素 X 的前驱节点
Position Predecessor(treapTree T, Position y, Type X);

//在位置 y 处查找元素 X 的后继节点
Position Successor(treapTree T, Position y, Type X);

//在Treap树中查找第 k 个元素并返回
Position FindKth(treapTree T, int k);

//返回Treap树小于元素值 X 的元素个数
int LessX(treapTree T, Type X, int cur);

#endif

