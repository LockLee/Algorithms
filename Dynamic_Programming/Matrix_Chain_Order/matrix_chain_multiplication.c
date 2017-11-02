#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int m[10][10] = {0};
int s[10][10] = {0};

#define min(a, b) (a>b) ? a : b

void matrix_chain_order(int p[], int n)
{
	int i, j, L, k;
	int q;

	for(i = 1; i <= n; i++)
	{
		m[i][i] = 0;
	}

	for(L = 2; L <= n; L++)
	{
		for(i = 1; i <= n-L+1; i++)
		{
			j = i + L - 1;
			m[i][j] = INT_MAX;
			for(k = i; k < j; k++)
			{
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
