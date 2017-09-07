#ifndef _DStack_Head_
#define _DStack_Head_

struct dnode;
typedef struct dnode DNode;
typedef struct dnode *ptrDNode;
typedef ptrDNode DStack;
typedef ptrDNode DPosition;

int IsDStackEmpty(DStack S);
DStack CreateDStack(void );
void DisposeDStack(DStack S);
void MakeDStackEmpty(DStack S);
void DPush(double X, DStack S);
double DTop(DStack S);
void DPop(DStack S);
double DTopAndPop(DStack S);

struct dnode
{
        double value;
        struct dnode *next;
};

#endif
