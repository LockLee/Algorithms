/*
 *NAME:AVL TREE DELETE FUNCTION
 *TIME:2016.11.02
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

static int Max(int a,int b)                                             //Max函数求a,b的最大值
{
        return (a > b) ? a :b;
}

static int Height(Position P)                                           //求节点的高
{
        if( P == NULL) 
                return -1;
        else
                return P->Height;
}

static Position SingleRotateWithLeft(Position K2)                       //左单旋转，也就是在左子树的左子树中插入新节点
{
        Position K1;

        K1 = K2->Left;
        K2->Left = K1->Right;
        K1->Right = K2;

        K2->Height = Max( Height(K2->Left) , Height(K2->Right) ) + 1;   //更新旋转节点的高
        K1->Height = Max( Height(K1->Left) , K2->Height ) + 1;

        return K1;
}

static Position SingleRotateWithRight(Position K2)                      //右单旋转
{
        Position K1;

        K1 = K2->Right;
        K2->Right = K1->Left;
        K1->Left = K2;

        K2->Height = Max( Height(K2->Left) , Height(K2->Right) ) + 1;
        K1->Height = Max( Height(K1->Right) , K2->Height ) + 1;

        return K1;
}

static Position DoubleRotateLeftAndRight( Position K3)                  //左右双旋转，也就是在左子树的右子树中插入新节点
{
        K3->Left = SingleRotateWithRight( K3->Left );
        return SingleRotateWithLeft( K3 );
}

static Position DoubleRotateRightAndLeft( Position K3)                  //右左双旋转
{
        K3->Right = SingleRotateWithLeft( K3->Right);
        return SingleRotateWithRight( K3 );
}

AvlTree Delete(int X,AvlTree T)                           //删除元素X
{
        Position TmpCell;
        if(!T)                                                  //如果树为空，直接返回
        {
                printf("The Tree is NULL!");
                exit(1);
        }
        else if(X < T->Value )                                  //如果X < T->value，在左子树中递归删除
  	{              
		T->Left = Delete(X,T->Left);
   		if(Height(T->Right) - Height(T->Left) == 2)
		{
			if(Height(T->Right->Right) > Height(T->Right->Left))
				T = SingleRotateWithRight( T );
			else
				T = DoubleRotateRightAndLeft( T );
		}
	}
	else if(X > T->Value )                                  //在右子树中递归删除
	{        
        	T->Right = Delete(X,T->Right);
		if(Height(T->Left) - Height(T->Right) == 2)
		{
			if(Height(T->Left->Left) > Height(T->Left->Right))
				T = SingleRotateWithLeft( T );
			else
				T = DoubleRotateLeftAndRight( T );
		}
       	}
	else if(T->Left && T->Right)                            //如果待删节点左，右子树都不为空，则用该节点的后继替换该节点
        {
                TmpCell = FindMin(T->Right);         
                T->Value = TmpCell->Value;                      //惰性删除
                T->Right = Delete(T->Value,T->Right);           //递归删除后继节点
                if(Height(T->Left) - Height(T->Right) == 2)	//	
                {
                        if(Height(T->Left->Left) > Height(T->Left->Right))
                                T = SingleRotateWithLeft( T );
                        else
                                T = DoubleRotateLeftAndRight( T );
                }
	}
        else                                                    //否则待删节点左子树为空或者右子树为空或者都为空
        {
                TmpCell = T;
                if(T->Left == NULL)                             //如果左子树为空或者都为空，用右子树替换该节点
		{ 
                       	T = T->Right;
	        }
		else                                            //右子树为空
		{ 
                     	T = T->Left;
		}
		
		free(TmpCell);
        }

 	if(T != NULL) 
		T->Height = Max(Height(T->Left),Height(T->Right)) + 1;

	return T;                                               //返回T
}

