/*
 *NAME:RED_BLACK TREE(DELETE FUNCTION)
 *TIME:2016.10.24
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

/*
#define RED   0
#define BLACK 1

typedef int Type;

struct RBTreeNode;
typedef struct RBTreeNode Node;
typedef struct RBTreeNode *Position;
typedef struct RBTreeNode *RBTree;

struct RBRootNode;
typedef struct RBRootNode RBNode;
typedef struct RBRootNode *RBRoot;

RBRoot Delete(Type ,RBRoot );

struct RBTreeNode{
	Type Value;
        bool Color;
        Position Parent;
        Position Left;
        Position Right;
};

struct RBRootNode{
        RBTree node;
};
*/

static Position FindX(Type X,RBTree T)
{
        if(!T || X == T->Value)
                return T;
        else if(X < T->Value)
                return FindX(X,T->Left);
        else
                return FindX(X,T->Right);
}

static void LeftRotation(RBRoot root,Position x)
{
        Position y;

        y = x->Right;
        x->Right = y->Left;
        if(y->Left != NULL)
                y->Left->Parent = x;
        y->Parent = x->Parent;
        if(x->Parent == NULL)
                root->node = y;
        else if(x == x->Parent->Left)
                x->Parent->Left = y;
        else
                x->Parent->Right = y;
        y->Left = x;
        x->Parent = y;
}

static void RightRotation(RBRoot root,Position x)
{
        Position y;

        y = x->Left;
        x->Left = y->Right;
        if(y->Right != NULL)
                y->Right->Parent = x;
        y->Parent = x->Parent;
        if(x->Parent == NULL)
                root->node = y;
        else if(x == x->Parent->Left)
                x->Parent->Left = y;
        else
                x->Parent->Right = y;
        y->Right = x;
        x->Parent = y;
}


static void RBDeleteFixup(RBRoot root, Position x, Position parent)
{
	Position other;
	
	while((!x || (x->Color == BLACK)) && x != root->node)
	{
		if(parent->Left == x)
		{
			other = parent->Right;					//other must isn't NULL
			if(other->Color == RED)					//othre is RED. case 1
			{
				other->Color = BLACK;
				parent->Color = RED;
				LeftRotation(root, parent);
				other = parent->Right;
			}
			//other is BLACK and double children are BLACK (may be all NULL).case 2
			if((!other->Left || (other->Left->Color == BLACK)) &&	
			   (!other->Right || (other->Right->Color == BLACK)))
			{
				other->Color = RED;
				x = parent;
				parent = x->Parent;
			}
			else			      				
			{
				//other is BLACK and right child is BLACK and left(must exist) is RED.case 3
				if(!other->Right || (other->Right->Color == BLACK))
				{
					other->Left->Color = BLACK;
					other->Color = RED;
					RightRotation(root, other);
					other = parent->Right;	
				}
				//case 4
				other->Color = parent->Color;
				parent->Color = BLACK;
				other->Right->Color = BLACK;
				LeftRotation(root, parent);
				x = root->node;
			}
		}
		else		//same as up
		{
			other = parent->Left;
			if(other->Color == RED)
			{
				other->Color = BLACK;
				parent->Color = RED;
				RightRotation(root, parent);
				other = parent->Left;
			}
			if((!other->Left || (other->Left->Color == BLACK)) && 
			   (!other->Right || (other->Right->Color == BLACK)))
			{
				other->Color = RED;
				x = parent;
				parent = x->Parent;
			}
			else
			{
				if(!other->Left || (other->Left->Color == BLACK))
				{
					other->Right->Color == BLACK;
					other->Color = RED;
					LeftRotation(root, other);
					other = parent->Left;
				}
				other->Color = parent->Color;
				parent->Color = BLACK;
				other->Left->Color = BLACK;
				RightRotation(root, parent);
				x = root->node;
			}
		}
	}		
	
	if(x)
		x->Color = BLACK;
}

/*
 *红黑树的删除例程，类似于二叉搜索树的删除操作，有以下几点区别：
 *	第一：该删除操作是用后继节点 replace 替换要删除节点 z；
 *	第二：该红黑树数据结构中比二叉搜索树数据结构多了父节点指针；
 *	第三：需要记录被删除节点的颜色，以便恢复红黑树性质；
 *
 *删除过程大致分为两种情况：
 *	第一种情况：要删除节点 z 的左子树和右子树都不为空；
 *	第二种情况：要删除左子树为空或者右子树为空；
 *对于第二种情况比较好处理，直接用左子树或者右子树替换要删除节点即可，
 *对于第一种情况又分为两种小细节：
 *	a)：要删除节点 z 的后继节点 replace 是 z 的右孩子，此时直接将 z 替换为 z 的左孩子，不需要更新后继节点的右孩子指针；
 *	b)：要删除节点 z 的后继节点 replace 是 z 右孩子的左子树中节点，此时要更新后继节点的右孩子指针
 *
 */
RBRoot Delete(Type X, RBRoot root)
{
	Position z, child, parent, replace;
	bool color;
	
	z = NULL;
	z = FindX(X, root->node);
	if(z == NULL)
	{
		printf("%d not Find!",X);
		exit(1);
	}	 


	if((z->Left != NULL) && (z->Right != NULL))
	{
		replace = z->Right;
		while(replace->Left != NULL)
			replace = replace->Left;		
		
		color = replace->Color;
		child = replace->Right;
		parent = replace->Parent;
		
		if(z->Parent != NULL)
		{
			if(z->Parent->Left == z)
				z->Parent->Left = replace;
			else
				z->Parent->Right = replace;
		}
		else
			root->node = replace;
		
		if(parent == z)
			parent = replace;				//Fixup() use the parent
		else
		{
			if(child != NULL)
				child->Parent = parent;
			parent->Left = child;

			replace->Right = z->Right;
			z->Right->Parent = replace;
		}
		
		replace->Parent = z->Parent;
		replace->Left = z->Left;
		z->Left->Parent = replace;
		replace->Color = z->Color;
	}
	else
	{
		if(z->Left != NULL)
			child = z->Left;
		else
			child = z->Right;
		
		parent =z->Parent;

		color = z->Color;
	
		if(child != NULL)
			child->Parent = parent;
	
		if(parent != NULL)
		{
			if(parent->Left == z)
				parent->Left = child;
			else
				parent->Right = child;
		}
		else
			root->node = child;
	}
	
	if(color == BLACK)
		RBDeleteFixup(root,child,parent);
	
	free(z);
	
	return root;
}
