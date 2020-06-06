#pragma once
#include "Item.h"

#define BIGHEART_MANA_GIVEN			5

#define BIGHEART_DISPLAY_DURATION	4500
#define BIGHEART_DELAY				600

class BigHeart : public Item
{
public:
	BigHeart(float posX, float posY);
	~BigHeart();
};

