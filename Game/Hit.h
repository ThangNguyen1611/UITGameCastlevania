#pragma once
#include "Effect.h"

#define SPARKLE_DISPLAY_DURATION		600

class Hit : public Effect
{
public:
	Hit(float posX, float posY);
	~Hit();

	void Update(DWORD dt);
};

