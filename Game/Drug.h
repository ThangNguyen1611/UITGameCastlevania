#pragma once
#include "Item.h"

#define DRUG_GRAVITY			0.03f

#define DRUG_TIMEDISPLAYMAX		4500
#define DRUG_TIMEDELAYMAX		600

class Drug : public Item
{
public:
	Drug(float posX, float posY);
	~Drug();
};

