#include <stdio.h>
#include <stdlib.h>

void FindMinCoin(int money, int coin[], int n)
{
	int coinNum[money + 1];
	int coinValue[money + 1];
	
	int minNum = 0;
	int usedMoney = 0;

	int i, j;	

	coinNum[0] = 0;
	
	for(i = 1; i <= money; i++)
	{
		minNum = i;
		usedMoney = 0;
	
		for(j = 0; j < n; j++)
		{
			if(i >= coin[j])
			{
				if((coinNum[i - coin[j]] + 1 < minNum) && (i == coin[j] || coinValue[i - coin[j]] != 0))
				{
					minNum = coinNum[i - coin[j]] + 1;
					usedMoney = coin[j];
				}
			}
			coinNum[i] = minNum;
			coinValue[i] = usedMoney; 
		}
	}
	
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
