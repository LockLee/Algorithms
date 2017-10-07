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
 * 自顶向下伸展过程，并返回根节点
 * 
 *  注意：
 *   (a)：伸展树中存在"键值为 X 的节点"。
 *          将"键值为 X 的节点"伸展为根节点。
 *   (b)：伸展树中不存在"键值为 X 的节点"，并且 X < root->Value。
 *      b-1 "键值为 X 的节点"的前驱节点存在的话，将"键值为 X 的节点"的前驱节点伸展为根节点。
 *      b-2 "键值为 X 的节点"的前驱节点不存在的话，则意味着，X 比树中任何键值都小，那么此时，将最小节点旋转为根节点。
 *   (c)：伸展树中不存在"键值为 X 的节点"，并且key > tree->key。
 *      c-1 "键值为 X 的节点"的后继节点存在的话，将"键值为 X 的节点"的后继节点旋转为根节点。
 *      c-2 "键值为 X 的节点"的后继节点不存在的话，则意味着，X 比树中任何键值都大，那么此时，将最大节点旋转为根节点。
 *
 *  伸展过程大致分为三个过程，左连接、右连接和集成。
 *  在访问的任意时刻，都有一个当前节点 P ，它是其子树的根；
 *  树 header.Left 存储树 T 中小于 P 的节点，但不存储 P 的子树中的节点
 *  树 header.Right 存储树 T 中大于 P 的节点，但不存储 P 的子树中的节点
 *    第一个过程：左连接
 *           将小于当前节点并且不是当前节点子树中的节点左连接到 header.Left 中
 *    第二个过程：右连接
 *           将大于当前节点并且不是当前节点子树中的节点右连接到 header.Right 中
 *    第三个过程：集成
 *           将当前节点和 header.Left、header.Right 中子树集成为一颗伸展树
 */
splayTree Splay(Type X, Position P)
{
	//定义一个头节点，其左、右子树分别存储树 L 和树 R
	static struct splayNode header;
	//跟踪左、右连接指针
	Position leftMax, rightMin;
	
	//初始化树 L 和树 R都为 NullNode
	header.Left = header.Right = NullNode;
	//初始化左、右连接指针指向头结点
	leftMax = rightMin = &header;

	//
	NullNode->Value = X;

	//如果待展开值不等于当前节点值
	while(X != P->Value)
	{
		//如果待展开值小于当前节点值
		if(X < P->Value)
		{
			//并且小于当前节点左孩子的值，
			//则这种情况属于 “一字形”，进行右旋转
			//然后进行右连接
			if(X < P->Left->Value)
				P = SingleRotateWithRight( P );
			//如果当前节点左孩子为空
			//则说明没有找到待展开值，退出循环
			//否则这种情况属于“之字形”，进行简化的自顶向下的之字形旋转
			//然后进行右连接
			if(P->Left == NullNode)
				break;
	
			//进行右连接
			//将当前节点及其子树右连接到树 R 中
			rightMin->Left = P;
			rightMin = P;
			//当前节点更换为P的左孩子
			P = P->Left;
		}
		//如果待展开值大于当前节点值
		else
		{
			//并且大于当前节点右孩子的值，
			//则这种情况属于 “一字形”，进行左旋转
			//然后进行左连接
			if(X > P->Right->Value)
				P = SingleRotateWithLeft( P );
			//如果当前节点右孩子为空
			//则说明没有找到待展开值，退出循环
			//否则这种情况属于“之字形”，进行简化的自顶向下的之字形旋转
			//然后进行左连接
			if(P->Right == NullNode)
				break;
			
			//进行右连接
			//将当前节点及其子树右连接到树 R 中
			leftMax->Right = P;
			leftMax = P;
			//当前节点更换为P的右孩子
			P = P->Right; 
		}
	}
	//将树 L 和树 R 分别赋给当前节点的左孩子、右孩子
	leftMax->Right = P->Left;
	rightMin->Left = P->Right;
	P->Left = header.Right;
	P->Right = header.Left;
	//返回树根节点
	return P;
}

/*
 *在伸展树 T 中插入值 X
 *
 *参数 X：待插入值
 *     T：伸展树
 *
 *返回新伸展树地址
 */
splayTree Insert(Type X, splayTree T)
{
	static Position NewNode = NULL;
	
	//分配新节点
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

	//伸展树为空
	if(T == NullNode)
	{
		NewNode->Left = NewNode->Right = NullNode;
		T = NewNode;
	}
	//伸展树 T 不为空
	else
	{
		//将伸展树在值 X 处展开
		T = Splay(X, T);
		//如果待插入值 X 小于在值 X 处展开后的根节点值
		//那么 T 的新根和它的右子树变成新节点的右子树
		// T 的左子树则成为新节点的左子树
		if(X < T->Value)
		{
			NewNode->Left = T->Left;
			NewNode->Right = T;
			T->Left = NullNode;
			T = NewNode;
		}
		//类似以上
		else if(X > T->Value)
		{
			NewNode->Right = T->Right;
			NewNode->Left = T;
			T->Right = NullNode;
			T = NewNode;
		}
		//说明待插入值已在伸展树中
		else
			return T;
	}
	//清空，以备下次插入
	NewNode = NULL;
	
	return T;
}

/*
 *在伸展树中删除值 X
 *
 *参数 X：待删除值
 *     T：伸展树
 *
 *返回新的伸展树地址
 */
splayTree Delete(Type X, splayTree T)
{
	Position NewTree;
	
	if( T != NullNode)
	{
		T = Splay(X, T);
		//说明找到待删除值 X
		if(X == T->Value)
		{
			//左子树为空，说明待删除值为伸展树中最小值
			if(T->Left == NullNode)
				NewTree = T->Right;
			//将待删除值得前驱节点设为根节点
			else
			{
				NewTree = T->Left;
				NewTree = Splay(X, NewTree);
				NewTree->Right = T->Right;
			}
			//释放节点
			free(T);
			//设置伸展树新根
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

