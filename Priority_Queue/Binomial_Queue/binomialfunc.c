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
/*
 *将二项树T2合并到二项树T1中
 *
 *参数 T1：二项树指针
 *     T2：二项树指针
 *
 *返回二项树T1指针
 */
static BinTree CombineTrees(BinTree T1, BinTree T2)
{
	//保证函数CombineTrees(T1, T2)中 T1->value 小于等于 T2->value 
	if(T1->value > T2->value)
		return CombineTrees(T2, T1);
	
	//将T1的左孩子赋给T2的兄弟
	T2->sibling = T1->left;
	//是T2成为T1的左孩子
	T1->left = T2;
	
	return T1;
}

/*
 *将二项队列H2合并到二项队列H1中
 *
 *参数 H1：二项队列指针
 *     H2: 二项队列指针
 *
 *返回二项队列H1指针
 */
BinQueue Merge(BinQueue H1, BinQueue H2)
{
	BinTree T1, T2, carry;
	int i, j;

	//二项树临时指针
	carry = NULL;

	//判断待合并二项队列元素是否超过最大容量
	if(H1->currentSize + H2->currentSize > Capacity)
	{
		fprintf(stderr, "out of space");
		exit(1);
	}	

	//更新当前容量
	H1->currentSize += H2->currentSize;
	
	//i用于索引二项队列中二项树的
	//j表示二项队列最大可能二项树个数，因为N个节点的二项队列中二项树最多有logN个
	for(i=0, j=1; j <= H1->currentSize; i++, j*=2)
	{
		//T1表示二项队列H1中索引为i的二项树
		//T2表示二项队列H2中索引为i的二项树
		T1 = H1->theTrees[i];
		T2 = H2->theTrees[i];

		//如果T1非空，则!!T1为1，否则!!T1为0，T2和carry类似
		//T1、T2、carry组合共八种情况，分别对应以下情况
		switch(!!T1 + 2*!!T2 + 4*!!carry)
		{
			//T1、T2和carry为空
			case 0:
			//T1非空，T2和carry为空
			case 1:
				break;
			//T2非空，T1和carry为空
			//将二项树T2直接赋给二项队列H1相应位置并清空二项队列H2相应位置
			case 2:
				H1->theTrees[i] = T2;
				H2->theTrees[i] = NULL;
				break;
			//carry非空，T1和T2为空
			//将二项树carry直接赋给二项队列H1相应位置并清空二项树carry
			case 4:
				H1->theTrees[i] = carry;
				carry = NULL;
				break;
			//T1和T2非空，carry为空
			//合并二项树T1、T2，赋给carry，并清空二项队列H1、H2相应位置
			case 3:
				carry = CombineTrees(T1, T2);
				H1->theTrees[i] = H2->theTrees[i] = NULL;
				break;
			//类似以上
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

	//返回合并后的H1指针
	return H1;
}

/*
 *将元素X插入二项队列H中
 *
 *参数 X：待插入元素值
 *     H：二项队列指针
 *
 *无返回值
 */
void Insert(Elemtype X, BinQueue H)
{
	BinQueue tmp;
	BinTree newone;
	
	//新建一个二项队列
	tmp = Initialize();
	newone = (BinTree)malloc(sizeof(struct BinNode));
	if(newone == NULL)
	{
		fprintf(stderr, "Out of space");
		exit(1);
	}
	
	newone->value = X;
	newone->left = newone->sibling = NULL;
	
	//将元素节点链接到二项队列tmp中
	tmp->currentSize = 1;
	tmp->theTrees[0] = newone;

	//合并二项队列H和tmp
	Merge(H, tmp);

	//释放二项队列tmp
	free(tmp);
}

/*
 *找到二项队列H中最小元素并返回
 *
 *参数 H：二项队列指针
 *
 *返回最小元素值
 */
Elemtype FindMinValue(BinQueue H)
{
	int i, j;
	Elemtype minvalue;
	
	if(IsEmpty(H))
	{
		fprintf(stderr,"The Binomial Queue is NULL.\n");
		exit(1);
	}	
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

/*
 *找到二项队列H中最小元素下标并返回
 *
 *参数 H：二项队列指针
 *
 *返回最小元素下标值
 */
int FindMinIndex(BinQueue H)
{
        int i, j,minindex;
        Elemtype minvalue;

        if(IsEmpty(H))
	{
		fprintf(stderr,"The Binomial Queue is NULL.\n");
		exit(1);
	}
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

/*
 *删除二项队列H中最小元素并返回
 *
 *参数 H：二项队列指针
 *
 *返回二项队列最小值
 */
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

	//找到二项队列H最小值下标
	minIndex = FindMinIndex(H);
	
	//是oldTree指向最小值二项树
	oldTree = H->theTrees[minIndex];
	//将最小值赋给minValue
	minValue = oldTree->value;
	
	//deletedTree指向最小值二项树的左孩子
	deletedTree = oldTree->left;
	
	//释放最小值节点
	free(oldTree);
	
	//新建一个二项队列用于保存被删除最小值二项树的子树
	deletedQueue = Initialize();
	//设置新二项队列大小为 (1*2^minIndex-1)
	deletedQueue->currentSize = (1<<minIndex) - 1;
	//将被删除二项队列中的二项树依次赋给临时二项队列deletedQueue
	for(i = minIndex-1; i >= 0; i--)
	{
		deletedQueue->theTrees[i] =deletedTree;
		deletedTree = deletedTree->sibling;
		deletedQueue->theTrees[i]->sibling = NULL; 
	}

	H->theTrees[minIndex] = NULL;
	//更新二项队列当前大小
	H->currentSize -= deletedQueue->currentSize + 1;
	
	//合并
	Merge(H, deletedQueue);
	
	//释放二项队列 deletedQueue
	free(deletedQueue);
	
	//返回二项队列最小值
	return minValue;
}

//递归销毁二项树
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

//销毁二项队列
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

//打印二项树
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

//打印二项队列信息
void PrintBinomialQueue(BinQueue H)
{
    int i, j;

    for(i=0, j=1; j <= H->currentSize; i++, j*=2)
    {
        printf("H[%d] = \n", i);
        PrintPreorderChildSibling(1, H->theTrees[i]);
    }    
}
