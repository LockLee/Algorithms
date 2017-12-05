/*
 *NAME:CHESSBOARD-COVERAGE(O(n2))
 *TIME:2017.12.5
 *AUTHOR:LS
 */

/*
PROBLEM:
  Given a n by n board where n is of form 2k where k >= 1 (Basically n is a power of 2 with
  minimum value as 2). The board has one missing cell (of size 1 x 1). Fill the board using 
  L shaped tiles. A L shaped tile is a 2 x 2 square with one cell of size 1×1 missing.
  
INPUT: A n by n square board, with one of the 1 by 1 square missing, where n = 2k for some k >= 1.
OUTPUT: A tiling of the board using a tromino, a three square tile obtained by deleting the upper 
        right 1 by 1 corner from a 2 by 2 square.

*/
#include <stdio.h>
#include <stdlib.h>

int BOARD_SZ = 8;
int tile = 1;
//二维数组Board[size][size]表示一个棋盘， Board[0][0]是棋盘的左上角方格。其中，size = 2^k。
//为了在递归处理的过程中使用同一个棋盘，将数组Board设为全局变量.
int board[100][100];


//子棋盘：在棋盘数组Board[size][size]中，由子棋盘左上角的下标 tr、tc 和棋盘边长 size 表示；
//特殊方格：用Board[dr][dc]表示，dr和dc是该特殊方格在棋盘数组Board中的下标；
//将所有L型骨牌从1开始连续编号，用一个全局整型变量 tile 表示，其初始值为1。
/*
算法的输入参数是：
     tr:棋盘左上角方格的行号 
     tc:棋盘左上角方格的列号 
     dr:特殊方格所在的行号 
     dc:特殊方格所在的列号 
     size:size= 2^k ,棋盘规格为 2^k * 2^k
*/
void chess_board(int tr, int tc, int dr, int dc, int size)
{
	//棋盘只有一个方格且是特殊方格
	if(size == 1)
		return;
	
	// L型骨牌号
        int t = tile++;
	// 划分棋盘
        int sz = size / 2;
	
	//left up
	// 特殊方格在左上角子棋盘中
	if(dr < tr+sz && dc < tc+sz)
		//递归处理子棋盘
		chess_board(tr, tc, dr, dc, sz);
	// 用 t 号 L 型骨牌覆盖右下角，再递归处理子棋盘
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

//打印棋盘
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
