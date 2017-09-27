#include "tree.h"

#ifndef _Stack_H
#define _Stack_H

//初始化栈空间大小为20
#define STACK_INIT_SIZE 20
//如果栈满则在多分配5个栈空间
#define STACK_INCREASE 5

struct stackRecord;
typedef struct stackRecord *pStack;

//定义栈数据结构
//base 指向栈底元素
//top  指向栈顶元素
//size 表示当前栈容量
struct stackRecord
{
	Position *base;
	Position *top;
	int size;
};

//初始化一个容量为20的栈
pStack initStack( );

//销毁栈
void destoryStack(pStack );

//清空栈，使栈顶指向栈底
void clearStack(pStack );

//判断栈是否为空
int isEmpty(pStack );

//返回当前栈大小
int lengthStack(pStack );

//入栈
void Push(Position ,pStack );

//出栈
Position Pop(pStack );

#endif

