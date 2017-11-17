#include <stdio.h>
#include <stdlib.h>
	
int max(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}

void knapsack_0_1(int v[], int w[], int length, int W)
{
	int i, j, k;
	int c[length+1][W+1];
	
	for(i = 0; i < W+1; i++)
		c[0][i] = 0;
	for(i = 0; i < length+1; i++)
		c[i][0] = 0;

	for(i = 1; i < length+1; i++)
	{
		for(j = 1; j < W+1; j++)
		{
			if(w[i-1] > j)
				c[i][j] = c[i-1][j];
			else
			{
				c[i][j] = max(c[i-1][j], c[i-1][j-w[i-1]]+v[i-1]);
			}
		}	
	}
	printf("Max Value:%d\n", c[length][W]);
/*
	for(i = 0; i <= length; i++)
	{
		for(j = 0; j <= W; j++)
			printf("%d   ",c[i][j]);
		printf("\n");
	}
*/	
	j = W;
	for(i = length; i > 0; i--)
	{
		if(c[i][j] == c[i-1][j])
			printf("Goods %d No!\n",i);
		else
		{
			printf("Goods %d Yes!\n",i);
			j -= w[i-1];
		}
	}
}
	
int main() {
	int value[] = {60,100,120};
	int weight[] = {10,20,30};
	int total = 50;
    	knapsack_0_1(value,weight,sizeof(value)/sizeof(value[0]),total);
	return 0;
}
