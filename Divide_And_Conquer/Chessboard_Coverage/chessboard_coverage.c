#include <stdio.h>
#include <stdlib.h>

int BOARD_SZ = 8;
int tile = 1;
int board[100][100];

void chess_board(int tr, int tc, int dr, int dc, int size)
{
	if(size == 1)
		return;
	
        int t = tile++;
        int sz = size / 2;
	
	//left up
	if(dr < tr+sz && dc < tc+sz)
		chess_board(tr, tc, dr, dc, sz);
	else
	{
		board[tr+sz-1][tc+sz-1] = t;
		chess_board(tr, tc, tr+sz-1, tc+sz-1, sz);
	}
	
	//right up
	if(dr < tr+sz && dc >= tc+sz)
		chess_board(tr, tc+sz, dr, dc, sz);
	else
	{
		board[tr+sz-1][tc+sz]  = t;
		chess_board(tr, tc+sz, tr+sz-1, tc+sz, sz);
	}

	//left down
	if(dr >= tr+sz && dc < tc+sz)
		chess_board(tr+sz, tc, dr, dc, sz);
	else
	{
		board[tr+sz][tc+sz-1] = t;
		chess_board(tr+sz, tc, tr+sz, tc+sz-1, sz);
	}
	
	//right down
	if(dr >= tr+sz && dc >= tc+sz)
		chess_board(tr+sz, tc+sz, dr, dc, sz);
	else
	{
		board[tr+sz][tc+sz] = t;
		chess_board(tr+sz, tc+sz, tr+sz, tc+sz, sz);
	}
} 

void print_chess_board()  
{    
	int i, j;

	for(i = 0; i < BOARD_SZ; i++)
	{  
		for(j = 0; j < BOARD_SZ; j++)
		{  
            		printf("%d   ",board[i][j]);  
        	}  
        	printf("\n"); 
	}  
}  
  

int main()  
{  
    chess_board(0, 0, 2, 6, BOARD_SZ);  
    print_chess_board();  
    return 0;  
}  
