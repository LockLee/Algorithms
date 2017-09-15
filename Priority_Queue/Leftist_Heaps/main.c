#include <stdio.h>
#include "leftistheap.h"
 
#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )
 
void main()
{
	int i;
	int a[]= {21,8,10,3,14,23,26,17};
	int b[]= {12,33,24,7,18,6,37};
	int alen=LENGTH(a);
	int blen=LENGTH(b);
	Leftist ha,hb;

	ha = hb = NULL;

	printf("== 左倾堆(ha)中依次添加: ");
	for(i=0; i<alen; i++)
	{
		printf("%d ", a[i]);
		ha = InsertLeftist(a[i], ha);
	}
	printf("\n== 左倾堆(ha)的详细信息: \n");
	PrintLeftist(ha);

 
	printf("\n== 左倾堆(hb)中依次添加: ");
	for(i=0; i<blen; i++)
	{
		printf("%d ", b[i]);
		hb = InsertLeftist(b[i], hb);
	}
	printf("\n== 左倾堆(hb)的详细信息: \n");
	PrintLeftist(hb);

	// 将"左倾堆hb"合并到"左倾堆ha"中。
	ha = MergeLeftist(ha, hb);
	printf("\n== 合并ha和hb后的详细信息: \n");
	PrintLeftist(ha);
 
	//
	ha = DeleteMin(ha);
	printf("\n==删除ha的最小元素后的详细信息：\n");
	PrintLeftist(ha);
	
	// 销毁左倾堆
	DestroyLeftist(ha);
}
