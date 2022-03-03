// Tetris.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "Game.h"

int main()
{
	Game tetris;
	forms* gameform = new forms(tetris.getwidth());
	tetris.gameInitializing(gameform);
	while (!tetris.IsGameOver())
	{
		Sleep(500-tetris.RetGameSpeed());
		tetris.Draw();
		tetris.Input();
		tetris.Logic(gameform);
	}
	tetris.EndGame();
	system("pause");
	return 0;
}