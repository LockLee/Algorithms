#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
   Given a rod of length n inches and a table of prices pi for i = 1、2、3 . . . n, 
   determine the maximum revenue rn obtainable by cutting up the rod and selling the pieces. 

   Note that if the price pn for a rod of length n is large enough, an optimal solution may require no cutting at all.
*/

/*
 *自底向上计算最优切割方案
 *
 *参数 p: 不同英寸钢条价格
 *     n: 钢条长度
 *
 *打印输出长度为 n 的钢条的最大利润并输出一个最优切割方案
 */
void Bottom_Up_Cut_Rod(int p[], int n)
{
	int i, j;

	int q;

	//保存不同长度钢条的最大利润
	int r[n + 1];
	//保存不同长度钢条的最近一次切割方案
	int s[n + 1];
	
	//长度为 0 的钢条的最大利润和最近一次切割都为 0
	r[0] = 0;
	s[0] = 0;
	
	for(j = 1; j <= n; j++)
	{
		q = INT_MIN;
		for(i = 1; i <= j; i++)
		{
			if(q < p[i] + r[j - i])
			{
				q = p[i] + r[j - i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	
	printf("The length of %d max revenue is:%d\n",n, r[n]);
	
	//打印输出最大利润
	printf("An optimal solution is:");
	//打印输出切割方案
	while(n > 0)
	{
		printf("%d   ",s[n]);
		n -= s[n];
	}
	printf("\n\n");
}

int main()
{
	int i;
	int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int length = sizeof(p)/sizeof(p[0]);
	
	for(i = 1; i < lenght; i++)
		Bottom_Up_Cut_Rod(p, i);
	
}
