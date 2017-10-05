/*
 *NAME:AVL TREE DELETE FUNCTION
 *TIME:2016.11.02
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
static Position DoubleRotateLeftAndRight( Position K3)                  //左右双旋转，也就是在左子树的右子树中插入新节点
{
        K3->Left = SingleRotateWithLeft( K3->Left );
        return SingleRotateWithLeft( K3 );
}

/*
 *右左双旋转，也就是在右子树的左子树中插入新节点
 *
 *参数 K3：不满足AVL平衡特性的节点地址
 *
 *返回旋转后的AVL树节点地址
 */
static Position DoubleRotateRightAndLeft( Position K3)                  //右左双旋转
{
        K3->Right = SingleRotateWithRight( K3->Right);
        return SingleRotateWithRight( K3 );
}

/*
 *在AVL树中删除元素X
 *
 *参数 X：待删除元素值
 *     T：AVL树地址
 *
 *返回新的AVL树地址
 */
AvlTree Delete(int X,AvlTree T)                       
{
        Position TmpCell;
	TmpCell = NULL;
	//如果树为空，直接退出
        if(!T)                                             
        {
                printf("The Tree is NULL!");
                exit(1);
        }
	//如果X < T->value，在左子树中递归删除
        else if(X < T->Value )                                  
  	{              
		T->Left = Delete(X,T->Left);
		//如果右子树高度减左子树高度等于2，进行旋转操作
   		if(Height(T->Right) - Height(T->Left) == 2)
		{
			//如果右子树的右子树比右子树的左子树高，相当于在右子树的右子树中插入，进行左单旋转
			if(Height(T->Right->Right) > Height(T->Right->Left))
				T = SingleRotateWithLeft( T );
			//如果右子树的右子树比右子树的左子树低，相当于在右子树的左子树中插入，进行双旋转
			else
				T = DoubleRotateRightAndLeft( T );
		}
	}
	//如果X < T->value，在右子树中递归删除，类似上面情况
	else if(X > T->Value )                              
	{        
        	T->Right = Delete(X,T->Right);
		//如果左子树高度减右子树高度等于2，进行旋转操作
		if(Height(T->Left) - Height(T->Right) == 2)
		{
			if(Height(T->Left->Left) > Height(T->Left->Right))
				T = SingleRotateWithRight( T );
			else
				T = DoubleRotateLeftAndRight( T );
		}
       	}
	//如果待删节点左，右子树都不为空，则用该节点的后继替换该节点
	else if(T->Left && T->Right)                           
        {
		//寻找要删除节点的后继节点
                TmpCell = FindMin(T->Right);         
		//用后继节点替换要删除节点
                T->Value = TmpCell->Value;
		//递归删除后继节点
                T->Right = Delete(T->Value,T->Right);
		//类似上面情况
                if(Height(T->Left) - Height(T->Right) == 2)	
                {
                        if(Height(T->Left->Left) > Height(T->Left->Right))
                                T = SingleRotateWithRight( T );
                        else
                                T = DoubleRotateLeftAndRight( T );
                }
	}
	//否则待删节点左子树为空或者右子树为空或者都为空
        else                                                    
        {
                TmpCell = T;
		//如果左子树为空或者都为空，用右子树替换该节点
                if(T->Left == NULL)                            
		{ 
                       	T = T->Right;
	        }
		//右子树为空
		else                                            
		{ 
                     	T = T->Left;
		}
		
		//释放节点
		free(TmpCell);
        }

	//更新节点高度
 	if(T != NULL) 
		T->Height = Max(Height(T->Left),Height(T->Right)) + 1;

	//返回AVL树
	return T;                                             
}

