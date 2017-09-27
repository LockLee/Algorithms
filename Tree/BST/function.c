/*
 *NAME:BINARY SEARCH TREE FUNCTIONS
 *TIME:2016.10.16
 *AUTHOR:LS
 *UPDATE:2016.10.29
 *UPDATE:2017.9.27 ADD COMMENTS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "stackda.h"

/*
 *中序遍历二叉树递归方法
 *
 *参数 T：二叉树指针
 *
 *打印输出二叉树
 */
void Inorder(SearchTree T)
{
	if(T)
	{
		Inorder(T->Left);
		printf("%d	",T->value);
		Inorder(T->Right);
	}

}

/*
 *中序遍历非递归方法
 *
 *参数 T：二叉树指针
 *
 *打印输出二叉树
 */
void Iterative_Inorder(SearchTree T)				
{
	Position pTmp,pT = T;
	pStack pS = initStack();
	
	while(pT || !isEmpty(pS))
	{	
		if(pT)
		{
			Push(pT, pS);				//入栈
			pT = pT->Left;
		}	
		else
		{
			pTmp = Pop(pS);				//出栈
			printf("%d	",pTmp->value);
			pT = pTmp->Right;			
		}
	}
}


SearchTree MakeEmpty(SearchTree T)				//销毁树，返回NULL
{

	if(T)							//如果树不空，递归销毁左子树，右子树
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(int X,SearchTree T)				//查找元素X
{
	if(!T || X == T->value)					//如果T为NULL或者X == T->value,直接返回T
		return T;
	if(X < T->value)					//否则如果X < T->value,递归查找左子树
		return Find(X,T->Left);
	else 							//递归查找右子树
		return Find(X,T->Right);
}
/*
Position Iterative_Find(int X, SearchTree T)			//非递归方法
{
	while(T && X != T->value)				//迭代寻找T
	{
		if(X < T->value)
			T = T->Left;
		else
			T = T->Right;
	}
	return T;		
}
*/
Position FindMin(SearchTree T)					//查找T的最小元素
{
	if(!T || !T->Left)					//如果T为空说明该树为空，返回NULL；或者T的左子树为空说明T就是最小元素
		return T;
	else 
		return FindMin(T->Left);			//否则递归查找左子树
}

/*
Position Iterative_FindMin(int X,SearchTree T)			//迭代方法
{
	while(T && T->Left)					//迭代循环寻找该树的最左节点
		T = T->Left;
	return T;
}
*/

Position FindMax(SearchTree T)					//查找T的最大元素，类似
{
	if(!T || !T->Right)
		return T;
	else
		return FindMax(T->Right);
}

/*
Position Iterative_FindMax(int X,SearchTree T)			//迭代方法
{
	while(T && T->Right)
		T = T->Right;
	return T;
}
*/

SearchTree Insert(int X,SearchTree T)				//插入新元素
{
	if(!T)							//如果该树为空，则创建新节点，返回新节点
	{
		T = (Position)malloc(sizeof(Node));
		if(!T)
		{
			printf("ERROR!");
			exit(1);
		}
		else
		{
			T->value = X;
			T->Left = T->Right = NULL;
		}
	}	
	else if(X < T->value)					//否则如果X < T->value,在左子树中递归插入
		T->Left = Insert(X,T->Left);
	else if(X > T->value)					//在右子树中递归插入
		T->Right = Insert(X,T->Right);	
	return T;						//在递归中返回插入节点的位置，最后返回该树
}

/*
SearchTree Iterative_Insert(int X,SearchTree T)			//非递归方法插入节点X	
{
	Position p,q,x;
	
	x = (Position)malloc(sizeof(Node));			//创建新节点
	if(!x)
	{
		printf("ERROR!");
		exit(1);
	}	
	else
	{
		x->value = X;
		x-Left = T->Right = NULL;
	}

	
	p = NULL;		
	q = T;
	while(q)						//迭代循环查找X待插入位置，由p指向
	{
		p = q;
		if(X < q->value)
			q = q->Left;	
		else
			q = q->Right;
	}
	if(p == NULL)						//如果p == NULL ,说明该树T == NULL
		T = x;
	else if(X < p->value)					//如果X < p->value,说明X要插在p的左子树上
		p->Left = x;
	else 							//否则插在右子树上
		p->Right = x;

	return T;
}
*/


SearchTree Delete(int X,SearchTree T)				//删除元素X
{
	Position TmpCell;
	if(!T)							//如果树为空，直接返回
	{
		printf("The Tree is NULL!");
		exit(1);
	}
	else if(X < T->value )					//如果X < T->value，在左子树中递归删除
		T->Left = Delete(X,T->Left);
	else if(X > T->value )					//在右子树中递归删除
		T->Right = Delete(X,T->Right);
	else if(T->Left && T->Right)				//如果待删节点左，右子树都不为空，则用该节点的后继替换该节点
	{
		TmpCell = FindMin(T->Right);
		T->value = TmpCell->value;
		T->Right = Delete(T->value,T->Right);		//递归删除后继节点
	}
	else							//否则待删节点左子树为空或者右子树为空或者都为空
	{
		TmpCell = T;
		if(T->Left == NULL)				//如果左子树为空，用右子树替换该节点
			T = T->Right;
		else if(T->Right == NULL)			//右子树为空
			T = T->Left;		
		free(TmpCell);  
	}
	return T;						//返回T
}
/*
SearchTree Delete(int X,SearchTree T)				//迭代版删除元素X
{
	Position P,Q,Tmp;
	if(!T)							//如果该树为空，直接退出
	{
		printf("The Tree is NULL!");
		exit(1);
	}
	
	P = NULL;
	Q = T;
	while(Q && Q->value != X)				//迭代寻找待删除元素位置，由Q指向，P指向其父节点
	{
		P = Q;
		if(X < Q->value)
			Q = Q->Left;
		else
			Q = Q->Right;
	}
	
	if(Q->Left && Q->Right)					//如果待删除元素左右子树都不为空
	{
		Tmp = Q;
		P = Q;
		Q = Q->Right;
		while(Q && Q->Left)				//寻找其后继节点，由Q指向，P指向其后继节点的父节点
		{
			P = Q;
			Q = Q->Left;
		}
		Tmp->value = Q->value;				//将待删元素替换为其后继节点
		if(Q->value < P->value)				//如果后继节点在P父节点的左子树上，将Q的右子树赋给P->Left
		{
			P->Left = Q->Right;
			free(Q);				//清空Q
		}
		else						//类似
		{
			P->Right = Q->Right;
			free(Q);
		}
		
	}
	else if(Q->Left == NULL)				//如果待删节点左子树为空
	{
		if(X < P->value)
			P->Left = Q->Right;
		else
			P->Right = Q->Right;
		free(Q);
	}		
	else							//如果待删节点右子树为空
	{
		if(X < P->value)
			P->Left = Q->Left;
		else
			P->Right = Q->Left;
		free(Q);
	}

	return T;
}
*/
