#pragma once
#include "Weapon.h"

class StopWatch : public Weapon
{
public:
	StopWatch();
	~StopWatch();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom); //need ?
};

