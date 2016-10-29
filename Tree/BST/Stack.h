#include "tree.h"

#ifndef _Stack_Head_
#define _Stack_Head_

#define STACK_INIT_SIZE 20
#define STACK_INCREASE 5

struct stackRecord;
typedef struct stackRecord *pStack;

struct stackRecord
{
	Position *base;
	Position *top;
	int size;
};

pStack initStack( );
void destoryStack(pStack );
void clearStack(pStack );
int isEmpty(pStack );
int lengthStack(pStack );
void Push(Position ,pStack );
Position Pop(pStack );

#endif

