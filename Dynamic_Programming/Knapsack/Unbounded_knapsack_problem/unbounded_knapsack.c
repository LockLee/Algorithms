#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
        if(a > b)
                return a;
        else
                return b;
}

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

void knapsack_complete2(int v[], int w[], int length, int W)
{
        int i, j, k;
        int cLen = length + 1;
        int fW = W + 1;
        int f[fW];

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

