/*
 *NAME:AVL TREE INSERT FUNCTION
 *TIME:2016.10.16
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*
 *Max函数求a,b的最大值
 */
static int Max(int a,int b)						
{
	return (a > b) ? a :b;
}

/*
 *求节点的高
 *
 *参数 P：节点地址
 * 
 *如果P非空则返回节点的高，否则返回-1
 */
static int Height(Position P)						
{
	if( P == NULL)
		return -1;
	else
		return P->Height;
}

/*
 *右单旋转，也就是在左子树的左子树中插入新节点
 *
 *参数 K2：不满足AVL平衡特性的节点地址
 *
 *返回旋转后的AVL树节点地址
 */
static Position SingleRotateWithRight(Position K2)			
{
	Position K1;

	//旋转节点，使满足AVL平衡特性
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	//更新旋转节点的高
	K2->Height = Max( Height(K2->Left) , Height(K2->Right) ) + 1;	
	K1->Height = Max( Height(K1->Left) , K2->Height ) + 1;
	
	return K1;
}

/*
 *左单旋转，也就是在右子树的右子树中插入新节点
 *
 *参数 K2：不满足AVL平衡特性的节点地址
 *
 *返回旋转后的AVL树节点地址
 */
static Position SingleRotateWithLeft(Position K2)
{
	Position K1;
	
	//旋转节点，是满足AVL平衡特性
	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	//更新旋转节点高度
	K2->Height = Max( Height(K2->Left) , Height(K2->Right) ) + 1;
	K1->Height = Max( Height(K1->Right) , K2->Height ) + 1;

	return K1;
}

/*
 *左右双旋转，也就是在左子树的右子树中插入新节点
 *
 *参数 K3：不满足AVL平衡特性的节点地址
 *
 *返回旋转后的AVL树节点地址
 */
static Position DoubleRotateLeftAndRight( Position K3)			
{
	K3->Left = SingleRotateWithLeft( K3->Left );
	return SingleRotateWithRight( K3 );
}

/*
 *右左双旋转，也就是在右子树的左子树中插入新节点
 *
 *参数 K3：不满足AVL平衡特性的节点地址
 *
 *返回旋转后的AVL树节点地址
 */
static Position DoubleRotateRightAndLeft( Position K3)
{
	K3->Right = SingleRotateWithRight( K3->Right);
	return SingleRotateWithLeft( K3 );
}

/*
 *在AVL树T中插入元素X
 *
 *参数 X：待插入元素值
 *     T：AVL树地址
 *
 *返回新AVL树地址
 */
AvlTree Insert (int X,AvlTree T)					
{	
	//如果该树为空，构建新节点
	if( !T )							
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
	//否则该树不为空并且X小于T->value,在左子树中递归插入
	else if(X < T->Value)						
	{
		T->Left = Insert(X ,T->Left);
		//如果左子树高度减右子树高度等于2，进行旋转操作
		if(Height(T->Left) - Height(T->Right) == 2)	
			//如果在左子树的左子树中插入，执行单旋转
			if(X < T->Left->Value)				
				T = SingleRotateWithRight( T );
			//否则则是在左子树的右子树中插入，执行双旋转
			else						
				T = DoubleRotateLeftAndRight( T );

	}
	//否则该树不为空并且X大于T->value,在右子树中递归插入
	else if(X > T->Value)				
	{
		T->Right = Insert(X , T->Right);
		//如果右子树高度减左子树高度等于2，进行旋转操作
		if(Height(T->Right) - Height(T->Left) == 2)
			//如果在右子树的右子树中插入，执行单旋转
			if(X > T->Right->Value)
				T = SingleRotateWithLeft( T );
			//否则则是在右子树的左子树中插入，执行双旋转
			else
				T = DoubleRotateRightAndLeft( T );
	}
	
	//更新节点高度
	if(T != NULL)
		T->Height = Max( Height(T->Left), Height(T->Right) ) + 1;	
	
	//返回新的根节点
	return T;							
}

