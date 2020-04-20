#pragma once
#include "Item.h"

#define ITEMDAGGER_GRAVITY			0.03f

#define ITEMDAGGER_TIMEDISPLAYMAX		4500
#define ITEMDAGGER_TIMEDELAYMAX			300

class ItemDagger : public Item
{
public:
	ItemDagger(float posX, float posY);
	~ItemDagger();
};

