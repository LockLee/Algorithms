/*

"Imagine you have a collection of N wines placed next to each other on a shelf. 
For simplicity, let's number the wines from left to right as they are standing 
on the shelf with integers from 1 to N, respectively. The price of the ith wine 
is pi. (prices of different wines can be different).

Because the wines get better every year, supposing today is the year 1, on year y
the price of the ith wine will be y*pi, i.e. y-times the value that current year.

You want to sell all the wines you have, but you want to sell exactly one wine 
per year, starting on this year. One more constraint - on each year you are allowed
to sell only either the leftmost or the rightmost wine on the shelf and you are not
allowed to reorder the wines on the shelf (i.e. they must stay in the same order as 
they are in the beginning).

You want to find out, what is the maximum profit you can get, if you sell the wines 
in optimal order?"

So, for example, if the prices of the wines are (in the order as they are placed on 
the shelf, from left to right): p1=1, p2=4, p3=2, p4=3. The optimal solution would 
be to sell the wines in the order p1, p4, p3, p2 for a total profit 1 * 1 + 3 * 2 + 2 * 3 + 4 * 4 = 29.

*/

/*
 *Name: Wine Profit of Dynamic Programming Solution
 *Author：LS
 *Time：2017.11.2
 */

#include <stdio.h>
#include <stdlib.h>

//用于存放最大利润，从m[1][1]开始
int m[10][10] = {0};
//用于存放出售策略，从s[1][1]开始
int s[10][10] = {0};

#define max(a, b) (a>b) ? a : b

/*
 *求最大利润函数
 *
 *参数p[]: 表示每瓶酒的售价，从p[0]开始，p[0]表示第一瓶酒的售价
 *     n:  表示共有 n 瓶酒
 *
 *m[i][j]表示 Pi 到 Pj 瓶酒的最大利润
 *s[i][i]表示 Pi 到 Pj 瓶酒当前应出售的酒编号
 */
void Wines_Profit(int p[], int n)
{
	int i, j, L, k;
	int profit;
	int year;

	for(i = 1; i <= n; i++)
	{
		m[i][i] = n * p[i-1];
		s[i][i] = i;
	}

	for(L = 2; L <= n; L++)
	{
		for(i = 1; i <= n-L+1; i++)
		{
			j = i+L-1;
			year = n-L+1;
			if((m[i][j-1] + year*p[j-1]) > (m[i+1][j]+year*p[i-1]))
			{
				m[i][j] = m[i][j-1] + year*p[j-1];
				s[i][j] = j;
			}
			else
			{
				m[i][j] = m[i+1][j] + year*p[i-1];
				s[i][j] = i;
			}
		}
	}
}

/*
 *打印输出最大利润方案
 *
 *参数   p[]: 表示每瓶酒的售价，从p[0]开始，p[0]表示第一瓶酒的售价
 *     m[][]: 表示 Pi 到 Pj 瓶酒的最大利润
 *     s[][]: 表示 Pi 到 Pj 瓶酒当前应出售的酒编号
 *	   i: 表示从第 i 瓶酒开始
 *         j：表示到第 j 瓶酒结束 
 *
 */
void Print_Optimal_Profit(int p[], int m[][10], int s[][10], int i, int j)
{	
	int tmp = s[i][j];
	int year = 1;
	
	while(i != j)
	{
		printf("P%d  ", s[i][j]);
		tmp = m[i][j] - (year++)*p[s[i][j]-1];
		if(m[i+1][j] == tmp)
			i++;
		else
			j--;
	}

	printf("P%d  ", s[i][j]);
	printf("\n");
}

void main()
{
	int i, j;
	int count = 0;

	int p[] = {2, 3, 5, 1, 4};
	int length = sizeof(p)/sizeof(p[0]);

	Wines_Profit(p, length);
	
	printf("Max Profit:%d\n",m[1][length]);

	Print_Optimal_Profit(p, m, s, 1, 5);
}
