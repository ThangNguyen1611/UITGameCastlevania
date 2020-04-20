#pragma once
#include "Effect.h"

#define SCORE_TIME_OF_PER_EFFECT			600		

#define SCORE_100_ANI_BEGIN					0
#define SCORE_100_ANI_END					1
#define SCORE_400_ANI_BEGIN					2
#define SCORE_400_ANI_END					3
#define SCORE_700_ANI_BEGIN					4
#define SCORE_700_ANI_END					5
#define SCORE_1000_ANI_BEGIN				6
#define SCORE_1000_ANI_END					7

class Score : public Effect
{
	EntityType scoreType;
public:
	Score(float posX, float posY, EntityType scoreType);
	~Score();

	void Update(DWORD dt);
};

