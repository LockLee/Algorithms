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
/*
 *Time Cost O(nW)
 *Space Cost O(nW)
 */
void knapsack_0_1_OnW(int v[], int w[], int length, int W)
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
/*
 *0/1 动态规划空间优化
 *时间复杂度 O(length*W) 空间复杂度 O(W)
 */
void knapsack_0_1_OW(int v[], int w[], int length, int W)
{
        int i, j, k;
        int cLen = length + 1;
        int fW = W + 1;
        int f[fW];

        for(j = 0; j < fW; j++)
        {
                f[j] = 0;
        }

	//在01背包中， j 变化的区间是逆序循环的原因：要保证由状态f[i-1][j-w[i]]递推到状态 f[i][j] 时，
	//f[i-1][j-w[i]]表示没有放入第i件物品。之后，在第i循环时，放入一件第i件物品。
        for(i = 1; i < cLen; i++)
                for(j = W; j >= w[i-1]; j--)
                        f[j] = max(f[j], f[j-w[i-1]] + v[i-1]);

        printf("%d\n",f[W]);
}

	
int main() {
	int value[] = {60,100,120};
	int weight[] = {10,20,30};
	int total = 50;
	int length = sizeof(value)/sizeof(value[0]);
    	knapsack_0_1_OnW(value,weight,length,total);
	return 0;
}
