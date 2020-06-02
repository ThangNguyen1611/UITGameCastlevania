#pragma once
#include "Item.h"

#define ITEMSTOPWATCH_GRAVITY				0.03f

#define ITEMSTOPWATCH_DISPLAY_DURATION		4500
#define ITEMSTOPWATCH_DELAY					600

class ItemStopWatch : public Item
{
public:
	ItemStopWatch(float posX, float posY);
	~ItemStopWatch();
};

