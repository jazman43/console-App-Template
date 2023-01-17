#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <conio.h>


#ifndef UNICODE
#error Please enable UNICODE for your compiler!
#define UNICODE
#define _UNICODE
#endif

//colour enum
	//FG = fore ground
	//BG = back ground
enum COLOUR {
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007,
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,

	//background
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,

};

enum SYMBOL_TYPE {
	//symbols
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};


class WindowInti {
public:
	WindowInti();
	~WindowInti();

	void Update();

	void DrawTextWString(int x, int y, std::wstring text, short color = FG_WHITE);

	void ClearConsole();
	
	std::string DrawUserInput(short x, short y, WORD color = FG_WHITE);

	void Draw(int x, int y, short symbol = PIXEL_SOLID, short color = FG_WHITE);

	void DrawLine(int startX, int startY, int endX, int endY, short symbol = PIXEL_SOLID, short color = FG_WHITE);

	void CreateBackBuffer();
	
	void handleKeyBoardInput();
	void handleMouseInput();

	int ScreenWidth()
	{
		return width;
	}

	int ScreenHeight()
	{
		return height;
	}

private:
		
	int width = 120;
	int height = 40;
	CHAR_INFO* screen;
	CHAR_INFO* backBuffer;

	INPUT_RECORD inputBuffer[32];
	DWORD events = 0;
	
	DWORD read, written;
	COORD coord;
	SMALL_RECT rectWindow;
	
	HANDLE handleStdOut, handleStdIn;
	//holds original console handle
	HANDLE handleConsole;

	CONSOLE_SCREEN_BUFFER_INFO OriginalConsoleInfo;

	CHAR chBuffer[256];

	int Error(const wchar_t* msg);
	


protected:

	//mouse and keybored state/verabiles
	struct keyState {
		bool isPressed;
		bool isHold;
		bool isRelesed;
	}keys[256],mouse[5];

	int mousePosX;
	int mousePosY;

	short keyOldState[256] = { 0 };
	short keyNewState[256] = { 0 };
	bool mouseOldState[5] = { 0 };
	bool mouseNewState[5] = { 0 };
	bool consoleInFocus = true;

public:

	keyState GetKey(int keyID) { return keys[keyID]; }
	int GetMouseX() { return mousePosX; }
	int GetMouseY() { return mousePosY; }
	keyState GetMouse(int mouseButtonID) { return mouse[mouseButtonID]; }
	bool IsFocsed() { return consoleInFocus; }

};