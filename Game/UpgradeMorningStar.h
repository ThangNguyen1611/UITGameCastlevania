#pragma once
#include "Item.h"

#define UPGRADEMS_GRAVITY				0.03f

#define UPGRADEMS_TIMEDISPLAYMAX		4500

class UpgradeMorningStar : public Item
{
public:
	UpgradeMorningStar(float posX, float posY);
	~UpgradeMorningStar();
};
