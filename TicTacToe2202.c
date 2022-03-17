#include <stdio.h>
#include <stdlib.h>

void initBoard(char board[][3])
{
	int i, j;
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void disp_board(char board[3][3])
{
	int i;
	
	for(i = 0; i < 3; i++)
	{
		printf("---|---|---|\n");
		printf(" %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
		printf("---|---|---\n");
	}
	
	printf("---|---|---|\n");
}

int main(void)
{
	char board[3][3];
	int player;
	int x, y;
	int count = 0;
	int i = 0;
	int j, k;
	
	initBoard(board);
	
	while (1)
	{
		disp_board(board);
		
		printf("좌표 입력 : ");
		scanf("%d %d", &x, &y);
		
		if (board[x][y] == ' ')
		{
			board[x][y] = 'O';
			
			count++;
		}
		else
		{
			printf("다시 입력하세요.\n");
			
			continue;
		}
		
		for (j = 0; j < 3; j++)
		{
			if (count == 9)
			{
				disp_board(board);
				printf("게임 종료!");
				
				return 0;
			}
			if (board[i][j] == ' ')
			{
				board[i][j] = 'X';
				
				count++;
				
				break;
			}
			if (j == 2)
			{
				i++;
				j = -1;
			}
		}
	}
	
	return 0;
}
