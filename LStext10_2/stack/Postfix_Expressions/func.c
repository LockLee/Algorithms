#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "dstack.h"
/*

#ifndef _Stack_Head_
#define _Stack_Head_

struct node;
typedef struct node Node;
typedef struct node *ptrNode;
typedef ptrNode Stack;
typedef ptrNode Position;

int IsEmpty(Stack S);
Stack CreateStack(void );
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(Elemtype X, Stack S);
Elemtype Top(Stack S);
void Pop(Stack S);
Elemtype TopAndPop(Stack S);		                

struct node
{
        int value;
        struct node *next;
};

 */

Elemtype IsEmpty(Stack S)					//判断栈是否为空，为空返回1，否则返回0
{
	return S->next == NULL;
}

void Pop(Stack S)						//将栈顶元素弹出
{
	ptrNode firstCell;
	
	if(IsEmpty(S))
		printf("Empty Stack!!!");
	else
	{
		firstCell = S->next;
		S->next = S->next->next;
		free(firstCell);
	}
}

void DisposeStack(Stack S)					//销毁栈
{
	Stack tmp,tnext;
	if(S == NULL)
		;
	else
	{
		tmp = S->next;
		while(tmp)
		{
			tnext = tmp;
			tmp = tmp->next;
			free(tnext);
		}
		free(S);
	}

}

void Push(Elemtype X, Stack S)					//将元素X压入栈顶
{
	ptrNode tmpCell;
	tmpCell = (ptrNode)malloc(sizeof(Node));
	if(S == NULL)
		printf("Must use CreateStack first!!!");
	else if(tmpCell == NULL)
		printf("Out of Space!!!");
	else
	{
		tmpCell->value = X;
		tmpCell->next = S->next;
		S->next = tmpCell;
	}
}

void MakeEmpty(Stack S)						//清空栈
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

Stack CreateStack()						//创建一个带头节点的空栈，返回指向头节点的指针
{
	Stack S;
	S = (Stack)malloc(sizeof(struct node));
	if(S == NULL)
	{
		printf("Out of Space!!!");
		return NULL;
	}
	S->next = NULL;
	MakeEmpty(S);
	return S;
}

Elemtype Top(Stack S)						//取出栈顶元素，并不弹出
{
	if(!IsEmpty(S))
		return S->next->value;
	printf("Empty Stack!!!");
	return -1;
}

Elemtype TopAndPop(Stack S)					//取出并弹出栈顶元素
{
	Elemtype tmp;
	
	if(IsEmpty(S))
	{
		printf("Empty Stack!!!");
		tmp = -1;
	}
	else
	{
		tmp = Top(S);
		Pop(S);
	}	

	return tmp;

}

int IsOperator(char c)						//判断字符c是否是‘+-*/%^’其中之一操作符
{
        int i;
        char ops[] = "+-*/%^";

        for(i = 0; i < 6; i++)
        {
                if(c == ops[i])
                        return 1;
        }
        return 0;
}

int Precedence(char op)						//返回各个操作符的优先级，‘（’优先级最低
{
        if(op == '(')
                return -1;
        else if(op == '+' || op == '-')
                return 0;
        else if(op == '*' || op == '/' || op == '%')
                return 1;
        else if(op == '^')
                return 2;
}

void MidfixToPostfix(char *Midfix, char *Postfix)		//将中缀表达式转换成后缀表达式
{
        int i, j;
        int length = 0;
        length = strlen(Midfix);
        Stack experStack = CreateStack();			//创建一个保存操作符的栈

        for(i = 0, j = 0; i < length; i++)
        {
                if(Midfix[i] == '(')				//如果是左括号直接入栈
                {
                        Push(Midfix[i], experStack);
                }
                else if(Midfix[i] == ')')			//如果是右括号，将栈中元素弹出，直到遇到左括号为止
                {
                        while(Top(experStack) != '(')
                        {
                                Postfix[j++] = TopAndPop(experStack);	//将弹出的操作符放入后缀表达式中
                        }
                        Pop(experStack);			//左括号丢弃掉
                }
                else
                {
                        if(!IsOperator(Midfix[i]))		//否则如果不是操作符的话，即可能是数字和小数点，将直接放入后缀表达式中
			{
                                Postfix[j++] = Midfix[i];
                	}
		        else					//如果是操作符
                        {
                                Postfix[j++] = ' ';		//放一个空格在后缀表达式中，将两个数字分割开
                                while(!IsEmpty(experStack) && (Precedence(Top(experStack)) >= Precedence(Midfix[i])))
                                {				//如果操作符栈非空并且栈顶元素的优先级大于等于该操作符的优先级
                               
                                        Postfix[j++] = TopAndPop(experStack);	//将栈顶元素取出放入后缀表达式中
                                }
                                Push(Midfix[i],experStack);	//将该操作符放入表达式栈中
                        }
                }
        }

        while(!IsEmpty(experStack))				//如果操作符栈非空，依次取出栈顶元素放入后缀表达式中
        {
                Postfix[j++] = TopAndPop(experStack);
        }
        DisposeStack(experStack);				//销毁表达式栈
        Postfix[j] = 0;

}

double Calcute(char *Postfix)					//计算后缀表达式的值
{
	int i, j;
	int length = strlen(Postfix);
	double x, y, tmp, result, tmpd;
	char str[length];					//创建一个字符串用来保存小数
	i = 0; j = 0;
	
	DStack rStack = CreateDStack();				//创建一个栈，用来保存计算结果
	
	while(i < length)					//扫描后缀表达式
	{
		if(IsOperator(Postfix[i]))			//如果是操作符，取出栈中两个数据并计算结果再将结果存入栈中
		{
			x = DTopAndPop(rStack);
			y = DTopAndPop(rStack);
			switch(Postfix[i])
			{
				case '+':
					tmp = y + x;
					break;
				case '-':
					tmp = y - x;
					break;
				case '*':
					tmp = y * x;
					break;
				case '/':
					tmp = y / x;
					break;
				case '%':
					tmp = (double)((int)y % (int)x);
					break;
				case '^':
					tmp = pow(y, x);
					break;
			}
		DPush(tmp,rStack);				//将计算结果存入栈中
		i++;						//继续扫描下一个字符
		}
		else if(Postfix[i] == ' ')			//如果该字符是空格，将自动扫描下一个字符
			i++;
		else						//否则可能数字或者小数点，则连续取出直到遇到空格或者操作符
		{
			for(j = 0; j < length; j++)		//清空字符串用来存放该数字
				str[j] = '\0';
			j = 0;
			while(!IsOperator(Postfix[i]) && Postfix[i] != ' ')
				str[j++] = Postfix[i++];
			
			tmpd = atof(str);			//将该数字转换成double类型
			DPush(tmpd, rStack);			//压入栈中
		}
	}
        
	result = DTop(rStack);					//取出栈顶元素结果
	DisposeDStack(rStack);					//销毁栈
	
	return result; 						//返回最终计算结果
}
