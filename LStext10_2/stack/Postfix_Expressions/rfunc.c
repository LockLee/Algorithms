/*
 *这里的函数和 func.c 中函数实现功能一样
 *只不过这里是对 struct dnode 实现的
 *struct dnode 是用来保存计算结果的结构体
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dstack.h"

/*
struct dnode;
typedef struct dnode DNode;
typedef struct dnode *ptrDNode;
typedef ptrDNode DStack;
typedef ptrDNode DPosition;

double IsDStackEmpty(DStack S);
DStack CreateDStack(void );
void DisposeDStack(DStack S);
void MakeDStackEmpty(DStack S);
void DPush(double X, DStack S);
double DTop(DStack S);
void DPop(DStack S);

struct dnode
{
        double value;
        struct dnode *next;
};
*/

int IsDStackEmpty(DStack S)
{
        if(S->next == NULL)
		return 1;
	else
		return 0;
}

void DPop(DStack S)
{
        ptrDNode firstCell;

        if(IsDStackEmpty(S))
                printf("Empty Stack!!!");
        else
        {
                firstCell = S->next;
                S->next = S->next->next;
                free(firstCell);
        }
}

void DisposeDStack(DStack S)
{
        if(S == NULL)
                ;
        else
        {
                MakeDStackEmpty(S);
                free(S);
        }

}

void DPush(double X, DStack S)
{
        ptrDNode tmpCell;
        tmpCell = (ptrDNode)malloc(sizeof(DNode));
        if(S == NULL)
                printf("Must use CreateDStack first!!!");
        else if(tmpCell == NULL)
                printf("Out of Space!!!");
        else
        {
                tmpCell->value = X;
                tmpCell->next = S->next;
                S->next = tmpCell;
        }
}


void MakeDStackEmpty(DStack S)
{
        if(S == NULL)
        {
                printf("Must use CreateStack first!!!");

        }
        else
        {
                while(!IsEmpty(S))
                        Pop(S);
        }

}

DStack CreateDStack(void )
{
	DStack S;
        S = (DStack)malloc(sizeof(struct dnode));
        if(S == NULL)
        {
                printf("Out of Space!!!");
                return NULL;
        }
        S->next = NULL;
        MakeDStackEmpty(S);
        return S;

}

double DTop(DStack S)
{
        if(!IsDStackEmpty(S))
                return S->next->value;
        printf("Empty Stack!!!");
        return -1;
}

double DTopAndPop(DStack S)
{
        double tmp;
	DStack dstack;

        if(IsDStackEmpty(S))
        {
                printf("Empty Stack!!!");
                tmp = -1;
        }
        else
        {
                tmp = DTop(S);
		//printf("Top is :%lf\n",tmp);
                DPop(S);
        }

        return tmp;

}

