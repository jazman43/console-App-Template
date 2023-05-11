
#include "windowInti.h"

WindowInti::WindowInti()
{

	handleStdIn = GetStdHandle(STD_INPUT_HANDLE);
	handleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	


	if (handleStdIn == INVALID_HANDLE_VALUE || handleStdOut == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"),
			MB_OK);
		Error(L"Bad Handle");
	}

	rectWindow = { 0,0,1,1 };
	SetConsoleWindowInfo(handleStdOut, true, &rectWindow);

	//set size of screen buffer;
	coord = { (short)width,(short)height };
	if (!SetConsoleScreenBufferSize(handleStdOut, coord)) {
		//return an error text
		Error(L"SetConsoleScreenBufferSize");
	}

	//Assign screen buffer to console
	if (!SetConsoleActiveScreenBuffer(handleStdOut)) {
		//return an error Text
		Error(L"SetConsoleActiveScreenBuffer");
	}

	//set physical console size
	rectWindow = { 0,0,(short)width - 1,(short)height - 1 };
	if (!SetConsoleWindowInfo(handleStdOut, TRUE, &rectWindow)) {
		//return an error Text
		Error(L"SetConsoleWindowInfo");
	}
	
	//set flags to allow mouse input
	if (!SetConsoleMode(handleStdIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT)) {
		//return an error Text
		Error(L"SetConsoleMode");
	}

	//allocate menory for screen buffer
	screen = new CHAR_INFO[width * height];
	memset(screen, 0, sizeof(CHAR_INFO) * width * height);

	CreateBackBuffer();


	

	SetConsoleTitle(L"Console-Window");
}

WindowInti::~WindowInti()
{
	SetConsoleActiveScreenBuffer(handleConsole);
	delete[] screen;
}


void WindowInti::Update()
{
	handleKeyBoardInput();
	handleMouseInput();

	

	//memcpy(screen, backBuffer, sizeof(CHAR_INFO) * width * height);
	WriteConsoleOutput(handleStdOut, screen, { (short)width, (short)height }, { 0,0 }, &rectWindow);
	
}


void WindowInti::DrawTextWString(int x, int y, std::wstring text, short color)
{
	
	for (int i = 0; i < text.size(); i++) {
		screen[y * width + x + i].Char.UnicodeChar = text[i];
		screen[y * width + x + i].Attributes = color;
	}
}

void WindowInti::ClearConsole(bool clearAll, int x, int y, int textHeight, int textWidth)
{

	CHAR_INFO emptyCharInfo = { L' ', BG_BLACK };

	if (clearAll) {
		
		for (int i = 0; i < width * height; i++) {
			screen[i] = emptyCharInfo;
		}
	}
	else
	{
		for (int i = y; i < y + textHeight; i++) {
			 for (int j = x; j < x + textWidth; j++) {
			      screen[i * width + j] = emptyCharInfo;
			 }
		}
	}
	



}



std::string WindowInti::DrawUserInput(short x, short y, WORD color)
{
	std::string text;
	COORD cursorPos = { x, y };
	SetConsoleCursorPosition(handleStdOut, cursorPos);
	int boxWidth = 32, boxHeight = 1;

	while (true)
	{
		INPUT_RECORD input;
		DWORD events;
		ReadConsoleInput(handleStdIn, &input, 1, &events);

		if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown)
		{
			char ch = input.Event.KeyEvent.uChar.AsciiChar;

			if (GetKey(VK_RETURN).isPressed)
				break;

			if (GetKey(VK_BACK).isPressed && cursorPos.X > x && cursorPos.X < x + boxWidth && cursorPos.Y > y && cursorPos.Y < y + boxHeight)
			{
				text.pop_back();
				cursorPos.X--;
				int index = cursorPos.Y * width + cursorPos.X;
				backBuffer[index].Char.UnicodeChar = L' ';
				Update();
			}
			else if (cursorPos.X >= x && cursorPos.X < x + boxWidth && cursorPos.Y >= y && cursorPos.Y < y)
			{
				text += ch;
				DWORD written;
				WriteConsoleW(handleStdOut, &ch, 1, &written, NULL);
				cursorPos.X++;

				// update the back buffer
				int index = cursorPos.Y * width + cursorPos.X;
				backBuffer[index].Char.UnicodeChar = ch;
				backBuffer[index].Attributes = color;
				Update();
			}
		}

	}
		
	return text;
}


int WindowInti::Error(const wchar_t* msg)
{
	wchar_t buf[256];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
	SetConsoleActiveScreenBuffer(handleConsole);
	wprintf(L"ERROR: %s\n\t%s\n", msg, buf);
	return 1;
	
}



void WindowInti::Draw(int x, int y, short symbol, short color)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		screen[y * width + x].Char.UnicodeChar = symbol;
		screen[y * width + x].Attributes = color;
	}
}

void WindowInti::DrawLine(int startX, int startY, int endX, int endY, short symbol, short color)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;


	dx = endX - startX;
	dy = endY - startY;
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;


	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = startX;
			y = startY;
			xe = endX;
		}
		else
		{
			x = endX;
			y = endY;
			xe = startX;
		}

		Draw(x, y, symbol, color);

		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) 
					y = y + 1;
				else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			Draw(x, y, symbol, color);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = startX;
			y = startY;
			ye = endY;
		}
		else
		{
			x = endX;
			y = endY;
			ye = startY;
		}

		Draw(x, y, symbol, color);

		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					x = x + 1;
				else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			Draw(x, y, symbol, color);
		}
	}

}

void WindowInti::CreateBackBuffer()
{
	backBuffer = new CHAR_INFO[width * height];
	memset(backBuffer, 0, sizeof(CHAR_INFO) * width * height);

}

void WindowInti::handleKeyBoardInput()
{
	// handle keyboard input
		for (int i = 0; i < 256; i++) {
			keyNewState[i] = GetAsyncKeyState(i);

			keys[i].isPressed = false;
			keys[i].isRelesed = false;

			if (keyNewState[i] != keyOldState[i]) {

				if (keyNewState[i] & 0x8000) {
					keys[i].isPressed = !keys[i].isHold;
					keys[i].isHold = true;
				}
				else
				{
					keys[i].isRelesed = true;
					keys[i].isHold = false;
				}
			}

			keyOldState[i] = keyNewState[i];

		}
}

void WindowInti::handleMouseInput()
{

	inputBuffer[31];
	events = 0;
	GetNumberOfConsoleInputEvents(handleStdIn, &events);
	if (events > 0) {
		ReadConsoleInput(handleStdIn, inputBuffer, events, &events);
	}

	for (DWORD i = 0; i < events; i++) {
		switch (inputBuffer[i].EventType)
		{
		case FOCUS_EVENT:
			//set focus
			consoleInFocus = inputBuffer[i].Event.FocusEvent.bSetFocus;
			break;
		case MOUSE_EVENT:
			switch (inputBuffer[i].Event.MouseEvent.dwEventFlags)
			{
			case MOUSE_MOVED:
				mousePosX = inputBuffer[i].Event.MouseEvent.dwMousePosition.X;
				mousePosY = inputBuffer[i].Event.MouseEvent.dwMousePosition.Y;
				break;
			case 0:
				for (int m = 0; m < 5; m++) {
					mouseNewState[m] = (inputBuffer[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;
				}

			default:
				break;
			}
		default:
			break;
		}
	}
	for (int m = 0; m < 5; m++) {
		mouse[m].isPressed = false;
		mouse[m].isRelesed = false;

		if (mouseNewState[m] != mouseOldState[m]) {
			if (mouseNewState[m]) {
				mouse[m].isPressed = true;
				mouse[m].isHold = true;
			}
			else
			{
				mouse[m].isRelesed = true;
				mouse[m].isHold = false;
			}
		}

		mouseOldState[m] = mouseNewState[m];

	}
}

