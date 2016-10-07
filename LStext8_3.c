/*
 *NAME:RADIX SORT (O(d(n+k)))
 *TIME:2016.10.6
 *AUTHOR:LS
*/ 


#include <stdio.h>
#include <stdlib.h>

#define MaxDigit 8						//定义待排数的最大位数，也就是说该程序最大只能排8位数
#define Radix 10						//定义基数，也就是十进制数

struct node;
typedef struct node Node;
typedef struct node *ptrNode;

struct headNode;
typedef struct headNode HeadNode;
typedef struct headNode *ptrHeadNode;

struct node{							//定义元数节点
	int value;
	ptrNode next;
};

struct headNode{						//定义桶节点
	ptrNode phead,
		ptail;
};
typedef HeadNode Bucket[Radix];					//定义桶数组


int getDigit(int ,int );
void LSDRadixSort(int* ,int );

int main()
{
        int i, n;
        n = 0;
        printf("Please input the array numbers:");
        scanf("%d",&n);                                         //输入数组大小
        int A[n];
        printf("Please input %d numbers:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }                                                       //初始化数组
        LSDRadixSort(A,n);
	for(i = 0;i < n;i++)
        {
                printf("%d      ",A[i]);
        }
        printf("\n");
	return 0;
}



int getDigit(int X,int D)					//取得X第D位的数值
{
	int d,i;
	for(i = 1;i < D;i++)
	{
		//d = X % 10;
		X = X / Radix;
	}
	d = X % Radix;
	return d;
}

void LSDRadixSort(int *A,int num)				//基数排序，次位优先
{
	int i,D,Di;
	Bucket B;
	ptrNode p,pTmp,List;
	List = NULL;
	for(i = 0;i < Radix;i++)				//初始化每个桶为空链表
		B[i].phead = B[i].ptail = NULL;
	for(i = 0;i < num;i++)					//将原始数据存入List链表中，采用头插法
	{
		pTmp = (ptrNode)malloc(sizeof(Node));
		pTmp->value = A[i];
		pTmp->next = List;
		List = pTmp;	
	}
	for(D = 1;D <= MaxDigit; D++)				//基数排序主部分，对数值X的每一位进行循环
	{
		p = List;
		while(p)					//遍历链表
		{
			Di = getDigit(p->value,D);		//取得第D位数值
			pTmp = p;				//将该节点从List中摘除
			p = p->next;
			pTmp->next = NULL;
			if(B[Di].phead == NULL)			//插入到B[Di]相应的桶尾
				B[Di].phead = B[Di].ptail = pTmp;
			else
			{
				B[Di].ptail->next = pTmp;
				B[Di].ptail = pTmp;
			}			
		}
		List = NULL;
		for(Di = Radix-1;Di >= 0; Di--)			//将每个桶的元素顺序收集入List
		{
			if(B[Di].phead)				//如果桶不空
			{
				B[Di].ptail->next = List;	//整桶插入到List表头
				List = B[Di].phead;
				B[Di].phead = B[Di].ptail = NULL; 	//清空桶
			}			
		}			
	}
	
	for(i = 0; i < num ; i++)				//将List复制到A[],并释放空间
	{
		pTmp = List;
		List = List->next;
		A[i] = pTmp->value;
		free(pTmp);
	}
}

