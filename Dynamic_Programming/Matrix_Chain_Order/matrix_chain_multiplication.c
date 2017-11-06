/*
 *给定一个n个矩阵的序列⟨A1,A2,A3...An⟩,我们要计算他们的乘积：A1A2A3...An，
 *由于矩阵乘法满足结合律，加括号不会影响结果，但是不同的加括号方法，算法复杂度有很大的差别： 
 *考虑矩阵链：⟨A1,A2,A3⟩，三个矩阵规模分别为10×100、100×5、5×50 
 *如果按((A1A2)A3)方式，需要做10∗100∗5=5000次，再与A3相乘，又需要10∗5∗50=2500，共需要7500次运算： 
 *如果按(A1（A2A3）)方式计算，共需要100∗5∗50+10∗100∗50=75000次标量乘法，具有10倍的差别。
 *可见一个好的加括号方式，对计算效率有很大影响。 
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int m[10][10] = {0};
int s[10][10] = {0};

#define min(a, b) (a>b) ? a : b

/*
 *计算矩阵链需要的最少乘法数
 *
 *参数：p 矩阵链
 *     n 矩阵个数
 *
 */
void matrix_chain_order(int p[], int n)
{
	int i, j, L, k;
	int q;

	for(i = 1; i <= n; i++)
	{
		m[i][i] = 0;
	}

	//依次计算矩阵为 2 、3、... 需要的最小乘法数
	for(L = 2; L <= n; L++)
	{
		for(i = 1; i <= n-L+1; i++)
		{
			j = i + L - 1;
			m[i][j] = INT_MAX;
			for(k = i; k < j; k++)
			{
				//最优的代价 q 保存在 m[i][j] 中
				//最优大划分位置 k 保存在 s[i][j] 中
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if(q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}			
			}
		}
	}
}

/*
 *打印输出最优划分方案
 */
void Print_Order(int m[][10], int i, int j)
{
	if(i == j)
		printf("A%d",i);
	else
	{
		printf("(");
		Print_Order(m, i, s[i][j]);
		Print_Order(m, s[i][j]+1, j);
		printf(")");
	}	
}

int main()
{
	int i, j;
	int count = 0;

	int p[] = {5, 10, 3, 12, 5, 50, 6};
	int length = sizeof(p)/sizeof(p[0]) - 1;
	
	matrix_chain_order(p, length);

	printf("Min Mul:%d\n", m[1][length]);
        Print_Order(m, 1, length);
	printf("\n");
/*
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			printf("%d   ",m[i][j]);
		}
		printf("\n");
	}

	printf("\n");
        for(i = 0; i < 10; i++)
        {
                for(j = 0; j < 10; j++)
                {
                        printf("%d   ",s[i][j]);
                }
                printf("\n");
        }
*/	
	
}
