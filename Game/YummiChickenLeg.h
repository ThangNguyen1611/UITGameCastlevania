#pragma once
#include "Item.h"

#define CHICKEN_GRAVITY				0.03f

#define CHICKEN_DISPLAY_DURATION	4500
#define CHICKEN_DELAY				600

class YummiChickenLeg : public Item
{
public:
	YummiChickenLeg(float posX, float posY);
	~YummiChickenLeg();
};

