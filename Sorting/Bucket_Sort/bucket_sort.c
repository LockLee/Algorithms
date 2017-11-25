/*
 *NAME:BUCKET-SORT
 *TIME:2017.11.25
 *AUTHOR:LS
 */

/*
The Best-case performance O(n).
 
The Worst-case performance O(n2).

The Average performance O(n).

The Bucket Sort is Stability.

The Worst-case space complexity О(n) total, O(n) auxiliary.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

//定义结构体节点类型
struct node;
typedef struct node Node;
typedef struct node *ptrNode;
typedef ptrNode List;
typedef ptrNode Position;

struct node
{
	int value;
	struct node *next;
};

void insert_sort(int X, ptrNode *pB);
void bucket_sort(int A[], int n, int maxn);

int main()
{
	int i, j;
	//定义待排序数组大小
	int N = 100;
	//定义待排序数组元素最大值
	int MaxN = 1000;
	
	int A[N];

	//随机生成 N 个数
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++)
		A[i] = rand()%(MaxN+1);

        for(i = 0; i < N; i++)
                printf("%d   ",A[i]);
	printf("\n\n\n");
	
	bucket_sort(A, N, MaxN);
	
        for(i = 0; i < N; i++)
                printf("%d   ",A[i]);
	printf("\n");

}

/*
 *将元素依次放入相应桶中，并按照非递减序排列
 *
 *函数参数 X：需要放入相应桶中的元素值
 *      *pB：元素放入对应桶的头指针
 *
 */
void insert_sort(int X, ptrNode *pB)
{
	ptrNode p,prev,ptmp;
	p = NULL;
	prev = NULL;
	ptmp = NULL;

	//申请一个节点空间
	ptmp = (ptrNode)malloc(sizeof(Node));
	if(ptmp == NULL)
	{
		printf("Out of Space!\n");
		exit(1) ;
	}
	ptmp->value = X;
	ptmp->next = NULL;
	
	//如果该桶为空，直接将该元素值放入桶中
	//否则，按照非递减序放入该桶中
	if(*pB == NULL)
		*pB = ptmp;
	else
	{
		p = *pB;
		prev = p;
		while(p != NULL && p->value <= X)
		{
			prev = p;
			p = p->next;
		}
		//此行很关键
		//主要没有头节点，需要判断是不是将元素值插在第一个位置
		if(prev == *pB && X < prev->value)
		{
			ptmp->next = prev;
			*pB = ptmp;
		}
		else
		{
			ptmp->next = prev->next;
			prev->next = ptmp;
		}
	}	
}

/*
 *桶排序主要例程
 *
 *参数 A[]：待排序数组
 *       n：数组大小
 *    maxn：数组中最大元素值
 *
 */
void bucket_sort(int A[], int n, int maxn)
{
	int i, j, k;
	ptrNode pnext,ptmp;	
	pnext = NULL;
	ptmp = NULL;

	k = maxn/n;
	ptrNode Bucket[n+1];
	
	for(j = 0; j <= n; j++)
		Bucket[j] = NULL;
	
	//将数组中元素依次放入相应桶中
	for(i = 0; i < n; i++)
	{
		insert_sort(A[i], &Bucket[A[i]/k]);
	}

/*
	for(j = 0; j <= n; j++)
	{
		if(Bucket[j])
		{
			ptmp = Bucket[j];
			while(ptmp)
			{
				printf("%d\n",ptmp->value);
				ptmp = ptmp->next;
			}
		}
	}
*/
	//将桶中元素依次取出
	for(i = 0,j = 0; j <= n; j++)
	{
		if(Bucket[j] != NULL)
		{
			pnext = Bucket[j];
			while(pnext)
			{
				A[i] = pnext->value;
				ptmp = pnext;
				pnext = pnext->next;		
				free(ptmp);
				i++;
			}
		}
	}

}

