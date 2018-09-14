#include <stdio.h>
#include <stdlib.h>
//该头文件定义了int类型的最大值INT_MAX（+2147483647）
#include <limits.h>
#include "binheap.h"

//检测二叉堆容量的最小值不能小于5，大于255
#if (PQ_MINIMUM_CAPACITY < 5)
#error PQ_MINIMUM_CAPACITY must not be less than 5
#elif (PQ_MINIMUM_CAPACITY > 255)
#warning PQ_MIMIMUM_CAPACITY is unreasonably high, recommended value is 5
#endif

//检测二叉堆容量的最大值不能小于二叉堆容量的最小值，并且不能大于等于int（32位系统）类型的最大值
#if (PQ_MAXIMUM_CAPACITY < PQ_MINIMUM_CAPACITY)
#error PQ_MAXIMUM_CAPACITY must not be less than PQ_MINIMUM_CAPACITY
#elif (PQ_MAXIMUM_CAPACITY >= 2147473647)
#error PQ_MAXIMUM_CAPACITY must not exceed range of 2147483647
#endif


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
	
	//如果初始化的堆大小小于二叉堆的最小容量，打印输出信息并返回NULL
	if(maxElements < PQ_MINIMUM_CAPACITY)
	{
		printf("The Priority Queue Size Is Small,Must large equal 5.\n");
		return NULL;
	}
	//如果初始化的堆大小大于二叉堆的最大容量，打印输出信息并返回NULL
	if(maxElements > PQ_MAXIMUM_CAPACITY)
	{
		printf("The Priority Queue Size Is Large,Must small equal 2147483647.\n");
		return NULL;
	}
	
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

/*
 *将位置P上的元素值减少Delta
 *
 *参数 P：待减少的元素位置
 *    Delta：位置P元素值减少的量
 *    H：二叉堆指针
 *
 *如果二叉堆为空，打印错误信息
 *如果位置P不合法，即超出二叉堆大小，打印错误信息
 *否则将位置P的值减少Delta，并保持二叉堆属性
 */
void DecreaseKey(int P, int Delta, PriorityQueue H)
{
        int i;
	Elemtype newValue;

        if(IsEmpty(H))
	{
		printf("The Priority Queue Is Empty.\n");
		//return NULL;
	}
	//检测待增加位置P的合法性
	else if(H->size < P)
	{
		printf("The Position Is Big Than The Priority Queue Size\n");
		//return NULL;
	}
	else
	{
		newValue = H->Elements[P] - Delta;
		//执行上滤，找到新元素值的正确位置
		for(i = P; H->Elements[i/2] > newValue; i /= 2 )
			H->Elements[i] = H->Elements[i/2];
		
		//将新元素值放入正确位置
		H->Elements[i] = newValue;	
	}
}

/*
 *将位置P上的元素值增加Delta
 *
 *参数 P：待增加的元素位置
 *    Delta：位置P元素值减增加的量
 *    H：二叉堆指针
 *
 *如果二叉堆为空，打印错误信息
 *如果位置P不合法，即超出二叉堆大小，打印错误信息
 *否则将位置P的值增加Delta，并保持二叉堆属性
 */
void IncreaseKey(int P, int Delta, PriorityQueue H)
{
        int i, child;
        Elemtype newValue;

        if(IsEmpty(H))
        {
                printf("The Priority Queue Is Empty.\n");
                //return NULL;
        }
        else if(H->size < P)
        {
                printf("The Position Is Big Than The Priority Queue Size\n");
                //return NULL;
        }
        else
        {
		newValue = H->Elements[P] + Delta;
		//执行下滤，找到新元素的正确位置
		for(i = P; 2*i <= H->size; i = child)
		{
			child = 2*i;
			if(child < H->size && H->Elements[child+1] < H->Elements[child])
				child++;
			if(H->Elements[child] < newValue)
				H->Elements[i] = H->Elements[child];
			else
				break;
		}         	
	
                H->Elements[i] = newValue;
        }
}

//将位置P上的元素上滤
void PercolateUp(int P, PriorityQueue H)
{
	int i, child;
	Elemtype value;
	value = H->Elements[P];
	
	//执行上滤，找到新元素值的正确位置
	for(i = P; H->Elements[i/2] > value; i /= 2 )
		H->Elements[i] = H->Elements[i/2];
		
	//将新元素值放入正确位置
	H->Elements[i] = value;
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
 *删除位置P的元素
 *
 *参数 P：待删除的元素位置
 *    H：二叉堆指针
 *
 *如果二叉堆为空，打印错误信息
 *如果位置P不合法，即超出二叉堆大小，打印错误信息
 *否则将删除位置P的值，并返回
 *
 */
Elemtype Delete(int P, PriorityQueue H)
{
	int i, child;
	Elemtype value;

        if(IsEmpty(H))
        {
                printf("The Priority Queue Is Empty.\n");
                //return NULL;
        }
        else if(H->size < P)
        {
                printf("The Position Is Big Than The Priority Queue Size.\n");
                //return NULL;
        }
        else
	{
		value = H->Elements[P];
		//将最后一个元素的值赋给优先队列位置P
		//并将堆元素个数减 1
		H->Elements[P] = H->Elements[H->size--];
		//在位置P上执行下滤
		PercolateDown(P, H);
	}
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
	
	//将数组元素插入二叉堆中
	for(i = 0; i < length; i++)
		Insert(Array[i], H);

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

