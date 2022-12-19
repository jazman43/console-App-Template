#pragma once
#include <windows.h>
#include <string>

#ifndef UNICODE
#error Please enable UNICODE for your compiler! VS: Project Properties -> General -> \
Character Set -> Use Unicode.
#define UNICODE
#define _UNICODE
#endif



class WindowInti {
public:
	WindowInti();
	~WindowInti();

	void Update();

	void DrawTextWString(int x, int y, std::wstring text, short color = 0x000F);

	void ClearConsole();
	
	void DrawUserInput(int x, int y);
	
	bool GetKey(unsigned short key);

	void Draw(int x, int y, short symbol = 0x2588, short color = 0x000F);

	void DrawLine(int startX, int startY, int endX, int endY, short symbol = 0x2588, short color = 0x000F);
	
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

	short keyOldState[256] = { 0 };
	short keyNewState[256] = { 0 };


	SMALL_RECT rectWindow;

	DWORD dwBytesWitten;
	
	HANDLE handleStdOut, handleStdIn;

	HANDLE handleConsole;

	CONSOLE_SCREEN_BUFFER_INFO OriginalConsoleInfo;



	int Error(const wchar_t* msg);
	
		
};