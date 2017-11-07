/*
问题描述：
给予不同面值的硬币若干种种（每种硬币个数无限多），用若干种硬币组合为某种面额的钱，使硬币的的个数最少。
假设要用50、20、10、5、1（元）找出87元来，任何人都可以简单地得出：1张50、1张20、1张10、1张5和2张1元就可以满足。

动态规划解法：
对于数额n，可做如下考虑：
1）如果n = 1，则用1个1元来找零，这就是最优解；
2）如果n > 1，则对于每个可能的值i，分别找出i元和n-i元来。
*/

#include <stdio.h>
#include <stdlib.h>

/*
 *计算最少硬币找零数
 *
 *参数 money：需要找零的钱
 *      coin：硬币面值
 *         n：硬币种类个数
 *
 *打印输出最少硬币找零数和找零方案
 */
void FindMinCoin(int money, int coin[], int n)
{
	//存储1...money找零最少需要的硬币的个数
	int coinNum[money + 1];
	////最后加入的硬币，方便后面输出是哪几个硬币
	int coinValue[money + 1];
	
	int minNum = 0;
	int usedMoney = 0;

	int i, j;	
	//初始化0元硬币需要0个硬币
	coinNum[0] = 0;
	
	for(i = 1; i <= money; i++)
	{
		//i面值的钱找零需要的最少硬币个数  
		minNum = i;
		//这次找零，在原来的基础上需要的硬币
		usedMoney = 0;
	
		for(j = 0; j < n; j++)
		{
			//如果需要找零的钱大于这个硬币的面值 
			if(i >= coin[j])
			{
				//所需硬币个数减少了,并且i要能被找开
				//i要能被找开有两种可能，i能被直接找开或者i能被coinValue[i-coin[j]]和coin[j]找开
                		//coinValue[i-coin[j]] == 0 表示coinValue[i-coin[j]]不能被找开
				if((coinNum[i - coin[j]] + 1 < minNum) && (i == coin[j] || coinValue[i - coin[j]] != 0))
				{
					//更新找零需要的最少硬币数和最后加入的硬币
					minNum = coinNum[i - coin[j]] + 1;
					usedMoney = coin[j];
				}
			}
			coinNum[i] = minNum;
			coinValue[i] = usedMoney; 
		}
	}
	
	//输出结果
	if(coinValue[money] == 0)
		printf("The money %d can't change.",money);
	else
	{
		printf("Change %d Min Coin Is %d\n:",money,coinNum[money]);
	
		printf("The Money Is:");
		while(money > 0)
		{
			printf("%d   ",coinValue[money]);
			money -= coinValue[money];
		}
	}
	printf("\n");
}

int main()  
{  
	int Money=6;  
	int coin[]={2,3,5};  
	int length = sizeof(coin)/sizeof(coin[0]);
	
	FindMinCoin(Money,coin,length);  
  
}  
