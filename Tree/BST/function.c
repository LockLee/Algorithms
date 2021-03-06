/*
 *NAME:BINARY SEARCH TREE FUNCTIONS
 *TIME:2016.10.16
 *AUTHOR:LS
 *UPDATE:2016.10.29
 *UPDATE:2017.9.27 ADD COMMENTS
 *UPDATE:2017.9.29 REWRITE DETELE() FUNCTION
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
Position Iterative_FindMin(SearchTree T)		
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
	//否则元素X已经在树中，我们将什么也不做
	//在递归中返回插入节点的位置，最后返回该树
	//这一行很重要，不能漏写
	return T;						
}

/*
 *在二叉搜索树T中非递归插入值X
 *
 *参数 X：待插入元素值
 *     T：二叉搜索树
 *
 *返回二叉搜索树
 */
SearchTree Iterative_Insert(int X,SearchTree T)			
{
	Position p,q,x;
	
	//创建新节点
	x = (Position)malloc(sizeof(Node));			
	if(!x)
	{
		printf("ERROR!");
		exit(1);
	}	
	else
	{
		x->value = X;
		x-Left = x->Right = NULL;
	}

	
	p = NULL;		
	q = T;
	//迭代循环查找X待插入位置，由p指向
	while(q)						
	{
		p = q;
		if(X < q->value)
			q = q->Left;	
		else
			q = q->Right;
	}
	//如果p == NULL ,说明该树T == NULL
	if(p == NULL)						
		T = x;
	//如果X < p->value,说明X要插在p的左子树上
	else if(X < p->value)					
		p->Left = x;
	//否则插在右子树上
	else 							
		p->Right = x;

	return T;
}


/*
 *在二叉搜索树T中递归删除值X
 *
 *参数 X：待删除元素值
 *     T：二叉搜索树
 *
 *返回二叉搜索树
 */
SearchTree Delete(int X,SearchTree T)				
{
	Position TmpCell;
	//如果树为空，直接退出
	if(!T)							
	{
		printf("The Tree is NULL!");
		exit(1);
	}
	//如果X < T->value，在左子树中递归删除
	else if(X < T->value )					
		T->Left = Delete(X,T->Left);
	//在右子树中递归删除
	else if(X > T->value )					
		T->Right = Delete(X,T->Right);
	//如果待删节点左，右子树都不为空，则用该节点的后继节点即右子树的最小节点替换该节点
	else if(T->Left && T->Right)				
	{
		//找到该节点的后继节点
		TmpCell = FindMin(T->Right);
		//用后继节点的值替换该节点的值
		T->value = TmpCell->value;
		//递归删除后继节点，此时T->value表示后继节点的值
		T->Right = Delete(T->value,T->Right);		
	}
	//否则待删节点左子树为空或者右子树为空或者都为空
	else							
	{
		TmpCell = T;
		//如果左子树为空，用右子树替换该节点
		if(T->Left == NULL)				
			T = T->Right;
		//右子树为空
		else if(T->Right == NULL)			
			T = T->Left;		
		free(TmpCell);  
	}
	//返回T
	return T;						
}

			       
/*
 *在二叉搜索树T中非递归删除值X
 *
 *参数 X：待删除元素值
 *     T：二叉搜索树
 *
 *返回二叉搜索树
 */			       
			       
/*
SearchTree Delete(int X,SearchTree T)				
{
	Position P,Q,Tmp;
	//如果该树为空，直接退出
	if(!T)							
	{
		printf("The Tree is NULL!");
		exit(1);
	}
	
	P = NULL;
	Q = T;
	//迭代寻找待删除元素位置，由Q指向，P指向其父节点
	while(Q && Q->value != X)				
	{
		P = Q;
		if(X < Q->value)
			Q = Q->Left;
		else
			Q = Q->Right;
	}
	
	//如果待删除元素左右子树都不为空
	if(Q->Left && Q->Right)					
	{
		Tmp = Q;
		P = Q;
		Q = Q->Right;
		
		//寻找其后继节点，由Q指向，P指向其后继节点的父节点
		while(Q && Q->Left)				
		{
			P = Q;
			Q = Q->Left;
		}
		//将待删元素替换为其后继节点
		Tmp->value = Q->value;	
		//如果后继节点在P父节点的左子树上，将Q的右子树赋给P->Left
		if(Q->value < P->value)				
		{
			P->Left = Q->Right;
			//清空Q
			free(Q);				
		}
		else						//类似
		{
			P->Right = Q->Right;
			free(Q);
		}
		
	}
	//如果待删节点左子树为空
	else if(Q->Left == NULL)				
	{
		if(X < P->value)
			P->Left = Q->Right;
		else
			P->Right = Q->Right;
		free(Q);
	}		
	//如果待删节点右子树为空
	else							
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
			       
			       
SearchTree Iterative_Delete(int X,SearchTree T)
{
        Position searchNode, parentNode;
        Position nextNode, nextParentNode;

        searchNode = T;
        parentNode = T;

	//先找到要删除节点位置
        while(searchNode->value != X)
        {
                parentNode = searchNode;
		
		//已经是叶子节点，但是还没有找到该值，表示该树中并没有要删除的节点
                if(searchNode->Left == NULL && searchNode->Right == NULL)
                {
                        printf("The Delete Function Excecute!");
                        return T;
                }

                if(X < searchNode->value)
                        searchNode = searchNode->Left;
                else if(X > searchNode->value)
                        searchNode = searchNode->Right;
                else
                        break;
        }

	//已经找到该节点，且该节点是叶子节点
        if(searchNode->Left == NULL && searchNode->Right == NULL)
        {
		//要删除节点是根节点
                if(T->Left == NULL && T->Right == NULL)
                {
                        free(T);
                        T = NULL;
                }
                else
                {
			//要删除节点不是根节点，是普通叶子节点
			//需要判断要删除节点是其父节点的左子树还是右子树
                        if(searchNode->value < parentNode->value)
                                parentNode->Left = NULL;
                        else
                                parentNode->Right = NULL;

                        free(searchNode);
                }
	}

	//已经找到该节点，且该节点的左子树非空，右子树为空
        else if(searchNode->Left != NULL && searchNode->Right == NULL)
        {
		//需要判断要删除节点是其父节点的左子树还是右子树
		//然后将要删除节点的父节点指向其左子树
                if(searchNode->value < parentNode->value)
                        parentNode->Left = searchNode->Left;
                else
                        parentNode->Right = searchNode->Left;

                free(searchNode);
        }

	//类似以上
        else if(searchNode->Left ==NULL && searchNode->Right != NULL)
        {
                if(searchNode->value < parentNode->value)
                        parentNode->Left = searchNode->Right;
                else
                        parentNode->Right = searchNode->Right;

                free(searchNode);
        }

	//要删除节点的左右子树都不为空
	//需要找到其后继节点，用后继节点替换要删除的节点
	//然后删除后继节点
        else if(searchNode->Left != NULL && searchNode->Right != NULL)
        {
                nextParentNode = searchNode;
                nextNode = searchNode->Right;

		//找到要删除节点的后继节点，nextParentNode指向要删除节点的后继节点的父节点
                while(nextNode->Left != NULL)
                {
                        nextParentNode = nextNode;
                        nextNode = nextNode->Left;
                }

		//用后继节点替换要删除的节点
                searchNode->value = nextNode->value;

		//判断后继节点是其父节点的左子树还是右子树
		//然后将后继节点的右子树赋给其父节点的左子树或者右子树
                if(nextNode->value < nextParentNode->value)
                        nextParentNode->Left = nextNode->Right;
                else
                        nextParentNode->Right = nextNode->Right;

		//释放后继节点
                free(nextNode);
        }

	//返回二叉搜索树
        return T;
}

