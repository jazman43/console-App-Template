#include <iostream>
#include "windowInti.h"




int main() {
	//main loop will call one function that will handle quiting starting menu and will include header files needed.

	WindowInti consoleCreate;	
	

	//clears console else will get wied symbols
	consoleCreate.ClearConsole();
	int y = 11;
	while (true)
	{
		//Draw Text wstring fucntion tack an x and y position and a wide string (L"text") upper case L must come frist 
		consoleCreate.DrawTextWString(10, 10,L"hello");
		//can crash program
		//consoleCreate.DrawUserInput(11, 11);
		
		if (consoleCreate.GetKey('S')) {
			consoleCreate.ClearConsole();
		}

		//updates console every frame
		consoleCreate.Update();
	}

	return 0;
}