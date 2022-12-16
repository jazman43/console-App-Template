#include "windowInti.h"

WindowInti::WindowInti()
{

	screen = new wchar_t[width * height];
	handleConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(handleConsole);
	dwBytesWitten = 0;
	
}

WindowInti::~WindowInti()
{
}


void WindowInti::Update()
{
	

	screen[width * height - 1] = '\0';
	WriteConsoleOutputCharacter(handleConsole, screen, width * height, { 0,0 }, &dwBytesWitten);
}


void WindowInti::DrawTextWString(int x, int y, std::wstring text)
{
	
	for (int i = 0; i < text.size(); i++) {
		screen[y * width + x + i] = text[i];
	}
}

void WindowInti::ClearConsole()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			screen[y * width + x] = L' ';
		}
	}
	
}
//not working yet
void WindowInti::DrawUserInput(int x, int y)
{
	//std::wstring text;
	unsigned short input =' ';

	if (GetKey(input)) {

		for (int i = 0; i < sizeof(std::wstring); i++) {
			screen[y * width + x + i] = input;
		}
	}
	

	
}

bool WindowInti::GetKey(unsigned short key)
{
	char currentKey = key;
	
	if (GetAsyncKeyState(key) & 0x8000) {
		return 1;
	}

	return 0;
}



//void WindowInti::Draw(int x, int y, short symbol)
//{
//	if (x >= 0 && x < width && y >= 0 && y < height)
//	{
//		screen[y * width + x] = symbol;
//		
//	}
//}

//void WindowInti::DrawLine(int startX, int startY, int endX, int endY, short symbol)
//{
//	for (int x = startX; x < width; x++) {
//		for (int y = startY; y < height; y++) {
//
//			screen[y * width + x + y] = symbol;
//			
//		}
//	}
//
//}

