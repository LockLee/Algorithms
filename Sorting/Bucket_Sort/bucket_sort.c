#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

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
	int N = 100;
	int MaxN = 1000;
	
	int A[N];
	

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

void insert_sort(int X, ptrNode *pB)
{
	ptrNode p,prev,ptmp;
	p = NULL;
	prev = NULL;
	ptmp = NULL;
	
	ptmp = (ptrNode)malloc(sizeof(Node));
	if(ptmp == NULL)
	{
		printf("Out of Space!\n");
		exit(1) ;
	}
	ptmp->value = X;
	ptmp->next = NULL;
	
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

