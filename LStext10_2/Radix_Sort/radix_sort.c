/*
 *Name:RADIX SORT
 *Time: 2017.9.2
 *Author: LS
 *UPDATE:2017.11.26,Add some comments.
 */

/*
Radix sort complexity is O(wn) for n keys which are integers of word size w.

The Radix Sort is Stability.

The Worst case space complexity is O(n + k) auxiliary.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//
#define RADIX_10 10
//unsigned int 类型表示数范围为0-4294967295，最多是十位数字
#define KEYNUM_31 10						

int randInt(int N)						//随机生成[0:N-1]之间的整数
{
        int randNum;

        srand((unsigned)time(NULL));
        randNum = rand()%N;

        return randNum;

}

void swap(int *a, int *b)					//交换*a和*b的值
{
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
}

int rand_seq3(int A[], int N)					//生成N个[0:N-1]之间的整数，存在数组A中
{
        int i,j;

        for(i=0; i<N; i++)					//初始化数组A，使A[i]=i
                A[i] = i;

        for(i=1; i<N; i++)					//交换A[i]和A[randInt(i)],randInt(i)是[0:i-1]之间的随机数
                swap(&A[i], &A[randInt(i)]);		

        return 0;
}

void printArray(int A[], int N)					//打印数组A
{
	int i;
	for(i = 0; i < N; i++)
		printf("%d\t",A[i]);
	printf("\n");
}

int getNumOfPos(int num, int pos)				//返回num的第pos位数字，pos从1开始
{
	int i;
	int temp = 1;
	for(i = 1; i < pos; i++)
		temp *= 10;

	return (num/temp)%10;
}

void radixSort(int A[], int N)					//基数排序数组A，数组长度为N
{
	int i, j, k;
	int pos, index, numOfBit;
	int *bucket[RADIX_10];					//建立0-9之间的桶

	for(i = 0; i < RADIX_10; i++)				//建立基数排序桶，bucket[i][0]表示桶中数据个数，初始化为0
	{
		bucket[i] = (int *)malloc(sizeof(int) * (N + 1));
		bucket[i][0] = 0;
	}

	for(pos = 1; pos <= KEYNUM_31; pos++)			//基数排序核心部分，依次按数据位pos排序
	{
		for(i = 0; i < N; i++)				//将数组中数据依次按照pos放入相应桶中
		{
			numOfBit = getNumOfPos(A[i],pos);
			index = ++bucket[numOfBit][0];
			bucket[numOfBit][index] = A[i];	
		}

		for(i = 0, j = 0; i < RADIX_10; i++)		//将桶中数据取出放入数组中
		{
			for(k = 1; k <= bucket[i][0]; k++)
				A[j++] = bucket[i][k];
			bucket[i][0] = 0;
		}
		
		//printArray(pArray, N);
	}
}

int main()
{	
	int N = 1000000;					//设置数组大小为1,000,000
	int A[N];
	
	rand_seq3(A, N);					//随机生成数组A
	printArray(A, N);
	radixSort(A, N);
	printArray(A, N);
}

