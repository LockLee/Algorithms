#ifndef _Stack_Head_
#define _Stack_Head_

typedef char Elemtype;

struct node;
typedef struct node Node;
typedef struct node *ptrNode;
typedef ptrNode Stack;
typedef ptrNode Position;

Elemtype IsEmpty(Stack S);
Stack CreateStack(void );
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(Elemtype X, Stack S);
Elemtype Top(Stack S);
void Pop(Stack S);
Elemtype TopAndPop(Stack S);

int IsOperator(char c);
int Precedence(char op);
void MidfixToPostfix(char *Midfix, char *Postfix);
double Calcute(char *Postfix);
			//_Stack_Head_

struct node
{
	Elemtype value;
	struct node *next;
};

#endif
