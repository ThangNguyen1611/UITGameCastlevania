#pragma once
#include "Item.h"

#define ITEMPOKEBALL_DISPLAY_DURATION	4500
#define ITEMPOKEBALL_DELAY				600

class ItemPokeball : public Item
{
public:
	ItemPokeball(float posX, float posY);
	~ItemPokeball();
};

