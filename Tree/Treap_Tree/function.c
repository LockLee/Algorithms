#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "treap.h"

/*
 *随机数生成函数，赋给Treap的优先级
 *
 *返回一个随机值
 */
static int randNum()
{
	int num;
	num = rand();

	return num;
}

/*
 *生成节点并初始化
 *
 *返回该节点地址
 */
static Position InitNode(Type e)
{
	Position P = NULL;

	P = (Position )malloc(sizeof(struct treapNode));
	if(P == NULL)
	{
		printf("Malloc A Node Out Space!");
		exit(1);
	}
	
	P->value = e;
	P->fix = randNum();
	P->size = 1;
	P->cnt = 1;
	P->Left = NULL;
	P->Right = NULL;	

	return P;
}

/*
 *右旋函数并维护旋转节点子树大小
 *
 */
static Position RightRotation(Position x)
{
	Position y = NULL;

	//正常右旋操作
	y = x->Left;
	x->Left = y->Right;
	y->Right = x;
	
	x = y;
	
	//维护变动节点的子树大小
	y = x->Right;
	if(y != NULL)
	{
		y->size = y->cnt;
		if(y->Left != NULL)
			y->size = y->size + y->Left->size;
		if(y->Right != NULL)
			y->size = y->size + y->Right->size;
	}

	x->size = x->cnt;
	if(x->Left != NULL)
		x->size = x->size + x->Left->size;
        if(x->Right != NULL)
		x->size = x->size + x->Right->size;
	
	return x;
}

/*
 *左旋函数并维护旋转节点子树大小
 *
 */
static Position LeftRotation(Position x)
{
	Position y = NULL;
	
	//正常左旋操作
	y = x->Right;
	x->Right = y->Left;
	y->Left = x;
	
	x = y;
	
	//维护变动节点的子树大小
	y = x->Left;
	if(y != NULL)
	{
		y->size = y->cnt;
		if(y->Left != NULL)
			y->size = y->size + y->Left->size;
		if(y->Right != NULL)
			y->size =y->size + y->Right->size;
	}
	
	x->size = x->cnt;
	if(x->Left != NULL)
		x->size = x->size + x->Left->size;
	if(x->Right != NULL)
		x->size = x->size + x->Right->size;

	return x;
}

/*
 *递归前序遍历Treap树
 */
void Preorder(treapTree T)
{
	if(T)
	{
		printf("%d	",T->value);
		Preorder(T->Left);
		Preorder(T->Right);
	}
}

/*
 *递归中序遍历Treap树
 */
void Inorder(treapTree T)
{
        if(T)
        {
                Inorder(T->Left);
                printf("%d      ",T->value);
                Inorder(T->Right);
        }
}

/*
 *递归销毁Treap树
 */
void DestroyTree(treapTree T)
{
	if(T)
	{
		DestroyTree(T->Left);
		DestroyTree(T->Right);
		free(T);
	}
}

/*
 *在Treap树中查找元素 X
 */
Position FindX(treapTree T, Type X)
{
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
 *在AVL树中找到最小元素
 *
 *参数 T：AVL树
 *
 *如果AVL树非空则返回最小元素的地址，否则返回NULL
 */
Position FindMin(treapTree T)
{
	while(T && T->Left)
		T = T->Left;
	
	return T;
}

/*
 *在AVL树中找到最大元素
 *
 *参数 T：AVL树
 *
 *如果AVL树非空则返回最大元素的地址，否则返回NULL
 */
Position FindMax(treapTree T)
{
	while(T && T->Right)
		T = T->Right;
	
	return T;
}

/*
 *打印Treap树信息
 */
void PrintTree(treapTree T, Type Key, int direction)
{
	if(T != NULL)
	{
		if(direction == 0)
			printf("%3d is root.fix is %3d.size is %3d.count is %3d\n", T->value, T->fix, T->size, T->cnt);
		else
			printf("%3d is %3d's %6s child.fix is %3d.size is %3d.count is %3d\n", T->value, Key, direction==1?"right" : "left", T->fix, T->size, T->cnt);
	
		PrintTree(T->Left, T->value, -1);
		PrintTree(T->Right, T->value, 1);
	}
}

/*
 *在Treap树T中插入元素X
 *
 *参数 X：待插入元素值
 *     T：Treap树地址
 *
 *返回新Treap树地址
 */
treapTree Insert(treapTree T, Type X)
{
	if(T == NULL)
	{
		T = InitNode(X);
		if( T == NULL)
	        {
        	        printf("Malloc A Node Out Space!");
                	exit(1);
        	}
	
	}
	else if(X < T->value)
	{
		T->size++;
		T->Left = Insert(T->Left, X);
		if(T->Left->fix < T->fix)
			T = RightRotation(T);
	}
	else if(X > T->value)
	{
		T->size++;
		T->Right = Insert(T->Right, X);
		if(T->Right->fix < T->fix)
			T = LeftRotation(T);
	}
	else
	{
		T->size++;
		T->cnt++;
	}

	return T;
}

/*
 *關於Treap的刪除，我們可以先递归查找到要刪除的節點後，在分成兩個case來討論:
 *
 *	1.該節點為葉節點或鏈節點，則該節點是可以直接刪除的節點，就直接刪除吧
 *	2.節點有兩個非空子節點。我們可以通過旋轉，使該節點變為可以直接刪除的節點。
 *     	  如果該節點的左子節點的修正值小於右子節點的修正值，右旋該節點，使該節點降為右子樹的根節點，然後訪問右子樹的根節點，繼續討論
 *	  反之，左旋該節點，使該節點降為左子樹的根節點，然後訪問左子樹的根節點，繼續討論，直到變成可以直接刪除的節點。
 */
treapTree Delete(treapTree T, Type X)
{
	Position Tmp = NULL;
	int count;

	if(T == NULL)
		return NULL;
	else if(X < T->value)
	{
		T->size--;
		T->Left = Delete(T->Left, X);
	}
	else if(X > T->value)
	{
		T->size--;
		T->Right = Delete(T->Right, X); 
	}
	else
	{
		count = T->cnt-1;
		if(count <= 0)
		{
			if(T->Left != NULL && T->Right != NULL)
			{
				if(T->Left->fix < T->Right->fix)
				{
					T = RightRotation(T);
					T->size--;
					T->Right = Delete(T->Right, X);
				}	
				else
				{
					T = LeftRotation(T);
					T->size--;
					T->Left = Delete(T->Left, X);
				}		
			}
                        else if(T->Left != NULL)
                        {
                                Tmp = T;
                                T = T->Left;
                                free(Tmp);
                        }
                        else if(T->Right != NULL)
                        {
                                Tmp = T;
                                T = T->Right;
                                free(Tmp);
                        }
                        else
                        {
                                Tmp = T;
                                T = NULL;
                                free(Tmp);
                        }
		}
		else
		{
			T->size--;
			T->cnt--;
		}
	}

	return T;
}

/*
 *
 *查找第K小元素：
 *1. 定义 P 为当前访问的节点，从根节点开始访问，查找排名第 k 的元素；                                                         
 *2. 若满足 P->left->size + 1 <=k <= P->left->size + P->cnt，则当前节点包含的元素就是排名第 k 的元素；
 *3. 若满足 k <P->left->size+ 1，则在左子树中查找排名第 k 的元素；
 *4. 若满足 k >P->left->size + P->cnt，则在右子树中查找排名第 k-(P->left->size + P->cnt)的元素。
 */
Position FindKth(treapTree T, int k)
{
	int leftsize = 0;
	
	if(T->Left != NULL)
		leftsize = T->Left->size;	

	if(k < (leftsize + 1))
		return FindKth(T->Left, k);
	else if(k > (leftsize + T->cnt))
		return FindKth(T->Right, k - ((T->Left ? T->Left->size : 0) + T->cnt));
	else 
		return T;
}

/*
 *首先判断root中的元素是否大于等于x：
 *
 *1. 如果是，则root和右侧子树中的元素全都大于x，递归左子树即可；
 *2. 如果root中的元素小于x，则左侧元素都小于x。因此，左侧子树中的所有元素都要算入答案。而在右侧子树中，
 *   利用递归方式算出小于x的元素个数。最终将左右侧小于x的元素个数与根节点个数相加就能得到答案。
 */
int LessX(treapTree T, Type X, int cur)
{	
	if(T == NULL)
		return cur + 0;
	if(T->value == X)
		return cur + (T->Left ? T->Left->size : 0);
	else if(X < T->value)
		return LessX(T->Left, X, cur);
	else 
	{
		cur += (T->Left ? T->Left->size : 0) + T->cnt;
		return LessX(T->Right, X, cur);
	}
}
