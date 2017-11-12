#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LCS(char *a, char *b)
{
	int i, j;
	int maxlcs;

	int lena = strlen(a);
	int lenb = strlen(b);
	//printf("%d\n",lena);
	//printf("%d\n",lenb);

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
	//printf("%d\n",i);
	//printf("%d\n",j);

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
	//printf("Done!\n");
	
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
