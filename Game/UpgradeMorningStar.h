#pragma once
#include "Item.h"

#define UPGRADEMS_DISPLAY_DURATION		4500
#define UPGRADEMS_DELAY					600

class UpgradeMorningStar : public Item
{
public:
	UpgradeMorningStar(float posX, float posY);
	~UpgradeMorningStar();
};
