#ifndef _Queue_Link_
#define _Queue_Link_

typedef int Elemtype;

struct node;
typedef struct node QNode;
typedef struct node *ptrQNode;
typedef ptrQNode Queue;
typedef ptrQNode QPosition;

struct linknode;
typedef struct linknode LinkQueue;

int IsQueueEmpty(LinkQueue *Q);
LinkQueue* CreateQueue(void );
void DisposeQueue(LinkQueue *Q);
void MakeQueueEmpty(LinkQueue *Q);
void EnQueue(Elemtype X, LinkQueue *Q);
Elemtype Front(LinkQueue *Q);
void DeQueue(LinkQueue *Q);
Elemtype FrontAndDequeue(LinkQueue *Q);


struct node
{
	Elemtype value;
	struct node *next;
};

struct linknode
{
	ptrQNode front;
	ptrQNode rear;
};
           
#endif
                       
