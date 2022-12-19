#include <iostream>
#include "windowInti.h"


//use Unicode to change color and symbol (0x000F);


int main() {
	//main loop will call one function that will handle quiting starting menu and will include header files needed.

	WindowInti consoleCreate;	
	

	
	int y = 11;
	while (true)
	{
		//Draw Text wstring fucntion tack an x and y position and a wide string (L"text") upper case L must come frist 
		consoleCreate.DrawTextWString(10, 20,L"hello Thierry");
		
		consoleCreate.Draw(0, 0);
		
		consoleCreate.DrawLine(0, 1, 60, 1);

		if (consoleCreate.GetKey('S')) {
			consoleCreate.DrawTextWString(20, y, L"hello jared");	
			y++;
		}
		if (consoleCreate.GetKey('W'))
		{
			consoleCreate.ClearConsole();
		}
		
		

		//updates console every frame
		consoleCreate.Update();
	}

	return 0;
}