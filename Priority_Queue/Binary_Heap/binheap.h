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

PriorityQueue Initialize(int maxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(Elemtype X, PriorityQueue H);
Elemtype DeleteMin(PriorityQueue H);
Elemtype FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
void DecreaseKey(int P, int Delta, PriorityQueue H);
void IncreaseKey(int P, int Delta, PriorityQueue H);
Elemtype Delete(int P, PriorityQueue H);
PriorityQueue BuildHeap(Elemtype *Array, int length);
void PercolateDown(int P, PriorityQueue H);
void PercolateUp(int P, PriorityQueue H);
void swap(Elemtype *a, Elemtype *b);

#endif
