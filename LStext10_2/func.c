#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
struct node;
typedef struct node Node;
typedef struct node *ptrNode;
typedef ptrNode List;
typedef ptrNode Position;

List makeEmpty(List L);
int isEmpty(List L);
int isLast(List L,Position P);
Position findX(int x,List L);
void deleteX(int x,List L);
Position findPre(int x,List L);
void insert(int x,List L,Position P);
void deleteList(List L);
Position header(List L);
Position first(List L);
Position advance(Position P);
int retrieve(Position P);

*/

List makeEmpty(List L)					//Make the List L empty (not delete the List)
{
	ptrNode p;
	//p = L->next;
	while(L->next)
	{
		p = L->next;
		L->next = p->next;
		free(p);	
	}
	return L;	
}

int isEmpty(List L)					//Return true if L is empty
{
	return L->next == NULL;
}

int isLast(List L,Position P)				//Return true if P is last
{
	return P->next == NULL;
}

Position findX(int x,List L)				//Return Position of x in L,NULL if not found
{
	ptrNode p;
	p = L->next;
	while(p != NULL && p->value != x)
		p = p->next;
	return p;
}

void deleteX(int x,List L)				//Delete first occurrence of x from List L
{
	ptrNode p,tmp;
	p = findPre(x,L);	
	if(!isLast(L,p))				//if x found,delete it.if p is the last Position,x not found
	{
		tmp = p->next;
		p->next = tmp->next;
		free(tmp);
	}	
}

Position findPre(int x,List L)				//Return prePosition of x,if x not found,return the last Position
{
	ptrNode p;
	p = L;
	while(p->next != NULL && p->next->value != x)
		p = p->next;
	return p;
}

void insert(int x,List L,Position P)			//Insert x after legal Position
{
	ptrNode tmp;
	tmp = (ptrNode)malloc(sizeof(Node));
	tmp->value = x;
	tmp->next = P->next;
	P->next = tmp;
}

void deleteList(List L)					//Delete the List L
{
	L = makeEmpty(L);
	free(L);	
} 

Position header(List L)
{
	return L;
}

Position first(List L)					//IF List L not NULL,return first element place;else return NULL
{
	if(L->next)
		return L->next;
	else
		return NULL;
}

