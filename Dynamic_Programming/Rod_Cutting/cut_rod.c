#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Bottom_Up_Cut_Rod(int p[], int n)
{
	int i, j;

	int q;

	int r[n + 1];
	int s[n + 1];
	
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
	
	printf("An optimal solution is:");
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
	
	for(i = 1; i <=10; i++)
		Bottom_Up_Cut_Rod(p, i);
	
}
