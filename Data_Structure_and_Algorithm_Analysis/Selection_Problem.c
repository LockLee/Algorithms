/*
最近在读《数据结构与算法分析（C语言描述）》，在优先队列（堆）一节中，
作者总结了关于“选择问题——求第k个最大的元素”的几种思路，在此简单总结一下：
第一种
将这N个数读进一个数组中，再通过某种简单的算法，比如冒泡排序、选择排序等，以递减顺序将数组进行排序，
然后返回位置k上的元素。假设使用最简单的排序算法，则运行时间为O(N2)
第二种
这是对第一种算法的简单优化。申请一个大小为k的数组，然后先把前k个元素读入数组并以递减顺序进行排序。
接着，将剩下的元素再逐个读入。当新元素被读到时，如果它小于数组中的第k个元素则忽略，否则将其放到数组中正确的位置上（就是插入排序啊！），
同时将数组中最后一个元素挤出数组。当算法终止时，位于第k个位置上的元素就是最终结果，即第k个最大的元素。 
该算法的平均运行时间为O(N⋅k)，但是最差时间为O(N2)

以下实现第二种算法：
*/

#include <stdio.h>
#include <stdlib.h>
                                                        
int nums[] = {7,9,8,0,1,3,5,2,4};       
 
int select(int k, int length, int nums[]);
void sortK(int k, int kNums[]);
int comp(const void*a,const void*b);              //用来做比较的函数。


int main(){
	int k = 0;
	int length;
	length = sizeof(nums)/sizeof(nums[0]);
	
	printf("Please Input K: (1<=K<=%d)\n",length);
	scanf("%d", &k);


	
	if(length < k){
		printf("The Input of K Error!");
		return 0;
	}
	
	
	int KthNum = select(k, length, nums);
	
	printf("The Kth number of nums is: %d\n", KthNum);
	
	return 0;
}

//返回数组第 K 大元素
int select(int k, int length, int nums[]){
	int kNums[k];
	for(int i = 0; i < k; i++){
		kNums[i] = nums[i];
	}

	//将前K个元素进行递减排序
	qsort(kNums, k, sizeof(int), comp);
	
	//将数组中后 length-k 个元素插入到数组 kNums 中
	for(int i = k; i < length; i++){
		int iNum = nums[i];
		if(iNum > kNums[k-1]){
			int tmpNum;
			for(int j = 0; j < k; j++){
				if(iNum > kNums[j]){
					tmpNum = kNums[j];
					kNums[j] = iNum;
					iNum = tmpNum;
				}
			}
		}
	}
	
	return kNums[k-1];
}

int comp(const void*a,const void*b)  //用来做比较的函数。
{
    return *(int*)b-*(int*)a;
}
