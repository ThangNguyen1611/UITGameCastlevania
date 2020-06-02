#pragma once
#include "Effect.h"

#define SCORE_100_ANI					0
#define SCORE_400_ANI					1
#define SCORE_700_ANI					2
#define SCORE_1000_ANI					3

#define SCORE_DISPLAY_DURATION			600

class Score : public Effect
{
	int type;
public:
	Score(float posX, float posY, EntityType scoreType);
	~Score();

	void Update(DWORD dt);
	void Render();
	void SetType(EntityType type);
};

