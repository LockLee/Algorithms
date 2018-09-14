#include <stdio.h>
#include <stdlib.h>
                                                        
int nums[] = {7,9,8,0,1,3,5,2,4};       

int Qselect(int k, int left, int right, int *nums);
void swap(int *a,int *b);

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
	
	
	int KthNum = Qselect(k, 0, length-1, nums);
	
	printf("The Kth number of nums is: %d\n", KthNum);
	
	return 0;
}

int Qselect(int k, int left, int right, int *nums){
	int l, r;
	int pivot;
	
	l = left;
	r = right-1;
	pivot = nums[right];

	if(l <= r){
		while(1){
			while(1){
				if(nums[l] > pivot)
					l++;	
				else
					break;
			}
			while(1){
				if(nums[r] < pivot)
					r--;
				else
					break;
			}
			
			if(l < r){
				swap(&nums[l], &nums[r]);
			}
			else
				break;
		}		
	}
	
	if(l+1 == k)
		return pivot;
	else {
		swap(&nums[l], &nums[right]);
		
		if(l+1 < k)
			return Qselect(k, l+1, right, nums);
		else
			return Qselect(k, 0, l-1, nums);
	} 
}

void swap(int *a,int *b)
{
        int tmp;
        tmp = *a;
        *a = *b;
        *b = tmp;
}
