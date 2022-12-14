#include "windowInti.h"

WindowInti::WindowInti()
{
	wchar_t* screen = new wchar_t[width * height];
	HANDLE handleConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(handleConsole);
	DWORD dwBytesWitten = 0;

}

WindowInti::~WindowInti()
{
}
//