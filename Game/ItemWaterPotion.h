#pragma once
#include "Item.h"

#define ITEMWATERPOTION_GRAVITY				0.03f

#define ITEMWATERPOTION_DISPLAY_DURATION	4500
#define ITEMWATERPOTION_DELAY				600

class ItemWaterPotion : public Item
{
public:
	ItemWaterPotion(float posX, float posY);
	~ItemWaterPotion();
};

