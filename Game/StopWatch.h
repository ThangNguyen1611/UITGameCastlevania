#pragma once
#include "Weapon.h"

#define STOPWATCH_MANA_COST		5

class StopWatch : public Weapon
{
public:
	StopWatch();
	~StopWatch();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom); //need ?
};

