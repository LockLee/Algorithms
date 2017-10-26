/*
 *Name: Treap_Tree
 *Author: LS
 *Time: 2017.10.25
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "treap.h"

//求数组大小
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
	int i;
	int N;
	int A[] = {1,2,3,4,5,5,6,7,7,8};
	treapTree T = NULL;	
	
	//随机数种子
	srand((unsigned)time(NULL));
		
	//将数组 A 中元素插入Treap 中
	N = TBL_SIZE(A);
	for(i = 0; i < N; i++)
		T = Insert(T, A[i]);
	
	//打印Treap 信息
	PrintTree(T, T->value, 0);
	
	//在Treap 中删除元素 6
	T = Delete( T, 6);
	
	PrintTree(T, T->value, 0);
	
	//找到Treap 中第 6 个元素
	printf("Find 6th : %d\n",FindKth(T, 6)->value);
		
	//计算Treap 中小于 6 的元素个数
	printf("Less 6 num: %d\n", LessX(T, 6, 0));
		
	return 0;

}
