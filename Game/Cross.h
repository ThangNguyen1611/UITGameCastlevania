#pragma once
#include "Item.h"

#define CROSS_GRAVITY				0.03f

#define CROSS_TIMEDISPLAYMAX		4500
#define CROSS_TIMEDELAYMAX			600

class Cross : public Item
{
public:
	Cross(float posX, float posY);
	~Cross();
};
