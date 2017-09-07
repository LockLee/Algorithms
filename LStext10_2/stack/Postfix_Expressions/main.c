#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "dstack.h"
#include <error.h>
#include <math.h>
    
int main()
{
	char midFix[100];
	char postFix[150];
	double result = 0.0;
	
	while(1)
	{
		printf("Please enter an expression: ");
		fgets(midFix, 100, stdin);
		printf("midfix is : %s \n",midFix);
		MidfixToPostfix(midFix,postFix);
		printf("postFix is : %s \n",postFix);
		result = Calcute(postFix);
		printf("calculation is : %lf \n",result);
   	}
    return 0;
}

