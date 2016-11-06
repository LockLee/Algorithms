/*
 *NAME:HASH MAIN FUNCTION(FOR TEST)
 *TIME:2016.11.06
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

int main()
{
        int i, n, query, tmp;
        n = 0;
        
	HashTable H;	

        printf("Please input the Hash numbers:");
        scanf("%d",&n);                                 //输入数组大小

	H = InitTable(n);
	int A[n];
		
        printf("Please input %d numbers:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }                                               //初始化数组

	for(i = 0;i < n;i++)
	{
		Insert(A[i], H);
	}
	//print detail information
	for(i = 0;i <n;i++)
	{
		query = Find(A[i],H);
		printf("%d	%d	%d",H->TheNodes[query].Value,query,H->TheNodes[query].Info);
		printf("\n");
	}	
	//test Delete()function	
	printf("Please input the delete number:");
	scanf("%d",&tmp);
	Delete(tmp, H);
	//test Find()function
	printf("Please input the find number:");
	scanf("%d",&tmp);
	query = Find(tmp, H);
	printf("%d      %d      %d",H->TheNodes[query].Value,query,H->TheNodes[query].Info);	
	printf("\n");
	
	return 0;
}

