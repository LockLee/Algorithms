#ifndef _Queue_Array_
#define _Queue_Array_

typedef int Elemtype;

struct node;
typedef struct node ANode;
typedef struct node *ptrANode;
typedef ptrANode Queue;

int IsEmpty(Queue Q );
int IsFull(Queue Q);
Queue CreateQueue();
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
int QueueLen(Queue Q);
void EnQueue(Elemtype X, Queue Q);
Elemtype Front(Queue Q);
void DeQueue(Queue Q);
Elemtype FrontAndDequeue(Queue Q);

struct node
{
	int front;
	int rear;
	Elemtype *array;
};

#endif
