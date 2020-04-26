#include "BigHeart.h"

BigHeart::BigHeart(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BIGHEART));
	tag = EntityType::BIGHEART;

	this->posX = posX;
	this->posY = posY;
	
	vY = BIGHEART_GRAVITY;
	displayTimer = new Timer(BIGHEART_TIMEDISPLAYMAX);
	displayTimer->Start();
	delayLimit = BIGHERAT_TIMEDELAYMAX;
}

BigHeart::~BigHeart(){}