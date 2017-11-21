/*
1、问题描述：
	已知:有一个容量为 W 的背包和 N 件物品，第 i 件物品的重量是 weight[i]，收益是 value[i]。
	条件:每种物品都有无限件，能放多少就放多少。
	问题:在不超过背包容量的情况下，最多能获得多少价值或收益

2、状态转移方程：
	F[i, j] = max{ F[i-1, j], F[i, j - wi] + vi}
	
3、Time Cost O(length*W)
   Space Cost O(length*W)
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
 *在完全背包中，v变化的区间是顺序循环的原因：完全背包的特点是每种物品可选无限件，
 *在求解加选第i种物品带来的收益f[i][v]时，在状态f[i][v-c[i]]中已经尽可能多的放
 *入物品i了，此时在f[i][v-c[i]]的基础上，我们可以再次放入一件物品i，此时也是在不
 *超过背包容量的基础下，尽可能多的放入物品i。
 */
void knapsack_complete(int v[], int w[], int length, int W)
{
        int i, j, k;
	int cLen = length + 1;
	int cW = W + 1;
        int c[cLen][cW];
	int num[length];

        for(i = 0; i < cW; i++)
                c[0][i] = 0;
        for(i = 0; i < cLen; i++)
                c[i][0] = 0;

        for(i = 1; i < cLen; i++)
        {
                for(j = 1; j < cW; j++)
                {
                        if(w[i-1] > j)
                                c[i][j] = c[i-1][j];
                        else
                        {
                                c[i][j] = max(c[i-1][j], c[i][j-w[i-1]]+v[i-1]);
                        }
                }
        }
        printf("\nMax Value:%d\n\n", c[length][W]);
 /* 
	for(i = 0; i < cLen; i++)
	{
		for(j = 0; j < cW; j++)
			printf("%d   ",c[i][j]);
		printf("\n");
	}      
*/
	
	//打印输出最优解方案
	i = length;
	j = W;
        for(i = length; i > 0; i--)
        {	
		k = 0;
		while(j > 0 && c[i][j] != c[i-1][j])
		{
                	k++;
			j -= w[i-1];
        	}
		num[i-1] = k;
	}
	
	for(i = 0; i < length; i++)
		printf("Good %d Get %d\n", i+1,num[i]);

	printf("\n");
}

/*
 *空间优化 Space Cost:O(W)
 *
 *该状态转移方程：F[j] = max{ F[j], F[j-w[i-1]] + v[i-1] }
 */
void knapsack_complete2(int v[], int w[], int length, int W)
{
        int i, j, k;
        int cLen = length + 1;
        int fW = W + 1;
        int f[fW];

	//这个伪代码与 01_背包问题 的伪代码只有 j 的循环次序不同而已。
	//为什么这样一改就可行呢？首先想想为什么 01_背包问题 中要按照 
	// j=W..0 的逆序来循环。这是因为要保证第i次循环中的状态f[i][j]
	//是由状态f[i-1][j-w[i-1]](C语言下标从 0 开始)递推而来。
	//换句话说，这正是为了保证每件物品只选一次，保证在考虑“选入
	//第 i 件物品”这件策略时，依据的是一个绝无已经选入第 i 件物品
	//的子结果f[i-1][j-[i-1]]。而现在完全背包的特点恰是每种物品可选
	//无限件，所以在考虑“加选一件第i种物品”这种策略时，却正需要一个可能
	//已选入第i种物品的子结果f[i][j-w[i-1]]，所以就可以并且必须采用 j=0...W
	//的顺序循环。这就是这个简单的程序为何成立的道理。
        for(j = 0; j < fW; j++)
        {
                f[j] = 0;
        }

        for(i = 1; i < cLen; i++)
                for(j = w[i-1]; j < fW; j++)
                        f[j] = max(f[j], f[j-w[i-1]] + v[i-1]);

        printf("%d\n",f[W]);
}

int main() {
        int value[] = {6,5,10,2,16,8};
        int weight[] = {3,2,5,1,6,4};
        int total = 10;
	int length = sizeof(value)/sizeof(value[0]);

        knapsack_complete(value, weight, length, total);

        return 0;
}
