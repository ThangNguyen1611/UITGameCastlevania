#pragma once
#include "Item.h"

#define SMALLHEART_GRAVITY				0.1f
#define SMALLHEART_SPEED_X				0.08f
#define SMALLHEART_AMPLITUDE_VERTICAL	30.0f	
#define SMALLHEART_MANA_GIVEN			1

#define SMALLHEART_DISPLAY_DURATION		4500
#define SMALLHEART_DELAY			600

class SmallHeart : public Item
{
	float tempX;
public:
	SmallHeart(float posX, float posY);
	~SmallHeart();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
};

