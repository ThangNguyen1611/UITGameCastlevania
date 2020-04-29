#pragma once
#include "Item.h"

#define ITEMAXE_GRAVITY				0.03f

#define ITEMAXE_TIMEDISPLAYMAX		4500
#define ITEMAXE_TIMEDELAYMAX		600

class ItemAxe : public Item
{
public:
	ItemAxe(float posX, float posY);
	~ItemAxe();
};

