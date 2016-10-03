/*
 *NAME:LINKED LIST
 *TIME:2016.10.3
 *AUTHOR:LS
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main()
{
	int i ,j,n;
	ptrNode L,p,q;
	L = (ptrNode)malloc(sizeof(Node));
	L->next == NULL;
	for(i = 0;i < 5; i++)
		insert(i,L,L);
	p = L->next;
	while(p)
	{
		printf("%d	",p->value);
		p = p->next;
	}
	printf("\n");
	q = findX(3,L);
	printf("%0X\n",q);
	
	deleteX(3,L);
	p = L->next;
        while(p)
        {
                printf("%d      ",p->value);
                p = p->next;
        }
        printf("\n");

	q = findX(3,L);
	printf("%0x\n",q);
	return 0;
}
