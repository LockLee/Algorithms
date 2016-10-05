#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

/*
struct polyNode;
typedef struct polyNode Node;
typedef struct polyNode *ptrNode;

ptrNode readPoly();
ptrNode multPoly(ptrNode ,ptrNode );
ptrNode addPoly(ptrNode ,ptrNode );
void printPoly(ptrNode );
void attachNode(int ,int ,ptrNode );

struct polyNode{
        int coef;
        int expon;
        ptrNode next;
};
*/

void attachNode(int coef,int expon,ptrNode *pPtrRear)
{
	ptrNode p;
	p = (ptrNode)malloc(sizeof(Node));
	p->coef = coef;
	p->expon = expon;
	p->next = NULL;
	(*pPtrRear)->next = p;
	*pPtrRear = p;
}

ptrNode readPoly()
{
	ptrNode p,pRear,pTmp;
	int coef,expon,num;
	
	printf("Please input the numbers of polynomial:");
	scanf("%d",&num);
	
	p = (ptrNode)malloc(sizeof(Node));
	p->next = NULL;
	pRear = p;
	
	while(num--)
	{
		scanf("%d %d",&coef,&expon);
		attachNode(coef,expon,&pRear);
	}
	
	pTmp = p;
	p = p->next;
	free(pTmp);
	return p; 		
}

ptrNode addPoly(ptrNode p1,ptrNode p2)
{
	ptrNode p,pRear,pTmp,t1,t2;
	t1 = p1;t2 = p2;
	p = (ptrNode)malloc(sizeof(Node));
	pRear = p;
	while(t1 && t2)
	{
		if(t1->expon == t2->expon)
		{
			if((t1->coef + t2->coef) == 0)
			{
				t1 = t1->next;
				t2 = t2->next;
			//	break;
			}
			else
			{
				attachNode(t1->coef + t2->coef,t1->expon,&pRear);
				t1 = t1->next;
				t2 = t2->next;
			}
		}
		else if(t1->expon > t2->expon)
		{
			attachNode(t1->coef,t1->expon,&pRear);
			t1 = t1->next;
		}
		else
		{
			attachNode(t2->coef,t2->expon,&pRear);
			t2 = t2->next;
		}	
	}
	while(t1)
	{
		attachNode(t1->coef,t1->expon,&pRear);
		t1 = t1->next;
	}
	while(t2)
	{
		attachNode(t2->coef,t2->expon,&pRear);
		t2 = t2->next;
	}
	
	pTmp = p;
        p = p->next;
        free(pTmp);

        return p;	
}

ptrNode multPoly(ptrNode p1,ptrNode p2)
{
	ptrNode p,pRear,pTmp,t1,t2;
	int expon,coef;	
	
	t1 = p1;t2 = p2;
        p = (ptrNode)malloc(sizeof(Node));
        pRear = p;
	
	if(!t1 || !t2)
		return NULL;
	
	while(t2)
	{
		attachNode(t1->coef * t2->coef,t1->expon + t2->expon,&pRear);
		t2 = t2->next;
	}
	
	t1 = t1->next;
	while(t1)
	{
		t2 = p2;
		pRear = p;
		while(t2)
		{
			coef = t1->coef * t2->coef;
			expon = t1->expon + t2->expon;
			while(pRear->next && pRear->next->expon > expon)
				pRear = pRear->next;
			if(pRear->next)
			{
				if(pRear->next->expon == expon)
				{
					if(pRear->next->coef + coef)
						pRear->next->coef += coef;
					else
					{
						pTmp = pRear->next;
						pRear->next = pTmp->next;
						free(pTmp);	
					}	
				
				}
				else
				{
					pTmp = (ptrNode)malloc(sizeof(Node));
					pTmp->coef = coef;
					pTmp->expon = expon;
					pTmp->next = pRear->next;
					pRear->next = pTmp;
				}
			}
			else
			{
				pTmp = (ptrNode)malloc(sizeof(Node));
                                pTmp->coef = coef;
                                pTmp->expon = expon;
                                pTmp->next = pRear->next;
                                pRear->next = pTmp;
	
			}
			
			t2 = t2->next;			
		}
	t1 = t1->next;
	}
	
	pTmp = p;
        p = p->next;
        free(pTmp);
			
        return p;

}

void printPoly(ptrNode p)
{
	if(!p)
	{
		printf("0 0\n ");
		return ;
	}
	while(p)
	{
		printf("%d %d	",p->coef,p->expon);
		p = p->next;
	}
	printf("\n");
}

