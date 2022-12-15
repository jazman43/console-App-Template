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
	
	for (size_t i = 0; i < text.size(); i++) {
		screen[y * width + x + i] = text[i];
	}
}

void WindowInti::ClearConsole()
{
	for (size_t x = 0; x < width; x++) {
		for (size_t y = 0; y < height; y++) {
			screen[y * width + x] = L' ';
		}
	}
	
}

void WindowInti::Draw(int x, int y, short symbol)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		screen[y * width + x] = symbol;
		
	}
}

void WindowInti::DrawLine(int x1, int y1, int x2, int y2, short symbol)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;

	dy = y2 - y1;

	dx1 = abs(dx);

	dy1 = abs(dy);

	px = 2 * dy1 - dx1;

	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; y = y1;
			xe = x2;
		}
		else
		{
			x = x2; y = y2;
			xe = x1;
		}

		Draw(x, y, symbol);

		for (i = 0; x < xe; i++)
		{
			x += 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			Draw(x, y, symbol);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}

		Draw(x, y, symbol);

		for (i = 0; y < ye; i++)
		{
			y += 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			Draw(x, y, symbol);
		}
	}

}

