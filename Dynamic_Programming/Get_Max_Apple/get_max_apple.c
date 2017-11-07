#include <stdio.h>
#include <stdlib.h>

int mx[11][11] = {0};
int s[11][11] = {0};

void max_apple(int a[][4], int n, int m)
{
	int i, j, k;
	int q = 0;
	
	for(i = 1; i <= n; i++)
	{
		mx[i][1] = a[i-1][1-1] + mx[i-1][1];
		s[i][1] = 1;
	}
	for(i = 1; i <= m; i++)
	{
		mx[1][i] = a[1-1][i-1] + mx[1][i-1];
		s[1][i] = -1;
	}

	for(i = 2; i <= n; i++)
	{
		for(j = 2; j <= m; j++)
		{
			if(mx[i-1][j] > mx[i][j-1])
			{
				mx[i][j] = mx[i-1][j] + a[i-1][j-1];
				s[i][j] = 1;
			}	
			else
			{
				mx[i][j] = mx[i][j-1] + a[i-1][j-1];
				s[i][j] = -1;
			}
		}
	}

	printf("Max Apple Is:%d\n",mx[n][m]);

/*	
	for(i = 0; i < 11; i++)
	{
		for(j = 0; j < 11; j++)
			printf("%d   ",mx[i][j]);
		printf("\n");
	}
*/
}

void print_path(int n, int m)
{
	int i, j;
	i = n;
	j = m;
	
	if(i == 1 && j == 1)
		printf("a[%d][%d]   ",i-1,j-1);

	else if(s[i][j] == 1)
	{
		print_path(n-1,m);
		printf("a[%d][%d]   ", i-1, j-1);
	}
	else
	{
		print_path(n,m-1);
		printf("a[%d][%d]   ", i-1, j-1);
	}

}


int main()
{
	int a[3][4] = {{4, 3, 7, 6}, {5, 2, 4,3}, {3, 7, 2, 5}};
	
	max_apple(a, 3, 4);
	print_path(3,4);

	printf("\n");
}
