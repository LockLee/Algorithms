/*
问题描述：输入是由一些字母和单词构成的二维数组，目标是找出字谜中的单词，
这些单词可以是水平、垂直或沿对角线以任何方向放置。找出二维数组中所有的单词
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define DICTSIZE 7                                     //字典内最大单词数
#define WORDSIZE 34                                    //单词最大长度 + 1
#define WORDLEN 4
#define WORDHIGH 4
#define NUMCHARS(a, b) ((a) > (b) ? (a) : (b))


char puzzle[WORDLEN][WORDHIGH] = {
    {'t','h','i','s'},
    {'w','a','t','s'},
    {'o','a','h','g'},
    {'f','g','d','t'}
};                                                                    //字谜数组 
const char * dict[DICTSIZE] = { "this", "two", "otw", "fat", "that", "hello", "good" };       //单词字典
 
void wordExist(int x, int y, int dir, int maxChars, char * retWord);
void wordCopy(const char * str, char * retWord );


int main(void)
{   
	//printf("len = %d",strlen(const dict*));
    char word[WORDSIZE] = {'\0'};
    
    for (int i = 0; i < WORDLEN; i++)
	{
        for (int j = 0; j < WORDHIGH; j++)
		{
            for (int d = 0; d < 8; d++)
			{
                for (int n = 1; n <= NUMCHARS(WORDLEN, WORDHIGH); n++)
				{
					wordExist(i, j, d, n, word);
				}
            }
        }
    }

    system("pause");
    return 0;
}
 
/*
查找是否有单词存在
如果有，将找到的第一个单词写入retWord
查找位置(x, y)，方向dir
*/
void wordExist(int x, int y, int dir, int numChars, char * retWord)
{
    char str[WORDSIZE] = {'\0',};
    int ct = 0;
 
    switch (dir)
    {
	    case 0:        //从左到右
    		for (int i = 0; i < numChars; i++)
    		{
    			str[ct++] = puzzle[x][y];
    			if(y < WORDLEN - 1)
    				y++;
    			else 
    				break;
			}
			str[ct] = '\0';
			if(strlen(str) < numChars)
				break;
        	wordCopy( str,  retWord );
        	break;
        case 1:        //从右到左
    		for (int i = 0; i < numChars; i++)
    		{
    			str[ct++] = puzzle[x][y];
    			if(y > 0)
    				y--;
    			else
    				break;
			}
			str[ct] = '\0';
			if(strlen(str) < numChars)
				break;
        	wordCopy( str,  retWord );
	        break;
        case 2:        //从上到下
    		for (int i = 0; i < numChars; i++)
    		{
    			str[ct++] = puzzle[x][y];
    			if(x < WORDHIGH - 1)
					x++;
				else
					break;
			}
			str[ct] = '\0';
			if(strlen(str) < numChars)
				break;
        	wordCopy( str,  retWord );
            break;
        case 3:        //从下到上
    		for (int i = 0; i < numChars; i++)
    		{
    			str[ct++] = puzzle[x][y];
    			if(x > 0)
					x--;
				else
					break;
			}
			str[ct] = '\0';
			if(strlen(str) < numChars)
				break;
			wordCopy( str,  retWord );
            break;
        case 4:        //从左上到右下
    		for (int i = 0; i < numChars; i++)
    		{
    			str[ct++] = puzzle[x][y];
    			if(x < WORDHIGH - 1 && y < WORDLEN -1)
    			{
					x++;
    				y++;
				}
				else
					break;
				
			}
			str[ct] = '\0';
			if(strlen(str) < numChars)
				break;
        	wordCopy( str,  retWord );
            break;
        case 5:        //从右下到左上
	    	for (int i = 0; i < numChars; i++)
    		{
    			str[ct++] = puzzle[x][y];
    			if(x > 0 && y > 0)
    			{
    				x--;
    				y--;
				}
				else
					break;
			}
			str[ct] = '\0';
			if(strlen(str) < numChars)
				break;
			wordCopy( str,  retWord );
            break;
        case 6:        //从右上到左下
    		for (int i = 0; i < numChars; i++)
    		{
    			str[ct++] = puzzle[x][y];
    			if(x > 0 && y < WORDLEN -1)
				{
					x--;
    				y++;
    			}
    			else
    				break;
			}
			str[ct] = '\0';
			if(strlen(str) < numChars)
				break;
			wordCopy( str,  retWord );
            break;
        case 7:        //从左下到右上
	    	for (int i = 0; i < numChars; i++)
    		{
    			str[ct++] = puzzle[x][y];
    			if(x < WORDHIGH - 1 && y > 0)
				{
					x++;
    				y--;
				}
				else
					break;
			}
			str[ct] = '\0';
			if(strlen(str) < numChars)
				break;
        	wordCopy( str,  retWord );
			break;
        default:
            puts("Direction error.");
        	break;
		}
}

//单词比较并打印 
void wordCopy(const char * str, char * retWord )
{
    for (int j = 0; j < DICTSIZE; j++)
    {
        if (strcmp(str, dict[j]) == 0)
        {
            strcpy(retWord, dict[j]);
            printf("%s\n", retWord);
        }
	}
}
