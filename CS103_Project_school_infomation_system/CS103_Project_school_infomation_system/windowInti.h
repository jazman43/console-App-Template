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

	void DrawTextWString(int x, int y, std::wstring text);

	void ClearConsole();

	virtual void Draw(int x, int y, short symbol);

	void DrawLine(int x1, int y1, int x2, int y2, short symbol = 0x2588);

private:
		
	int width = 120;
	int height = 40;
	wchar_t* screen;

	DWORD dwBytesWitten;
	

	HANDLE handleConsole;
};