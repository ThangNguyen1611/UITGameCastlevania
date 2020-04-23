#pragma once
#include "Sprites.h"
#include <string>
using namespace std;

class Text
{
	LPSPRITE textSpr;
public:
	Text();
	~Text();
	void Render(float posX, float posY, const string &str);

	string FillZeroString(string str, UINT MaxStringLenght);
};

