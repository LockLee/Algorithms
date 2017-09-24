#ifndef _BINOMIAL_QUEUE_H
#define _BINOMIAL_QUEUE_H

#define MaxSize 30

#define Capacity 1073741824


typedef int Elemtype;


struct BinNode;
typedef struct BinNode node;
typedef node *BinTree;
typedef node *Position;


struct Collection;
typedef struct Collection *BinQueue;

BinQueue Initialize();

int IsEmpty(BinQueue H);

int IsFull(BinQueue H);

void Insert(Elemtype X, BinQueue H);

Elemtype  FindMinValue(BinQueue H);

int FindMinIndex(BinQueue H);

void DestroyQueue(BinQueue H);

BinQueue Merge(BinQueue H1, BinQueue H2);

Elemtype DeleteMin(BinQueue H);


//void PrintTree(BinTree T,int depth);
void PrintBinomialQueue(BinQueue H);


#endif
