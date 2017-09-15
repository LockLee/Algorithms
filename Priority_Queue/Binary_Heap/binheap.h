#ifndef _BinHeap_H
#define _BinHeap_H

//定义堆容量的最小量
#define PQ_MINIMUM_CAPACITY 5
//定义堆容量的最大量
#define PQ_MAXIMUM_CAPACITY 2147483647

#define EMPTY_STRING "\0"

#define MAX(x, y)    ((x) > (y) ? (x) : (y))
#define MAX3(x, y, z)    ((x) > (y) ? MAX(x, z) : MAX(y, z))
#define MIN(x, y)    ((x) < (y) ? (x) : (y))
#define MIN3(x, y, z)    ((x) < (y) ? MIN(x, z) : MIN(y, z))

//自定义元素类型为int类型
typedef int Elemtype;

struct BinHeap;
typedef struct BinHeap Heap;
typedef Heap *PriorityQueue;

struct BinHeap
{
        int capacity;
        int size;
        Elemtype *Elements;
};

//初始化二叉堆，大小为maxElements
PriorityQueue Initialize(int maxElements);

//销毁二叉堆
void Destroy(PriorityQueue H);

//清空二叉堆
void MakeEmpty(PriorityQueue H);

//将元素X插入二叉堆H中
void Insert(Elemtype X, PriorityQueue H);

//返回并删除二叉堆的最小元素
Elemtype DeleteMin(PriorityQueue H);

//返回二叉堆的最小元素
Elemtype FindMin(PriorityQueue H);

//判断二叉堆是否为空
int IsEmpty(PriorityQueue H);

//判断二叉堆是否已满
int IsFull(PriorityQueue H);

//将二叉堆H位置P处的元素值减少Delta
void DecreaseKey(int P, int Delta, PriorityQueue H);

//将二叉堆位置P处的元素值增加Delta
void IncreaseKey(int P, int Delta, PriorityQueue H);

//将二叉堆H位置P处的元素删除并返回
Elemtype Delete(int P, PriorityQueue H);

//用数组Array[]中元素构建二叉堆，数组长度为Length
PriorityQueue BuildHeap(Elemtype *Array, int length);

//将位置P的元素下滤，即向下找到位置P元素的正确位置
void PercolateDown(int P, PriorityQueue H);

//将位置P的元素上滤，即向上找到位置P元素的正确位置
void PercolateUp(int P, PriorityQueue H);

//将*a和*b的值交换
void swap(Elemtype *a, Elemtype *b);


#endif
