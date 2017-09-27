#include <stdio.h>
#include <stdlib.h>
#include "stackda.h"
#include "tree.h"

/*
 *初始化一个容量大小为20的栈，
 *
 *返回栈指针
 */

pStack InitStack()
{
	pStack S;
	S = (pStack)malloc(sizeof(struct stackRecord));
	if(!S)
	{
		printf("ERROR!");
		exit(1);
	}
	S->base = (Position* )malloc(sizeof(Position )*STACK_INIT_SIZE);
	if(!S->base)
	{
		printf("ERROR!");
		exit(1);
	}
	//栈顶指针指向栈底，表示栈为空
	S->top = S->base;
	//初始化栈容量为20
	S->size = STACK_INIT_SIZE;
	
	return S;
}

/*
 *销毁栈
 */
void DestoryStack(pStack S)
{
	if(!S)
	{
		printf("Stack is NULL!");
		exit(1);
	}
	//释放栈内元素
	free(S->base);
	//释放栈
	free(S);
}

/*
 *清空栈，使栈元素为0
 */
void ClearStack(pStack S)
{
	S->top = S->base;	
}

/*
 *判断栈是否为空
 *
 *参数 S：栈指针
 *
 *栈为空则返回1，否则返回0
 */
int IsEmpty(pStack S)
{
	return S->top == S->base;
}

/*
 *计算栈元素个数
 *
 *参数 S：栈指针
 *
 *返回栈元素个数
 */
int LenStack(pStack S)
{
	return S->top - S->base;
}

/*
 *入栈
 *
 *参数 X：栈元素
 *     S：栈指针
 *
 */
void Push(Position X,pStack S)
{
	//如果栈已满，则再增加5个元素空间
	if((S->top - S->base) >= S->size)
	{
		S->base = (Position* )realloc(S->base,sizeof(Position )*(S->size + STACK_INCREASE));
		if(!S->base)
		{
			printf("ERROR!");
			exit(1);
		}
	S->top = S->base + S->size;
	S->size += STACK_INCREASE;
	}
	//入栈
	*(S->top) = X;
	(S->top)++;
}
/*
 *出栈
 *
 *参数 S：栈指针
 *
 *返回栈顶元素
 */
Position Pop(pStack S)
{
	if(isEmpty(S))
	{
		printf("Stack is Empty!");
		exit(1);
	}
	//出栈
	S->top--;
	return *S->top;
}
