#include <stdio.h>
#include <string.h>
#include <Windows.h>

// Console defines
#define CONSOLE_WIDTH 238
#define CONSOLE_HEIGHT 66

// Board defines
#define BOARD_SIZE 63

#define X_OFFSET ((CONSOLE_WIDTH >> 2) - 2)
#define Y_OFFSET 3

// Inputs
#define GetKeyDown(keyCode) GetAsyncKeyState(keyCode) & 0x8000
#define GetKey(keyCode) GetAsyncKeyState(keyCode) & 0x8001
#define GetKeyUp(keyCode) GetAsyncKeyState(keyCode) & 0x0001

// Global variables
unsigned char screenIndex;

HANDLE screen[2];

// Tic Tac Toe games
int cursorPositionX;
int cursorPositionY;
char winner;
char board[BOARD_SIZE * BOARD_SIZE];

// Flags
unsigned char quitEvent;
unsigned char oTurn;
unsigned char win;

// Functions
void Init();
void Update();
void Render();
void Quit();

void CheckQuitProcess();

void MoveCursor();
void MarkInBoard();

char CheckWinner(char player);

void DrawBoard();
void DrawCursor();
void DrawWinner();

void ScreenFlipping();
void ScreenClear();
void ScreenPrint(unsigned short x, unsigned short y, char* message);

int main(void)
{
	Init();
	
	while (!quitEvent)
	{
		Update();
		Sleep(10);
	}
	
	Quit();
	
	return 0;
}

void Init()
{
	// Full screen
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	
	// Setup console
	system("title Double Buffering");
	
	// Screen setup
	CONSOLE_CURSOR_INFO consoleCursorInfo;
		
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
		
	screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
	SetConsoleCursorInfo(screen[0], &consoleCursorInfo);
	SetConsoleCursorInfo(screen[1], &consoleCursorInfo);
	
	// Initialize global variables
	memset(board, 0, sizeof(board));
}

void Update()
{
	CheckQuitProcess();
	ScreenClear();
	MoveCursor();
	MarkInBoard();
	Render();
	ScreenFlipping();
}

void Render()
{
	DrawBoard();
	DrawCursor();
	DrawWinner();
}

void Quit()
{
	CloseHandle(screen[0]);
	CloseHandle(screen[1]);
}

void CheckQuitProcess()
{
	if (GetKeyDown(27))
	{
		quitEvent = 1;
	}
}

void MoveCursor()
{
	if ((GetKeyDown('W') || GetKeyDown('w')) && cursorPositionY - 1 >= 0)
	{
		cursorPositionY--;
	}
	if ((GetKeyDown('A') || GetKeyDown('a')) && cursorPositionX - 1 >= 0)
	{
		cursorPositionX--;
	}
	if ((GetKeyDown('S') || GetKeyDown('s')) && cursorPositionY + 1 < BOARD_SIZE)
	{
		cursorPositionY++;
	}
	if ((GetKeyDown('D') || GetKeyDown('d')) && cursorPositionX + 1 < BOARD_SIZE)
	{
		cursorPositionX++;
	}
}

void MarkInBoard()
{
	if (GetKeyDown(32) && board[cursorPositionX + cursorPositionY * BOARD_SIZE] == 0)
	{
		board[cursorPositionX + cursorPositionY * BOARD_SIZE] = oTurn ? 'O' : 'X';
		
		winner = CheckWinner(oTurn ? 'O' : 'X');
		
		if (winner == 0)
		{
			oTurn = !oTurn;	
			
			return;
		}
		
		win = 1;
	}
}

char CheckWinner(char player)
{
	int x;
	int y;
	
	for (y = 0; y < BOARD_SIZE - 4; y++)
	{
		for (x = 0; x < BOARD_SIZE - 4; x++)
		{
			if ((board[x + y * BOARD_SIZE] == player && board[x + 1 + y * BOARD_SIZE] == player && board[x + 2 + y * BOARD_SIZE] == player && board[x + 3 + y * BOARD_SIZE] == player && board[x + 4 + y * BOARD_SIZE] == player) ||
				(board[x + (y + 1) * BOARD_SIZE] == player && board[x + 1 + (y + 1) * BOARD_SIZE] == player && board[x + 2 + (y + 1) * BOARD_SIZE] == player && board[x + 3 + (y + 1) * BOARD_SIZE] == player && board[x + 4 + (y + 1) * BOARD_SIZE] == player) ||
				(board[x + (y + 2) * BOARD_SIZE] == player && board[x + 1 + (y + 2) * BOARD_SIZE] == player && board[x + 2 + (y + 2) * BOARD_SIZE] == player && board[x + 3 + (y + 2) * BOARD_SIZE] == player && board[x + 4 + (y + 2) * BOARD_SIZE] == player) ||
				(board[x + y * BOARD_SIZE] == player && board[x + (y + 1) * BOARD_SIZE] == player && board[x + (y + 2) * BOARD_SIZE] == player && board[x + (y + 3) * BOARD_SIZE] == player && board[x + (y + 4) * BOARD_SIZE] == player) ||
				(board[x + 1 + y * BOARD_SIZE] == player && board[x + 1 + (y + 1) * BOARD_SIZE] == player && board[x + 1 + (y + 2) * BOARD_SIZE] == player && board[x + 1 + (y + 3) * BOARD_SIZE] == player && board[x + 1 + (y + 4) * BOARD_SIZE] == player) ||
				(board[x + 2 + y * BOARD_SIZE] == player && board[x + 2 + (y + 1) * BOARD_SIZE] == player && board[x + 2 + (y + 2) * BOARD_SIZE] == player && board[x + 2 + (y + 3) * BOARD_SIZE] == player && board[x + 2 + (y + 4) * BOARD_SIZE] == player) ||
				(board[x + y * BOARD_SIZE] == player && board[x + 1 + (y + 1) * BOARD_SIZE] == player && board[x + 2 + (y + 2) * BOARD_SIZE] == player && board[x + 3 + (y + 3) * BOARD_SIZE] == player && board[x + 4 + (y + 4) * BOARD_SIZE] == player) ||
				(board[x + 4 + y * BOARD_SIZE] == player && board[x + 3 + (y + 1) * BOARD_SIZE] == player && board[x + 2 + (y + 2) * BOARD_SIZE] == player && board[x + 1 + (y + 3) * BOARD_SIZE] == player && board[x + (y + 4) * BOARD_SIZE] == player))
			{
				return player;
			}
		}
	}
	
	return 0;
}

void DrawBoard()
{
	int x;
	int y;
	
	for (y = -1; y <= BOARD_SIZE; y++)
	{
		for (x = -1; x <= BOARD_SIZE; x++)
		{
			if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
			{
				char temp[3];
				
				sprintf(temp, "%c", board[x + y * BOARD_SIZE]);
				ScreenPrint(x * 2 + X_OFFSET, y + Y_OFFSET, temp);
			}
			else
			{
				ScreenPrint(x * 2 + X_OFFSET, y + Y_OFFSET, "бс");
			}
		}
	}
}

void DrawCursor()
{
	ScreenPrint(cursorPositionX * 2 + X_OFFSET, cursorPositionY + Y_OFFSET, "б▌");
}

void DrawWinner()
{
	char temp[7];
	
	sprintf(temp, "%c Won!", winner);
	ScreenPrint((CONSOLE_WIDTH >> 1) - 3, 0, temp);
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(screen[screenIndex]);
	
	screenIndex = !screenIndex;
}

void ScreenClear()
{
	COORD coord = { 0, 0 };
	DWORD dw;
	
	FillConsoleOutputCharacter(screen[screenIndex], ' ', (CONSOLE_WIDTH + 2) * (CONSOLE_HEIGHT + 1), coord, &dw);
}

void ScreenPrint(unsigned short x, unsigned short y, char* message)
{
	COORD position = { x, y };
	DWORD dw;
	
	SetConsoleCursorPosition(screen[screenIndex], position);
	WriteFile(screen[screenIndex], message, strlen(message), &dw, NULL);
}
