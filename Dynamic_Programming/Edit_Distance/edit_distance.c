/*
给定 2 个字符串 a, b. 编辑距离是将 a 转换为 b 的最少操作次数，操作只允许如下 3 种：

  1. 插入一个字符，例如：fj -> fxj 
  2. 删除一个字符，例如：fxj -> fj
  3. 替换一个字符，例如：jxj -> fyj

动态规划解法：时间复杂度O(mn),空间复杂度O(m)
*/

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

