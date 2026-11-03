#include"stdafx.h"
#include"Game.h"
#include<Windows.h>
int main()//1
{
	//Game object
	Game game;
	//Running the game when quit==false or window is not closed
	/*HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);*/

	game.run();

	return 0;//0
}