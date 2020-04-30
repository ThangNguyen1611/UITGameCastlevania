#pragma once
#include "Item.h"

#define ITEMWATERPOTION_GRAVITY				0.03f

#define ITEMWATERPOTION_TIMEDISPLAYMAX		4500
#define ITEMWATERPOTION_TIMEDELAYMAX		600

class ItemWaterPotion : public Item
{
public:
	ItemWaterPotion(float posX, float posY);
	~ItemWaterPotion();
};

