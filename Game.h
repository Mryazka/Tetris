#pragma once
#include <vector>
#include"form.h"

class Game
{
	enum Edirection
	{
		STOP = 0,
		LEFT,
		RIGHT,
		TURN,
		DOWN,
		MOVE,
		BEGIN,
	} dir;
	int counter;
	bool gameOver;
	const int width = 10;
	const int height = 20;
	int speedChanger = 0;
	int turncounter;
	int score;
	EForms Status;
	bool map[10][20] = { false };
	std::pair<int, int> nullpair = { 0,0 };
	int maxHeight = height - 1;

	bool LHeight;
	bool LMidle;
	bool LDown;

	bool RHeight;
	bool RMidle;
	bool RDown;

public:
	void gameInitializing(forms* ptrobj);
	int getwidth();
	std::pair<int, int> CoorVec1[200] = {};
	bool IsGameOver();
	void GameOverSwitch(bool switcher);
	int GetScore();
	void setStatus(forms* ptrobj);
	void Draw();
	void Input();
	void Logic(forms* ptrobj); 
	void ShiftField(int count);
	void ShiftDown(int i, int j, int count);
	void ShiftArr(int pos);
	void ChangeCoords(int pos_in_arr);
	int pos_in_arr(int x, int y);
	std::vector<bool> LineCheck();
	std::pair<bool, bool> FormTroublePos(forms* ptrobj);
	bool TryTurn(forms* ptrobj, int turncounter);
	void EndGame();
	int RetGameSpeed();
	~Game();
};

