#pragma once
#include <vector>


enum EForms
{
	TwoAngles,
	sqare,
	TForm,
	Line,
	LAngle,
	RAngle
};

class forms
{
	std::pair<int, int> xy[4] = { };
	bool coolision[4] = {true,true,true,true};
	std::pair<int, int> mainxy;
	EForms what_form;
public:
	forms(int wide) {
		this->xy[0] = { wide / 2, 2 };
		this->mainxy = this->xy[0];
		this->xy[1] = { (wide / 2) - 1, 2 };
		this->xy[2] = { (wide / 2) + 1, 2 };
		this->coolision[2] = false;
		this->xy[3] = { (wide / 2) + 1, 3 };
		what_form = LAngle;
	};
	void ToPosArray(std::pair<int, int>* ptr_pair, int pos);
	std::pair<int, int>* getcoords();
	std::pair<int, int> getMain();
	std::pair<int, int> getDowncoords();
	std::pair<int, int> getLeftcoords();
	std::pair<int, int> getRightcoords();
	std::pair<int, int> getheighstcoords();
	std::pair<int, int>* WhoCanCatch();
	void turnForm(int turnCounter);
	void changecoords(int x, int y);
	void SetupFirst(int width, int numForm);
	EForms getForm();
	~forms()
	{
		delete[] &this->xy;
		delete[] this;
	}
};


