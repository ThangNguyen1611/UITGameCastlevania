#pragma once
#include "Item.h"

#define ITEMBOOMERANG_DISPLAY_DURATION		4500
#define ITEMBOOMERANG_DELAY					600

class ItemBoomerang : public Item
{
public:
	ItemBoomerang(float posX, float posY);
	~ItemBoomerang();
};

