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
	pStack pS = InitStack();
	
	//如果左子树非空将左子树入栈，否则出栈打印结果
	//然后将指针转移到右子树
	while(pT || !IsEmpty(pS))
	{	
		if(pT)
		{
			Push(pT, pS);
			pT = pT->Left;
		}
		else
		{
			pTmp = Pop(pS);			
			printf("%d	",pTmp->value）；
			pT = pTmp->Right;			
		}
	}
}

/*
 *销毁树
 *
 *参数 T：二叉搜索树指针
 */
void DestroyTree(SearchTree T)			
{

	//如果树不空，递归销毁左子树，右子树
	if(T)					
	{
		DestroyTree(T->Left);
		DestroyTree(T->Right);
		free(T);
	}
}
			       
/*
 *在二叉搜索树T中递归查找值X
 *
 *参数 X：待查找元素值
 *     T：二叉搜索树
 *
 *如果查找成功则返回元素指针，否则返回NULL
 */
Position Find(int X,SearchTree T)				
{
	//如果T为NULL或者X == T->value,直接返回T
	if(!T || X == T->value)					
		return T;
	//否则如果X < T->value,递归查找左子树
	if(X < T->value)					
		return Find(X,T->Left);
	//否则递归查找右子树
	else 							
		return Find(X,T->Right);
}

/*
 *在二叉搜索树T中非递归查找值X
 *
 *参数 X：待查找元素值
 *     T：二叉搜索树
 *
 *如果查找成功则返回元素指针，否则返回NULL
 */
Position Iterative_Find(int X, SearchTree T)	
{
	//迭代寻找值X
	while(T && X != T->value)			
	{
		if(X < T->value)
			T = T->Left;
		else
			T = T->Right;
	}
	return T;		
}

/*
 *在二叉搜索树T中递归查找最小值
 *
 *参数 T：二叉搜索树
 *
 *如果查找成功则返回最小值元素指针，否则返回NULL
 */
Position FindMin(SearchTree T)					
{
	//如果T为空说明该树为空，返回NULL；或者T的左子树为空说明T就是最小元素
	if(!T || !T->Left)					
		return T;
	else 
		//否则递归查找左子树
		return FindMin(T->Left);			
}

/*
 *在二叉搜索树T中非递归查找最小值
 *
 *参数 T：二叉搜索树
 *
 *如果查找成功则返回最小值元素指针，否则返回NULL
 */
Position Iterative_FindMin(int X,SearchTree T)		
{
	//迭代循环寻找该树的最左节点
	while(T && T->Left)	
		T = T->Left;
	return T;
}

/*
 *在二叉搜索树T中递归查找最大值
 *
 *参数 T：二叉搜索树
 *
 *如果查找成功则返回最大值元素指针，否则返回NULL
 */
Position FindMax(SearchTree T)				
{
	if(!T || !T->Right)
		return T;
	else
		return FindMax(T->Right);
}

/*
 *在二叉搜索树T中非递归查找最大值
 *
 *参数 T：二叉搜索树
 *
 *如果查找成功则返回最大值元素指针，否则返回NULL
 */
Position Iterative_FindMax(SearchTree T)			
{
	while(T && T->Right)
		T = T->Right;
	return T;
}

/*
 *在二叉搜索树T中递归插入值X
 *
 *参数 X：待插入元素值
 *     T：二叉搜索树
 *
 *返回二叉搜索树
 */
SearchTree Insert(int X,SearchTree T)				
{
	//如果该树为空，则创建新节点，返回新节点
	if(!T)							
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
	//否则如果X < T->value,在左子树中递归插入
	else if(X < T->value)					
		T->Left = Insert(X,T->Left);
	//在右子树中递归插入
	else if(X > T->value)					
		T->Right = Insert(X,T->Right);	
	//在递归中返回插入节点的位置，最后返回该树
	//这一行很重要，不能漏写
	return T;						
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
