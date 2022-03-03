#include "stdafx.h"
#include "form.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "windows.h"



void forms::SetupFirst(int width, int numForm)
{
	switch (numForm)
	{
	case sqare:
		this->coolision[0] = { true };
		this->coolision[1] = { true };
		this->coolision[2] = { false };
		this->coolision[3] = { false };
		this->xy[0] = { width / 2, 3 };
		this->mainxy = this->xy[0];
		this->xy[1] = { (width / 2) - 1, 3 };
		this->xy[2] = { (width / 2) - 1, 2 };
		this->xy[3] = { (width / 2), 2 };
		what_form = sqare;
		break;
	case TForm:
		this->coolision[0] = { false };
		this->coolision[1] = { true };
		this->coolision[2] = { true };
		this->coolision[3] = { true };
		this->xy[0] = { width / 2, 2 };
		this->mainxy = this->xy[0];
		this->xy[1] = { (width / 2) - 1, 2 };
		this->xy[2] = { (width / 2) + 1, 2 };
		this->xy[3] = { (width / 2), 3 };
		what_form = TForm;
		break;
	case LAngle:
		this->coolision[0] = { true };
		this->coolision[1] = { true };
		this->coolision[2] = { false };
		this->coolision[3] = { true };
		this->xy[0] = { width / 2, 2 };
		this->mainxy = this->xy[0];
		this->xy[1] = { (width / 2) - 1, 2 };
		this->xy[2] = { (width / 2) + 1, 2 };
		this->xy[3] = { (width / 2) + 1, 3 };
		what_form = LAngle;
		break;
	case RAngle:
		this->coolision[0] = { true };
		this->coolision[1] = { false };
		this->coolision[2] = { true };
		this->coolision[3] = { true };
		this->xy[0] = { width / 2, 2 };
		this->mainxy = this->xy[0];
		this->xy[1] = { (width / 2) - 1, 2 };
		this->xy[2] = { (width / 2) + 1, 2 };
		this->xy[3] = { (width / 2) - 1, 3 };
		what_form = RAngle;
		break;
	case TwoAngles:
		this->coolision[0] = { false };
		this->coolision[1] = { true };
		this->coolision[2] = { true };
		this->coolision[3] = { true };
		this->xy[0] = { width / 2, 2 };
		this->mainxy = this->xy[0];
		this->xy[1] = { (width / 2) - 1, 3 };
		this->xy[2] = { (width / 2) + 1, 2 };
		this->xy[3] = { (width / 2), 3 };
		what_form = TwoAngles;
		break;
	case Line:
		this->coolision[0] = { false };
		this->coolision[1] = { true };
		this->coolision[2] = { true };
		this->coolision[3] = { true };
		this->xy[0] = { width / 2, 2 };
		this->mainxy = this->xy[0];
		this->xy[1] = { (width / 2) - 1, 2 };
		this->xy[2] = { (width / 2) + 1, 2 };
		this->xy[3] = { (width / 2) + 2, 2 };
		what_form = Line;
		break;
	}
}

EForms forms::getForm()
{
	return this->what_form;
}

static int counterpos = 0;

void forms::ToPosArray(std::pair<int, int>* ptr_pair, int pos)
{
	 for (int i=0; i < 4; i++)
	 {
		 ptr_pair[pos - i - 1] = xy[i];
	 }
}

 std::pair<int, int>* forms::getcoords()
 {
	 return this->xy;
 }

 std::pair<int, int> forms::getMain()
 {
	 return this->mainxy;
 }
 
 std::pair<int, int> forms::getDowncoords()
 {
	 std::pair<int, int> return_pair;
	 return_pair = this->mainxy;
	 int maxy = this->mainxy.second;
	 for (int i = 0; i < 4; i++)
	 {
		 if (xy[i].second > maxy)
		 {
			 maxy = xy[i].second;
			 return_pair = this->xy[i];
		 }
	 }
	 return return_pair;
 }

 std::pair<int, int> forms::getLeftcoords()
{
	 std::pair<int,int> return_pair;
	 return_pair = this->mainxy;
	 int minx = this->mainxy.first;
	 for (int i = 0; i < 4; i++)
		{
			if (xy[i].first < minx)
			{
				minx = xy[i].first;
				return_pair = xy[i];
			} 
		}
	 return return_pair;
			
}

 std::pair<int, int> forms::getRightcoords()
 {
	 std::pair<int, int> return_pair;
	 return_pair = this->mainxy;
	 int maxx = this->mainxy.first;
	 for (int i = 0; i < 4; i++)
	 {
		 if (xy[i].first > maxx)
		 {
			 maxx = xy[i].first;
			 return_pair = this->xy[i];
		 }
	 }
	 return return_pair;
 }

 std::pair<int, int> forms::getheighstcoords()
 {
	 std::pair<int, int> return_pair;
	 return_pair = this->mainxy;
	 int maxy = this->mainxy.second;
	 for (int i = 0; i < 4; i++)
	 {
		 if (xy[i].second < maxy)
		 {
			 maxy = xy[i].second;
			 return_pair = xy[i];
		 }
	 }
	 return return_pair;
 }

 std::pair<int, int>* forms::WhoCanCatch()
 {
	 int size = 4;
	 int j = 0;
	 std::pair<int, int> arr_coords[4] = { };
	 
	 for (size_t i = 0, j=i; i < size; i++)
	 {
		 if (coolision[j]) 
		 {
			 arr_coords[i] = xy[j];
			 j++;
		 }
		 else
		 {
			 arr_coords[size - 1] = { 0,0 };
			 size--;
			 i--;
			 j++;
		 }
	 }	
	return arr_coords;
 }

 void forms::turnForm(int turnCounter)
 {
	 switch (what_form)
	 {
	 case sqare:
		 break;
	 case TForm:
	 switch (turnCounter)
		 {
		 case 1:
			 this->xy[2].first--;
			 this->xy[2].second--;
			 this->coolision[2] = false;
			 break;
		 case 2:
			 this->xy[3].first++;
			 this->xy[3].second--;
			 this->coolision[0] = true;
			 break;
		 case 3:
			 this->xy[1].first++;
			 this->xy[1].second++;
			 this->coolision[0] = false;
			
			 break;
		 case 4:
			 turnCounter = 0;
			 this->xy[2].first++;
			 this->xy[2].second++;
			 this->coolision[2] = true;
			 this->xy[3].first--;
			 this->xy[3].second++;
			 this->xy[1].first--;
			 this->xy[1].second--;
			 this->coolision[0] = false;
			 break;
		 }
		 break;
	 case LAngle:
		 switch (turnCounter)
		 {
		 case 1:
			 this->coolision[0] = false;
			 this->xy[1].first++;
			 this->xy[1].second--;
			 this->coolision[1] = false;
			 this->xy[3].first -= 2;
			 this->xy[2].first--;
			 this->xy[2].second++;
			 this->coolision[2] = true;
			 break;
		 case 2:
			 this->coolision[0] = true;
			 this->xy[1].first++;
			 this->xy[1].second++;
			 this->coolision[1] = true;
			 this->xy[3].second -= 2;
			 this->coolision[3] = false;
			 this->xy[2].first--;
			 this->xy[2].second--;
			 break;
		 case 3:
			 this->coolision[0] = false;
			 this->xy[1].first--;
			 this->xy[1].second++;
			 this->xy[3].first += 2;
			 this->coolision[3] = true;
			 this->xy[2].first++;
			 this->xy[2].second--;
			 this->coolision[2] = false;
			 break;
		 case 4:
			 turnCounter = 0;
			 this->xy[1].first--;
			 this->xy[1].second--;
			 this->xy[3].second += 2;
			 this->xy[2].first++;
			 this->xy[2].second++;
			 this->coolision[0] = true;
			 break;
		 }
		 break;
	 case RAngle:
		 switch (turnCounter)
		 {
		 case 1:
			 this->xy[1].first++;
			 this->xy[1].second--;
			 this->xy[3].second -= 2;
			 this->xy[2].first--;
			 this->xy[2].second++;
			 this->coolision[0] = false;
			 break;
		 case 2:
			 this->xy[1].first++;
			 this->xy[1].second++;
			 this->xy[3].first += 2;
			 this->coolision[3] = false;
			 this->xy[2].first--;
			 this->xy[2].second--;
			 this->coolision[0] = true;
			 this->coolision[1] = true;
			 this->coolision[2] = true;
			 break;
		 case 3:
			 this->coolision[0] = false;
			 this->xy[1].first--;
			 this->xy[1].second++;
			 this->xy[3].second += 2;
			 this->coolision[3] = true;
			 this->xy[2].first++;
			 this->xy[2].second--;
			 this->coolision[2] = false;
			 break;
		 case 4:
			 turnCounter = 0;
			 this->xy[1].first--;
			 this->xy[1].second--;
			 this->coolision[1] = false;
			 this->xy[3].first -= 2;
			 this->xy[2].first++;
			 this->xy[2].second++;
			 this->coolision[0] = true;
			 this->coolision[2] = true;
			 break;
		 }
		 break;
	 case TwoAngles:
		 switch (turnCounter)
		 {
		 case 1:
			 this->xy[1].second -= 2;
			 this->xy[2].first -= 2;
			 this->coolision[1] = false;
			 break;
		 case 2:
			 turnCounter = 0;
			 this->xy[1].second += 2;
			 this->xy[2].first += 2;
			 this->coolision[1] = true;
			 break;
		 }
		 break;
	 case Line:
		 switch (turnCounter)
		 {
		 case 1:
			 this->xy[1].second++;
			 this->xy[1].first++;
			 this->xy[2].first--;
			 this->xy[2].second--;
			 this->xy[3].first-=2;
			 this->xy[3].second+=2;
			 this->coolision[0] = false;
			 this->coolision[1] = false;
			 this->coolision[2] = false;
			 break;
		 case 2:
			 turnCounter = 0;
			 this->xy[1].second--;
			 this->xy[1].first--;
			 this->xy[2].first++;
			 this->xy[2].second++;
			 this->xy[3].first += 2;
			 this->xy[3].second -= 2;
			 this->coolision[0] = false;
			 this->coolision[1] = true;
			 this->coolision[2] = true;
			 break;
		 }
		 break;
	 }

 }

void forms::changecoords(int x = 0, int y = 0)
{
	for (int i = 0; i < 4; i++)
	{
		xy[i].first += x;
		xy[i].second += y;
	}
	this->mainxy.first += x;
	this->mainxy.second += y;
}








