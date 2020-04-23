#pragma once
#include "Effect.h"

#define SCORE_100_ANI					0
#define SCORE_400_ANI					2
#define SCORE_700_ANI					4
#define SCORE_1000_ANI					6

#define SCORE_DISPLAY					600

class Score : public Effect
{
	EntityType scoreType;
public:
	Score(float posX, float posY, EntityType scoreType);
	~Score();

	void Update(DWORD dt);
	void Render();
};

