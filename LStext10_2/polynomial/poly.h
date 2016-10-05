#ifndef _Poly_Head_
#define _Poly_Head_

struct polyNode;
typedef struct polyNode Node;
typedef struct polyNode *ptrNode;

ptrNode readPoly();
ptrNode multPoly(ptrNode ,ptrNode );
ptrNode addPoly(ptrNode ,ptrNode );
void printPoly(ptrNode );
void attachNode(int ,int ,ptrNode* );

struct polyNode{
	int coef;
	int expon;
	ptrNode next;
};

#endif
