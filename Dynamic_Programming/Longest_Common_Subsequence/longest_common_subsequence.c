/*
In the longest-common-subsequence problem, 
we are given two sequences X = {x1; x2; . . . ; xm} and Y = {y1; y2; . . . ; yn} 
and wish to find a maximumlength common subsequence of X and Y .

1. Optimal substructure of an LCS:
	Let X = {x1; x2; . . . ; xm} and Y = {y1; y2; . . . ; yn} be sequences, and let Z =
	{z1; z2; . . . ; zk} be any LCS of X and Y .
	1. If xm = yn, then zk = xm = yn and Zk-1 is an LCS of Xm=1 and Yn-1.
	2. If xm != yn, then zk != xm implies that Z is an LCS of Xm-1 and Y .
	3. If xm != yn, then zk != yn implies that Z is an LCS of X and Yn-1.

2. Overlapping Subproblems Property:
		  0                        if i = 0 or j = 0
	c[i, j] = c[i-1,j-1] + 1           if i,j > 0 and xi = yj  
	          max(c[i,j-1],c[i-1,j])   if i,j > 0 and xi != yj
		 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LCS(char *a, char *b)
{
	int i, j;
	int maxlcs;

	int lena = strlen(a);
	int lenb = strlen(b);

	int c[lena + 1][lenb + 1];
	
	for(i = 0; i <= lena; i++)
		c[i][0] = 0;
	for(j = 0; j <= lenb; j++)
		c[0][j] = 0;

	for(i = 1; i <= lena; i++)
	{
		for(j = 1; j <= lenb; j++)
		{
			if(a[i-1] == b[j-1])
				c[i][j] = c[i-1][j-1] + 1;
			else if(c[i-1][j] >= c[i][j-1])
				c[i][j] = c[i-1][j];
			else
				c[i][j] = c[i][j-1];
		}
	}

	maxlcs = c[lena][lenb];
	printf("The Max LCS Is: %d\n",maxlcs);
	
	char com_string[maxlcs];
	i = lena;
	j = lenb;

	while(maxlcs > 0)
	{
		if(a[i-1] == b[j-1])
		{
			com_string[--maxlcs] = a[i-1];
			i--;
			j--;
		}
		else if(c[i-1][j] >= c[i][j-1])
		{
			i--;
		}
		else
		{
			j--;
		}
	}
	
	maxlcs = c[lena][lenb];

	printf("A Longest Commom Subsequence Is:\n");
	for(i = 0; i < maxlcs; i++)
		printf("%c   ",com_string[i]);
}

int main()  
{  
    char pStr1[]="akqrshrengxqiyxuloqk";  
    char pStr2[]="tdzbujtlqhecaqgwfzbck";  
    LCS(pStr1,pStr2);  
    printf("\n");  
    return 0;  
}  
