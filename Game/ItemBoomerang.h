#pragma once
#include "Item.h"

#define ITEMBOOMERANG_GRAVITY			0.03f

#define ITEMBOOMERANG_TIMEDISPLAYMAX		4500
#define ITEMBOOMERANG_TIMEDELAYMAX			300

class ItemBoomerang : public Item
{
public:
	ItemBoomerang(float posX, float posY);
	~ItemBoomerang();
};

