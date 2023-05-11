#include <iostream>
#include "windowInti.h"


//use Unicode to change color and symbol (0x000F);


int main() {
	//main loop will call one function that will handle quiting starting menu and will include header files needed.

	WindowInti consoleCreate;	
	bool canClear = false;

	
	
	while (true)
	{
		//consoleCreate.ClearConsole

		//Draw Text wstring fucntion tack an x and y position and a wide string (L"text") upper case L must come frist 
		consoleCreate.DrawTextWString(10, 20,L"hello and welcome");
		if(consoleCreate.GetMouseX() >= 10 
			&& consoleCreate.GetMouseY() == 20 
			&& consoleCreate.GetMouse(0).isPressed)
		{			
			consoleCreate.DrawTextWString(10, 10, L"hello User jared");
			consoleCreate.DrawLine(2, 10, 2, 100);
			
		}
		//consoleCreate.DrawUserInput(12, 6, FG_WHITE);
		
		
		if (consoleCreate.IsFocsed()) {
			consoleCreate.DrawTextWString(10, 22, L"isfocice");
		}
		else
		{
			canClear = true;
		}
		
		
		

		//use captile letter for get key and use VK_ for other keys
		
		if (consoleCreate.GetMouseX() == 55 && consoleCreate.GetMouseY() == 30) {
			consoleCreate.DrawTextWString(55, 30, L"the mouse is at 55x and 30y ish");
		}

		//0 for left 1 for right mouse button
		if (consoleCreate.GetMouse(1).isPressed) {
			consoleCreate.DrawTextWString(55, 31, L"the mouse button (1) is pressed",BG_GREEN);
		}
		if (consoleCreate.GetMouse(0).isPressed) {
			consoleCreate.DrawTextWString(55, 32, L"the mouse button (0) is pressed");
		}
		//updates console and mouse/keys every frame 
		if (canClear) {
			consoleCreate.ClearConsole(true,0,0,0,0);
			canClear = false;
		}
		consoleCreate.Update();
	}

	return 0;
}