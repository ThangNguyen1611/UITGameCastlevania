#pragma once
#include "Item.h"

#define BIGHEART_GRAVITY			0.03f

#define BIGHEART_TIMEDISPLAYMAX		4500

class BigHeart : public Item
{
public:
	BigHeart(float posX, float posY);
	~BigHeart();
};

