#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

//自定义元素类型
typedef int Type;

//定义结构体
struct splayNode;

typedef struct splayNode *splayTree;
typedef struct splayNode *Position;

//伸展树数据结构
struct splayNode
{
	Type Value;
	Position Left;
	Position Right;
};

//前序遍历伸展树
void Preorder(splayTree T);

//中序遍历伸展树
void Inorder(splayTree T);

//将伸展树以元素值X展开
splayTree Splay(Type X, Position P);

//销毁伸展树
splayTree DestroyTree(splayTree T);

//在伸展树中寻找值X，并展开
Position Find(Type X, splayTree T);

//在伸展树中寻找最小值并展开
Position FindMin(splayTree T);

//在伸展树中寻找最大值并展开
Position FindMax(splayTree T);

//初始化伸展树
splayTree Initialize(void );

//将值X插入伸展树中并展开
splayTree Insert(Type X, splayTree T);

//在伸展树中删除值X
splayTree Delete(Type X, splayTree T);

//打印伸展树节点信息
void PrintSplay(splayTree tree, Type Value, int direction);

#endif
