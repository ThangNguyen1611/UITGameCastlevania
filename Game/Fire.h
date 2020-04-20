#pragma once
#include "Effect.h"

#define FIRE_TIME_OF_PER_EFFECT			150		

#define FIRE_ANI_BEGIN					0
#define FIRE_ANI_END					3

class Fire : public Effect
{
public:
	Fire(float posX, float posY);
	~Fire();

	void Update(DWORD dt);
};

