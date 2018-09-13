#include <stdio.h>
#include <stdlib.h>
//该头文件定义了int类型的最大值INT_MAX（+2147483647）
#include <limits.h>
#include "binheap.h"


/*
 *初始化优先队列
 *
 *参数 maxElements：表示初始化二叉堆的大小
 *
 *如果初始化成功返回一个二叉堆指针
 *否则返回NULL
 */
PriorityQueue Initialize(int maxElements)
{
	PriorityQueue H;
	
	//动态分配一个二叉堆结点
	H = (PriorityQueue )malloc(sizeof(struct BinHeap));
	if(H == NULL)
	{
		printf("The Space Is OUT.\n");
		return NULL;
	}
	
	//动态分配一个大小为（maxElements + 1）的数组，H->Elements指向该数组
	H->Elements = (Elemtype *)malloc((maxElements + 1)*sizeof(Elemtype));
	if(H->Elements == NULL)
	{
		printf("The Malloc Space Is OUt.\n");
		return NULL;
	}
	
	//二叉堆容量为maxElements
	H->capacity = maxElements;
	//二叉堆大小为0
	H->size = 0;
	//放一个最小值用作哨兵，INT_MIN定义为（-2147483648）
	H->Elements[0] = INT_MIN;

	return H;
}

/*
 *销毁队列
 *
 *参数 H：二叉堆节点指针
 *
 */
void Destroy(PriorityQueue H)
{
	if(H != NULL)
	{
		if(H->Elements != NULL)
			free(H->Elements);
		free(H);
	}
}

/*
 *清空二叉堆中元素，即使H->size为0
 *
 *参数 H；二叉堆节点指针
 *
 */
void MakeEmpty(PriorityQueue H)
{
	if(H != NULL)
		H->size = 0;
	else
		printf("The Priority Queue is NULL.\n");
}

/*
 *将元素X插入二叉堆H中
 *
 *参数 X：待插入元素值
 *    H：二叉堆指针
 *
 *返回新的二叉堆指针
 */
void Insert(Elemtype X, PriorityQueue H)
{
	int i;
	int lastCapacity = H->capacity;
	
	
	//如果二叉堆容量已满，则重新申请空间
	if(H->size == H->capacity)
	{
		//重新分配内存，增加10个元素内存空间
		H->Elements = (Elemtype *)realloc(H->Elements, 10*sizeof(Elemtype) + sizeof(H->Elements));
		//如果申请内存失败，打印错误信息,并直接返回
		if(H->Elements == NULL)
	        {
                	printf("The Realloc Space Is Out.\n");
			return ;
        	}
	
		//重新设置二叉堆大小
		H->capacity = lastCapacity + 10;
	}

	//上滤(percolate up)，找到元素X正确插入位置,并将堆元素个数加 1
	//H->Elements[0]存放一个哨兵（sentinal），简化逻辑判断
	for(i = ++H->size; H->Elements[i/2] > X; i /= 2)
		H->Elements[i] = H->Elements[i/2];
 	//位置[i]即为元素X插入的正确位置
	H->Elements[i] = X;

}

/*
 *返回并删除优先队列H的最小元素
 *
 *参数 H：二叉堆指针
 *
 *如果二叉堆为空，返回INT_MIN（-2147483648）
 *否则返回最小元素
 */
Elemtype DeleteMin(PriorityQueue H)
{
	int i, child;
	Elemtype minElement, lastElement;

	if(IsEmpty(H))
	{
		printf("The Priority Queue Is Empty.\n");
		return H->Elements[0];
	}

	minElement = H->Elements[1];
	//取出最后元素并将堆元素个数减 1
	lastElement = H->Elements[H->size--];

	//下滤（percolate down），找到最后一个元素lastElement的正确插入位置
	for(i = 1; 2*i <= H->size; i = child)
	{
		child = i * 2;
		//如果有两个儿子节点，找到两儿子节点的较小元素
		if(child < H->size && H->Elements[child +1] < H->Elements[child])
			child++;
		//如果儿子节点比最后一个元素小，则下滤（percolate down）
		if(lastElement > H->Elements[child])
			H->Elements[i] = H->Elements[child];
		//否则就找到最后元素的正确插入位置
		else
			break;
	}
	
	//将最后一个元素插入正确位置
	H->Elements[i] = lastElement;
	
	return minElement;
}

//将位置P上的元素上滤
void PercolateUp(int P, PriorityQueue H)
{
	int i, child;
	Elemtype value;
	value = H->Elements[P];
	
	for(i = P; H->Elements[i/2] > value; i /= 2)
		swap(&value, &(H->Elements[i]));
}

//交换两元素的值
void swap(Elemtype *a, Elemtype *b)
{
	Elemtype tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//将位置P上的元素值下滤
void PercolateDown(int P, PriorityQueue H)
{
	int i, child;
	Elemtype value;
	value = H->Elements[P];
	
	for(i = P; 2*i <= H->size; i = child)
	{
		child = 2*i;
		if(child < H->size && H->Elements[child + 1] < H->Elements[child] )
			child++;
		if(H->Elements[child] < value)
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	
	H->Elements[i] = value;
}


/*
 *构建优先队列
 *
 *参数 Array：关键二叉堆的数组
 *    length：数组长度
 *
 *返回二叉堆指针
 */
PriorityQueue BuildHeap(Elemtype *Array, int length)
{
	int i;
	PriorityQueue H;
	
	//初始化二叉堆
	H = Initialize(length);
	
	//将数组元素放入二叉堆中
	for(i = 0; i < length; i++)
		H->Elements[i+1] = Array[i];
	H->size = length;
		
	//构建二叉堆 
	for(i = (length+1)/2; i > 0; i--)
		PercolateDown(i, H);

	return H;
}

/*
 *返回二叉堆的最小值
 *
 */
Elemtype FindMin(PriorityQueue H)
{
	if(H != NULL)
		return H->Elements[1];
}

/*
 *判断二叉堆是否为空
 *是空二叉堆则返回1
 *否则返回0
 */
int IsEmpty(PriorityQueue H)
{
	return (H->size == 0);
}

/*
 *判断二叉堆是否已满
 *是满二叉堆则返回1
 *否则返回0
 */
int IsFull(PriorityQueue H)
{
	return (H->size == H->capacity);
}
