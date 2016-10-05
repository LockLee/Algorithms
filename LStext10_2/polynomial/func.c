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

void attachNode(int coef,int expon,ptrNode *pPtrRear)					//将新节点插入链表中，尾插法，最后一个参数是最后一个节点地址的地址
{
	ptrNode p;
	p = (ptrNode)malloc(sizeof(Node));
	p->coef = coef;
	p->expon = expon;
	p->next = NULL;
	(*pPtrRear)->next = p;							
	*pPtrRear = p;									//*pPtrRear指向链表最后一个节点
}

ptrNode readPoly()									//初始化一个多项式
{
	ptrNode p,pRear,pTmp;
	int coef,expon,num;
	
	printf("Please input the numbers of polynomial:");				//提示输入多项式的项数
	scanf("%d",&num);
	
	p = (ptrNode)malloc(sizeof(Node));						//构建一个头节点
	p->next = NULL;
	pRear = p;
	
	while(num--)									//依次将新节点插入链表尾部
	{
		scanf("%d %d",&coef,&expon);
		attachNode(coef,expon,&pRear);
	}
	
	pTmp = p;									//删除头节点
	p = p->next;
	free(pTmp);
	return p; 		
}

ptrNode addPoly(ptrNode p1,ptrNode p2)							//多项式加法函数
{
	ptrNode p,pRear,pTmp,t1,t2;
	t1 = p1;t2 = p2;
	p = (ptrNode)malloc(sizeof(Node));
	pRear = p;
	while(t1 && t2)									//如果多项式t1,t2都没有到达最后一个节点，依次比较他们的指数
	{
		if(t1->expon == t2->expon)						//指数相等情况
		{
			if((t1->coef + t2->coef) == 0)					//如果系数相加等于0
			{
				t1 = t1->next;
				t2 = t2->next;
			//	break;
			}
			else								//否则将新节点链到多项式和的链表中
			{
				attachNode(t1->coef + t2->coef,t1->expon,&pRear);
				t1 = t1->next;
				t2 = t2->next;
			}
		}
		else if(t1->expon > t2->expon)						//如果t1的指数大于t2的指数，则将t1节点链入
		{
			attachNode(t1->coef,t1->expon,&pRear);
			t1 = t1->next;
		}
		else									//否则将t2节点链入
		{
			attachNode(t2->coef,t2->expon,&pRear);
			t2 = t2->next;
		}	
	}
	while(t1)									//如果其中一个链表结束，则将另一个直接链入
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

ptrNode multPoly(ptrNode p1,ptrNode p2)							//多项式乘法函数
{
	ptrNode p,pRear,pTmp,t1,t2;
	int expon,coef;	
	
	t1 = p1;t2 = p2;
        p = (ptrNode)malloc(sizeof(Node));
        pRear = p;
	
	if(!t1 || !t2)
		return NULL;
	
	while(t2)									//先用t1的第一项乘以t2的每一项得到p
	{
		attachNode(t1->coef * t2->coef,t1->expon + t2->expon,&pRear);
		t2 = t2->next;
	}
	
	t1 = t1->next;
	while(t1)									//用t1的余下项乘以t2的每一项
	{
		t2 = p2;
		pRear = p;
		while(t2)                          					//该循环关键是找到乘得的项的插入位置                               	
		{
			coef = t1->coef * t2->coef;
			expon = t1->expon + t2->expon;
			while(pRear->next && pRear->next->expon > expon)		//找到插入位置的前驱节点
				pRear = pRear->next;
			if(pRear->next)							//如果不在链表末尾插入
			{
				if(pRear->next->expon == expon)				//如果新项指数与链表中项指数相同，判断系数相加是否为0
				{
					if(pRear->next->coef + coef)			//如果系数相加不等于0，更新系数
						pRear->next->coef += coef;
					else						//如果系数相加等于0,free()节点
					{
						pTmp = pRear->next;
						pRear->next = pTmp->next;
						free(pTmp);	
					}	
				
				}
				else							//如果新项指数与链表中项指数都不相等，直接插入节点
				{
					pTmp = (ptrNode)malloc(sizeof(Node));
					pTmp->coef = coef;
					pTmp->expon = expon;
					pTmp->next = pRear->next;
					pRear->next = pTmp;
				}
			}
			else								//如果乘积多项式到达末尾，直接插入
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

void printPoly(ptrNode p)								//打印输出多项式
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

