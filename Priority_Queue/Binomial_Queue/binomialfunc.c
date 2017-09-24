#include <stdio.h>
#include <stdlib.h>
#include "binomialheap.h"

//二项树元素节点
struct BinNode
{
        Elemtype value;
        Position left;
        Position sibling;
};

//二项队列
struct Collection
{
        int currentSize;
        BinTree theTrees[MaxSize];
};

/*
 *初始化构造一个二项队列
 *
 *返回二项队列指针
 *
 */
BinQueue Initialize()
{
	int i;
	BinQueue H;
	
	H = (BinQueue)malloc(sizeof(struct Collection));
	if(H == NULL)
	{
		fprintf(stderr,"not enough memory");
		exit(1);
	}

	//二项队列当前元素个数为0
	H->currentSize = 0;
	
	//将二项队列中二项树指针清空
	for(i=0; i<MaxSize; i++)
		H->theTrees[i] = NULL;

	return H;
}

/*
 *判断二项队列H是否为空
 *
 *参数 H：二项队列指针
 *
 *如果二项队列为空则返回1，否则返回0
 */
int IsEmpty(BinQueue H)
{
        if(H == NULL)
        {
                fprintf(stderr,"Please Initialize Binomial Queue First.\n");
                exit(1);
        }

	return H->currentSize == 0;
}

/*
 *判断二项队列H是否满
 *
 *参数 H：二项队列指针
 *
 *如果二项队列已满则返回1，否则返回0
 */
int IsFull(BinQueue H)
{
        if(H == NULL)
        {
                fprintf(stderr,"Please Initialize Binomial Queue First.\n");
                exit(1);
        }

        return H->currentSize >= Capacity;
}

static BinTree CombineTrees(BinTree T1, BinTree T2)
{
	if(T1->value > T2->value)
		return CombineTrees(T2, T1);
	
	T2->sibling = T1->left;
	T1->left = T2;
	
	return T1;
}

BinQueue Merge(BinQueue H1, BinQueue H2)
{
	BinTree T1, T2, carry;
	int i, j;

	carry = NULL;

	if(H1->currentSize + H2->currentSize > Capacity)
	{
		fprintf(stderr, "out of space");
		exit(1);
	}	

	H1->currentSize += H2->currentSize;
	
	for(i=0, j=1; j <= H1->currentSize; i++, j*=2)
	{
		T1 = H1->theTrees[i];
		T2 = H2->theTrees[i];

		switch(!!T1 + 2*!!T2 + 4*!!carry)
		{
			case 0:
			case 1:
				break;
			case 2:
				H1->theTrees[i] = T2;
				H2->theTrees[i] = NULL;
				break;
			case 4:
				H1->theTrees[i] = carry;
				carry = NULL;
				break;
			case 3:
				carry = CombineTrees(T1, T2);
				H1->theTrees[i] = H2->theTrees[i] = NULL;
				break;
			case 5:
				carry = CombineTrees(T1, carry);
				H1->theTrees[i] = NULL;
				break;
			case 6:
				carry = CombineTrees(T2, carry);
				H2->theTrees[i] = NULL;
				break;
			case 7:
				H1->theTrees[i] = carry;
				carry = CombineTrees(T1, T2);
				H2->theTrees[i] = NULL;
				break;
		}
	}

	return H1;
}

void Insert(Elemtype X, BinQueue H)
{
	BinQueue tmp;
	BinTree newone;
	
	tmp = Initialize();
	newone = (BinTree)malloc(sizeof(struct BinNode));
	if(newone == NULL)
	{
		fprintf(stderr, "Out of space");
		exit(1);
	}
	
	newone->value = X;
	newone->left = newone->sibling = NULL;
	
	tmp->currentSize = 1;
	tmp->theTrees[0] = newone;

	Merge(H, tmp);
	
	free(tmp);
}

Elemtype FindMinValue(BinQueue H)
{
	int i, j;
	Elemtype minvalue;
	
	if(IsEmpty(H))
		return;
	else
		minvalue = H->theTrees[0]->value;
	
	for(i=1, j=1; j <= H->currentSize; i++, j*=2)
	{
		if(H->theTrees[i])
			if(H->theTrees[i]->value < minvalue)
				minvalue = H->theTrees[i]->value;
	}
	
	return minvalue;
}

int FindMinIndex(BinQueue H)
{
        int i, j,minindex;
        Elemtype minvalue;

        if(IsEmpty(H))
                return;
        else
	{
                minvalue = H->theTrees[0]->value;
		minindex = 0;
	}

        for(i=1, j=1; j <= H->currentSize; i++, j*=2)
        {
                if(H->theTrees[i])
                        if(H->theTrees[i]->value < minvalue)
			{
                                minvalue = H->theTrees[i]->value;
        			minindex = i;
			}
	}

        return minindex;
}

Elemtype DeleteMin(BinQueue H)
{
	int i, minIndex;
	Elemtype minValue;
	
	BinTree deletedTree, oldTree;
	BinQueue deletedQueue;
	
	if(IsEmpty(H))
	{
		fprintf(stderr, "The Binomial Queue Is Empty.\n");
		exit(1);
	}

	minIndex = FindMinIndex(H);
	
	oldTree = H->theTrees[minIndex];
	minValue = oldTree->value;
	
	deletedTree = oldTree->left;
	
	free(oldTree);
	
	deletedQueue = Initialize();
	deletedQueue->currentSize = (1<<minIndex) - 1;
	for(i = minIndex-1; i >= 0; i--)
	{
		deletedQueue->theTrees[i] =deletedTree;
		deletedTree = deletedTree->sibling;
		deletedQueue->theTrees[i]->sibling = NULL; 
	}

	H->theTrees[minIndex] = NULL;
	H->currentSize -= deletedQueue->currentSize + 1;
	
	Merge(H, deletedQueue);
	
	return minValue;
}

void DestroyTree(BinTree T)
{
	if(T == NULL)
		return;
	
	if(T->left != NULL)
		DestroyTree(T->left);
	if(T->sibling != NULL)
		DestroyTree(T->sibling);
	
	free(T);
}

void DestroyQueue(BinQueue H)
{
	int i, j;
	BinTree tmp;
	
	if(H == NULL)
		return;
	for(i=0, j=1; j<=H->currentSize; j*=2)
	{
		tmp = H->theTrees[i];
		DestroyTree(tmp);			
	}
	
	free(H);
}

static void PrintPreorderChildSibling(int depth, BinTree T)
{            
	int i;
    
	if(T) 
	{        
        	for(i = 0; i < depth; i++)
            		printf("    ");
        
		printf("%d\n", T->value);            
        	PrintPreorderChildSibling(depth + 1, T->left);                                    
        	PrintPreorderChildSibling(depth, T->sibling);
	} 
	else
	{
        	for(i = 0; i < depth; i++)
        		printf("    ");
        	
		printf("NULL\n");
	}
}

void PrintBinomialQueue(BinQueue H)
{
    int i, j;

    for(i=0, j=1; j <= H->currentSize; i++, j*=2)
    {
        printf("H[%d] = \n", i);
        PrintPreorderChildSibling(1, H->theTrees[i]);
    }    
}

