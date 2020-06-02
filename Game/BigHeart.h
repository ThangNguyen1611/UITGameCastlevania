#pragma once
#include "Item.h"

#define BIGHEART_GRAVITY			0.03f

#define BIGHEART_DISPLAY_DURATION	4500
#define BIGHEART_DELAY				600

class BigHeart : public Item
{
public:
	BigHeart(float posX, float posY);
	~BigHeart();
};

