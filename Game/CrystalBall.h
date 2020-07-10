#pragma once
#include "Item.h"

#define CRYSTALBALL_SCORE_GIVEN			10000

#define CRYSTALBALL_DISPLAY_DURATION	300000	//Max time
#define CRYSTALBALL_DELAY				1000

class CrystalBall : public Item
{
public:
	CrystalBall(float posX, float posY);
	~CrystalBall();
};