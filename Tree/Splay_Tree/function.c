#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "splay.h"

//定义静态变量NullNode，只有在该文件中的函数可以使用该静态变量
static Position NullNode = NULL;

/*
 *初始化NullNode，使伸展树中所有空指针都指向NullNode
 *
 *返回NullNode地址
 */
splayTree Initialize(void )
{
	if(NullNode == NULL)
	{
		NullNode = (Position )malloc(sizeof(struct splayNode));
		if(NullNode == NULL)
		{
			printf("The Space Out!");
			exit(1);
		}
		//使NullNode左孩子右孩子都指向自己
		NullNode->Left = NullNode->Right = NullNode;
	}
	
	return NullNode;
}

/*
 *递归前序遍历伸展树
 *
 *参数 T：伸展树
 *
 *前序打印输出伸展树
 */
void Preorder(splayTree T)
{
	if((T != NULL) && (T != NullNode))
	{
		printf("%d	",T->Value);
		Preorder(T->Left);
		Preorder(T->Right);
	}
}

/*
 *递归中序遍历伸展树
 *
 *参数 T：伸展树
 *
 *中序打印输出伸展树
 */
void Inorder(splayTree T)
{
	if((T != NULL) && (T != NullNode))
	{
		Inorder(T->Left);
		printf("%d	",T->Value);
		Inorder(T->Right);
	}
}

/*
 *递归销毁伸展树
 *
 *参数 T：伸展树
 *
 *返回NullNode节点地址
 */
splayTree DestroyTree(splayTree T)
{
	if((T != NULL) && (T != NullNode))
	{
		DestroyTree(T->Left);
		DestroyTree(T->Right);
		free(T);
	}

	return NullNode;
}

/*
 *在伸展树中查找元素X，并展开
 *
 *参数 T：伸展树
 *
 *如果伸展树为空则返回NULL，
 *如果找到则返回元素X的指针，
 *如果没找到则返回X前驱节点地址
 */
Position Find(Type X, splayTree T)
{
	if(T == NullNode)
		return NULL;
	else 
		return Splay(X, T);
}

/*
 *在伸展树中查找最小元素，并展开
 *
 *参数 T：伸展树
 *
 *如果伸展树为空则返回NULL，
 *否则返回最小元素地址
 */
Position FindMin(splayTree T)
{
	if(T == NullNode)
		return NULL;
	else 
		//INT_MIN表示int类型最小值,在limits.h中定义
		return Splay(INT_MIN, T);
}

/*
 *在伸展树中查找最大元素，并展开
 *
 *参数 T：伸展树
 *
 *如果伸展树为空则返回NULL，
 *否则返回最大元素地址
 */
Position FindMax(splayTree T)
{
        if(T == NULL)
                return NULL;

        else
		//INT_MAX表示int类型最大值,在limits.h中定义
		return Splay(INT_MAX, T);
}

/*
 *右单旋转，向右旋转
 *
 *参数 K2：旋转点地址
 *
 *返回旋转后的节点地址
 */
static Position SingleRotateWithRight(Position K2)
{
	Position K1;
	
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	return K1;
}

/*
 *左单旋转，向左旋转
 *
 *参数 K2：旋转点地址
 *
 *返回旋转后的节点地址
 */
static Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	
	return K1;
}

/*
 * 
 * 
 *
 *
 *
 */
splayTree Splay(Type X, Position P)
{
	static struct splayNode header;
	Position leftMax, rightMin;
	
	//NullNode = Initialize();

	header.Left = header.Right = NullNode;
	leftMax = rightMin = &header;

	NullNode->Value = X;

	while(X != P->Value)
	{
		if(X < P->Value)
		{
			if(X < P->Left->Value)
				P = SingleRotateWithRight( P );		
			if(P->Left == NullNode)
				break;
	
			rightMin->Left = P;
			rightMin = P;
			P = P->Left;
		}
		else
		{
			if(X > P->Right->Value)
				P = SingleRotateWithLeft( P );
			if(P->Right == NullNode)
				break;
			
			leftMax->Right = P;
			leftMax = P;
			P = P->Right; 
		}
	}
	
	leftMax->Right = P->Left;
	rightMin->Left = P->Right;
	P->Left = header.Right;
	P->Right = header.Left;

	return P;
}

splayTree Insert(Type X, splayTree T)
{
	static Position NewNode = NULL;
	
	if(NewNode == NULL)
	{
		NewNode = (Position )malloc(sizeof(struct splayNode));
		if(NewNode == NULL)
		{
			printf("The Space Out!");
			exit(1);
		}
	}
	NewNode->Value = X;

	if(T == NullNode)
	{
		NewNode->Left = NewNode->Right = NullNode;
		T = NewNode;
	}
	else
	{
		T = Splay(X, T);
		if(X < T->Value)
		{
			NewNode->Left = T->Left;
			NewNode->Right = T;
			T->Left = NullNode;
			T = NewNode;
		}
		else if(X > T->Value)
		{
			NewNode->Right = T->Right;
			NewNode->Left = T;
			T->Right = NullNode;
			T = NewNode;
		}
		else
			return T;
	}

	NewNode = NULL;
	
	return T;
}

splayTree Delete(Type X, splayTree T)
{
	Position NewTree;
	
	if( T != NullNode)
	{
		T = Splay(X, T);
		if(X == T->Value)
		{
			if(T->Left == NullNode)
				NewTree = T->Right;
			else
			{
				NewTree = T->Left;
				NewTree = Splay(X, NewTree);
				NewTree->Right = T->Right;
			}
	
			free(T);
			T = NewTree;
		}
	}

	return T;
}

/*
 *打印伸展树信息
 */
void PrintSplay(splayTree tree, Type Value, int direction)
{
	if((tree != NULL) && (tree != NullNode))
	{
        	if(direction==0)    // tree是根节点
            		printf("%2d is root\n", tree->Value, Value);
        	else                // tree是分支节点
            		printf("%2d is %2d's %6s child\n", tree->Value, Value, direction==1?"right" : "left");

        	PrintSplay(tree->Left, tree->Value, -1);
        	PrintSplay(tree->Right,tree->Value,  1);
    }
}

