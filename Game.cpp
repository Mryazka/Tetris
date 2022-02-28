#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "windows.h"



Game::~Game()
{
	delete this;
}

void Game::gameInitializing(forms * ptrobj)
{
	score = 0;
	counter = 4;
	gameOver = false;
	dir = BEGIN;
	Status = ptrobj->getForm();
	ptrobj->ToPosArray(CoorVec1, counter);
	for (size_t i = 0; i < 4; i++) { map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true; }
}

int Game::getwidth()
{
	return width;
}

bool Game::IsGameOver()
{
	return gameOver;
}

void Game::GameOverSwitch(bool switcher)
{
	gameOver = switcher;
}

int Game::GetScore()
{
	return score;
}

void Game::setStatus(forms* ptrobj)
{
	Status = ptrobj->getForm();
}

void Game::Draw()
{

	std::vector<int> xes;
	std::vector<int> yes;
	for (int j = 0; j<counter; j++)
	{
		xes.push_back(CoorVec1[j].first);
		yes.push_back(CoorVec1[j].second);
	}
	system("cls");
	for (int i = 0; i < width; i++)
	{
		std::cout << "#";
		map[i][0] = true;
	}
	std::cout << std::endl;

	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((j == 0) || (j == (width - 1)))
			{
				std::cout << '#';
				map[j][i] = true;
			}
			else
			{
				if (map[j][i])
				{
					for (int k = 0; k < counter; k++)
					{
						if ((CoorVec1[k].second == i) && (CoorVec1[k].first == j))
						{
							std::cout << "o";
						}
					}
				}
				else
				{
					std::cout << " ";
				}
			}


		} std::cout << std::endl;
	}

	for (int i = 0; i < width; i++)
	{
		std::cout << "#";
		map[i][height] = true;
	}
	for (int j = 0; j<counter; j++)
	{
		CoorVec1[j].first = xes[j];
		CoorVec1[j].second = yes[j];
	}
	std::cout << std::endl;
}

void Game::Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case' ':
			dir = BEGIN;
			break;
		case'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case'w':
			dir = TURN;
			break;
		case's':
			dir = DOWN;
			break;
		case'x':
			gameOver = true;
			break;
		}
	}
}

void Game::Logic(forms * ptrobj)
{
	switch (dir)
	{
	case BEGIN:
		dir = MOVE;
		turncounter = 0;
		break;
	case LEFT:
		if (map[ptrobj->getLeftcoords().first - 1][ptrobj->getLeftcoords().second]) { ptrobj->changecoords(0, 0); dir = MOVE; break; }
		else
		{
			for (int i = 0; i < 4; i++)
			{
				map[(ptrobj->getcoords()[i]).first][(ptrobj->getcoords()[i]).second] = false;
			}
			ptrobj->changecoords(-1, 0);
			for (int i = 0; i < 4; i++)
			{
				CoorVec1[counter - i - 1].first--;
				map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true;
			}
			dir = MOVE;
			break;
		}
	case RIGHT:
		if (map[ptrobj->getRightcoords().first + 1][ptrobj->getRightcoords().second]) { ptrobj->changecoords(0, 0); dir = MOVE; break; }
		else
		{
			for (int i = 0; i < 4; i++)
			{
				map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
			}
			ptrobj->changecoords(1, 0);
			for (int i = 0; i < 4; i++)
			{
				CoorVec1[counter - i - 1].first++;
				map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true;
			}
			dir = MOVE;
			break;
		}

	case TURN:
		if (Status == ptrobj->getForm())
		{
			if (turncounter < 4) { turncounter++; }
			else { turncounter = 1; }
		}
		else { Status = ptrobj->getForm(); turncounter = 1; }

		if (ptrobj->getForm() == Line)
		{
			if (turncounter == 2)
			{
				if (map[ptrobj->getLeftcoords().first - 1][ptrobj->getLeftcoords().second])
				{
					for (int i = 0; i < 4; i++)
					{
						map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
					}
					ptrobj->turnForm(turncounter);
					ptrobj->changecoords(1, 0);
				}

				else if (map[ptrobj->getRightcoords().first + 1][ptrobj->getRightcoords().second])
				{
					for (int i = 0; i < 4; i++)
					{
						map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
					}
					ptrobj->turnForm(turncounter);
					ptrobj->changecoords(-2, 0);
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
					}
					ptrobj->turnForm(turncounter);
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
				}
				ptrobj->turnForm(turncounter);
			}
		}
		else
		{
			std::pair<bool, bool> CheckerBoolPair = FormTroublePos(ptrobj);
			if (CheckerBoolPair.first)
			{
				for (int i = 0; i < 4; i++)
				{
					map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
				}
				ptrobj->changecoords(1, 0);
				if (TryTurn(ptrobj, turncounter))
				{
					ptrobj->turnForm(turncounter);
				}
				else
				{
					ptrobj->changecoords(-1, 0);
					turncounter--;
					break;
				}
			}
			else if (CheckerBoolPair.second)
			{
				for (int i = 0; i < 4; i++)
				{
					map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
				}
				ptrobj->changecoords(-1, 0);
				if (TryTurn(ptrobj, turncounter))
				{
					ptrobj->turnForm(turncounter);
				}
				else
				{
					ptrobj->changecoords(1, 0);
					turncounter--;
					break;
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
				}

				if (TryTurn(ptrobj, turncounter))
				{
					ptrobj->turnForm(turncounter);
				}
				else
				{
					if (turncounter == 0)
					{
						turncounter = 4;
					}
					else
					{
						turncounter--;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true;
		}
		ptrobj->ToPosArray(CoorVec1, counter);
		dir = MOVE;
		break;

	case DOWN:
		if (map[ptrobj->getDowncoords().first][ptrobj->getDowncoords().second + 2] || map[ptrobj->getDowncoords().first][ptrobj->getDowncoords().second + 1]) { ptrobj->changecoords(0, 0); dir = MOVE; break; }
		else
		{
			for (int i = 0; i < 4; i++)
			{
				map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
			}
			ptrobj->changecoords(0, 2);
			for (int i = 0; i < 4; i++)
			{
				CoorVec1[counter - i - 1].second += 2;
				map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true;
			}
			dir = MOVE;
			break;
		}

	case STOP:
		ptrobj->changecoords(0, 0);
		break;

	case MOVE:
		int j = 0;
		while (ptrobj->WhoCanCatch()[j].second != 0)
		{
			if (map[ptrobj->WhoCanCatch()[j].first][ptrobj->WhoCanCatch()[j].second + 1])
			{
				map[ptrobj->getcoords()[j].first][ptrobj->getcoords()[j].second] = true; dir = STOP; break;
			}
			j++;
		}
		if (dir == STOP) { break; }
		for (size_t i = 0; i < 4; i++)
		{
			map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = false;
		}
		ptrobj->changecoords(0, 1);
		for (int i = 0; i < 4; i++)
		{
			CoorVec1[counter - i - 1].second++;
			map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true;
		}
		break;
	}

	std::pair<int, int> Downcoord = ptrobj->getDowncoords();
	std::vector<bool> lines = LineCheck();

	if (dir == STOP)
	{
		for (size_t j = 0; j < 4; j++)
		{
			map[ptrobj->getcoords()[j].first][ptrobj->getcoords()[j].second] = true;
		}

		if (ptrobj->getheighstcoords().second <= maxHeight)
		{
			maxHeight = ptrobj->getheighstcoords().second - 1;
		}

		if (lines.size() != 0)
		{
			for (int i = 0; i < lines.size(); i++)
			{
				if (lines[i])
				{
					ShiftField(i);
					lines = LineCheck();
					i--;
					for (int j = 0; j<counter; j++)
					{
						map[CoorVec1[j].first][CoorVec1[j].second] = true;
					}
					score += 10;
					speedChanger += 5;
				}
				else { continue; }
			}
			int randstuf = rand() % 5 + 0;
			ptrobj->SetupFirst(width, randstuf);
			counter += 4;
			ptrobj->ToPosArray(CoorVec1, counter);
			for (size_t i = 0; i < 4; i++)
			{
				map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true;
			}
			dir = BEGIN;
		}
		else
		{
			for (size_t i = 0; i < 4; i++)
			{
				map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true;
			}
			int randstuf = rand() % 5 + 0;
			ptrobj->SetupFirst(width, randstuf);
			counter += 4;
			ptrobj->ToPosArray(CoorVec1, counter);
			for (size_t i = 0; i < 4; i++)
			{
				map[ptrobj->getcoords()[i].first][ptrobj->getcoords()[i].second] = true;
			}
			dir = BEGIN;
		}
	}
	if (maxHeight <= 3) { gameOver = true; }
}

void Game::ShiftField(int count)
{
	int j = height - 1 - count;
	for (int i = 1; i < width - 1; i++)
	{
		ShiftDown(i, j, count);
	}
	maxHeight++;
}

void Game::ShiftDown(int i, int j, int count)
{
	while (maxHeight - 1 != j)
	{
		if (j == height - 1 - count)
		{
			if (map[i][(j - 1)] && map[i][j])
			{
				ShiftArr(pos_in_arr(i, j - 1));
				map[i][j - 1] = false;
			}
			else if (map[i][j - 1] && !map[i][j])
			{
				ChangeCoords(pos_in_arr(i, j - 1));
				map[i][j - 1] = false;
				map[i][j] = true;
			}
			else if (map[i][j])
			{
				ShiftArr(pos_in_arr(i, j));
				map[i][j] = false;
			}
		}
		else if (map[i][j - 1] && map[i][j])
		{
			ShiftArr(pos_in_arr(i, j - 1));
			map[i][j - 1] = false;
			map[i][j] = true;
		}
		else if (map[i][j - 1] && !map[i][j])
		{
			ChangeCoords(pos_in_arr(i, j - 1));
			map[i][j - 1] = false;
			map[i][j] = true;
		}
		j--;
	}
}

void Game::ShiftArr(int pos)
{
	while (pos < counter + 1)
	{
		int x = CoorVec1[pos + 1].first;
		int y = CoorVec1[pos + 1].second;
		CoorVec1[pos].first = x;
		CoorVec1[pos].second = y;
		pos++;
	}
	counter--;
}

void Game::ChangeCoords(int pos_in_arr)
{
	if ((CoorVec1[pos_in_arr].second + 1 < CoorVec1[pos_in_arr].second + 2) < height)
	{
		CoorVec1[pos_in_arr].second = CoorVec1[pos_in_arr].second + 1;
	}
}

int Game::pos_in_arr(int x, int y)
{
	for (int i = 0; i < counter; i++)
	{
		if (x == CoorVec1[i].first && y == CoorVec1[i].second) { return i; }
	}

}

std::vector<bool> Game::LineCheck()
{
	std::vector<bool> checker;
	for (int j = height - 1; j > maxHeight; j--)
	{
		int lineCounter = 0;
		for (int i = 1; i < width; i++)
		{
			if (width - 2 > lineCounter)
			{
				if (map[i][j] == true)
				{
					lineCounter++;
				}
				else
				{
					lineCounter = 0;
					checker.push_back(false);
					break;
				}
			}
			else
			{
				checker.push_back(true);
				break;
			}
		}
	}
	return checker;
}

std::pair<bool, bool> Game::FormTroublePos(forms * ptrobj)
{
	bool DownLeftCoord = map[ptrobj->getLeftcoords().first][ptrobj->getDowncoords().second];
	bool DownRightCoord = map[ptrobj->getRightcoords().first][ptrobj->getDowncoords().second];
	if (ptrobj->getMain() == ptrobj->getLeftcoords())
	{
		bool Left = map[ptrobj->getMain().first - 1][ptrobj->getMain().second];
		bool RRight = map[ptrobj->getMain().first + 2][ptrobj->getMain().second];

		if ((Left && RRight))
		{
			return{ true,true };
		}
		else if (Left)
		{
			return{ true,false };
		}
		else
		{
			return{ false, false };
		}
	}
	else if (ptrobj->getMain() == ptrobj->getRightcoords())
	{
		bool Right = map[ptrobj->getMain().first + 1][ptrobj->getMain().second];
		bool LLeft = map[ptrobj->getMain().first - 2][ptrobj->getMain().second];
		if (LLeft && Right)
		{
			return{ true,true };
		}
		else if (Right)
		{
			return{ false, true };
		}
		else
		{
			return{ false, false };
		}
	}
	else
	{
		return{ false, false };
	}
}

bool Game::TryTurn(forms * ptrobj, int turncounter)
{
	forms* tempForm = new forms(*ptrobj);
	int errorcacher = 0;
	tempForm->turnForm(turncounter);
	for (size_t i = 0; i < 4; i++)
	{
		std::pair<int, int> temp = tempForm->getcoords()[i];
		if (map[temp.first][temp.second])
		{
			return false;
		}
	}
	free(tempForm);
	return true;
}

void Game::EndGame()
{
	std::cout << "GAME OVER!" << std::endl;
	std::cout << "Your Score : " << score << std::endl;
}

int Game::RetGameSpeed()
{
	return speedChanger;
}
