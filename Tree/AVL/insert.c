/*
 *NAME:AVL TREE INSERT FUNCTION
 *TIME:2016.10.16
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

static int Max(int a,int b)						//Max函数求a,b的最大值
{
	return (a > b) ? a :b;
}

static int Height(Position P)						//求节点的高
{
	if( P == NULL)
		return -1;
	else
		return P->Height;
}

static Position SingleRotateWithLeft(Position K2)			//左单旋转，也就是在左子树的左子树中插入新节点
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max( Height(K2->Left) , Height(K2->Right) ) + 1;	//更新旋转节点的高
	K1->Height = Max( Height(K1->Left) , K2->Height ) + 1;
	
	return K1;
}

static Position SingleRotateWithRight(Position K2)			//右单旋转
{
	Position K1;
	
	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K2->Height = Max( Height(K2->Left) , Height(K2->Right) ) + 1;
	K1->Height = Max( Height(K1->Right) , K2->Height ) + 1;

	return K1;
}

static Position DoubleRotateLeftAndRight( Position K3)			//左右双旋转，也就是在左子树的右子树中插入新节点
{
	K3->Left = SingleRotateWithRight( K3->Left );
	return SingleRotateWithLeft( K3 );
}

static Position DoubleRotateRightAndLeft( Position K3)			//右左双旋转
{
	K3->Right = SingleRotateWithLeft( K3->Right);
	return SingleRotateWithRight( K3 );
}

AvlTree Insert (int X,AvlTree T)					//插入新节点
{	
	if( !T )							//如果该树为空，构建新节点
	{
		T = (Position)malloc(sizeof(Node));
		if(!T)
		{
			printf("ERROR!");
			exit(1);
		}
		else
		{
			T->Value = X;
			T->Left = T->Right = NULL;
			T->Height = 0;
		}
	}
	else if(X < T->Value)						//否则如果X小于T->value,在左子树中递归插入
	{
		T->Left = Insert(X ,T->Left);
		if(Height(T->Left) - Height(T->Right) == 2)		//如果左子树高度减右子树高度等于2，进行旋转操作
			if(X < T->Left->Value)				//如果在左子树的左子树中插入，执行单旋转
				T = SingleRotateWithLeft( T );
			else						//否则则是在左子树的右子树中插入，执行双旋转
				T = DoubleRotateLeftAndRight( T );

	}
	else if(X > T->Value)						//类似以上
	{
		T->Right = Insert(X , T->Right);
		if(Height(T->Right) - Height(T->Left) == 2)
			if(X > T->Right->Value)
				T = SingleRotateWithRight( T );
			else
				T = DoubleRotateRightAndLeft( T );
	}
	
	T->Height = Max( Height(T->Left), Height(T->Right) ) + 1;	//更新节点高度
	
	return T;							//返回新的根节点
}

