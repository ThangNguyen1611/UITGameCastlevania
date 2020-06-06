#pragma once
#include "Item.h"

#define ITEMWATERPOTION_DISPLAY_DURATION	4500
#define ITEMWATERPOTION_DELAY				600

class ItemWaterPotion : public Item
{
public:
	ItemWaterPotion(float posX, float posY);
	~ItemWaterPotion();
};

