#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

/*
struct polyNode;
typedef struct polyNode Node;
typedef struct polyNode *ptrNode;

ptrNode readPoly();
ptrNode multPoly(ptrNode ;ptrNode );
ptrNode addPoly(ptrNode ;ptrNode );
void printPoly(ptrNode );
void attachNode(int ;int ;ptrNode );

struct polyNode{
        int coef;
        int expon;
        ptrNode next;
};
*/

int main()
{
	ptrNode p1,p2,pMult,pAdd;
	
	p1 = readPoly();
	p2 = readPoly();
	pMult = multPoly (p1,p2);
	printPoly(pMult);
	pAdd = addPoly(p1,p2);
	printPoly(pAdd);

	return 0;
	
}
