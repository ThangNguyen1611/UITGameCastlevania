#pragma once
#include "Item.h"

#define CHICKEN_GRAVITY				0.03f

#define CHICKEN_TIMEDISPLAYMAX		4500

class YummiChickenLeg : public Item
{
public:
	YummiChickenLeg(float posX, float posY);
	~YummiChickenLeg();
};

