/*
0-1 knapsack problem:
	A thief robbing a store finds n	items. The ith item is worth vi dollars 
	and weighs wi pounds, where vi and wi are integers. The thief wants to 
	take as valuable a load as possible, but he can carry at most W pounds 
	in his knapsack, for some integer W . Which items should he take?
	(We call this the 0-1 knapsack problem because for each item, the thief 
	must either426 Chapter 16 Greedy Algorithms take it or leave it behind; 
	he cannot take a fractional amount of an item or take an item more than once.)

Optimal-substructure property:
	For the 0-1 problem, consider the most valuable load that weighs at most 
	W pounds. If we remove item j from this load, the remaining load must be 
	the most valuable load weighing at most W - wj that the thief can take from 
	the n - 1 original items excluding j . 

Overlapping Subproblems Property:
		 0                                if i = 0 or w = 0
	c[i,j] = c[i-1,j]		          if wi > j
		 max(c[i-1,j], c[i-1,j-wj]+vi)    if i>0 and j >= wi
		
Time Cost O(nW)
Space Cost O(nW)
*/


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
	int clen;
	int cW;
	clen = length + 1;
	cW = W + 1;
	int c[clen][cW];
	
	for(i = 0; i < cW; i++)
		c[0][i] = 0;
	for(i = 0; i < clen; i++)
		c[i][0] = 0;
	
	//构造最优解
	for(i = 1; i < clen; i++)
	{
		for(j = 1; j < cW; j++)
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
	//打印输出最优解方案
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
	int length = sizeof(value)/sizeof(value[0]);
    	knapsack_0_1(value,weight,length,total);
	return 0;
}
