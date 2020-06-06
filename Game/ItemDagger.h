#pragma once
#include "Item.h"

#define ITEMDAGGER_DISPLAY_DURATION		4500
#define ITEMDAGGER_DELAY				600

class ItemDagger : public Item
{
public:
	ItemDagger(float posX, float posY);
	~ItemDagger();
};

