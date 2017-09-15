#include <stdio.h>
#include <stdlib.h>
#include "leftistheap.h"

/*
 *前序遍历
 *参数 H：左倾树根节点的指针
 */
void PreorderLeftist(Leftist H)
{
	if(H != NULL)
	{
		printf("%d	",H->value);
		PreorderLeftist(H->left);
		PreorderLeftist(H->right);
	}
}

/*
 *中序遍历
 *参数 H：左倾树根节点的指针
 */
void InorderLeftist(Leftist H)
{
	if(H != NULL)
	{
		InorderLeftist(H->left);
		printf("%d	",H->value);
		InorderLeftist(H->right);
	}
}

/*
 *后序遍历
 *参数 H：左倾树根节点的指针
 */
void PostorderLeftist(Leftist H)
{
	if(H != NULL)
	{
		PostorderLeftist(H->left);
		PostorderLeftist(H->right);
		printf("%d	",H->value);
	}
}

/*
 *交换节点的左儿子和右儿子
 *参数 L：左儿子节点地址的地址
 *    R：右儿子节点地址的地址
 */
static void SwapNode(Leftist *L, Leftist *R)
{
	Leftist tmp;
	
	tmp = *L;
	*L = *R;
	*R = tmp;
}

/*
 *返回左倾树的最小元素值
 *参数 H：左倾树根节点的指针
 */
Elemtype GetMin(Leftist H)
{
	//如果左倾树为空，打印信息并返回-1
	if(H == NULL)
	{
		printf("The Leftist Heap Is Empty.\n");
		return -1;
	}
	else
		return H->value;
}

/*
 *将左倾树H2合并到左倾树H1中的实际例程
 *参数 H1：左倾树H1的根节点指针
 *    H2：左倾树H2的根节点指针
 *（H1的根节点比H2的根节点值小）
 *返回左倾树H1的根节点指针
 */
static Leftist Merge1(Leftist H1, Leftist H2)
{
	//如果H1只有一个节点，直接使H2成为H1的左儿子
        if(H1->left == NULL)
                H1->left = H2;
        else
        {
		//否则递归将H2与H1的右儿子合并，因为H1的根节点值比H2的根节点值小
                H1->right = MergeLeftist(H1->right, H2);
		//如果合并之后H1左儿子的npl小于右儿子的npl
                if(H1->left->npl < H1->right->npl)
			//交换H1的左儿子和右儿子
                        SwapNode(&(H1->left), &(H1->right));

		//更新H1的npl
                H1->npl = H1->right->npl + 1;
        }

        return H1;
}


/*
 *合并左倾树H1和H2的驱动例程
 *参数 H1：左倾树H1的根节点指针
 *    H2：左倾树H2的根节点指针
 *返回合并后的左倾树根节点指针
 */
Leftist MergeLeftist(Leftist H1, Leftist H2)
{
	if(H1 == NULL)
		return H2;
	if(H2 == NULL)
		return H1;
	//保证Merge1（H1, H2）中H1有较小根
	if(H1->value < H2->value)
		return Merge1(H1, H2);
	else
		return Merge1(H2, H1);
}

/*
 *将元素X插入左倾树H中
 *参数 X：待插入节点值
 *    H: 左倾树根节点指针
 *返回插入X后的左倾树根节点指针
 */
Leftist InsertLeftist(Elemtype X, Leftist H)
{
	Leftist pnode;
	pnode = (LNode *)malloc(sizeof(LNode));
	if(pnode == NULL)
		return H;
	
	pnode->value = X;
	pnode->npl = 0;
	pnode->left = pnode->right = NULL;
	
	//相当于将节点合并到左倾树H中
	return MergeLeftist(H, pnode);
}

/*
 *删除左倾树H的最小节点
 *参数 H：左倾树根节点指针
 *返回新的根节点指针
 */
Leftist DeleteMin(Leftist H)
{
	Leftist L,R;	

	if(H == NULL)
		return NULL;

	L = H->left;
	R = H->right;
	//释放节点H
	free(H);
	
	//将左儿子和右儿子合并，返回新的左倾树根节点指针
	return MergeLeftist(L, R);
}

/*
 *销毁左倾树
 *
 */
void DestroyLeftist(Leftist H)
{
	if(H == NULL)
		return;
	
	if(H->left != NULL)
		DestroyLeftist(H->left);
	if(H->right != NULL)
		DestroyLeftist(H->right);

	free(H);
}

/*
 *打印左倾树信息
 *参数 H：左倾树根节点指针
 *    value：节点值
 *    direction: 为0 表示是根节点
 *               为1 表示是右儿子
 *               为-1 表示左儿子
 */
static void Leftist_Print(Leftist H, Elemtype value, int direction)
{
	if(H != NULL)
	{
		if(direction == 0)
			printf("%2d(%d) is root.\n",H->value,H->npl);
		else
			printf("%2d(%d) is %2d's %6s child.\n",H->value,H->npl,value,direction==1?"right" : "left");
	
		Leftist_Print(H->left, H->value, -1);
		Leftist_Print(H->right, H->value, 1);
	}
}

void PrintLeftist(Leftist H)
{
	if(H != NULL)
		Leftist_Print(H, H->value, 0);
}
