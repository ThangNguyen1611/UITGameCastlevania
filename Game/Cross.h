#pragma once
#include "Item.h"

#define CROSS_DISPLAY_DURATION		4500
#define CROSS_DELAY					600

class Cross : public Item
{
public:
	Cross(float posX, float posY);
	~Cross();
};
