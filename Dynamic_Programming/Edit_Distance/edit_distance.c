#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(a, b, c)
{
	int tmp;

	if(a<=b)
		tmp = a;
	else 
		tmp = b;
	if(tmp <= c)
		return tmp;
	else
		return c;	
}

int edit_distance(char *a, char *b)
{
	int i, j, k;
	int old, tmp;

	int lena = strlen(a);
	int lenb = strlen(b);

	int d[lenb + 1];

	for(i = 0; i <= lenb; i++)
	{
		d[i] = i;
	}
	
	for(i = 1; i <= lena; i++)
	{
		old = i -1;
		d[0] = i;
		for(j = 1; j <= lenb; j++)
		{
			tmp = d[j];
			if(a[i-1] == b[j-1])
				d[j] = old;
			else
				d[j] = min(old + 1, d[j -1] + 1, d[j] + 1);
			
			old = tmp;
		}

	}

	return d[lenb];
}

int main()
{
	char a[] = "sailn";
	char b[] = "failing";

	printf("%d\n",edit_distance(a, b));
}

