#include <iostream>
#include <chrono>
#include <thread>


#include "windowInti.h"


//use Unicode to change color and symbol (0x000F);







int main() {
	//main loop will call one function that will handle quiting starting menu and will include header files needed.

	WindowInti consoleCreate;	
	bool canClear = false;

	constexpr double refreshRate = 60.0; // Refresh rate in frames per second
	

	const std::chrono::duration<double> frameDuration = std::chrono::duration<double>(1.0 / refreshRate);
	
	while (true)
	{
		
		const auto frameStartTime = std::chrono::steady_clock::now();


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
			consoleCreate.ClearConsole(1, 0, 0, 0, 0);
		}
		
		
		

		//use captile letter for get key and use VK_ for other keys
		
		if (consoleCreate.GetMouseX() >= 55 && consoleCreate.GetMouseY() == 30) {
			consoleCreate.DrawTextWString(55, 30, L"the mouse is at 55x and 30y ish");
		}

		//0 for left 1 for right mouse button
		if (consoleCreate.GetMouse(1).isPressed) {
			consoleCreate.DrawTextWString(55, 31, L"the mouse button (1) is pressed",BG_GREEN);
		}
		if (consoleCreate.GetMouse(0).isPressed) {
			consoleCreate.DrawTextWString(55, 32, L"the mouse button (0) is pressed");
		}
		
		
		//consoleCreate.ClearConsole(true, 0, 0, 0, 0);
		consoleCreate.Update();
		

		// Calculate the time taken for the frame update and clearing
		const auto frameEndTime = std::chrono::steady_clock::now();
		const std::chrono::duration<double> frameTime = frameEndTime - frameStartTime;

		// Sleep for the remaining time to achieve the desired refresh rate
		const std::chrono::duration<double> sleepTime = frameDuration - frameTime;
		if (sleepTime > std::chrono::duration<double>(0))
		{
			std::this_thread::sleep_for(sleepTime);
		}
	}

	return 0;
}