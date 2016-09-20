/*
 * NAME:THE MAX-SUBARRAY PROBLEM BY DIVIDE-AND-CONQUER(	O(nlgn))
 * TIME:2016.9.18
 * AUTHOR:LS
 */

#include <stdio.h>
#include <limits.h>                            		 //该头文件定义了int类型的最大值INT_MAX
#include <stdlib.h>					//该头文件声明了malloc()和free()函数

int *maxMidSubarray(int A[],int low,int mid,int high);
int *maximumSubarray(int A[],int low,int high);		//函数声明

int main()
{
        int i, n;
        n = 0;
        int *max;
        printf("Please input the array numbers:");
        scanf("%d",&n);                         	//输入数组大小
        int A[n];
        printf("Please input %d numbers:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }                                       	//初始化数组
        max = maximumSubarray(A,0,n-1);              	//调用求最大子数列maximumSubarray()函数
        printf("The Max Sum is %d !From %d to %d !\n",*max,*(max + 1),*(max + 2));	//打印输出结果
	free(max);					//free()释放malloc()函数动态分配的内存空间

}


int *maxMidSubarray(int A[],int low,int mid,int high)	//该函数求最大子数列跨越了中点
{
	int *M;
	M =(int *)malloc(sizeof(int)*3);		//动态分配三个int大小的内存空间，并由M指针指向
    	int leftSum,rightSum,sum;			
	int i,j;
	leftSum = rightSum = INT_MIN;			//初始化左右最大和为int类型最小值
	sum = 0;					//初始化sum等于0
	for(i = mid;i >= low;i--)			//该循环求左半边和的最大值
	{
		sum += A[i];
		if(sum > leftSum)
		{
			leftSum = sum;
			*(M + 1) = i;			//保存左位置
		}	
	}						
	sum = 0;	
	for(j = mid + 1;j <= high;j++)			//求右半边和的最大值
	{
		sum += A[j];
		if(sum > rightSum)
		{
			rightSum = sum;
			*(M + 2) = j;			//保存右半边位置
		}		
	}						
	*M = leftSum + rightSum;			//保存左半边和右半边最大值的和
	//*(M + 1) = i;
	//*(M + 2) = j;
	return M;
}           

int *maximumSubarray(int A[],int low,int high) 
{
	int mid;
	mid = (low + high)/2;
	int *l,*r,*c;
	int *one,*leftMax,*rightMax,*crossMax;
	one =(int *)malloc(sizeof(int)*3);		//动态分配内存空间，用来记录递归函数返回值	
	leftMax = (int *)malloc(sizeof(int)*3);
	rightMax = (int *)malloc(sizeof(int)*3);
	crossMax = (int *)malloc(sizeof(int)*3);
	if(low == high)					//只有一个数的基准情况
	{
		*one = A[low];
		*(one + 1) = low;
		*(one + 2) = high;
		free(leftMax);free(rightMax);free(crossMax);	
		return one;				//释放其他分配的内存空间，并返回one指针
	}
	else
	{
		l = maximumSubarray(A,low,mid);						//递归调用，求左半边的最大子数列
		*leftMax = *l;*(leftMax + 1) = *(l + 1);*(leftMax + 2) = *(l + 2);	//将返回信息复制给leftMax指针指向的内存空间
		free(l);								//释放l指针指向的内存空间
		r = maximumSubarray(A,mid + 1,high);					//类似以上
		*rightMax = *r;*(rightMax + 1) = *(r + 1);*(rightMax + 2) = *(r + 2);
		free(r);
		c = maxMidSubarray(A,low,mid,high);					//求跨越早点的最大子数列
		*crossMax = *c;*(crossMax + 1) = *(c + 1);*(crossMax + 2) = *(c + 2);
		free(c);
	}
	if(*leftMax >= *rightMax && *leftMax >= *crossMax)				//分别比较左半边，右半边，跨越中点的最大值并返回，释放其他内存空间
	{
		free(one);free(rightMax);free(crossMax);
		return leftMax;
	}
	else if(*rightMax >= *leftMax && *rightMax >= *crossMax)
	{
		free(one);free(leftMax);free(crossMax);
		return rightMax;
	}
	else
	{
		free(one);free(leftMax);free(rightMax);
		return crossMax;
	}
}                
