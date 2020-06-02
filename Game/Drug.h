#pragma once
#include "Item.h"

#define DRUG_GRAVITY			0.03f

#define DRUG_DISPLAY_DURATION	4500
#define DRUG_DELAY				600

class Drug : public Item
{
public:
	Drug(float posX, float posY);
	~Drug();
};

