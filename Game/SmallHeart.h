#pragma once
#include "Item.h"

#define SMALLHEART_GRAVITY				0.003f
#define SMALLHEART_SPEED_X				0.08f
#define SMALLHEART_AMPLITUDE_VERTICAL	30.0f	

#define SMALLHEART_TIMEDISPLAYMAX		4500

class SmallHeart : public Item
{
	float tempX;
public:
	SmallHeart(float posX, float posY);
	~SmallHeart();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
};

