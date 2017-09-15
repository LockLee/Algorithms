#ifndef _LEFTIST_HEAP_H
#define _LEFTIST_HEAP_H

typedef int Elemtype;
	
struct LeftistNode;
typedef struct LeftistNode LNode;
typedef LNode *pLNode;
typedef pLNode Leftist;

struct LeftistNode
{
	Elemtype value;
	pLNode left;
	pLNode right;
	int npl;
};

//
void PreorderLeftist(Leftist H);

//
void InorderLeftist(Leftist H);

//
void PostorderLeftist(Leftist H);

//
Elemtype GetMin(Leftist H);

//
Leftist MergeLeftist(Leftist H1, Leftist H2);

//
Leftist InsertLeftist(Elemtype X, Leftist H);

//
Leftist DeleteMin(Leftist H);

//
void DestroyLeftist(Leftist H);

//
void PrintLeftist(Leftist H);


#endif 
