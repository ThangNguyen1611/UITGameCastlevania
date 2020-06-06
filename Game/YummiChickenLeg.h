#pragma once
#include "Item.h"

#define CHICKEN_HP_RESTORE			4

#define CHICKEN_DISPLAY_DURATION	4500
#define CHICKEN_DELAY				600

class YummiChickenLeg : public Item
{
public:
	YummiChickenLeg(float posX, float posY);
	~YummiChickenLeg();
};

