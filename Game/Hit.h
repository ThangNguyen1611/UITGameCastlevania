#pragma once
#include "Effect.h"

#define HIT_TIME_OF_PER_EFFECT			600		// = 4 * Fire(150)

#define HIT_ANI_BEGIN					0
#define HIT_ANI_END						1

class Hit : public Effect
{
public:
	Hit(float posX, float posY);
	~Hit();

	void Update(DWORD dt);
};

