#pragma once
#include "Effect.h"

#define FIRE_BURN_DISPLAY	600

class Fire : public Effect
{
public:
	Fire(float posX, float posY);
	~Fire();

	void Update(DWORD dt);
};

