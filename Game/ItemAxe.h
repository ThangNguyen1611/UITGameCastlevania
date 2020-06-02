#pragma once
#include "Item.h"

#define ITEMAXE_GRAVITY				0.03f

#define ITEMAXE_DISPLAY_DURATION	4500
#define ITEMAXE_DELAY				600

class ItemAxe : public Item
{
public:
	ItemAxe(float posX, float posY);
	~ItemAxe();
};

