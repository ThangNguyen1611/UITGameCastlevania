#pragma once
#include "Texture2dManager.h"
#include "Sprite.h"
#include <string>
using namespace std;

class Text
{
	Texture2d* textTexture;
	Sprite* textSprite;
public:
	Text();
	~Text();
	void Render(float posX, float posY, const string &str);

	string FillZeroString(string str, UINT MaxStringLenght);

};

