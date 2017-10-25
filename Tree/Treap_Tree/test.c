#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "treap.h"

#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
	int i;
	int N;
	int A[] = {1,2,3,4,5,5,6,7,7,8};
	treapTree T = NULL;	
	
	srand((unsigned)time(NULL));
		
	N = TBL_SIZE(A);
	for(i = 0; i < N; i++)
		T = Insert(T, A[i]);
	
	PrintTree(T, T->value, 0);
	
	T = Delete( T, 6);
	
	PrintTree(T, T->value, 0);
	
	printf("Find 6th : %d\n",FindKth(T, 6)->value);
		
	printf("Less 6 num: %d\n", LessX(T, 6, 0));
		
	return 0;

}
