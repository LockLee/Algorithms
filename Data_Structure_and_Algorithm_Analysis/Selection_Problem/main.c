/*
利用堆排序的思想来查询数组中第K大元素。
首先提取子数组array[0...K-1]并构造小顶堆，然后把剩下子数组array[K...N-1]中的
所有元素与堆顶元素array[0]进行比较，若大于堆顶元素，则进行交换并重新构造子数组
array[0...K-1]使其满足小顶堆的要求。这样的话，最后子数组array[0...K-1]就是N个
元素中的前K个最大元素，堆顶array[0]就是N个元素中的第K大元素。
时间复杂度：O(NlgN)
具体实现代码如下：
*/
#include <stdio.h>
#include <stdlib.h>
#include "binheap.h" 
                                                        
int nums[] = {7,9,8,0,1,3,5,2,4};       

int select(int k, int length, int *nums);

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

int select(int k, int length, int *nums){
	PriorityQueue H;
	H = BuildHeap(nums, k);
	
	for(int i = k;i < length; i++){
		int min = FindMin(H);
		if(nums[i] > min){
			H->Elements[1] = nums[i];
			PercolateDown(1, H);
		}
	}
	
	int KthNum = FindMin(H);
	Destroy(H);
	return KthNum;
}
