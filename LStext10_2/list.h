#ifndef _List_Head_
#define _List_Head_

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

struct node
{
	int value;
	struct node *next;
};


#endif      
