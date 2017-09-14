#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "binheap.h"

#if (PQ_MINIMUM_CAPACITY < 5)
#error PQ_MINIMUM_CAPACITY must not be less than 5
#elif (PQ_MINIMUM_CAPACITY > 255)
#warning PQ_MIMIMUM_CAPACITY is unreasonably high, recommended value is 5
#endif
/*
#if (PQ_MAXIMUM_CAPACITY < PQ_MINIMUM_CAPACITY)
#error PQ_MAXIMUM_CAPACITY must not be less than PQ_MINIMUM_CAPACITY
#elif (PQ_MAXIMUM_CAPACITY >= INT_MAX)
#error PQ_MAXIMUM_CAPACITY must not exceed range of 2147483647
#endif
*/

//初始化优先队列，传入一个参数表示队列大小
PriorityQueue Initialize(int maxElements)
{
	PriorityQueue H;
	
	if(maxElements < PQ_MINIMUM_CAPACITY)
	{
		printf("The Priority Queue Size Is Small,Must large equal 5.\n");
		return NULL;
	}
	if(maxElements > PQ_MAXIMUM_CAPACITY)
	{
		printf("The Priority Queue Size Is Large,Must small equal 2147483647.\n");
		return NULL;
	}
	
	H = (PriorityQueue )malloc(sizeof(struct BinHeap));
	if(H == NULL)
	{
		printf("The Space Is OUT.\n");
		return NULL;
	}
	
	H->Elements = (Elemtype *)malloc((maxElements + 1)*sizeof(Elemtype));
	if(H->Elements == NULL)
	{
		printf("The Malloc Space Is OUt.\n");
		return NULL;
	}
	
	H->capacity = maxElements;
	H->size = 0;
	//放一个最小值用作哨兵
	H->Elements[0] = INT_MIN;

	return H;
}

//销毁队列
void Destroy(PriorityQueue H)
{
	if(H != NULL)
	{
		if(H->Elements != NULL)
			free(H->Elements);
		free(H);
	}
}

//清空队列
void MakeEmpty(PriorityQueue H)
{
	if(H != NULL)
		H->size = 0;
	else
		printf("The Priority Queue is NULL.\n");
}

//将元素X插入队列H中
void Insert(Elemtype X, PriorityQueue H)
{
	int i;
	int lastCapacity = H->capacity;
	
	if(H->size == H->capacity)
	{
		//重新分配内存，增加10个元素内存空间
		H->Elements = (Elemtype *)realloc(H->Elements, 10*sizeof(Elemtype) + sizeof(H->Elements));
		if(H->Elements == NULL)
	        {
                	printf("The Realloc Space Is Out.\n");
        	}
	
		H->capacity = lastCapacity + 10;
		H->size = lastCapacity;
	}

	//下滤，找到元素X正确插入位置
	for(i = ++H->size; H->Elements[i/2] > X; i /= 2)
		H->Elements[i] = H->Elements[i/2];
       	H->Elements[i] = X;

}

//返回并删除优先队列H的最小元素
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
	//取出最后元素
	lastElement = H->Elements[H->size--];

	//下滤，找到元素X的正确插入位置
	for(i = 1; 2*i <= H->size; i = child)
	{
		child = i * 2;
		//如果有两个儿子节点，找到两儿子节点的较小元素
		if(child < H->size && H->Elements[child +1] < H->Elements[child])
			child++;
		//如果儿子节点比最后一个元素小，则下滤
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

//将位置P上的元素值减少Delta
void DecreaseKey(int P, int Delta, PriorityQueue H)
{
        int i;
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
		newValue = H->Elements[P] - Delta;
		//执行上滤，找到新元素值的正确位置
		for(i = P; H->Elements[i/2] > newValue; i /= 2 )
			H->Elements[i] = H->Elements[i/2];
		
		H->Elements[i] = newValue;	
	}
}

//将位置P上的元素值增加Delta
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

//将位置P上的元素值上滤
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

//删除位置P的元素
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
		H->Elements[P] = H->Elements[H->size--];
		//在位置P上执行下滤
		PercolateDown(P, H);
	}
}

//构建优先队列
PriorityQueue BuildHeap(Elemtype *Array, int length)
{
	int i;
	PriorityQueue H;
	
	H = Initialize(length);
	
	for(i = 0; i < length; i++)
		Insert(Array[i], H);

	return H;
}

Elemtype FindMin(PriorityQueue H)
{
	if(H != NULL)
		return H->Elements[1];
}

int IsEmpty(PriorityQueue H)
{
	return (H->size == 0);
}

int IsFull(PriorityQueue H)
{
	return (H->size == H->capacity);
}

