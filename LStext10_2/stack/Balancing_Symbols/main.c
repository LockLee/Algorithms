/*
Name: Balancing_Symbols
Author: LS
Time: 2017.9.5
*/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <error.h>

int main(int argc, char **argv)
{
	int flag = 0;
	FILE *fp;
	Stack s;
	char c;
	char ctmp;
	
	if(argc != 2)
	{
		printf("usage: a.out <filename>\n");
		exit(0);
	}
	
	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		perror("fopen");
		exit(1);
	}

	s = CreateStack();
	c = fgetc(fp);
	while(c != EOF)
	{
		switch(c)
		{
			case '(':
				Push(c, s);
				break;
			case '[':
                                Push(c, s);
                                break;
		        case '{':
                                Push(c, s);
                                break;
			case ')':
				if(IsEmpty(s))
				{
					flag = 1;
					break;
				}
				else if(Top(s) != '(')
				{
					flag = 1;
					break;
				}
				else
				{
					Pop(s);
					break;
				}
      			case ']':
                                if(IsEmpty(s))
                                {
					flag = 1;
                                        break;
                                }
                                else if(Top(s) != '[')
                                {
					flag = 1;
                                        break;
                                }
                                else
				{
                                        Pop(s);
					break;
				}
			case '}':
                                if(IsEmpty(s))
                                {
					flag = 1;
                                        break;
                                }
                                else if(Top(s) != '{')
                                {
					flag = 1;
                                        break;
                                }
                                else
				{
                                        Pop(s);
					break;
				}
		}
		if(flag == 1)
			break;
	
		c = fgetc(fp);
	}
	
	if(flag == 1)
		printf("No Match!!!\n");
	else if(IsEmpty(s))
		printf("Match!!!\n");
	else
		printf("No Match!!!\n");

}
