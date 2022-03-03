#pragma once
#include <vector>
#include"form.h"

class Game
{
	Edirection dir;
	int counter;
	bool gameOver;
	const int width = 10;
	const int height = 20;
	const int sqare = width * height;
	int speedChanger = 0;
	int turncounter;
	int score;
	EForms Status;
	bool map[10][20] = { false }; // using standart arr, cuz have some problem with DynamicBoolArr.
	//bool** map;	 //bool map using for coolisions.
	std::pair<int, int> nullpair = { 0,0 };
	int maxHeight = height - 1;
	std::pair<int, int> CoorVec1[10 * 20] = {};

	bool LHeight;
	bool LMidle;
	bool LDown;

	bool RHeight;
	bool RMidle;
	bool RDown;
	
	
	void ShiftField(int count);
	void ShiftDown(int i, int j, int count);
	void ShiftArr(int pos);
	void ChangeCoords(int pos_in_arr);
	std::vector<bool> LineCheck();
	std::pair<bool, bool> FormTroublePos(forms* ptrobj);
	bool TryTurn(forms* ptrobj, int turncounter);
	void setStatus(forms* ptrobj);
	int GetScore();
	int pos_in_arr(int x, int y);
	void GameOverSwitch(bool switcher);
	
public:
	//Game::Game();
	void gameInitializing(forms* ptrobj);
	int getwidth();
	bool IsGameOver();
	void Draw();
	void Input();
	void Logic(forms* ptrobj); 
	void EndGame();
	int RetGameSpeed();
	~Game();
};

